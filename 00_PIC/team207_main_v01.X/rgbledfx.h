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
#include "mcc_generated_files/mcc.h"
#include "timers.h"
    
#define RGBLEDADDR 0x66 //CAT3626 1100 110
#define RGB_REGA 0x00
#define RGB_REGB 0x01
#define RGB_REGC 0x02
#define RGB_REGEN 0x03
#define RGB_AON 0x03
#define RGB_BON 0x0C
#define RGB_CON 0x30
#define RGB_ALLON 0xFF
#define RGB_ALLOFF 0x00

    
void updateDispVals(uint8_t mode, long alt, double temp, int hr);
void updateDispAnim();
void updateLED(uint8_t update, long alt, double temp, int hr);

void displayHR(int hr);
void displayTemp(int temp);
void displayAlt(int alt);
void displayAltFine(int alt);
void displayOff(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RGBLEDFX_H */
