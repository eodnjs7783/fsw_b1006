/*******************************************************************************************
 * @file vgssb_sub.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief Commands for a subset of the GSSB devices.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _VGSSB_SUB_H_
#define _VGSSB_SUB_H_


#include "vgssb.h"


int32 VGSSB_CommonGetSunVoltage(int32 device, uint8 addr, uint32 timeout, uint16* voltage);

int32 VGSSB_CommonResetCount(int32 device, uint8 addr, uint32 timeout);

int32 VGSSB_CommonStopBurn(int32 device, uint8 addr, uint32 timeout);

int32 VGSSB_CommonGetInternalTemperature(int32 device, uint8 addr, uint32 timeout, int16* tempOut);

int32 VGSSB_CommonSetBackupSettings(int32 device, uint8 addr, uint32 timeout, vgssb_backup_settings_t settings);

int32 VGSSB_CommonGetBackupSettings(int32 device, uint8 addr, uint32 timeout, vgssb_backup_settings_t* settings);

int32 VGSSB_CommonBurnChannel(int32 device, uint8 addr, uint32 timeout, uint8 channel, uint8 duration);

int32 VGSSB_CommonGetBackupStatus(int32 device, uint8 addr, uint32 timeout, vgssb_backup_status_t* backupStatus);

int32 VGSSB_CommonGetBoardStatus(int32 device, uint8 addr, uint32 timeout, vgssb_board_status_t* boardStatus);


#endif
