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


// Driver structure: 
// When the heart rate needs to be read, ideally one function should be called 
// that triggers a timed read. The main loop will then poll another function
// which is responsible for taking ADC readings. It will return a blocking
// value while readings are taking place, and then once enough readings have 
// been taken, it will return the actual value and reset. 
    
    
#define CAPTURE_TIME 10000
    
// Set up constants for calibration here
    
    
// Function that calls the pollHR function with initial settings and 
void triggerHR();

double pollHR();

// Placeholder function  
double detectBeats();



#ifdef	__cplusplus
}
#endif

#endif	/* HEARTRATE_H */

