/* 
 * File:   barometer.h
 * Author: mx3de
 *
 * Created on April 16, 2022, 12:42 PM
 */

#ifndef BAROMETER_H
#define	BAROMETER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
    
// RH sensor I2C constants
//#define RHADDR 0x40
//#define RH_HOLD 0xE5
//#define RH_NOHOLD 0xF5

// P&T sensor I2C constants
//#define BAROADDR 0x76
//#define BARO_RESET 0xFE
//#define READ_ADC 0x00
//size_t cmd_length = sizeof(BARO_RESET);

// Requirements to use provided barometer I2C library

/*
  * The header "i2c.h" has to be implemented for your own platform to 
  * conform the following protocol :
  * 
  */
enum i2c_transfer_direction {
	I2C_TRANSFER_WRITE = 0,
	I2C_TRANSFER_READ  = 1,
};

enum status_code {
	STATUS_OK           = 0x00,
	STATUS_ERR_OVERFLOW	= 0x01,
	STATUS_ERR_TIMEOUT  = 0x02,
};

struct i2c_master_packet {
	// Address to slave device
	uint16_t address;
	// Length of data array
	uint16_t data_length;
	// Data array containing all data to be transferred
	uint8_t *data;
};

void i2c_master_init(void);
enum status_code i2c_master_read_packet_wait(struct i2c_master_packet *const packet);
enum status_code i2c_master_write_packet_wait(struct i2c_master_packet *const packet);
enum status_code i2c_master_write_packet_wait_no_stop(struct i2c_master_packet *const packet);


#ifdef	__cplusplus
}
#endif

#endif	/* BAROMETER_H */

