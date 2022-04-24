/* 
 * File:   heartrate.h
 * Author: mx3de
 *
 * Created on April 17, 2022, 10:36 PM
 */

#ifndef HEARTRATE_H
#define	HEARTRATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "mcc_generated_files/mcc.h"
#include "timers.h"
    
// Driver structure: 
// When the heart rate needs to be read, ideally one function should be called 
// that triggers a timed read. The main loop will then poll another function
// which is responsible for taking ADC readings. It will return a blocking
// value while readings are taking place, and then once enough readings have 
// been taken, it will return the actual value and reset. 
    
// Set up constants for calibration here
#define CAPTURE_TIME 10000
    
    
// HrResults holds the return value of the HR sensor API
// Status key: 
// - 0: Ready to start polling
// - 1: Busy polling
// - 2: Polling complete
struct HrResults {
    uint8_t status;
    unsigned int hr;
};
   

// Main function that handles sensor polling
struct HrResults pollHR(uint8_t mode);

// Utility function that calls the pollHR function with initial settings
void triggerHR();

// Placeholder function for beat detection
unsigned int detectBeats(float threshold, int time);

int arrayLen;
//static float dataArray[32];

#ifdef	__cplusplus
}
#endif

#endif	/* HEARTRATE_H */

