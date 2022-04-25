#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "heartrate.h"

// Main function that handles sensor polling

static float dataArray[hrSubSampleArrayLen] = {0};

struct HrResults pollHR(uint8_t mode) {
    struct HrResults currentResults;

    static uint8_t scanning = 0; // what does this do?

    static unsigned long currentMillis = 0;
    static unsigned long startScanMillis = 0;

    static float currentReading = 0;
    static long double currentHR = 0;
   
    static int currentScan = 0;
    int deltaT;

    float triggerThreshold = 32000;

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
    if (mode == 1 && scanning == 0) {
        scanning = 1;
        startScanMillis = currentMillis;
    }
    if (scanning == 1) {
        if (currentScan >= hrSubSampleArrayLen) {
            //printf("Heart Rate Triggered");
            // only measure time between filling the array not each time it runs
            deltaT = (int) (currentMillis - startScanMillis);
            //printf("HR sample array full \n\r");
            currentHR = detectBeats(triggerThreshold, deltaT);
            //printf("Heart Rate: %i, Last sample: %d \n\r", currentHR, ADC_GetConversion(HRIN));
//            for (int i = 0; i < arrayLen; i++) {
//                printf("Sample at index %i is %f \n\r", i, dataArray[i]);
//            }
            currentScan = 0;
            scanning = 0;
            mode = 0;
            currentResults.status = 2;
                    // Default values while polling
            currentResults.hr = currentHR;
            currentResults.status = 1;
        }
        dataArray[currentScan] = (float) ADC_GetConversion(HRIN);
        
        //printf("Sample recorded - %f \n\r", dataArray[currentScan]);
        //printf("Index: %i", currentScan);

        currentScan++;

        // If the scan timer has run out, 
        /*
        if (currentMillis - startScanMillis >= CAPTURE_TIME) {
            scanning = 0;
            startScanMillis = currentMillis;
            currentResults.hr = currentHR;
            // Placeholder value, comment line below and uncomment line above
            //currentResults.hr = 80.0;
            currentResults.status = 2;

        }
        */
    }

    return currentResults;
}

// Utility function that calls the pollHR function with initial settings

void triggerHR() {
    pollHR(1);
}

// function for beat detection

long double detectBeats(float threshold, int time) {
    bool currentPeak = 0; //if it pass the threshold count it, starts false
    int peaks = 0; //how many beats counted
    for (int i = 0; i <= hrSubSampleArrayLen; i++) {
        if (dataArray[i] > threshold && currentPeak == 0) {// if data is bigger than threshold and it has not passed the threshold yet (False)
            peaks++; // count 1 beat
            //printf("Data above threshold: %f \n\r", (float) dataArray[i]);
            currentPeak = 1; // set to true and to ignore the future value above threshold
        } else {
            //printf("Data below threshold: %f \n\r", (float) dataArray[i]);
            currentPeak = 0; // if its below the threshold set to false )
        }
    }
    
    //printf("Num peaks: %i \n\r", peaks);
    //printf("Time: %i \n\r", time);
    long double BPM = (long double) 100; // ((60000 * peaks) / time)
    //printf("BPM: %i \n\r", (int) BPM);
    
    // Write function that takes in either a single reading or a data array,
    // decides if there is a heart beat present, and uses a buffer to 
    // figure out what the current estimated heart rate is.
    return BPM;
}

long double avgHR(){
    static uint8_t hrIndex = 0;
    static long double hrArray[hrAvgArrayLen] = {0};
    static long double avgHRVal;
    static long double runningTotal;
    if (hrIndex >= hrAvgArrayLen) {
            hrIndex = 0;
            runningTotal = 0;
            for (int i = 0; i < hrAvgArrayLen; i++){
                runningTotal = runningTotal + hrArray[i];
                //printf("HR value at index %i is %f \r\n", i, hrArray[i]);
            }
            //("Running Total: %f \r\n", runningTotal);
            avgHRVal = (long double) (runningTotal / hrAvgArrayLen);
            //printf("AVG HR is %f \n\r", avgHR);
        }
        long double currentHR = pollHR(1).hr;
        //printf("Heart rate polled and returned %f \r\n",currentHR);
        if (currentHR != hrArray[hrIndex]){
            hrIndex++;
            hrArray[hrIndex] = currentHR;
        }
        return avgHRVal;
}