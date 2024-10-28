// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XKALMAN_FILTER_H
#define XKALMAN_FILTER_H

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
#include "xkalman_filter_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XKalman_filter_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XKalman_filter;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XKalman_filter_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XKalman_filter_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XKalman_filter_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XKalman_filter_ReadReg(BaseAddress, RegOffset) \
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
int XKalman_filter_Initialize(XKalman_filter *InstancePtr, u16 DeviceId);
XKalman_filter_Config* XKalman_filter_LookupConfig(u16 DeviceId);
int XKalman_filter_CfgInitialize(XKalman_filter *InstancePtr, XKalman_filter_Config *ConfigPtr);
#else
int XKalman_filter_Initialize(XKalman_filter *InstancePtr, const char* InstanceName);
int XKalman_filter_Release(XKalman_filter *InstancePtr);
#endif


void XKalman_filter_Set_z_k(XKalman_filter *InstancePtr, u32 Data);
u32 XKalman_filter_Get_z_k(XKalman_filter *InstancePtr);
u32 XKalman_filter_Get_P_k(XKalman_filter *InstancePtr);
u32 XKalman_filter_Get_P_k_vld(XKalman_filter *InstancePtr);
u32 XKalman_filter_Get_x_hat(XKalman_filter *InstancePtr);
u32 XKalman_filter_Get_x_hat_vld(XKalman_filter *InstancePtr);
void XKalman_filter_Set_Q(XKalman_filter *InstancePtr, u32 Data);
u32 XKalman_filter_Get_Q(XKalman_filter *InstancePtr);
void XKalman_filter_Set_R(XKalman_filter *InstancePtr, u32 Data);
u32 XKalman_filter_Get_R(XKalman_filter *InstancePtr);
void XKalman_filter_Set_P_k_prev(XKalman_filter *InstancePtr, u32 Data);
u32 XKalman_filter_Get_P_k_prev(XKalman_filter *InstancePtr);
void XKalman_filter_Set_x_hat_prev(XKalman_filter *InstancePtr, u32 Data);
u32 XKalman_filter_Get_x_hat_prev(XKalman_filter *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
