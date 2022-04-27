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
    
#define HR_MODE 0
#define TEMP_MODE 1
#define ALTI_MODE 2
#define OFF_MODE 3

int beatToDelayOffset = 30;
int beatToDelay[] = {2000,1935,1875,1818,1765,1714,1667,1622,1579,1538,1500,1463,
                     1429,1395,1364,1333,1304,1277,1250,1224,1200,1176,1154,1132,
                     1111,1091,1071,1053,1034,1017,1000,984,968,952,938,923,909,
                     896,882,870,857,845,833,822,811,800,789,779,769,759,750,741,
                     732,723,714,706,698,690,682,674,667,659,652,645,638,632,625,
                     619,612,606,600,594,588,583,577,571,566,561,556,550,545,541,
                     536,531,526,522,517,513,508,504,500,496,492,488,484,480,476,
                     472,469,465,462,458,455,451,448,444,441,438,435,432,429,426,
                     423,420,417,414,411,408,405,403,400,397,395,392,390,387,385,
                     382,380,377,375,373,370,368,366,364,361,359,357,355,353,351,
                     349,347,345,343,341,339,337,335,333,331,330,328,326,324,323,
                     321,319,317,316,314,313,311,309,308,306,305,303,302,300};
    
void updateLED(uint8_t update, uint8_t mode, int hr, int temp, int alt);

void updateAllDispVals(int hr, int temp, int alt);
void updateDispHeartRate(int hr);
void updateDispTemp(int temp);
void updateDispAltitude(int alt);
void updateDispAnim(uint8_t mode);

void displayHR(int hr);
void displaySimpleHR(int heartRate);
void displayTemp(int temp);
void displayAlt(int alt);
void displayAlert(void);
void displayBattWarn(void);
void displayOff(void);

void setLED(uint8_t red, uint8_t green, uint8_t blue);

uint8_t byteMax(uint8_t a, uint8_t b);
uint8_t byteMin(uint8_t a, uint8_t b);


#ifdef	__cplusplus
}
#endif

#endif	/* RGBLEDFX_H */

