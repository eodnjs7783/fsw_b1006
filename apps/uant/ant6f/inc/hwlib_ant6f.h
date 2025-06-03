/*******************************************************************************************
 * @file hwlib_ant6f.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief ANT6F control library.
 * 
 * @version 1.0
 * 
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _HWLIB_ANT6F_H_
#define _HWLIB_ANT6F_H_


#include "hwlib.h"
#include "vgssb_ant6f.h"



int32 ANT6F_GetInternalTemperature(int16* temperature);

int32 ANT6F_BurnChannel(uint8 channel, uint8 duration);

int32 ANT6F_StopBurnAllChannels(void);

int32 ANT6F_GetReleaseStatus(vgssb_ant6f_release_status_t* channelStatus);

int32 ANT6F_GetBackupStatus(vgssb_backup_status_t* backupStatus);

int32 ANT6F_GetBoardStatus(vgssb_board_status_t* boardStatus);

int32 ANT6F_GetBackupSettings(vgssb_backup_settings_t* settings);

int32 ANT6F_SetBackupSettings(vgssb_backup_settings_t settings);

int32 ANT6F_ResetCount(void);

int32 ANT6F_RequestTelemetry(void);


#endif