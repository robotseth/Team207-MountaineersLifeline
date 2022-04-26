#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "barometer_i2c.h"

//All possible I2C commands that could possible relate to the barometer
//I2C1_SetTimeout(40); // doesnt work
//I2C1_Initialize();
//I2C1_Open(BAROADDR); // No known effect.
//I2C1_MasterOperation(true); // true for read, false for write. 
//I2C1_SetBuffer(buffer,i2cSize);
// stuff from the master example file
//read = I2C1_Read1ByteRegister(BAROADDR,???); // registers not clarified in datasheet. same issue with Read2ByteRegister
//I2C1_Write1ByteRegister(BAROADDR,???,baro_reset_cmd);
//I2C1_WriteNBytes(BAROADDR, baro_reset_cmd, cmd_length);
//I2C1_ReadNBytes(BAROADDR, readPointer,3);
//I2C1_Close();
// 

//Possible Route 1: Basic write/read
//I2C1_Initialize();
//I2C1_Open(BAROADDR);
//I2C1_MasterOperation(false);
//char buffer = READ_ADC;
//size_t i2cSize = sizeof(READ_ADC);
//I2C1_SetBuffer(buffer,i2cSize);
//I2C1_MasterOperation(true); //not clear what happens from here

//Possible Route 2: WriteNBytes/ReadNBytes
//I2C1_Initialize();
//I2C1_Open(BAROADDR);
//char buffer = READ_ADC;
//size_t i2cSize = sizeof(READ_ADC);
//I2C1_WriteNBytes(BAROADDR, READ_ADC, i2cSize);
//uint8_t read = 0;
//uint8_t *readPointer;
//I2C1_ReadNBytes(BAROADDR, readPointer,3);

//Possible Route 3: guessing registers (it probably won't work)
//                                ->        <- the problem
//I2C1_Write1ByteRegister(BAROADDR, BAROADDR , READ_ADC);
//uint8_t read = 0;
//read = I2C1_Read1ByteRegister(BAROADDR,  BAROADDR);

/*
enum i2c_transfer_direction {
    I2C_TRANSFER_WRITE = 0,
    I2C_TRANSFER_READ = 1,
};

enum status_code {
    STATUS_OK = 0x00,
    STATUS_ERR_OVERFLOW = 0x01,
    STATUS_ERR_TIMEOUT = 0x02,
};
*/

void i2c_master_init(void){
    I2C1_Initialize();
    
}


enum status_code i2c_master_read_packet_wait(struct i2c_master_packet *const packet){
    enum status_code status;
    
    uint8_t address = (uint8_t) packet->address;
    uint16_t len = (uint16_t) packet->data_length;
    uint8_t* dataptr = packet->data;
    
    i2c1_error_t output_status;
    
    while(!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetBuffer(dataptr,len);
    I2C1_MasterRead();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
    
    if(output_status != I2C1_NOERR){
        status = STATUS_ERR_TIMEOUT;
    } else {
        status = STATUS_OK;
    }
    
    if( status != STATUS_OK){
		return status;
    }
    
    return STATUS_OK;
}


enum status_code i2c_master_write_packet_wait(struct i2c_master_packet *const packet){
    enum status_code status;
    
    uint8_t address = (uint8_t) packet->address;
    uint16_t len = (uint16_t) packet->data_length;
    uint8_t* dataptr = packet->data;
    
    i2c1_error_t output_status;
    
    while(!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetBuffer(dataptr,len);
    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
    output_status = I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
    
    if(output_status != I2C1_NOERR){
        status = STATUS_ERR_TIMEOUT;
    } else {
        status = STATUS_OK;
    }
    
    if( status != STATUS_OK){
		return status;
    }
    
    return STATUS_OK;
}


enum status_code i2c_master_write_packet_wait_no_stop(struct i2c_master_packet *const packet){
    enum status_code status;
    
    uint8_t address = (uint8_t) packet->address;
    uint16_t len = (uint16_t) packet->data_length;
    uint8_t* dataptr = packet->data;
    
    i2c1_error_t output_status;
    
    while(!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetBuffer(dataptr,len);
    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
    output_status = I2C1_MasterWrite();
    //while(I2C1_BUSY == I2C1_Close()); // removed this because apparently we're not supposed to wait? 
    
    if(output_status != I2C1_NOERR){
        status = STATUS_ERR_TIMEOUT;
    } else {
        status = STATUS_OK;
    }
    
    if( status != STATUS_OK){
		return status;
    }
    
    return STATUS_OK;
    
}