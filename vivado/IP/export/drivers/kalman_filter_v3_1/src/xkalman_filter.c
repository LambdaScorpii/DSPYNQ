// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xkalman_filter.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XKalman_filter_CfgInitialize(XKalman_filter *InstancePtr, XKalman_filter_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XKalman_filter_Set_z_k(XKalman_filter *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKalman_filter_WriteReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_Z_K_DATA, Data);
}

u32 XKalman_filter_Get_z_k(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_Z_K_DATA);
    return Data;
}

u32 XKalman_filter_Get_P_k(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_P_K_DATA);
    return Data;
}

u32 XKalman_filter_Get_P_k_vld(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_P_K_CTRL);
    return Data & 0x1;
}

u32 XKalman_filter_Get_x_hat(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_X_HAT_DATA);
    return Data;
}

u32 XKalman_filter_Get_x_hat_vld(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_X_HAT_CTRL);
    return Data & 0x1;
}

void XKalman_filter_Set_Q(XKalman_filter *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKalman_filter_WriteReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_Q_DATA, Data);
}

u32 XKalman_filter_Get_Q(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_Q_DATA);
    return Data;
}

void XKalman_filter_Set_R(XKalman_filter *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKalman_filter_WriteReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_R_DATA, Data);
}

u32 XKalman_filter_Get_R(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_R_DATA);
    return Data;
}

void XKalman_filter_Set_P_k_prev(XKalman_filter *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKalman_filter_WriteReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_P_K_PREV_DATA, Data);
}

u32 XKalman_filter_Get_P_k_prev(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_P_K_PREV_DATA);
    return Data;
}

void XKalman_filter_Set_x_hat_prev(XKalman_filter *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKalman_filter_WriteReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_X_HAT_PREV_DATA, Data);
}

u32 XKalman_filter_Get_x_hat_prev(XKalman_filter *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKalman_filter_ReadReg(InstancePtr->Control_BaseAddress, XKALMAN_FILTER_CONTROL_ADDR_X_HAT_PREV_DATA);
    return Data;
}

