// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
// Tool Version Limit: 2024.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XDSP_ALU_H
#define XDSP_ALU_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xdsp_alu_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XDsp_alu_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XDsp_alu;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XDsp_alu_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XDsp_alu_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XDsp_alu_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XDsp_alu_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XDsp_alu_Initialize(XDsp_alu *InstancePtr, UINTPTR BaseAddress);
XDsp_alu_Config* XDsp_alu_LookupConfig(UINTPTR BaseAddress);
#else
int XDsp_alu_Initialize(XDsp_alu *InstancePtr, u16 DeviceId);
XDsp_alu_Config* XDsp_alu_LookupConfig(u16 DeviceId);
#endif
int XDsp_alu_CfgInitialize(XDsp_alu *InstancePtr, XDsp_alu_Config *ConfigPtr);
#else
int XDsp_alu_Initialize(XDsp_alu *InstancePtr, const char* InstanceName);
int XDsp_alu_Release(XDsp_alu *InstancePtr);
#endif

void XDsp_alu_Start(XDsp_alu *InstancePtr);
u32 XDsp_alu_IsDone(XDsp_alu *InstancePtr);
u32 XDsp_alu_IsIdle(XDsp_alu *InstancePtr);
u32 XDsp_alu_IsReady(XDsp_alu *InstancePtr);
void XDsp_alu_EnableAutoRestart(XDsp_alu *InstancePtr);
void XDsp_alu_DisableAutoRestart(XDsp_alu *InstancePtr);

void XDsp_alu_Set_A(XDsp_alu *InstancePtr, u64 Data);
u64 XDsp_alu_Get_A(XDsp_alu *InstancePtr);
void XDsp_alu_Set_B(XDsp_alu *InstancePtr, u64 Data);
u64 XDsp_alu_Get_B(XDsp_alu *InstancePtr);
void XDsp_alu_Set_Y(XDsp_alu *InstancePtr, u64 Data);
u64 XDsp_alu_Get_Y(XDsp_alu *InstancePtr);
void XDsp_alu_Set_Sel(XDsp_alu *InstancePtr, u32 Data);
u32 XDsp_alu_Get_Sel(XDsp_alu *InstancePtr);
void XDsp_alu_Set_size(XDsp_alu *InstancePtr, u32 Data);
u32 XDsp_alu_Get_size(XDsp_alu *InstancePtr);

void XDsp_alu_InterruptGlobalEnable(XDsp_alu *InstancePtr);
void XDsp_alu_InterruptGlobalDisable(XDsp_alu *InstancePtr);
void XDsp_alu_InterruptEnable(XDsp_alu *InstancePtr, u32 Mask);
void XDsp_alu_InterruptDisable(XDsp_alu *InstancePtr, u32 Mask);
void XDsp_alu_InterruptClear(XDsp_alu *InstancePtr, u32 Mask);
u32 XDsp_alu_InterruptGetEnabled(XDsp_alu *InstancePtr);
u32 XDsp_alu_InterruptGetStatus(XDsp_alu *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
