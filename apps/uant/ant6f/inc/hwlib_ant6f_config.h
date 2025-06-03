/*******************************************************************************************
 * @file hwlib_ant6f_config.h
 * 
 * @author Han-Gyeol Ryu (morimn21@gmail.com)
 * 
 * @brief Platform configurations for the ANT6F hardware.
 * 
 * @version 1.0
 * 
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2021 Astrodynamics & Control Lab. Yonsei Univ.
 * 
 ******************************************************************************************/
#ifndef _HWLIB_ANT6F_CONFIG_H_
#define _HWLIB_ANT6F_CONFIG_H_



/**
 * @brief I2C handle object.
 */
#define ANT6F_I2C_HANDLE                (&IO_LIB_LibData.I2C1)



/**
 * @brief I2C address.
 */
#define ANT6F_I2C_ADDR                  0x05



/**
 * @brief I2C transaction timeout in milliseconds.
 */
#define ANT6F_I2C_TIMEOUT               1000




#endif
