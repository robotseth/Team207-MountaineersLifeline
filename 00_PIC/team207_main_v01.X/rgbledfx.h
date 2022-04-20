/* 
 * File:   rgbledfx.h
 * Author: mx3de
 *
 * Created on April 7, 2022, 11:50 PM
 */

#ifndef RGBLEDFX_H
#define	RGBLEDFX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "timers.h"
    
#define RGBLEDADDR 0x66 //CAT3626 1100 110
#define RGB_REGA 0x00
#define RGB_REGB 0x01
#define RGB_REGC 0x02
#define RGB_REGEN 0x03
#define RGB_AON 0x03
#define RGB_BON 0x0C
#define RGB_CON 0x30
#define RGB_ANMASK 0x3C
#define RGB_BNMASK 0x33
#define RGB_CNMASK 0x0F
#define RGB_ALLON 0xFF
#define RGB_ALLOFF 0x00
#define RGB_MAX 0x12
    
void updateLED(uint8_t update, uint8_t mode, int hr, int temp, int alt);

void updateAllDispVals(int hr, int temp, int alt);
void updateDispHeartRate(int hr);
void updateDispTemp(int temp);
void updateDispAltitude(int alt);
void updateDispAnim(uint8_t mode);

void displayHR(int hr);
void displayTemp(int temp);
void displayAlt(int alt);
void displayOff(void);

void setLED(uint8_t red, uint8_t green, uint8_t blue);

uint8_t byteMax(uint8_t a, uint8_t b);
uint8_t byteMin(uint8_t a, uint8_t b);


#ifdef	__cplusplus
}
#endif

#endif	/* RGBLEDFX_H */

