#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "rgbledfx.h"


// Main LED driver code
void updateLED(uint8_t update, uint8_t mode, int hr, int temp, int alt){
    static int currentHR = 0;
    static int currentTemp = 0;
    static int currentAlt = 0;
    
    
    // Update determines whether there is a simple frame update or if the values
    // are being updated.
    // Mode determines which display mode is currently being displayed.
    
    
    // Only display normally if update is 0
    if(update == 0){
        // Depending on the current display mode, call the appropriate function
        switch(mode){
            case 1:
                // Heart rate display
                displayHR(currentHR);
                break;
            case 2:
                // Temperature display
                displayTemp(currentTemp);
                break;
            case 3:
                // Altitude display
                displayAlt(currentAlt);
                break;
            case 11: 
                // Alert display
                displayAlert();
            default:
                // Turn display off
                displayOff();
                break;
        }
        
        
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
    //  0 = Display off
    //  1 = Heart rate
    //  2 = Temperature
    //  3 = Altitude
    // 11 = Alert mode
    updateLED(0, mode, 0, 0, 0);
}

// Animation functions that actually set the colors depending on inputted values
void displayHR(int heartRate){
    // turn on blue LED
    // pulse (other?) LED at heart rate
    // Heart rate units are in BPM
    
    static unsigned long currentMillis = 0;
    static unsigned long previousMillis = 0; 
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

void displayTemp(int temp){
    // set LED color based on temp
    
    static unsigned long currentMillis = 0;
    static unsigned long previousMillis = 0;
    long blinkDelay = 750;
    long rapidDelay = 250;
    long currentDelay = 0;
    static uint8_t ledOn = 0;
    
    uint8_t calcR = 0;
    uint8_t calcG = 0;
    uint8_t calcB = 0;
    
    // Temp brackets: 
    // T < 20 = rapidly blinking blue
    // 20 <= T < 32 = blinking blue
    // 32 <= T < 45 = blue
    // 45 <= T < 65 = cyan
    // 65 <= T < 75 = green
    // 75 <= T < 85 = yellow
    // 85 <= T < 95 = orange
    // 95 <= T < 105 = red
    // 105 <= T < 115 = blinking red
    // T > 115 = rapidly blinking red
    
    if(temp < 20){
        calcB = RGB_MAX;
        currentDelay = rapidDelay;
    } else if(temp >= 20 && temp < 32){
        calcB = RGB_MAX;
        currentDelay = blinkDelay;
    } else if(temp >= 32 && temp < 45){
        calcB = RGB_MAX;
    } else if(temp >= 45 && temp < 65){
        calcB = RGB_MAX;
        calcG = RGB_MAX;
    } else if(temp >= 65 && temp < 75){
        calcG = RGB_MAX;
    } else if(temp >= 75 && temp < 85){
        calcG = RGB_MAX;
    } else if(temp >= 85 && temp < 95){
        calcG = RGB_MAX;
        calcR = RGB_MAX;
    } else if(temp >= 95 && temp < 105){
        calcR = RGB_MAX;
    } else if(temp >= 105 && temp < 115){
        calcR = RGB_MAX;
        currentDelay = blinkDelay;
    } else if(temp >= 115){
        calcR = RGB_MAX;
        currentDelay = rapidDelay;
    }
    
    if(currentDelay > 0){
        currentMillis = millis();
        if(currentMillis - previousMillis >= currentDelay){
            previousMillis = currentMillis;
            ledOn = !ledOn;
        }
    } else {
        ledOn = 1;
    }
    
    setLED(calcR*ledOn, calcG*ledOn, calcB*ledOn);
    
}

void displayAlt(int alt){
    // Display protocol: 
    // Show green if not blinking
    // Blink in white the number of the thousands digit
    // Pause for a second
    // Blink in blue the number of the hundreds digit
    // Pause for five seconds
    // Repeat
    
    static uint8_t dispStep = 0;
    static int currentAlt = 0;
    static int altThou = 0;
    static int altHund = 0;
    
    int onNumDelay = 250;
    int offNumDelay = 500;
    int placeSeperatorDelay = 1000;
    int completeDispDelay = 5000;
    
    static unsigned long currentMillis = 0;
    static unsigned long previousMillis = 0;
    static uint8_t ledOn = 0;
    static uint8_t counter = 0;
    
    currentMillis = millis();
    
    if (dispStep == 0){
        // Take in altitude value to display
        currentAlt = alt;
        altThou = alt % 1000;
        altHund = (alt - altThou*1000) % 100;
        dispStep = 1;
    } else if(dispStep == 1){
        // Blink thousands
        if(ledOn == 1){
            if(currentMillis - previousMillis >= onNumDelay){
                previousMillis = currentMillis;
                ledOn = 0;
            }
        } else {
            if(currentMillis - previousMillis >= offNumDelay){
                previousMillis = currentMillis;
                ledOn = 1;
                counter++;
            }
        }
        
        if(counter >= altThou){
            dispStep = 2;
            counter = 0;
            ledOn = 0;
        }
                
    } else if (dispStep == 2){
        // Pause for a second
        if(currentMillis - previousMillis >= placeSeperatorDelay){
            previousMillis = currentMillis;
            dispStep = 3;
        }
    } else if (dispStep == 3){
        // Blink hundreds
        if(ledOn == 1){
            if(currentMillis - previousMillis >= onNumDelay){
                previousMillis = currentMillis;
                ledOn = 0;
            }
        } else {
            if(currentMillis - previousMillis >= offNumDelay){
                previousMillis = currentMillis;
                ledOn = 1;
                counter++;
            }
        }
        
        
        if(counter >= altHund){
            dispStep = 4;
            counter = 0;
            ledOn = 0;
        }
    } else if (dispStep == 4){
        // Pause for five seconds
        if(currentMillis - previousMillis >= completeDispDelay){
            previousMillis = currentMillis;
            dispStep = 0;
        }
    } else {
        dispStep = 0;
    }
    
    if(ledOn == 1 && dispStep == 1){
        setLED(RGB_MAX, RGB_MAX, RGB_MAX);
    } else if (ledOn == 1 && dispStep == 3) {
        setLED(0, 0, RGB_MAX);
    } else {
        setLED(0, RGB_MAX, 0);
    }
    
    
}

void displayAlert(void){
    
    static unsigned long currentMillis = 0;
    static unsigned long previousMillis = 0;
    static uint8_t ledOn = 0;
    static uint8_t counter = 0;
    unsigned long blinkDelay = 75;
    
    currentMillis = millis();
    
    if(currentMillis - previousMillis >= blinkDelay){
        if(ledOn){
            ledOn = 0;
        } else {
            ledOn = 1;
        }
        previousMillis = currentMillis;
    }
    
    setLED(RGB_MAX*ledOn, 0, 0);
    
}

// Implement if we have time
//void displayBattWarn(void);

void displayOff(void){
    // turn off LED
    setLED(0, 0, 0);
}

void setLED(uint8_t red, uint8_t green, uint8_t blue){
    static uint8_t currentR = 0;
    static uint8_t currentG = 0;
    static uint8_t currentB = 0;
    
    currentR = byteMin(red, RGB_MAX);
    currentG = byteMin(green, RGB_MAX);
    currentB = byteMin(blue, RGB_MAX);
    
    uint8_t enableByte = 0x00;
    
    // Sets enables
    if(currentR == 0){
        enableByte = enableByte & RGB_CNMASK;
    } else {
        enableByte = enableByte | RGB_CON;
    }
    
    if(currentG == 0){
        enableByte = enableByte & RGB_BNMASK;
    } else {
        enableByte = enableByte | RGB_BON;
    }
    
    if(currentB == 0){
        enableByte = enableByte & RGB_ANMASK;
    } else {
        enableByte = enableByte | RGB_AON;
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


// Test code for main loop
/*
for(uint8_t j = 0; j < 3; j++){
    if(j == 0){
        for(uint8_t i = 0x00; i < 0x0D; i++){
            setLED(i, 0, 0);
            __delay_ms(250);
        }
        setLED(0,0,0);
    } else if(j == 1){
        for(uint8_t i = 0x00; i < 0x0D; i++){
            setLED(0, i, 0);
            __delay_ms(250);
        }
        setLED(0,0,0);
    } else {
        for(uint8_t i = 0x00; i < 0x0D; i++){
            setLED(0, 0, i);
            __delay_ms(250);
        } 
        setLED(0,0,0);
    }
}

setLED(0, 0, 0);

for(uint8_t i = 0; i < 10; i++){
    setLED(i, 0, 0);
    __delay_ms(250);
    setLED(0, 0, 0);
    __delay_ms(250);
}

for(uint8_t i = 0; i < 10; i++){
    setLED(0, i, 0);
    __delay_ms(250);
    setLED(0, 0, 0);
    __delay_ms(250);
}

for(uint8_t i = 0; i < 10; i++){
    setLED(0, 0, i);
    __delay_ms(250);
    setLED(0, 0, 0);
    __delay_ms(250);
}
 */