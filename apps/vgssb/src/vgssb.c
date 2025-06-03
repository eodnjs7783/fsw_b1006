/*******************************************************************************************
 * @file vgssb.c
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief GSSB functions.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#include "vgssb_dev.h"
#include "vgssb_sub.h"
#include "vgssb_cmd_id.h"

#include <csp/csp_endian.h>

#include "io_lib.h"



void VGSSB_BusScan(int32 device, uint8 startAddr, uint8 stopAddr, uint16 timeout, int8 devices[127]) {

    uint8 addr;
    uint8 tx[1];
    uint8 rx[4];

    if (!devices) return;

    tx[0] = GSSB_CMD_GET_UUID;
    stopAddr = stopAddr > 127 ? 127 : stopAddr;

    for (addr = startAddr; addr <= stopAddr; addr++) {
        devices[addr] = (bool) I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);
        devices[addr] = !devices[addr];
    }

}


int32 VGSSB_SoftReset(int32 device, uint8 addr, uint32 timeout) {

    uint8 tx[2];
    uint8 rx[1];

    tx[0] = GSSB_CMD_SOFT_RESET;
    tx[1] = 0x5A;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));

}

int32 VGSSB_GetVersion(int32 device, uint8 addr, uint32 timeout, uint8* version, uint8 version_len) {

    uint8 tx[1];
    tx[0] = GSSB_CMD_GET_ID;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), version, version_len, 0, timeout));

}

int32 VGSSB_GetUUID(int32 device, uint8 addr, uint32 timeout, uint32* uuid) {

    int32 status;
    uint8 tx[1];

    tx[0] = GSSB_CMD_GET_UUID;

    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), uuid, sizeof(uuid), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        *uuid = csp_betoh32(*uuid);
    }

    return HWLIB_StatusIO(status);

}


int32 VGSSB_GetModel(int32 device, uint8 addr, uint32 timeout, uint8* model) {

    int32 status;
    uint8 tx[1];
    uint8 rx[2];

    tx[0] = GSSB_CMD_GET_MODEL;

    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);
    *model = rx[1];

    return HWLIB_StatusIO(status);

}


int32 VGSSB_SetI2CAddr(int32 device, uint8 addr, uint16 timeout, uint8 newAddr) {

    uint8 tx[3];
    uint8 rx[1];

    tx[0] = GSSB_CMD_SET_I2C_ADDR;
    tx[1] = newAddr;
    tx[2] = 0;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));

}

int32 VGSSB_CommitNewI2CAddr(int32 device, uint8 addr, uint16 timeout, uint8 newAddr) {

    uint8 tx[2];
    uint8 rx[1];

    tx[0] = GSSB_CMD_COMMIT_I2C_ADDR;
    tx[1] = 0x33;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));

}


int32 VGSSB_CommonGetSunVoltage(int32 device, uint8 addr, uint32 timeout, uint16* voltage) {

    int32 status;
    uint8 tx[1];
    uint8 rx[4];

    tx[0] = GSSB_CMD_COMMON_GET_SUNSENSOR_VOLTAGE;
    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        *voltage = rx[2] | (rx[3] << 8);
    }

    return HWLIB_StatusIO(status);

}


int32 VGSSB_CommonResetCount(int32 device, uint8 addr, uint32 timeout) {

    uint8 tx[1];
    uint8 rx[1];

    tx[0] = GSSB_CMD_COMMON_RESET_COUNT;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));
 
}


int32 VGSSB_CommonStopBurn(int32 device, uint8 addr, uint32 timeout) {

    uint8 tx[1];
    uint8 rx[1];

    tx[0] = GSSB_CMD_COMMON_STOP_BURN;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));
 
}


int32 VGSSB_CommonGetInternalTemperature(int32 device, uint8 addr, uint32 timeout, int16* tempOut) {

    int32 status;
    uint8 tx[1];
    uint8 rx[4];

    tx[0] = GSSB_CMD_COMMON_GET_INTERNAL_TEMP;
    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        *tempOut = (int16) (rx[2] | (rx[3] << 8));
    }

    return HWLIB_StatusIO(status);

}


int32 VGSSB_CommonSetBackupSettings(int32 device, uint8 addr, uint32 timeout, vgssb_backup_settings_t settings) {
    
    uint8 tx[7];
    uint8 rx[1];

    tx[0] = GSSB_CMD_COMMON_SET_BACKUP_SETTINGS;
    tx[1] = 0;
    tx[2] = settings.minutes;
    tx[3] = settings.minutes >> 8;
    tx[4] = (bool) settings.backup_active;
    tx[5] = settings.max_burn_duration;
    tx[6] = 0x33;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));


}

int32 VGSSB_CommonGetBackupSettings(int32 device, uint8 addr, uint32 timeout, vgssb_backup_settings_t* settings) {

    int32 status;
    uint8 tx[1];
    uint8 rx[5];

    tx[0] = GSSB_CMD_COMMON_GET_BACKUP_SETTINGS;
    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        settings->minutes = (rx[1] | (rx[2] << 8));
        settings->backup_active = (rx[3]);
        settings->max_burn_duration = (rx[4]);
    }

    return HWLIB_StatusIO(status);

}

int32 VGSSB_CommonBurnChannel(int32 device, uint8 addr, uint32 timeout, uint8 channel, uint8 duration) {

    uint8 tx[3];
    uint8 rx[1];

    tx[0] = GSSB_CMD_COMMON_BURN_CHANNEL;
    tx[1] = channel;
    tx[2] = duration;

    return HWLIB_StatusIO(I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout));

}


int32 VGSSB_CommonGetBackupStatus(int32 device, uint8 addr, uint32 timeout, vgssb_backup_status_t* backupStatus) {

    int32 status;
    uint8 tx[1];
    uint8 rx[5];

    tx[0] = GSSB_CMD_COMMON_GET_BACKUP_STATUS;
    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        backupStatus->state = rx[0];
        memcpy(&backupStatus->seconds_to_deploy, rx + 1, 4);
    }

    return HWLIB_StatusIO(status);

}


int32 VGSSB_CommonGetBoardStatus(int32 device, uint8 addr, uint32 timeout, vgssb_board_status_t* boardStatus) {

    int32 status;
    uint8 tx[1];
    uint8 rx[6];

    tx[0] = GSSB_CMD_COMMON_GET_BOARD_STATUS;
    status = I2C_MasterTransactionDirect(device, addr, tx, sizeof(tx), rx, sizeof(rx), 0, timeout);

    if (status == IO_LIB_SUCCESS) {
        memcpy(&boardStatus->seconds_since_boot, rx + 1, 4);
        boardStatus->reboot_count = rx[5];
    }

    return HWLIB_StatusIO(status);

}
