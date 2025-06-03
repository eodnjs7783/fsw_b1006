/*******************************************************************************************
 * @file hwlib_ant6f.c
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
#include "hwlib_ant6f.h"
#include "hwlib_ant6f_config.h"
#include "vgssb_dev.h"
#include "vgssb_sub.h"
#include "vgssb_cmd_id.h"

#include "io_lib.h"



int32 ANT6F_GetInternalTemperature(int16* temperature) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonGetInternalTemperature(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, temperature);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_BurnChannel(uint8 channel, uint8 duration) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    //status = VGSSB_CommonBurnChannel(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, channel, duration);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    {return HWLIB_SUCCESS;}
    return status;
}


int32 ANT6F_StopBurnAllChannels(void) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonStopBurn(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_GetReleaseStatus(vgssb_ant6f_release_status_t* channelStatus) {
    int32 status;
    uint8 tx[1] = {GSSB_CMD_ANT6_GET_STATUS_ALL_CHANNELS};
    uint8 rx[8];
    status = I2C_MasterTransaction(ANT6F_I2C_HANDLE, ANT6F_I2C_ADDR, tx, sizeof(tx), rx, sizeof(rx), 0, ANT6F_I2C_TIMEOUT);
    if (status == IO_LIB_SUCCESS) {
        memcpy(channelStatus, rx, sizeof(rx));
    }
    return HWLIB_StatusIO(status);
}


int32 ANT6F_GetBackupStatus(vgssb_backup_status_t* backupStatus) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonGetBackupStatus(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, backupStatus);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_GetBoardStatus(vgssb_board_status_t* boardStatus) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonGetBoardStatus(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, boardStatus);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_GetBackupSettings(vgssb_backup_settings_t* settings) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonGetBackupSettings(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, settings);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_SetBackupSettings(vgssb_backup_settings_t settings) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonSetBackupSettings(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT, settings);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_ResetCount(void) {
    int32 status;
    OS_MutSemTake(ANT6F_I2C_HANDLE->mutex);
    status = VGSSB_CommonResetCount(ANT6F_I2C_HANDLE->device, ANT6F_I2C_ADDR, ANT6F_I2C_TIMEOUT);
    OS_MutSemGive(ANT6F_I2C_HANDLE->mutex);
    return status;
}


int32 ANT6F_RequestTelemetry(void) {
    return 0;
}
