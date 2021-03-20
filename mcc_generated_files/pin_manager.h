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
        Device            :  PIC18F45K20
        Driver Version    :  2.11
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

// get/set channel_AN0 aliases
#define channel_AN0_TRIS                 TRISAbits.TRISA0
#define channel_AN0_LAT                  LATAbits.LATA0
#define channel_AN0_PORT                 PORTAbits.RA0
#define channel_AN0_ANS                  ANSELbits.ANS0
#define channel_AN0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_AN0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_AN0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_AN0_GetValue()           PORTAbits.RA0
#define channel_AN0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_AN0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_AN0_SetAnalogMode()      do { ANSELbits.ANS0 = 1; } while(0)
#define channel_AN0_SetDigitalMode()     do { ANSELbits.ANS0 = 0; } while(0)

// get/set channel_AN1 aliases
#define channel_AN1_TRIS                 TRISAbits.TRISA1
#define channel_AN1_LAT                  LATAbits.LATA1
#define channel_AN1_PORT                 PORTAbits.RA1
#define channel_AN1_ANS                  ANSELbits.ANS1
#define channel_AN1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define channel_AN1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define channel_AN1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define channel_AN1_GetValue()           PORTAbits.RA1
#define channel_AN1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define channel_AN1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define channel_AN1_SetAnalogMode()      do { ANSELbits.ANS1 = 1; } while(0)
#define channel_AN1_SetDigitalMode()     do { ANSELbits.ANS1 = 0; } while(0)

// get/set channel_AN2 aliases
#define channel_AN2_TRIS                 TRISAbits.TRISA2
#define channel_AN2_LAT                  LATAbits.LATA2
#define channel_AN2_PORT                 PORTAbits.RA2
#define channel_AN2_ANS                  ANSELbits.ANS2
#define channel_AN2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define channel_AN2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define channel_AN2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define channel_AN2_GetValue()           PORTAbits.RA2
#define channel_AN2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define channel_AN2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define channel_AN2_SetAnalogMode()      do { ANSELbits.ANS2 = 1; } while(0)
#define channel_AN2_SetDigitalMode()     do { ANSELbits.ANS2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELbits.ANS3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELbits.ANS3 = 0; } while(0)

// get/set O_AUTO_MAN aliases
#define O_AUTO_MAN_TRIS                 TRISBbits.TRISB4
#define O_AUTO_MAN_LAT                  LATBbits.LATB4
#define O_AUTO_MAN_PORT                 PORTBbits.RB4
#define O_AUTO_MAN_WPU                  WPUBbits.WPUB4
#define O_AUTO_MAN_ANS                  ANSELHbits.ANS11
#define O_AUTO_MAN_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define O_AUTO_MAN_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define O_AUTO_MAN_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define O_AUTO_MAN_GetValue()           PORTBbits.RB4
#define O_AUTO_MAN_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define O_AUTO_MAN_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define O_AUTO_MAN_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define O_AUTO_MAN_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define O_AUTO_MAN_SetAnalogMode()      do { ANSELHbits.ANS11 = 1; } while(0)
#define O_AUTO_MAN_SetDigitalMode()     do { ANSELHbits.ANS11 = 0; } while(0)

// get/set O_STOP aliases
#define O_STOP_TRIS                 TRISBbits.TRISB5
#define O_STOP_LAT                  LATBbits.LATB5
#define O_STOP_PORT                 PORTBbits.RB5
#define O_STOP_WPU                  WPUBbits.WPUB5
#define O_STOP_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define O_STOP_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define O_STOP_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define O_STOP_GetValue()           PORTBbits.RB5
#define O_STOP_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define O_STOP_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define O_STOP_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define O_STOP_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)

// get/set O_REV aliases
#define O_REV_TRIS                 TRISBbits.TRISB6
#define O_REV_LAT                  LATBbits.LATB6
#define O_REV_PORT                 PORTBbits.RB6
#define O_REV_WPU                  WPUBbits.WPUB6
#define O_REV_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define O_REV_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define O_REV_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define O_REV_GetValue()           PORTBbits.RB6
#define O_REV_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define O_REV_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define O_REV_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define O_REV_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set O_FORWD aliases
#define O_FORWD_TRIS                 TRISBbits.TRISB7
#define O_FORWD_LAT                  LATBbits.LATB7
#define O_FORWD_PORT                 PORTBbits.RB7
#define O_FORWD_WPU                  WPUBbits.WPUB7
#define O_FORWD_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define O_FORWD_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define O_FORWD_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define O_FORWD_GetValue()           PORTBbits.RB7
#define O_FORWD_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define O_FORWD_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define O_FORWD_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define O_FORWD_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

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

// get/set O_RXTX_CONTROL aliases
#define O_RXTX_CONTROL_TRIS                 TRISDbits.TRISD0
#define O_RXTX_CONTROL_LAT                  LATDbits.LATD0
#define O_RXTX_CONTROL_PORT                 PORTDbits.RD0
#define O_RXTX_CONTROL_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define O_RXTX_CONTROL_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define O_RXTX_CONTROL_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define O_RXTX_CONTROL_GetValue()           PORTDbits.RD0
#define O_RXTX_CONTROL_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define O_RXTX_CONTROL_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set I_SW1 aliases
#define I_SW1_TRIS                 TRISDbits.TRISD1
#define I_SW1_LAT                  LATDbits.LATD1
#define I_SW1_PORT                 PORTDbits.RD1
#define I_SW1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define I_SW1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define I_SW1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define I_SW1_GetValue()           PORTDbits.RD1
#define I_SW1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define I_SW1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set I_SW2 aliases
#define I_SW2_TRIS                 TRISDbits.TRISD2
#define I_SW2_LAT                  LATDbits.LATD2
#define I_SW2_PORT                 PORTDbits.RD2
#define I_SW2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define I_SW2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define I_SW2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define I_SW2_GetValue()           PORTDbits.RD2
#define I_SW2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define I_SW2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set I_SW3 aliases
#define I_SW3_TRIS                 TRISDbits.TRISD3
#define I_SW3_LAT                  LATDbits.LATD3
#define I_SW3_PORT                 PORTDbits.RD3
#define I_SW3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define I_SW3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define I_SW3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define I_SW3_GetValue()           PORTDbits.RD3
#define I_SW3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define I_SW3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

// get/set I_SW4 aliases
#define I_SW4_TRIS                 TRISDbits.TRISD4
#define I_SW4_LAT                  LATDbits.LATD4
#define I_SW4_PORT                 PORTDbits.RD4
#define I_SW4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define I_SW4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define I_SW4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define I_SW4_GetValue()           PORTDbits.RD4
#define I_SW4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define I_SW4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)

// get/set O_LCD_EN aliases
#define O_LCD_EN_TRIS                 TRISDbits.TRISD6
#define O_LCD_EN_LAT                  LATDbits.LATD6
#define O_LCD_EN_PORT                 PORTDbits.RD6
#define O_LCD_EN_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define O_LCD_EN_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define O_LCD_EN_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define O_LCD_EN_GetValue()           PORTDbits.RD6
#define O_LCD_EN_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define O_LCD_EN_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)

// get/set O_LCD_STRB aliases
#define O_LCD_STRB_TRIS                 TRISDbits.TRISD7
#define O_LCD_STRB_LAT                  LATDbits.LATD7
#define O_LCD_STRB_PORT                 PORTDbits.RD7
#define O_LCD_STRB_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define O_LCD_STRB_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define O_LCD_STRB_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define O_LCD_STRB_GetValue()           PORTDbits.RD7
#define O_LCD_STRB_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define O_LCD_STRB_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)

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