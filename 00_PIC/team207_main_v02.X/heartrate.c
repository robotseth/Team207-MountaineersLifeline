#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "heartrate.h"

// Main function that handles sensor polling
struct HrResults pollHR(uint8_t mode){
    struct HrResults currentResults;
    
    static uint8_t scanning = 0; 
    
    static unsigned long currentMillis = 0; 
    static unsigned long startScanMillis = 0;
    
    static double currentReading = 0; 
    static double currentHR = 0;
    
    // Modes: 
    // - 0: Polling, will not do anything if it hasn't been triggered. 
    // - 1: Triggered, sets the variable and then locks the function until the 
    //      scan is done. 
    
    // Indicate that the sensor is ready to be triggered. 
    currentResults.hr = 0.0;
    currentResults.status = 0;
    
    currentMillis = millis(); 
    
    // If it is not currently scanning and the function has been triggered
    // enable the scan. 
    // If not that, then if it is just scanning then do the scanny things
    if(mode == 1 && scanning == 0){
        scanning = 1; 
        startScanMillis = currentMillis;
    } else if (scanning == 1) {
        currentReading = ADC_GetConversion(0);
        int deltaT = currentMillis - startScanMillis; 
        
        // Placeholder for math
        //currentHR = detectBeats([currentReading], 28000, deltaT);
        currentHR = 0;//Placeholder for placeholder
        // Default values while polling
        currentResults.hr = currentHR; 
        currentResults.status = 1;
        
        // If the scan timer has run out, 
        if(currentMillis - startScanMillis >= CAPTURE_TIME){
            scanning = 0; 
            startScanMillis = currentMillis;
            currentResults.hr = currentHR;
            // Placeholder value, comment line below and uncomment line above
            //currentResults.hr = 80.0;
            currentResults.status = 2;
            
        }
    }
    
    return currentResults;
}

// Utility function that calls the pollHR function with initial settings
void triggerHR(){
    pollHR(1);
}

// Placeholder function for beat detection
double detectBeats(float data[], int threshold, int time){
    bool currentPeak = 0; //if it pass the threshold count it, starts false
    int peaks = 0; //how many beats counted
    int len = sizeof(data) / sizeof(data[0]); // finds the total length of the array and divides that by the length of each element to find the number of elements
    for (int i = 0; i <= len; i++)
    {
        if (data[i] > threshold && currentPeak == 0) {// if data is bigger than threshold and it has not passed the threshold yet (False)
            peaks++; // count 1 beat
            currentPeak = 1;// set to true and to ignore the future value above threshold
        } else {
            currentPeak = 0;// if its below the threshold set to false )
        }
    }

    float BPM = (peaks / time)*60000; // how many beats counted so far divided by time started in millis and then convert to minute
    // Write function that takes in either a single reading or a data array,
    // decides if there is a heart beat present, and uses a buffer to 
    // figure out what the current estimated heart rate is.
    return BPM;
}