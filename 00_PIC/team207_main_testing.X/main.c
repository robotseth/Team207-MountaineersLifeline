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

#define TCaddress 0x48 //TC74A0 1001 000
#define READ_REG 0x00

#define RGBLEDADDR 0x66 //CAT3626 1100 110
#define RGB_REGA 0x00
#define RGB_REGB 0x01
#define RGB_REGC 0x02
#define RGB_REGEN 0x03
#define RGB_AON 0x03
#define RGB_BON 0x0C
#define RGB_CON 0x30
#define RGB_ALLON 0x3F

// RH sensor I2C constants
#define RHADDR 0x40
#define RH_HOLD 0xE5
#define RH_NOHOLD 0xF5

// P&T sensor I2C constants
#define BAROADDR 0x76
#define BARO_RESET 0xFE
size_t cmd_length = sizeof(BARO_RESET);

/*
                         Main application
 */
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
    
    size_t i2cSize = 1;
    char *bufferPointer;
    char buffer = 'A';
    
    bufferPointer = &buffer;
    
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        
        BDBG_SetLow();
        __delay_ms(50);
        BDBG_SetHigh();
        __delay_ms(50);
        printf("Testing\r\n");
        I2C1_SetBuffer(*bufferPointer, i2cSize);
        
        
        //Read temp sensor
        //printf("Read attempt \r\n");
        //uint8_t read = I2C1_Read1ByteRegister(TCaddress, READ_REG);// read=-1;
        
        //Write to RGB LED driver
        I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGA, 0x31);
        I2C1_Write1ByteRegister(RGBLEDADDR, RGB_REGEN, RGB_ALLON);
        
        //Reset barometer
        uint8_t baro_reset_cmd = BARO_RESET;
        cmd_length = sizeof(baro_reset_cmd); 
        I2C1_WriteNBytes(BAROADDR, &baro_reset_cmd, cmd_length);
        //__delay_ms(5);
    }
}
/**
 End of File
*/