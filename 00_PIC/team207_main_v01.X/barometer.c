#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "barometer.h"

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