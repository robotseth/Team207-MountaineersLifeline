#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "rgbledfx.h"


// Main LED driver code
void updateLED(uint8_t update, uint8_t mode, int hr, int temp, int alt){
    static int currentHR = 0;
    static int currentTemp = 0;
    static int currentAlt = 0;
    
    static int animFrame = 0;
    
    // Update determines whether there is a simple frame update or if the values
    // are being updated.
    // Mode determines which display mode is currently being displayed.
    
    
    // Only display normally if update is 0
    if(update == 0){
        // Depending on the current display mode, call the appropriate function
        switch(mode){
            case 0:
                // Heart rate display
                displayHR(animFrame, currentHR);
                break;
            case 1:
                // Temperature display
                break;
            case 2:
                // Altitude display
                break;
            case 3:
                // Fine altitude display
                break;
            default:
                // Turn display off
                displayOff();
                break;
        }
        
        // Increment the animation frame
        animFrame++;
        
        
    } else if(update == 1){
        // If the display needs to be updated, then update the values
        currentHR = hr; 
        currentTemp = temp;
        currentAlt = alt; 
    } else if(update == 2){
        currentHR = hr;
    } else if(update == 3){
        currentTemp = temp;
    } else if(update == 4){
        currentAlt = alt;
    }
    
    // If the display values are being updated, then reset the frame counter
    // Test and remove if necessary
    if(update > 0){
        animFrame = 0;
    }
        
}

// Helper functions to make value updates easier
void updateAllDispVals(int hr, int temp, int alt){
    updateLED(1, 0, hr, temp, alt);
}

void updateDispHeartRate(int hr){
    updateLED(2, 0, hr, 0, 0);
}

void updateDispTemp(int temp){
    updateLED(3, 0, 0, temp, 0);
}

void updateDispAltitude(int alt){
    updateLED(4, 0, 0, 0, alt);
}

// Helper function to make frame/animation updates easier
// Should be called at the "frame rate" of the display
void updateDispAnim(uint8_t mode){
    // Loads function with some default values that will not be accepted
    // Modes: 
    //  0 = Heart rate
    //  1 = Temperature
    //  2 = Altitude
    //  3 = Fine altitude
    // >3 = Display off
    updateLED(0, mode, 0, 0, 0);
}

// Animation functions that actually set the colors depending on inputted values
void displayHR(int frame, int heartRate){
    // turn on blue LED
    // pulse (other?) LED at heart rate
    // Heart rate units are in BPM
    
    static long currentMillis = 0;
    static long previousMillis = 0; 
    static uint8_t brightness = 0; 
    
    uint8_t maxBrightness = 255; 
    
    // Animation look: 
    // Red LED turns on and then fades at the heart rate specified
    // Once the timer is triggered, then reset the brightness value
    // Every frame update in between will measure the time since the last beat 
    // and apply a linear fade based on it. 
    
    // Calculate the delay between beats: 
    double currentHR = (double) heartRate;
    long beatDelay = (long) round(1000.0/(currentHR*0.0167));
    
    currentMillis = millis();
    
    if(currentMillis - previousMillis >= beatDelay){
        brightness = maxBrightness;
        previousMillis = currentMillis;
    } else {
        // Set brightness
        brightness = maxBrightness;
        // Output color
    }
    
}

void displayTemp(int frame, int temp){
    // set LED color based on temp
}

void displayAlt(int frame, int alt){
    // turn off LED
    float rate = alt * 0.00161290322;
    int delay_ms = (int)(1/rate);
    unsigned long time = 0;
    if (millis() - time >= delay_ms && displayActive == 1){
        // toggle LED
        time = millis();
    }
}

void displayAltFine(int frame, int alt){
    // turn on blue LED
    // pulse (other?) LED for altitude
}

void displayOff(void){
    // turn off LED
}