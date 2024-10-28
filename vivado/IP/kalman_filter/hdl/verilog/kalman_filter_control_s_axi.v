// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
// Tool Version Limit: 2024.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
`timescale 1ns/1ps
module kalman_filter_control_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 7,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire [31:0]                   z_k,
    input  wire [31:0]                   P_k,
    input  wire                          P_k_ap_vld,
    input  wire [31:0]                   x_hat,
    input  wire                          x_hat_ap_vld,
    output wire [31:0]                   Q,
    output wire [31:0]                   R,
    output wire [31:0]                   P_k_prev,
    output wire [31:0]                   x_hat_prev
);
//------------------------Address Info-------------------
// Protocol Used: ap_ctrl_none
//
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of z_k
//        bit 31~0 - z_k[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of P_k
//        bit 31~0 - P_k[31:0] (Read)
// 0x1c : Control signal of P_k
//        bit 0  - P_k_ap_vld (Read/COR)
//        others - reserved
// 0x28 : Data signal of x_hat
//        bit 31~0 - x_hat[31:0] (Read)
// 0x2c : Control signal of x_hat
//        bit 0  - x_hat_ap_vld (Read/COR)
//        others - reserved
// 0x38 : Data signal of Q
//        bit 31~0 - Q[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of R
//        bit 31~0 - R[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of P_k_prev
//        bit 31~0 - P_k_prev[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of x_hat_prev
//        bit 31~0 - x_hat_prev[31:0] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_Z_K_DATA_0        = 7'h10,
    ADDR_Z_K_CTRL          = 7'h14,
    ADDR_P_K_DATA_0        = 7'h18,
    ADDR_P_K_CTRL          = 7'h1c,
    ADDR_X_HAT_DATA_0      = 7'h28,
    ADDR_X_HAT_CTRL        = 7'h2c,
    ADDR_Q_DATA_0          = 7'h38,
    ADDR_Q_CTRL            = 7'h3c,
    ADDR_R_DATA_0          = 7'h40,
    ADDR_R_CTRL            = 7'h44,
    ADDR_P_K_PREV_DATA_0   = 7'h48,
    ADDR_P_K_PREV_CTRL     = 7'h4c,
    ADDR_X_HAT_PREV_DATA_0 = 7'h50,
    ADDR_X_HAT_PREV_CTRL   = 7'h54,
    WRIDLE                 = 2'd0,
    WRDATA                 = 2'd1,
    WRRESP                 = 2'd2,
    WRRESET                = 2'd3,
    RDIDLE                 = 2'd0,
    RDDATA                 = 2'd1,
    RDRESET                = 2'd2,
    ADDR_BITS                = 7;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg  [31:0]                   int_z_k = 'b0;
    reg                           int_P_k_ap_vld;
    reg  [31:0]                   int_P_k = 'b0;
    reg                           int_x_hat_ap_vld;
    reg  [31:0]                   int_x_hat = 'b0;
    reg  [31:0]                   int_Q = 'b0;
    reg  [31:0]                   int_R = 'b0;
    reg  [31:0]                   int_P_k_prev = 'b0;
    reg  [31:0]                   int_x_hat_prev = 'b0;

//------------------------Instantiation------------------


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= {AWADDR[ADDR_BITS-1:2], {2{1'b0}}};
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
            case (raddr)
                ADDR_Z_K_DATA_0: begin
                    rdata <= int_z_k[31:0];
                end
                ADDR_P_K_DATA_0: begin
                    rdata <= int_P_k[31:0];
                end
                ADDR_P_K_CTRL: begin
                    rdata[0] <= int_P_k_ap_vld;
                end
                ADDR_X_HAT_DATA_0: begin
                    rdata <= int_x_hat[31:0];
                end
                ADDR_X_HAT_CTRL: begin
                    rdata[0] <= int_x_hat_ap_vld;
                end
                ADDR_Q_DATA_0: begin
                    rdata <= int_Q[31:0];
                end
                ADDR_R_DATA_0: begin
                    rdata <= int_R[31:0];
                end
                ADDR_P_K_PREV_DATA_0: begin
                    rdata <= int_P_k_prev[31:0];
                end
                ADDR_X_HAT_PREV_DATA_0: begin
                    rdata <= int_x_hat_prev[31:0];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign z_k        = int_z_k;
assign Q          = int_Q;
assign R          = int_R;
assign P_k_prev   = int_P_k_prev;
assign x_hat_prev = int_x_hat_prev;
// int_z_k[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_z_k[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Z_K_DATA_0)
            int_z_k[31:0] <= (WDATA[31:0] & wmask) | (int_z_k[31:0] & ~wmask);
    end
end

// int_P_k
always @(posedge ACLK) begin
    if (ARESET)
        int_P_k <= 0;
    else if (ACLK_EN) begin
        if (P_k_ap_vld)
            int_P_k <= P_k;
    end
end

// int_P_k_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_P_k_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (P_k_ap_vld)
            int_P_k_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_P_K_CTRL)
            int_P_k_ap_vld <= 1'b0; // clear on read
    end
end

// int_x_hat
always @(posedge ACLK) begin
    if (ARESET)
        int_x_hat <= 0;
    else if (ACLK_EN) begin
        if (x_hat_ap_vld)
            int_x_hat <= x_hat;
    end
end

// int_x_hat_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_x_hat_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (x_hat_ap_vld)
            int_x_hat_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_X_HAT_CTRL)
            int_x_hat_ap_vld <= 1'b0; // clear on read
    end
end

// int_Q[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Q[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_Q_DATA_0)
            int_Q[31:0] <= (WDATA[31:0] & wmask) | (int_Q[31:0] & ~wmask);
    end
end

// int_R[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_R[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_R_DATA_0)
            int_R[31:0] <= (WDATA[31:0] & wmask) | (int_R[31:0] & ~wmask);
    end
end

// int_P_k_prev[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_P_k_prev[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_P_K_PREV_DATA_0)
            int_P_k_prev[31:0] <= (WDATA[31:0] & wmask) | (int_P_k_prev[31:0] & ~wmask);
    end
end

// int_x_hat_prev[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_x_hat_prev[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_X_HAT_PREV_DATA_0)
            int_x_hat_prev[31:0] <= (WDATA[31:0] & wmask) | (int_x_hat_prev[31:0] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
