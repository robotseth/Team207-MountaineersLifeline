/* 
 * File:   rgbled.h
 * Author: mx3de
 *
 * Created on March 7, 2022, 2:33 PM
 */

#include "mcc_generated_files/mcc.h"

#ifndef RGBLED_H
#define	RGBLED_H

#ifdef	__cplusplus
extern "C" {
#endif

// RegA is Blue
// RegB is Green
// RegC is Red
// RegEn turns individual channels on and off
    
// #define RGB_SLVADDR 0x66
i2c1_address_t RGB_SLVADDR = 0x66; 
    
// #define RGB_SLVADDR_W ((RGB_SLVADDR << 1) || 0)
// #define RGB_SLVADDR_R ((RGB_SLVADDR << 1) || 1)
    
#define RGB_REGA 0x00
#define RGB_REGB 0x01
#define RGB_REGC 0x02
#define RGB_REGEN 0x03
    
#define RGB_AON 0x03
#define RGB_BON 0x0C
#define RGB_CON 0x30
#define RGB_ALLON 0x3F
    


#ifdef	__cplusplus
}
#endif

#endif	/* RGBLED_H */

