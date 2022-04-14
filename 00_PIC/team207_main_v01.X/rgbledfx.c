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
    static uint8_t level = 0; 
       
    uint8_t maxLevel = RGB_MAX; 
    uint8_t levelFade = 0;
    // fadeFactor = RGB_MAX / fade_delay = 18 / 1000ms
    float fadeFactor = 0.018;
    
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
        level = maxLevel;
        previousMillis = currentMillis;
    } else {
        // Set brightness
        levelFade = (uint8_t) fmin(fadeFactor*(currentMillis-previousMillis),(float) maxLevel);
        // Output color
        
    }
    setLED(maxLevel - levelFade, 0, 0);
    
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

void setLED(uint8_t red, uint8_t green, uint8_t blue){
    static uint8_t currentR = 0;
    static uint8_t currentG = 0;
    static uint8_t currentB = 0;
    
    currentR = byteMax(red, RGB_MAX);
    currentG = byteMax(green, RGB_MAX);
    currentB = byteMax(blue, RGB_MAX);
    
    uint8_t enableByte = 0x00;
    
    // Sets enables
    if(currentR == 0){
        enableByte = enableByte && RGB_CNMASK;
    } else {
        enableByte = enableByte || RGB_CON;
    }
    
    if(currentG == 0){
        enableByte = enableByte && RGB_BNMASK;
    } else {
        enableByte = enableByte || RGB_BON;
    }
    
    if(currentR == 0){
        enableByte = enableByte && RGB_ANMASK;
    } else {
        enableByte = enableByte || RGB_AON;
    }
    
    // Set the enable register
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGEN, enableByte);
    
    // Set the brightness values
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGC, currentR);
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGB, currentG);
    I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGA, currentB);
}

uint8_t byteMax(uint8_t a, uint8_t b){
    return (((a) > (b)) ? (a) : (b));
}

uint8_t byteMin(uint8_t a, uint8_t b){
    return (((a) < (b)) ? (a) : (b));
}