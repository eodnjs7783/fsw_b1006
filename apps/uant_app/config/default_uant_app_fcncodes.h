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
 * @file
 *   Specification for the UANT_APP_APP command function codes
 *
 * @note
 *   This file should be strictly limited to the command/function code (CC)
 *   macro definitions.  Other definitions such as enums, typedefs, or other
 *   macros should be placed in the msgdefs.h or msg.h files.
 */
#ifndef UANT_APP_APP_FCNCODES_H
#define UANT_APP_APP_FCNCODES_H

/************************************************************************
 * Macro Definitions
 ************************************************************************/

/*
** Sample App command codes
*/
typedef enum
{
    /* Housekeeping / common */
    UANT_APP_NOOP_CC = 0,          /* Ping */
    UANT_APP_RESET_COUNTERS_CC,    /* Zero burn & reboot counters           */
    UANT_APP_SOFT_REBOOT_CC,       /* MCU soft reset                        */

    /* Burn control */
    UANT_APP_BURN_CHANNEL_CC,      /* Args: addr, channel (0|1), seconds    */
    UANT_APP_STOP_BURN_CC,         /* Args: addr                            */

    /* Telemetry */
    UANT_APP_GET_STATUS_CC,        /* Burn + release status (gs_gssb_ant6_get_release_status) */
    UANT_APP_GET_BACKUP_STATUS_CC, /* Backup timer/state  (gs_gssb_ant6_get_backup_status)  */
    UANT_APP_GET_BOARD_STATUS_CC,  /* Uptime, reboot cnt  (gs_gssb_ant6_get_board_status)   */
    UANT_APP_GET_TEMPERATURE_CC,   /* MCU internal temp (gs_gssb_ant6_get_internal_temp)   */

    /* Backup settings */
    UANT_APP_GET_SETTINGS_CC,      /* Read  backup cfg (minutes, active, max) */
    UANT_APP_SET_SETTINGS_CC,      /* Write backup cfg                        */

   

}uant_app_cc_n;

#endif

// processgroundcommand 에서 경우를 나누기 위한 코드