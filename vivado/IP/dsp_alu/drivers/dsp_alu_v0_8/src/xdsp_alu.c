// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
// Tool Version Limit: 2024.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xdsp_alu.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XDsp_alu_CfgInitialize(XDsp_alu *InstancePtr, XDsp_alu_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XDsp_alu_Start(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL) & 0x80;
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XDsp_alu_IsDone(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XDsp_alu_IsIdle(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XDsp_alu_IsReady(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XDsp_alu_EnableAutoRestart(XDsp_alu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XDsp_alu_DisableAutoRestart(XDsp_alu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_AP_CTRL, 0);
}

void XDsp_alu_Set_A(XDsp_alu *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_A_DATA, (u32)(Data));
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_A_DATA + 4, (u32)(Data >> 32));
}

u64 XDsp_alu_Get_A(XDsp_alu *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_A_DATA);
    Data += (u64)XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_A_DATA + 4) << 32;
    return Data;
}

void XDsp_alu_Set_B(XDsp_alu *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_B_DATA, (u32)(Data));
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_B_DATA + 4, (u32)(Data >> 32));
}

u64 XDsp_alu_Get_B(XDsp_alu *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_B_DATA);
    Data += (u64)XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_B_DATA + 4) << 32;
    return Data;
}

void XDsp_alu_Set_Y(XDsp_alu *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_Y_DATA, (u32)(Data));
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_Y_DATA + 4, (u32)(Data >> 32));
}

u64 XDsp_alu_Get_Y(XDsp_alu *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_Y_DATA);
    Data += (u64)XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_Y_DATA + 4) << 32;
    return Data;
}

void XDsp_alu_Set_Sel(XDsp_alu *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_SEL_DATA, Data);
}

u32 XDsp_alu_Get_Sel(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_SEL_DATA);
    return Data;
}

void XDsp_alu_Set_size(XDsp_alu *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XDsp_alu_Get_size(XDsp_alu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XDsp_alu_InterruptGlobalEnable(XDsp_alu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_GIE, 1);
}

void XDsp_alu_InterruptGlobalDisable(XDsp_alu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_GIE, 0);
}

void XDsp_alu_InterruptEnable(XDsp_alu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_IER);
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_IER, Register | Mask);
}

void XDsp_alu_InterruptDisable(XDsp_alu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_IER);
    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_IER, Register & (~Mask));
}

void XDsp_alu_InterruptClear(XDsp_alu *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDsp_alu_WriteReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_ISR, Mask);
}

u32 XDsp_alu_InterruptGetEnabled(XDsp_alu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_IER);
}

u32 XDsp_alu_InterruptGetStatus(XDsp_alu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDsp_alu_ReadReg(InstancePtr->Control_BaseAddress, XDSP_ALU_CONTROL_ADDR_ISR);
}

