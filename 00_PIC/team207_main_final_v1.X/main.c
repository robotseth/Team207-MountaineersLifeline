/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26J53
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include <stdio.h>
#include "rgbledfx.h"
#include "timers.h"
#include "heartrate.h"
//#include "ms8607.h"

#define TCaddress 0x48 //TC74A0 1001 000
#define READ_REG 0x00
#define rxBufferLen 30

long double heartRate = 0;

uint16_t convertedValue;


uint8_t currentMode = 0;
/*
                         Main application
 */

uint8_t loopTrigger = 0;
int testCounter = 0;
uint8_t buttonTriggered = 0;

void loopTriggerCallback() {
    testCounter++;
    if (testCounter > 500) {
        testCounter = 0;
        loopTrigger = 1;
    }
}

void updateHRValue() {
    heartRate = avgHR();
    //(currentMode);
    static int i = 0;
    if( i < 400 ){
        //setLED(0, 0, RGB_MAX);
        i++;
    } else {
        i = 0;
        GDBG_Toggle();
        //updateDispAnim(currentMode);
        //setLED(0, 0, RGB_MAX);
    }
}

/*
void buttonPressedCallback(){
    buttonTriggered = 1; 
}
 */


void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    GDBG_SetHigh();
    BDBG_SetHigh();
    HRLED_SetLow();

    TMR2_SetInterruptHandler(&updateHRValue);

    //INT1_SetInterruptHandler(&buttonPressedCallback);

    long currentMillis = 0;
    long previousMillis = 0;

    long dispUpdateDelay = 20;
    long previousDispUpdate = 0;

    long hrCheckDelay = 10;
    long previousHRCheck = 0;

    long hrDispDelay = 20000;
    long previousHRDisp = 0;

    long hrMQTTDelay = 5000;
    long previousHRMQTT = 0;

    int tempTesting = 15;

    long startTime = 0;
    
    uint8_t character;

    //    ms8607_init();
    //    if(ms8607_is_connected()){
    //        GDBG_SetLow();
    //        __delay_ms(1000);
    //        GDBG_SetHigh();
    //        __delay_ms(1000);
    //        
    //    }

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    //unsigned long convertedValue = 0;

    struct HrResults currentResults;
    currentResults.hr = 0.0;
    currentResults.status = 0;
    struct HrResults prevResults;
    prevResults.hr = 0.0;
    prevResults.status = 0;

    char rxBuffer[rxBufferLen];

    HRLED_SetHigh();

    //float hrArray[hrArrayLen] = {0};

    uint8_t hrIndex = 0;
    long double maxSafeHR = 80;

    printf("Initialize \n\r");
    //setLED(RGB_MAX, 0, 0);

    while (1) {
        //GDBG_Toggle();
        //printf("Warning! Heart rate is dangerously high: %i BPM\n\r", (int) heartRate); // sends message to MQTT server

        // loopTrigger should ensure that the loop runs every 1 ms or greater



        // Main control logic: 
        // - On startup, connect to the MQTT server and set everything up as
        //   if it was running at full-functionality. We're skipping battery
        //   saving. 
        // - The main loop is triggered by a timer interrupt that ensures it 
        //   runs at 1 ms, relatively precisely
        // - Modes: 
        //   - 0: No display
        //   - 1: Heart rate display
        //   - 11: Alert mode

        // - If the display heartbeat message is sent over MQTT, start 
        //   displaying the heartbeat and send the heartrate
        // - After 20 seconds, stop showing the heart rate

        // - Set RGB LED display
        //   - While the sensors are polling, update their values
        //   - Update frames for the correct mode every 20 ms

        // Increment the mode
        /*
        if(buttonTriggered && currentMode != 11){
            currentMode++;
                
            if(currentMode > 3){
                currentMode = 0; 
            }
                
            buttonTriggered = 0;
        }
         */

        // If a disp heartrate message is received
        if (EUSART2_is_rx_ready()) {
            //printf("Uart ready \n\r");
            character = EUSART2_Read();
            if (character == 'a') {
                character = ' ';
                currentMode = 1;
                startTime = millis();
                previousHRDisp = millis();
                //printf("message received %i \n\r", character);
                //__delay_ms(1000);
                if (heartRate >= 80) {
                    printf("Warning! Heart rate is dangerously high: %i BPM\n\r", (int) heartRate); // sends message to MQTT server
                } else {
                    printf("Heart rate is : %i BPM\n\r", (int) heartRate); // sends message to MQTT server
                }
                
            }
        }


//        if (currentMode == 1) {
//
//            if (currentMillis - previousHRCheck >= hrCheckDelay) {
//                heartRate = avgHR();
//                if (heartRate > maxSafeHR) {
//                    // Set to alert mode
//                    //printf("Warning! Heart rate is dangerously high: %i BPM\n\r", (int) heartRate); // sends message to MQTT server
//                    currentMode = 11;
//                } else {
//                    updateDispHeartRate((int) heartRate);
//                }
//                previousHRCheck = currentMillis;
//            }
//
//        }
       
        
        // If in alert mode, be stuck in alert mode until the end of the display period
//        if (currentMode == 11) {
//            if (currentMillis - previousHRCheck >= hrCheckDelay) {
//                heartRate = avgHR();
//
//                updateDispHeartRate((int) heartRate);
//                previousHRCheck = currentMillis;
//            }
//        }

        // If in either mode, send heart rate to MQTT
//        if (currentMode == 1 || currentMode == 11) {
//            if (currentMillis - previousHRMQTT >= hrMQTTDelay) {
//                //printf("Heart rate: %f \n\r", (float) heartRate);
//                previousHRMQTT = currentMillis;
//            }
//        }
        if (currentMode == 1 && millis() - startTime >= 5000) {
            currentMode = 0;
        }
        
        
        
        
        
        
        
        
        
        
        //updateDispHeartRate((int) heartRate);
        
        if(currentMode == 1){
            displaySimpleHR((int) 200);
        }
        
        
        
        
        
        
        //displaySimpleHR((int) heartRate);

        // Timer to update the RGB LED continuously
//        if (currentMillis - previousDispUpdate >= dispUpdateDelay) {
//            updateDispAnim(currentMode);
//            previousDispUpdate = currentMillis;
//        }

//        if (millis() - startTime >= 30000) {
//            updateDispAnim(currentMode);
//            //previousDispUpdate = currentMillis;
//            currentMode = 0;
//        }

        // If it has been longer than 20 seconds since the last time heart 
        // rate was displayed, then turn it off.
//        if (currentMode != 0 && (currentMillis - previousHRDisp >= hrDispDelay)) {
//            currentMode = 0;
//        }

        // if battery low, send message to MQTT server

        // if UART available, read UART
        // if UART message == "Display Heart Rate"
        // display heart rate with RGB LED
        // else if message == "Low Battery"
        // display battery warning on RGB LED

        /*
        printf("Heart rate: %f\n\r", heartRate); // avgHR() returns a float of the last heart rate value that it calculated - this updates every 30 seconds or so with a 10ms delay

        __delay_ms(10);

        convertedValue = ADC_GetConversion(HRIN);
        if (convertedValue >= 32000)
        {
            GDBG_SetLow();
        } else {
            GDBG_SetHigh();
        }
         */
        
        
        //updateDispAnim(currentMode);
        
        
        __delay_ms(10);
        //printf(" \r\n");

    }
}
/**
 End of File
 */