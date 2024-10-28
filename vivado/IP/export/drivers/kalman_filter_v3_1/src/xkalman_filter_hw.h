// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
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

#define XKALMAN_FILTER_CONTROL_ADDR_Z_K_DATA        0x10
#define XKALMAN_FILTER_CONTROL_BITS_Z_K_DATA        32
#define XKALMAN_FILTER_CONTROL_ADDR_P_K_DATA        0x18
#define XKALMAN_FILTER_CONTROL_BITS_P_K_DATA        32
#define XKALMAN_FILTER_CONTROL_ADDR_P_K_CTRL        0x1c
#define XKALMAN_FILTER_CONTROL_ADDR_X_HAT_DATA      0x28
#define XKALMAN_FILTER_CONTROL_BITS_X_HAT_DATA      32
#define XKALMAN_FILTER_CONTROL_ADDR_X_HAT_CTRL      0x2c
#define XKALMAN_FILTER_CONTROL_ADDR_Q_DATA          0x38
#define XKALMAN_FILTER_CONTROL_BITS_Q_DATA          32
#define XKALMAN_FILTER_CONTROL_ADDR_R_DATA          0x40
#define XKALMAN_FILTER_CONTROL_BITS_R_DATA          32
#define XKALMAN_FILTER_CONTROL_ADDR_P_K_PREV_DATA   0x48
#define XKALMAN_FILTER_CONTROL_BITS_P_K_PREV_DATA   32
#define XKALMAN_FILTER_CONTROL_ADDR_X_HAT_PREV_DATA 0x50
#define XKALMAN_FILTER_CONTROL_BITS_X_HAT_PREV_DATA 32

