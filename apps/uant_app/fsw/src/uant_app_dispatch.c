/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * \file
 *   This file contains the source code for the Sample App.
 */

/*
** Include Files:
*/
#include "uant.h" 
#include "uant_app.h"
#include "uant_app_dispatch.h"
#include "uant_app_cmds.h"
#include "uant_app_eventids.h"
#include "uant_app_msgids.h"
#include "uant_app_msg.h"
#include "cfe_msg.h"
#include <gs/gssb/gssb_ant6.h>


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Verify command packet length                                               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool UANT_APP_VerifyCmdLength(const CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
{
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(UANT_APP_CMD_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        UANT_APP_Data.ErrCounter++;
    }

    return result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* UANT ground commands                                                     */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void UANT_APP_ProcessGroundCommand(const CFE_SB_Buffer_t *SBBufPtr)
{   CFE_Status_t     status; // 내부 판단용
    CFE_MSG_FcnCode_t cc = 0;
    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &cc);
    gs_error_t   gs_st;

    switch (cc)
    {
        /* ───────── NOOP ───────── */
        case UANT_APP_NOOP_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_NoopCmd_t))) //지상에서 보내준 것과 정의한 구조가 일치하는지 검증
            {
                UANT_APP_NoopCmd((const UANT_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        /* ───────── 카운터 리셋 ───────── */
        case UANT_APP_RESET_COUNTERS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_ResetCountersCmd_t)))
            {
                UANT_APP_ResetCountersCmd((const UANT_APP_ResetCountersCmd_t *)SBBufPtr);
            }
            break;

        /* ───────── 장치 리셋 ───────── */
        case UANT_APP_RESET_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_ISIS_ResetCmd_t)))
            {
                status = ISIS_UANT_Reset();
                if (status != CFE_SUCCESS)
                {
                    CFE_EVS_SendEvent(UANT_APP_RESET_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "UANT: Reset command failed, status = 0x%08X", status);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

         /* ------------ Board Soft‑Reboot ------------ */
        case UANT_APP_SOFT_REBOOT_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_SoftRebootCmd_t)))
            {
                const UANT_APP_SoftRebootCmd_t *cmd = (const void *)SBBufPtr;
                gs_st = gs_gssb_soft_reset(cmd->Addr, UANT_I2C_TIMEOUT_MS);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_I2C_XFER_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "ANT‑6F soft‑reset failed, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;


        /* ------------ Burn / Stop ------------ */
        case UANT_APP_BURN_CHANNEL_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_BurnChannelCmd_t)))
            {
                const UANT_APP_BurnChannelCmd_t *cmd = (const void *)SBBufPtr;

                if (cmd->Channel > 1 || cmd->Duration > 60)
                {
                    CFE_EVS_SendEvent(UANT_APP_CC_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "Burn param out of range (ch=%u dur=%u)",
                                    cmd->Channel, cmd->Duration);
                    UANT_APP_Data.ErrCounter++;
                    break;
                }

                gs_st = gs_gssb_ant6_burn_channel(cmd->Addr, UANT_I2C_TIMEOUT_MS,
                                                cmd->Channel, cmd->Duration);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_BURN_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "Burn failed, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        case UANT_APP_STOP_BURN_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_StopBurnCmd_t)))
            {
                const UANT_APP_StopBurnCmd_t *cmd = (const void *)SBBufPtr;
                gs_st = gs_gssb_common_stop_burn(cmd->Addr, UANT_I2C_TIMEOUT_MS);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_STOP_BURN_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "Stop‑burn failed, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        /* ---------- BOARD‑STATUS (uptime, reboot‑cnt) ---------- */
        case UANT_APP_GET_BOARD_STATUS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_GetBoardStatusCmd_t)))
            {
                const UANT_APP_GetBoardStatusCmd_t *cmd = (const void *)SBBufPtr;
                gs_gssb_board_status_t bs;
                gs_st = gs_gssb_ant6_get_board_status(cmd->Addr, UANT_I2C_TIMEOUT_MS, &bs);

                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_GET_BOARD_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "get_board_status fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_BoardStatusTlm_t tlm;
                    CFE_MSG_Init(CFE_MSG_PTR(tlm.TlmHdr),
                                CFE_SB_ValueToMsgId(UANT_APP_BRD_TLM_MID),
                                sizeof(tlm));
                    memcpy(&tlm.Payload, &bs, sizeof(bs));
                    CFE_SB_TimeStampMsg(CFE_MSG_PTR(tlm.TlmHdr));
                    CFE_SB_TransmitMsg(CFE_MSG_PTR(tlm.TlmHdr), true);
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        /* ---------- MCU 내부 온도 ---------- */
        case UANT_APP_GET_TEMPERATURE_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_GetTemperatureCmd_t)))
            {
                const UANT_APP_GetTemperatureCmd_t *cmd = (const void *)SBBufPtr;
                int16_t temp;
                gs_st = gs_gssb_ant6_get_internal_temp(cmd->Addr, UANT_I2C_TIMEOUT_MS, &temp);

                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_GET_TEMP_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "get_internal_temp fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_TempTlm_t tlm;
                    CFE_MSG_Init(CFE_MSG_PTR(tlm.TlmHdr),
                                CFE_SB_ValueToMsgId(UANT_APP_TEMP_TLM_MID),
                                sizeof(tlm));
                    tlm.Payload.Temperature = temp;
                    CFE_SB_TimeStampMsg(CFE_MSG_PTR(tlm.TlmHdr));
                    CFE_SB_TransmitMsg(CFE_MSG_PTR(tlm.TlmHdr), true);
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;


       /* ------------ Telemetry pulls ------------ */
        case UANT_APP_GET_STATUS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_GetStatusCmd_t)))
            {
                const UANT_APP_GetStatusCmd_t *cmd = (const void *)SBBufPtr;
                gs_gssb_ant6_release_status_t st;
                gs_st = gs_gssb_ant6_get_release_status(cmd->Addr, UANT_I2C_TIMEOUT_MS, &st);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_GET_STATUS_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "get_release_status fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_RlsStatusTlm_t tlm;
                    CFE_MSG_Init(CFE_MSG_PTR(tlm.TlmHdr),
                                CFE_SB_ValueToMsgId(UANT_APP_RLS_TLM_MID),
                                sizeof(tlm));
                    memcpy(&tlm.Payload, &st, sizeof(st));
                    CFE_SB_TimeStampMsg(CFE_MSG_PTR(tlm.TlmHdr));
                    CFE_SB_TransmitMsg(CFE_MSG_PTR(tlm.TlmHdr), true);
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        case UANT_APP_GET_BACKUP_STATUS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_GetBackupStatusCmd_t)))
            {
                const UANT_APP_GetBackupStatusCmd_t *cmd = (const void *)SBBufPtr;
                gs_gssb_backup_status_t bs;
                gs_st = gs_gssb_ant6_get_backup_status(cmd->Addr, UANT_I2C_TIMEOUT_MS, &bs);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_GET_BACKUP_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "get_backup_status fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_BackupStatusTlm_t tlm;
                    CFE_MSG_Init(CFE_MSG_PTR(tlm.TlmHdr),
                                CFE_SB_ValueToMsgId(UANT_APP_BKP_TLM_MID),
                                sizeof(tlm));
                    memcpy(&tlm.Payload, &bs, sizeof(bs));
                    CFE_SB_TimeStampMsg(CFE_MSG_PTR(tlm.TlmHdr));
                    CFE_SB_TransmitMsg(CFE_MSG_PTR(tlm.TlmHdr), true);
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;
        
        /* ---------- 백업‑설정 READ ---------- */
        case UANT_APP_GET_SETTINGS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_GetSettingsCmd_t)))
            {
                const UANT_APP_GetSettingsCmd_t *cmd = (const void *)SBBufPtr;
                gs_gssb_backup_settings_t cfg;
                gs_st = gs_gssb_ant6_get_backup_settings(cmd->Addr, UANT_I2C_TIMEOUT_MS, &cfg);

                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_GET_SETTINGS_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "get_backup_settings fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_SettingsTlm_t tlm;
                    CFE_MSG_Init(CFE_MSG_PTR(tlm.TlmHdr),
                                CFE_SB_ValueToMsgId(UANT_APP_CFG_TLM_MID),
                                sizeof(tlm));
                    tlm.Payload.MinutesUntilDeploy = cfg.minutes;
                    tlm.Payload.BackupActive       = cfg.backup_active;
                    tlm.Payload.MaxBurnDuration    = cfg.max_burn_duration;
                    CFE_SB_TimeStampMsg(CFE_MSG_PTR(tlm.TlmHdr));
                    CFE_SB_TransmitMsg(CFE_MSG_PTR(tlm.TlmHdr), true);
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        /* ---------- 백업‑설정 WRITE ---------- */
        case UANT_APP_SET_SETTINGS_CC:
            if (UANT_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(UANT_APP_SetSettingsCmd_t)))
            {
                const UANT_APP_SetSettingsCmd_t *cmd = (const void *)SBBufPtr;
                gs_gssb_backup_settings_t cfg = {
                    .minutes           = cmd->MinutesUntilDeploy,
                    .backup_active     = cmd->BackupActive,
                    .max_burn_duration = cmd->MaxBurnDuration
                };

                /* 범위 검사 */
                if (cfg.minutes > 5000 || cfg.max_burn_duration > 60 || cfg.backup_active > 1)
                {
                    CFE_EVS_SendEvent(UANT_APP_SET_SETTINGS_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "backup_cfg param out of range");
                    UANT_APP_Data.ErrCounter++;
                    break;
                }

                gs_st = gs_gssb_ant6_set_backup_settings(cmd->Addr, UANT_I2C_TIMEOUT_MS, cfg);
                if (gs_st != GS_OK)
                {
                    CFE_EVS_SendEvent(UANT_APP_SET_SETTINGS_ERR_EID, CFE_EVS_EventType_ERROR,
                                    "set_backup_settings fail, gs_err=0x%02X", gs_st);
                    UANT_APP_Data.ErrCounter++;
                }
                else
                {
                    UANT_APP_Data.CmdCounter++;
                }
            }
            break;

        default:
            CFE_EVS_SendEvent(UANT_APP_CC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Invalid ground command code: CC = %d", CommandCode);
            break;
    }

   
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the UANT    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void UANT_APP_TaskPipe(const CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case UANT_APP_CMD_MID:
            UANT_APP_ProcessGroundCommand(SBBufPtr);
            break;
        //sch 추가?
        case UANT_APP_SEND_HK_MID:
            UANT_APP_SendHkCmd((const UANT_APP_SendHkCmd_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(UANT_APP_MID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "UANT: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }
}
