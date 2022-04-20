#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "rgbledfx.h"


void setLED(uint8_t red, uint8_t green, uint8_t blue){
    static uint8_t currentR = 0;
    static uint8_t currentG = 0;
    static uint8_t currentB = 0;
    
    currentR = byteMin(red, RGB_MAX);
    currentG = byteMin(green, RGB_MAX);
    currentB = byteMin(blue, RGB_MAX);
    
    uint8_t enableByte = 0x00;
    
    // Sets enables
    if(currentR == 0){
        enableByte = enableByte & RGB_CNMASK;
    } else {
        enableByte = enableByte | RGB_CON;
    }
    
    if(currentG == 0){
        enableByte = enableByte & RGB_BNMASK;
    } else {
        enableByte = enableByte | RGB_BON;
    }
    
    if(currentR == 0){
        enableByte = enableByte & RGB_ANMASK;
    } else {
        enableByte = enableByte | RGB_AON;
    }
    
    // Set the enable register
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGEN, enableByte);
    
    // Set the brightness values
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGC, currentR);
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGB, currentG);
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGA, currentB);
}

uint8_t byteMax(uint8_t a, uint8_t b){
    return (((a) > (b)) ? (a) : (b));
}

uint8_t byteMin(uint8_t a, uint8_t b){
    return (((a) < (b)) ? (a) : (b));
}
