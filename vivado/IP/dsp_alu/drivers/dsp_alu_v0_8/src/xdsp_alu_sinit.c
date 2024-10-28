// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
// Tool Version Limit: 2024.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xdsp_alu.h"

extern XDsp_alu_Config XDsp_alu_ConfigTable[];

#ifdef SDT
XDsp_alu_Config *XDsp_alu_LookupConfig(UINTPTR BaseAddress) {
	XDsp_alu_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XDsp_alu_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XDsp_alu_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XDsp_alu_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDsp_alu_Initialize(XDsp_alu *InstancePtr, UINTPTR BaseAddress) {
	XDsp_alu_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDsp_alu_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDsp_alu_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XDsp_alu_Config *XDsp_alu_LookupConfig(u16 DeviceId) {
	XDsp_alu_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XDSP_ALU_NUM_INSTANCES; Index++) {
		if (XDsp_alu_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XDsp_alu_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDsp_alu_Initialize(XDsp_alu *InstancePtr, u16 DeviceId) {
	XDsp_alu_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDsp_alu_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDsp_alu_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

