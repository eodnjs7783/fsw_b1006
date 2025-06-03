/*******************************************************************************************
 * @file vgssb_ant6f.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief ANT6F datatype definition.
 * 
 * @version 1.0
 * 
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _VGSSB_ANT6F_H_
#define _VGSSB_ANT6F_H_

#include "vgssb.h"

#define VGSSB_ANT6F_MAGIC_SOFT_RESET        0x5A
#define VGSSB_ANT6F_MAGIC_DATA_VALIDATION   0x33


typedef struct __attribute__((packed)) {
    uint8 ch0state;
    uint8 ch0burnTimeLeft;
    uint8 ch0status;
    uint8 ch1state;
    uint8 ch1burnTimeLeft;
    uint8 ch1status;
    uint8 ch0burnTries;
    uint8 ch1burnTries;
} vgssb_ant6f_release_status_t;


#endif
