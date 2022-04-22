/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26J53
        Driver Version    :  2.1.2
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set HRIN aliases
#define HRIN_TRIS                 TRISAbits.TRISA1
#define HRIN_LAT                  LATAbits.LATA1
#define HRIN_PORT                 PORTAbits.RA1
#define HRIN_ANS                  ANCON0bits.PCFG1
#define HRIN_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define HRIN_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define HRIN_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define HRIN_GetValue()           PORTAbits.RA1
#define HRIN_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define HRIN_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define HRIN_SetAnalogMode()      do { ANCON0bits.PCFG1 = 1; } while(0)
#define HRIN_SetDigitalMode()     do { ANCON0bits.PCFG1 = 0; } while(0)

// get/set BDBG aliases
#define BDBG_TRIS                 TRISAbits.TRISA6
#define BDBG_LAT                  LATAbits.LATA6
#define BDBG_PORT                 PORTAbits.RA6
#define BDBG_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define BDBG_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define BDBG_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define BDBG_GetValue()           PORTAbits.RA6
#define BDBG_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define BDBG_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set GDBG aliases
#define GDBG_TRIS                 TRISAbits.TRISA7
#define GDBG_LAT                  LATAbits.LATA7
#define GDBG_PORT                 PORTAbits.RA7
#define GDBG_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define GDBG_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define GDBG_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define GDBG_GetValue()           PORTAbits.RA7
#define GDBG_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define GDBG_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set BTN1 aliases
#define BTN1_TRIS                 TRISBbits.TRISB1
#define BTN1_LAT                  LATBbits.LATB1
#define BTN1_PORT                 PORTBbits.RB1
#define BTN1_WPU                  WPUBbits.WPUB1
#define BTN1_ANS                  ANCON1bits.PCFG10
#define BTN1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define BTN1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define BTN1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define BTN1_GetValue()           PORTBbits.RB1
#define BTN1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define BTN1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define BTN1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define BTN1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define BTN1_SetAnalogMode()      do { ANCON1bits.PCFG10 = 1; } while(0)
#define BTN1_SetDigitalMode()     do { ANCON1bits.PCFG10 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)

// get/set HRLED aliases
#define HRLED_TRIS                 TRISCbits.TRISC0
#define HRLED_LAT                  LATCbits.LATC0
#define HRLED_PORT                 PORTCbits.RC0
#define HRLED_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define HRLED_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define HRLED_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define HRLED_GetValue()           PORTCbits.RC0
#define HRLED_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define HRLED_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set LED0 aliases
#define LED0_TRIS                 TRISCbits.TRISC1
#define LED0_LAT                  LATCbits.LATC1
#define LED0_PORT                 PORTCbits.RC1
#define LED0_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED0_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED0_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED0_GetValue()           PORTCbits.RC1
#define LED0_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


#endif // PIN_MANAGER_H
/**
 End of File
*/