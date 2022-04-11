#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "rgbledfx.h"



// Main LED driver code
void updateLED(uint8_t update, long alt, double temp, int hr){
    static long currentAlt = 0;
    static double currentTemp = 0;
    static int currentHR = 0;
    
    static int animFrame = 0;
    
    // If the display needs to be updated, then update the values
    if(update == 1){
        currentAlt = alt;
        currentTemp = temp; 
        currentHR = hr; 
    } else if(update == 2){
        currentAlt = alt;
    } else if(update == 3){
        currentTemp = temp;
    } else if(update == 4){
        currentHR = hr;
    }
    
    // If the display values are being updated, then reset the frame counter
    if(update > 0){
        animFrame = 0;
    }
    
    
    
    
}

// Helper functions to make value updates easier
void updateAllDispVals(long alt, double temp, int hr){
    updateLED(1, alt, temp, hr);
}

void updateDispAltitude(long alt){
    updateLED(2, alt, 0, 0);
}

void updateDispTemp(long temp){
    updateLED(3, 0, temp, 0);
}

void updateDispHeartRate(long hr){
    updateLED(4, 0, 0, hr);
}

// Helper function to make frame/animation updates easier
void updateDispAnim(){
    // Loads function with some default values that will not be accepted
    updateLED(0, 0, 0, 0);
}

void displayHR(int heartRate){
    // turn on blue LED
    // pulse (other?) LED at heart rate
}

void displayTemp(int temp){
    // set LED color based on temp
}

void displayAlt(int alt){
    displayActive = 1;
    // turn off LED
    float rate = alt * 0.00161290322;
    int delay_ms = (int)(1/rate);
    unsigned long time = 0;
    if (millis() - time >= delay_ms && displayActive == 1){
        // toggle LED
        time = millis();
    }
}

void displayAltFine(int alt){
    // turn on blue LED
    // pulse (other?) LED for altitude
}

void displayOff(void){
    // turn off LED
    displayActive = 0;
}