/*******************************************************************************************
 * @file vgssb_cmd_id.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief GSSB command IDs.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _VGSSB_CMD_ID_H_
#define _VGSSB_CMD_ID_H_


typedef enum {
    GSSB_CMD_SUN_SAMPLE_SUNSENSOR           = 0, /* Sunsensor */
    GSSB_CMD_SUN_GET_SUNSENSOR_DATA         = 1, /* Sunsensor */
    GSSB_CMD_SUN_ADC_CONF                   = 2, /* Sunsensor */
    GSSB_CMD_SUN_ADC_SAVE_CONF              = 3, /* Sunsensor */
    GSSB_CMD_SUN_SAMPLE_TEMP                = 4, /* Sunsensor */
    GSSB_CMD_SUN_GET_TEMP                   = 5, /* Sunsensor */
    GSSB_CMD_SET_I2C_ADDR                   = 6, /* General */
    GSSB_CMD_COMMIT_I2C_ADDR                = 7, /* General */
    GSSB_CMD_GET_ID                         = 8, /* General */
    GSSB_CMD_ISTAGE_GET_RELEASE_STATUS      = 9, /* Interstage */
    GSSB_CMD_ISTAGE_GET_TEMP                = 10, /* Interstage */
    GSSB_CMD_ISTAGE_BURN                    = 11, /* Interstage */
    GSSB_CMD_COMMON_GET_SUNSENSOR_VOLTAGE   = 12, /* Interstage */
    GSSB_CMD_GET_UUID                       = 13, /* General */
    GSSB_CMD_ISTAGE_GET_BURN_SETTINGS1      = 14, /* Interstage */
    GSSB_CMD_ISTAGE_GET_BURN_SETTINGS2      = 15, /* Interstage */
    GSSB_CMD_ISTAGE_SET_BURN_SETTINGS1      = 16, /* Interstage */
    GSSB_CMD_ISTAGE_SET_BURN_SETTINGS2      = 17, /* Interstage */
    GSSB_CMD_ISTAGE_SET_BURN_SETTINGS3      = 18, /* Interstage */
    GSSB_CMD_ISTAGE_GET_BURN_COUNTERS       = 19, /* Interstage */
    GSSB_CMD_ISTAGE_SETTINGS_UNLOCK         = 20, /* Interstage */
    GSSB_CMD_ISTAGE_GET_BURN_CNT_RUNNING    = 21, /* Interstage */
    GSSB_CMD_SOFT_RESET                     = 22, /* Interstage */
    GSSB_CMD_ISTAGE_CHANGE_STATE            = 23, /* Interstage */
    GSSB_CMD_COMMON_GET_INTERNAL_TEMP       = 24, /* Common */
    GSSB_CMD_MSP_GET_OUTSIDE_TEMP           = 25, /* MSP */
    GSSB_CMD_COMMON_BURN_CHANNEL            = 26, /* Common */
    GSSB_CMD_ANT6_GET_STATUS_ALL_CHANNELS   = 27, /* ANT6 */
    GSSB_CMD_COMMON_STOP_BURN               = 28, /* Common */
    GSSB_CMD_COMMON_RESET_COUNT             = 29, /* Common */
    GSSB_CMD_COMMON_GET_BOARD_STATUS        = 30, /* Common */
    GSSB_CMD_MSP_CALIBRATE_OUTSIDE_TEMP     = 31, /* MSP */
    GSSB_CMD_GET_MODEL                      = 32, /* General */
    GSSB_CMD_AR6_SET_BACKUP_SETTINGS        = 33, /* AR6 */
    GSSB_CMD_AR6_GET_BACKUP_SETTINGS        = 34, /* AR6 */
    GSSB_CMD_COMMON_GET_BACKUP_STATUS       = 35, /* Common */
    GSSB_CMD_AR6_GET_STATUS                 = 36, /* AR6 */
    GSSB_CMD_AR6_BURN                       = 37, /* AR6 */
    GSSB_CMD_ISTAGE_RESET_BURN_CNT          = 38, /* Interstage */
    GSSB_CMD_ANT6_SET_BACKUP_SETTINGS       = 39, /* ANT6 */
    GSSB_CMD_ANT6_GET_BACKUP_SETTINGS       = 40, /* ANT6 */
    GSSB_CMD_I4_GET_STATUS_ALL_CHANNELS     = 41, /* I4 */
    GSSB_CMD_COMMON_GET_BACKUP_SETTINGS     = 42, /* Common */
    GSSB_CMD_COMMON_SET_BACKUP_SETTINGS     = 43, /* Common */
} VGSSB_CMD_ID;


#endif
