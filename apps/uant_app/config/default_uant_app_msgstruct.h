/************************************************************************
 * UANT (GomSpace ANT‑6F) ‑ cFS Application
 *
 * Message Structure Definitions
 ************************************************************************/

#ifndef UANT_APP_MSGSTRUCT_H
#define UANT_APP_MSGSTRUCT_H

/************************************************************************
 * Includes
 ************************************************************************/
#include <stdint.h>

#include "cfe_msg_hdr.h"
#include "uant_app_msgdefs.h"      /* 기능‑코드, 길이 매크로 등 */
#include "uant_app_mission_cfg.h"  /* 미션별 상수 */

/************************************************************************
 *  Command Messages
 *
 *  NOTE
 *  —— All commands that act on the ANT‑6F board carry the I²C address
 *     as the **first** payload byte (Addr).  Multi‑byte numerical
 *     fields are little‑endian by cFS 규약.
 ************************************************************************/

/* 0‑argument commands */
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
} UANT_APP_NoopCmd_t;              /* FC = UANT_APP_NOOP_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
} UANT_APP_ResetCountersCmd_t;     /* FC = UANT_APP_RESET_COUNTERS_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
} UANT_APP_SoftRebootCmd_t;        /* FC = UANT_APP_SOFT_REBOOT_CC */

/* Burn one channel for N seconds
   Args: Addr, Channel(0|1), Duration(0‑60 s) */
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
    uint8_t                 Channel;
    uint8_t                 Duration;
} UANT_APP_BurnChannelCmd_t;       /* FC = UANT_APP_BURN_CHANNEL_CC */

/* Stop any on‑going burn on the board
   Args: Addr */
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_StopBurnCmd_t;          /* FC = UANT_APP_STOP_BURN_CC */

/* Telemetry‑pull commands (all 1‑byte Addr argument) */
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_GetStatusCmd_t;         /* FC = UANT_APP_GET_STATUS_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_GetBackupStatusCmd_t;   /* FC = UANT_APP_GET_BACKUP_STATUS_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_GetBoardStatusCmd_t;    /* FC = UANT_APP_GET_BOARD_STATUS_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_GetTemperatureCmd_t;    /* FC = UANT_APP_GET_TEMPERATURE_CC */

/* Backup‑deploy settings (read / write) */
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
} UANT_APP_GetSettingsCmd_t;       /* FC = UANT_APP_GET_SETTINGS_CC */

typedef struct
{
    CFE_MSG_CommandHeader_t CmdHdr;
    uint8_t                 Addr;
    uint16_t                MinutesUntilDeploy;   /* 0‑5000 min */
    uint8_t                 BackupActive;         /* 0|1 */
    uint8_t                 MaxBurnDuration;      /* 0‑127 s */
} UANT_APP_SetSettingsCmd_t;       /* FC = UANT_APP_SET_SETTINGS_CC */

/************************************************************************
 *  Telemetry Messages
 ************************************************************************/

/*---------------- Housekeeping ----------------*/
typedef struct
{
    uint8_t  CmdCounter;     /* accepted */
    uint8_t  ErrCounter;     /* rejected */
} UANT_APP_HkTlm_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_HkTlm_Payload_t  Payload;
} UANT_APP_HkTlm_t;

/*---------------- Release / Burn status ----------------
   Maps 1‑to‑1 to gs_gssb_ant6_get_release_status() payload */
typedef struct
{
    uint8_t Ch0State;        /* 0 idle / 1 burning              */
    uint8_t Ch0TimeLeft;     /* seconds                         */
    uint8_t Ch0Released;     /* 0 not ‑ 1 yes                   */
    uint8_t Ch1State;
    uint8_t Ch1TimeLeft;
    uint8_t Ch1Released;
    uint8_t Ch0Tries;        /* burn attempts                   */
    uint8_t Ch1Tries;
} UANT_APP_RlsStatus_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_RlsStatus_Payload_t Payload;
} UANT_APP_RlsStatusTlm_t;

/*---------------- Backup‑timer status ---------------
   gs_gssb_ant6_get_backup_status() */
typedef struct
{
    uint8_t  State;              /* 0‑4 per ANT‑6F spec */
    uint32_t SecondsToDeploy;
} UANT_APP_BackupStatus_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_BackupStatus_Payload_t Payload;
} UANT_APP_BackupStatusTlm_t;

/*---------------- Board (MCU) status ----------------*/
typedef struct
{
    uint32_t SecondsSinceBoot;
    uint8_t  RebootCount;
} UANT_APP_BoardStatus_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_BoardStatus_Payload_t Payload;
} UANT_APP_BoardStatusTlm_t;

/*---------------- Temperature -----------------------*/
typedef struct
{
    int16_t  Temperature; /* °C × 1 (LM75 style) */
} UANT_APP_Temp_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_Temp_Payload_t   Payload;
} UANT_APP_TempTlm_t;

/*---------------- Backup‑settings readback ----------*/
typedef struct
{
    uint16_t MinutesUntilDeploy;
    uint8_t  BackupActive;
    uint8_t  MaxBurnDuration;
} UANT_APP_Settings_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t TlmHdr;
    UANT_APP_Settings_Payload_t Payload;
} UANT_APP_SettingsTlm_t;

#endif /* UANT_APP_MSGSTRUCT_H */
