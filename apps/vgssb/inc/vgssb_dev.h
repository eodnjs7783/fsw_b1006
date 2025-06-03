/*******************************************************************************************
 * @file vgssb_dev.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief Commands for all GSSB devices.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _VGSSB_DEV_H_
#define _VGSSB_DEV_H_

#include "vgssb.h"

void VGSSB_BusScan(int32 device, uint8 startAddr, uint8 stopAddr, uint16 timeout, int8 devices[127]);

int32 VGSSB_SoftReset(int32 device, uint8 addr, uint32 timeout);

int32 VGSSB_GetVersion(int32 device, uint8 addr, uint32 timeout, uint8* version, uint8 len);

int32 VGSSB_GetUUID(int32 device, uint8 addr, uint32 timeout, uint32* uuid);

int32 VGSSB_GetModel(int32 device, uint8 addr, uint32 timeout, uint8* model);

int32 VGSSB_SetI2CAddr(int32 device, uint8 addr, uint16 timeout, uint8 newAddr);

int32 VGSSB_CommitNewI2CAddr(int32 device, uint8 addr, uint16 timeout, uint8 newAddr);


#endif