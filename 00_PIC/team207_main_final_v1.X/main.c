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

uint16_t convertedValue;
/*
                         Main application
 */

uint8_t loopTrigger = 0;
uint8_t buttonTriggered = 0;


void loopTriggerCallback(){
    loopTrigger = 1;
}


void buttonPressedCallback(){
    buttonTriggered = 1; 
}


void main(void)
{
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
    
    TMR2_SetInterruptHandler(&loopTriggerCallback);
    
    INT1_SetInterruptHandler(&buttonPressedCallback);
    
    unsigned long currentMillis = 0;
    unsigned long previousMillis = 0;
    
    unsigned long dispUpdateDelay = 20;
    unsigned long previousDispUpdate = 0;
    
    unsigned long hrCheckDelay = 10;
    unsigned long previousHRCheck = 0;
    
    unsigned long tempCheckDelay = 1000;
    unsigned long previousTempCheck = 0;
    
    unsigned long altCheckDelay = 5000;
    unsigned long previousAltCheck = 0;
    
    int tempTesting = 15;
    
    uint8_t currentMode = 0;
    
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
    
    HRLED_SetHigh();
    
    //float hrArray[hrArrayLen] = {0};
    
    uint8_t hrIndex = 0;
    float heartRate = 0;
    float maxSafeHR = 80;
    
    while (1)
    {
        // loopTrigger should ensure that the loop runs every 1 ms or greater
        if(loopTrigger){
            
            
            // Main control logic: 
            // - On startup, connect to the MQTT server and set everything up as
            //   if it was running at full-functionality. We're skipping battery
            //   saving. 
            // - The main loop is triggered by a timer interrupt that ensures it 
            //   runs at 1 ms, relatively precisely
            // - The button is what cycles through standard modes. 
            // - Modes: 
            //   - 0: No display
            //   - 1: Heart rate display
            //   - 2: Temperature display
            //   - 3: Altitude display
            //   - 11: Alert mode (inaccessible using button)
            
            
            // - Determine what sensors should be polled
            //   - If it is in heart rate display mode or the heart rate has 
            //     been requested in the past 60 seconds, then poll heart rate
            //   - Same for temp or altitude (if working)
            //   - If in alert mode, then always poll heart rate
            
            // - Set RGB LED display
            //   - While the sensors are polling, update their values
            //   - Update frames for the correct mode every 20 ms
            
            currentMillis = millis();
            
            // Increment the mode
            if(buttonTriggered && currentMode != 11){
                currentMode++;
                
                if(currentMode > 3){
                    currentMode = 0; 
                }
                
                buttonTriggered = 0;
            }
            
            
            
            if(currentMode == 1){
                
                if(currentMillis - previousHRCheck >= hrCheckDelay){
                    heartRate = avgHR();
                    if(heartRate > maxSafeHR){
                        // Set to alert mode
                        printf("Warning! Heart rate is dangerously high: %f BPM\n\r", heartRate); // sends message to MQTT server
                        currentMode = 11;
                    } else {
                        updateDispHeartRate(heartRate);
                    }
                    previousHRCheck = currentMillis;
                }
                
            }

            
            if(currentMillis - previousDispUpdate >= dispUpdateDelay){
                updateDispAnim(currentMode);
                previousDispUpdate = currentMillis; 
            }
            
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
            
            // Readies the loop to be triggered again
            loopTrigger = 0;
            
        }
            
    }
    
}
/**
 End of File
*/