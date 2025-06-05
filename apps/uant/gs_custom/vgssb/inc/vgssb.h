/*******************************************************************************************
 * @file vgssb.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief GSSB common datatypes.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _VGSSB_H_
#define _VGSSB_H_


/* 
 * The GomSpace GSSB (GomSpace Sensor Bus) driver implementation is a total catastrophe
 * (compile-time fixed devices, complicated driver entries, deprecated gs services, etc.),
 * which is why this ported layer is introduced ("VGSSB" as in VISION GSSB).
 */


#include "hwlib.h"


typedef struct __attribute__((__packed__)) {
    /**
       State of backup deployment (0 = not active/finished successful, 1 = active and counting, 2 = finished unsuccessful)
     */
    uint8_t state;
    /**
       Time to backup deploy [s]
     */
    uint32_t seconds_to_deploy;
} vgssb_backup_status_t;


typedef struct __attribute__((__packed__)) {
    /**
       Time since last reboot [s]
     */
    uint32_t seconds_since_boot;
    /**
       Number of reboots
     */
    uint8_t reboot_count;
} vgssb_board_status_t;


typedef struct __attribute__((__packed__)) {
    /**
       Minutes until deployment
     */
    uint16_t minutes;
    /**
       Backup deployment activation (1 = active, 0 = not active)
     */
    uint8_t backup_active;
    /**
       Maximum burn duration for both backup burn and ordinary burns
     */
    uint8_t max_burn_duration;
} vgssb_backup_settings_t;


#endif
