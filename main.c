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
        Device            :  PIC18F45K20
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
#include "tick_keyboard.h"
#include "eeprom_wrapper.h"
#include "display_lcd.h"
#include "pwm_handler.h"
#include "valve_position.h"

/*
                         Main application
 */

#define FILTER_POINTS	2
#define ANALOG_FULLSCALE	3450	//3455	//3175	//5000

unsigned char dispMainState = 0;
unsigned char ucPassword = PSWD + 5;
ST_SYSTEM_STATUS SystemStatus;
STRUCT_CONTROLLER_SP SetPoint;
ST_SYS_CALIBRATION SystemCal;
unsigned char scanState = 0;
unsigned int adcFilter = 0;
unsigned char adcFilterCount = FILTER_POINTS;
RELAY_OUT RelayOut;

void initVariables(void) {
    //SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostion;
    //SystemStatus.uiValvePostionOutput = 
    readByte((unsigned char *) &SetPoint, 0, sizeof (SetPoint));

    if ((SetPoint.ucHysteresis == 0) || (SetPoint.ucHysteresis > 100)) {
        SetPoint.ucHysteresis = 10;
    }
    if (!((SetPoint.isAnalogOrDigitalMode == true) || (SetPoint.isAnalogOrDigitalMode == false))) {
        SetPoint.isAnalogOrDigitalMode = false;
    }
    readByte((unsigned char *) &SystemCal, sizeof (SetPoint), sizeof (SystemCal));

    if ((0 == SystemCal.ValvePostion.ucSpan) || (SystemCal.ValvePostion.ucSpan > 200)) {
        SystemCal.ValvePostion.ucSpan = FIXED_SPAN;
    }
    if ((0 == SystemCal.ValvePostion.ucZero) || (SystemCal.ValvePostion.ucZero > 200)) {
        SystemCal.ValvePostion.ucZero = FIXED_ZERO;
    }
    if ((0 == SystemCal.ValvePostionSPAuto.ucSpan) || (SystemCal.ValvePostionSPAuto.ucSpan > 200)) {
        SystemCal.ValvePostionSPAuto.ucSpan = FIXED_SPAN;
    }
    if ((0 == SystemCal.ValvePostionSPAuto.ucZero) || (SystemCal.ValvePostionSPAuto.ucZero > 200)) {
        SystemCal.ValvePostionSPAuto.ucZero = FIXED_ZERO;
    }
    if ((0 == SystemCal.ValvePostionSPAuto.ucSpan) || (SystemCal.ValvePostionSPAuto.ucSpan > 200)) {
        SystemCal.ValvePostionSPAuto.ucSpan = FIXED_SPAN;
    }
    if ((0 == SystemCal.ValvePostionOutput.ucZero) || (SystemCal.ValvePostionOutput.ucZero > 200)) {
        SystemCal.ValvePostionOutput.ucZero = FIXED_ZERO;
    }
    RelayOut.ucValue = 0x00;
}

void displaySubStateMachineScan(void) {
    static unsigned char ucDispSubState = 0;
    gotoRCLcd(0, 0);
    if (SystemStatus.status.bits.isStop) {
        putsRomLCD((rom char *) "><");
    } else if (SystemStatus.status.bits.isMoveForward) {
        putsRomLCD((rom char *) ">>");
    } else if (SystemStatus.status.bits.isMoveReverse) {
        putsRomLCD((rom char *) "<<");
    } else {
        putsRomLCD((rom char *) "--");
    }
    putsRomLCD((rom char *) "ValvePos");
    putIntLCD(SystemStatus.uiValvePostion / 10, 3);
    putCharLCD('.');
    putIntLCD(SystemStatus.uiValvePostion % 10, 1);
    putCharLCD('%');
    gotoRCLcd(1, 0);
    switch (ucDispSubState) {
        case 0:
            if (SystemStatus.digital.bits.isTorqueFullOpen) {
                putsRomLCD((rom char *) "Torque full open");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        case 1:
            if (SystemStatus.digital.bits.isTorqueFullClose) {
                putsRomLCD((rom char *) "Torq. full close");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        case 2:
            if (SystemStatus.digital.bits.isValveFullOpen) {
                putsRomLCD((rom char *) "Valve full  open");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        case 3:
            if (SystemStatus.digital.bits.isValveFullClose) {
                putsRomLCD((rom char *) "Valve full close");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        case 4:
            if (SystemStatus.digital.bits.isMotorTempTrip) {
                putsRomLCD((rom char *) "Motor temp trip!");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        case 5:
            if (SystemStatus.digital.bits.isMotorOL) {
                putsRomLCD((rom char *) "Motor overload!!");
                if (tick3000mSec) {
                    tick3000mSec = 0;
                    ucDispSubState++;
                }
                break; //don't free fall
            } else {
                ucDispSubState++; //free fall
            }
            //no break;
        default:
            if (SystemStatus.digital.bits.isRemoteOrLocalMode) { //auto
                putsRomLCD((rom char *) "[AUTO] ");
            } else { //man
                putsRomLCD((rom char *) "[MAN ] ");
            }
            putsRomLCD((rom char *) "SP:");
            putIntLCD(SystemStatus.uiValvePostionSP / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostionSP % 10, 1);
            putCharLCD('%');
            if (tick3000mSec) {
                tick3000mSec = 0;
                ucDispSubState = 0;
            }
            break;
    }
}

unsigned char displaySubStateMachinePro(void) {
    static unsigned char dispSubState = 0;
    switch (dispSubState) {
        case 0:
            gotoRCLcd(0, 0);
            //						0123456789012345
            putsRomLCD((rom char *) "Program SP ?    ");
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if ((keyDown & DNKEY_MASK) || (keyDown & PROKEY_MASK)) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = 0;
                return 1;
            }
            break;
        case 1: // Program mode
            gotoRCLcd(0, 0);
            //  0123456789012345
            putsRomLCD((rom char *) "Program mode    ");
            gotoRCLcd(1, 0);
            putsRomLCD((rom char*) "Password:");
            putBlank(' ', 4);
            putIntLCD(ucPassword, 3);
            checkAndInrDcrChar(&ucPassword, 100, 1);
            if (keyDown & ENTERKEY_MASK) {
                keyHold = 0x00;
                keyDown = 0x00;
                if (PSWD == ucPassword) {
                    dispSubState++;
                    ucPassword = PSWD + 5;
                } else {
                    dispSubState = 0;
                    ucPassword = PSWD + 5;
                    return 1;
                }
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                ucPassword = PSWD + 5;
                dispSubState = 0;
                return 1;
            }
            break;
        case 2:
            gotoRCLcd(0, 0);
            //						0123456789012345
            putsRomLCD((rom char *) "Enter hysteresis");
            gotoRCLcd(1, 0);
            putBlank(' ', 10);
            putIntLCD(SetPoint.ucHysteresis / 10, 3);
            putCharLCD('.');
            putIntLCD(SetPoint.ucHysteresis % 10, 1);
            putCharLCD('%');
            checkAndInrDcrChar(&SetPoint.ucHysteresis, 100, 1);
            if (keyDown & ENTERKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = PRO_EXIT_STATE;
            }
            break;
        case 3:
            gotoRCLcd(0, 0);
            //						0123456789012345
            putsRomLCD((rom char *) "Select mode:-   ");
            gotoRCLcd(1, 0);
            putBlank(' ', 9);
            if (SetPoint.isAnalogOrDigitalMode == true) {
                putsRomLCD((rom char *) "Analog ");
            } else {
                putsRomLCD((rom char *) "Digital");
            }
            if ((keyDown & UPKEY_MASK) || (keyDown & DNKEY_MASK)) {
                keyDown = 0x00;
                keyHold = 0x00;
                if (SetPoint.isAnalogOrDigitalMode == true) {
                    SetPoint.isAnalogOrDigitalMode = false;
                } else {
                    SetPoint.isAnalogOrDigitalMode = true;
                }
            }
            if (keyDown & ENTERKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = PRO_EXIT_STATE;
            }
            break;
        case 4:
            gotoRCLcd(0, 0);
            //  0123456789012345
            putsRomLCD((rom char *) "Re Program  ?   ");
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = 2;
            }
            if ((keyDown & DNKEY_MASK) || (keyDown & ENTERKEY_MASK) || (keyDown & PROKEY_MASK)) {
                keyDown = 0x00;
                keyHold = 0x00;
                writeByte((unsigned char *) &SetPoint, 0, sizeof (SetPoint));
                dispSubState = 0;
                return 1;
            }
            break;
        default:
            dispSubState = 0;
            break;
    }
    return 0;
}

unsigned char displaySubSubStateMachineCal(unsigned char* pucVal) {
    checkAndInrDcrChar(pucVal, 200, 1);
    if (keyDown & ENTERKEY_MASK) {
        keyDown = 0x00;
        keyHold = 0x00;
        return 1;
    }
    return (0);
}

unsigned char displaySubStateMachineCal(void) {
    static unsigned char dispSubState = 0;
    switch (dispSubState) {
        case 0: // CALIBARTION MODE
            gotoRCLcd(0, 0);
            //  0123456789012345
            putsRomLCD((rom char *) "Calibration?    ");
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if ((keyDown & DNKEY_MASK) || (keyDown & PROKEY_MASK)) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = 0;
                return 1;
            }
            break;
        case 1: // CALIBARTION MODE
            gotoRCLcd(0, 0);
            //  0123456789012345
            putsRomLCD((rom char *) "Calibration     ");
            gotoRCLcd(1, 0);
            putsRomLCD((rom char*) "Password:");
            putBlank(' ', 4);
            putIntLCD(ucPassword, 3);
            checkAndInrDcrChar(&ucPassword, 100, 1);
            if (keyDown & ENTERKEY_MASK) {
                keyHold = 0x00;
                keyDown = 0x00;
                if (PSWD == ucPassword) {
                    ucPassword = PSWD + 5;
                    dispSubState++;
                } else {
                    ucPassword = PSWD + 5;
                    dispSubState = 0;
                    return 1;
                }
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                ucPassword = PSWD + 5;
                dispSubState = 0;
                return 1;
            }
            break;
        case 2: // Setpoint
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "SetPoint");
            putBlank(' ', 1);
            putsRomLCD((rom char *) "Cal?");
            putBlank(' ', 3);
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if (keyDown & DNKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState += 3;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 3: // Setpoint-Zero
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "SetPoint");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostionSPAuto / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostionSPAuto % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Zero ");
            putIntLCD(SystemCal.ValvePostionSPAuto.ucZero, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostionSPAuto.ucZero)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 4: // Setpoint-Span
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "SetPoint");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostionSPAuto / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostionSPAuto % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Span ");
            putIntLCD(SystemCal.ValvePostionSPAuto.ucSpan, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostionSPAuto.ucSpan)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 5: // Postion
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Position");
            putBlank(' ', 1);
            putsRomLCD((rom char *) "Cal?");
            putBlank(' ', 3);
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if (keyDown & DNKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState += 3;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 6: // Position-Zero
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Position");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostion / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostion % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Zero ");
            putIntLCD(SystemCal.ValvePostion.ucZero, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostion.ucZero)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 7: // Position-Span
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Position");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostion / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostion % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Span ");
            putIntLCD(SystemCal.ValvePostion.ucSpan, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostion.ucSpan)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 8: // Output
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Output  ");
            putBlank(' ', 1);
            putsRomLCD((rom char *) "Cal?");
            putBlank(' ', 3);
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState++;
            }
            if (keyDown & DNKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState += 3;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 9: // Output-Zero
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Output  ");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostionOutput / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostionOutput % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Zero ");
            putIntLCD(SystemCal.ValvePostion.ucZero, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostion.ucZero)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 10: // Output-Span
            gotoRCLcd(0, 0);
            putsRomLCD((rom char *) "Position");
            putBlank(' ', 1);
            putIntLCD(SystemStatus.uiValvePostionOutput / 10, 3);
            putCharLCD('.');
            putIntLCD(SystemStatus.uiValvePostionOutput % 10, 1);
            putCharLCD('%');
            gotoRCLcd(1, 0);
            putsRomLCD((rom char *) "Span ");
            putIntLCD(SystemCal.ValvePostion.ucSpan, 4);
            putBlank(' ', 7);
            if (displaySubSubStateMachineCal(&SystemCal.ValvePostion.ucSpan)) {
                dispSubState++;
            }
            if (keyDown & PROKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = CAL_EXIT_STATE;
            }
            break;
        case 11:
            gotoRCLcd(0, 0);
            //  0123456789012345
            putsRomLCD((rom char *) "Re Calibrate?   ");
            gotoRCLcd(1, 0);
            putBlank(' ', 6);
            putsRomLCD((rom char *) " Y(^) N(v)");
            if (keyDown & UPKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = 2;
            }
            if (keyDown & DNKEY_MASK) {
                keyDown = 0x00;
                keyHold = 0x00;
                dispSubState = 0;
                writeByte((unsigned char *) &SystemCal, sizeof (SetPoint), sizeof (SystemCal));
                return 1;
            }
            break;
        default:
            dispSubState = 0;
            break;
    }
    return 0;
}

void inputScanTask(void) {
    long lTemp;
    while (!ADC_IsConversionDone()) {

    }
    adcFilter += ADC_GetConversionResult();
    do {
        if (--adcFilterCount > 0) {
            break;
        }
        adcFilterCount = FILTER_POINTS;
        unsigned int uiTemp = adcFilter / FILTER_POINTS;
        adcFilter = 0;
        switch (scanState) {
            case 0: //uiValvePostionSPAuto
                //3.175	->	1023
                //Gain = 1 + 18000/(2200+330+22) = 8.05329
                //18*8.05329 = 144.959
                //20*18*8.05329 = 2899 -> 934
                //4*18*8.05329 = 580 ->   186
                lTemp = ((long) ((long) uiTemp - (long) 186 - (long) SystemCal.ValvePostionSPAuto.ucZero + (long) FIXED_ZERO)*((long) SystemCal.ValvePostionSPAuto.ucSpan));
                lTemp = (long) lTemp / (long) 100;
                if (lTemp <= 1) {
                    SystemStatus.uiValvePostionSPAuto = 0;
                } else if (lTemp <= 1000) {
                    SystemStatus.uiValvePostionSPAuto = (unsigned int) lTemp;
                } else {
                    SystemStatus.uiValvePostionSPAuto = 1000;
                }
                scanState++;
                ADC_SelectChannel(scanState);
                break;
            case 1: //uiValvePostion
                //lTemp = ((long)(uiTemp)*(long)SystemCal.AC0Comp.ucSpan)/(long)368;
                lTemp = ((long) ((long) uiTemp - (long) 186 - (long) SystemCal.ValvePostion.ucZero + (long) FIXED_ZERO)*((long) SystemCal.ValvePostion.ucSpan));
                lTemp = (long) lTemp / (long) 100;
                if (lTemp <= 1) {
                    SystemStatus.uiValvePostion = 0;
                } else if (lTemp <= 1000) {
                    SystemStatus.uiValvePostion = (unsigned int) lTemp;
                } else {
                    SystemStatus.uiValvePostion = 1000;
                }
                scanState = 0;
                ADC_SelectChannel(scanState);
                break;
        }
    } while (0);
    ADC_StartConversion();
}

void initOutput() {

}

void DigitalInputScan(void) {
    if (!I_FORWD_GetValue()) {
        SystemStatus.sw.bits.isSwForwardCommand = 1;
    } else {
        SystemStatus.sw.bits.isSwForwardCommand = 0;
    }
    if (!I_REV_GetValue()) {
        SystemStatus.sw.bits.isSwReverseCommand = 1;
    } else {
        SystemStatus.sw.bits.isSwReverseCommand = 0;
    }
    if (!I_STOP_GetValue()) {
        SystemStatus.sw.bits.isSwStopCommand = 1;
    } else {
        SystemStatus.sw.bits.isSwStopCommand = 0;
    }
    if (SystemStatus.sw.bits.isSwStopCommandHist && SystemStatus.sw.bits.isSwStopCommand) { //stop continuing so override all commands
        SystemStatus.sw.bits.isSwForwardCommand = 0;
        SystemStatus.sw.bits.isSwReverseCommand = 0;
    }
    if (SystemStatus.sw.bits.isSwForwardCommandHist && SystemStatus.sw.bits.isSwForwardCommand) { //forward continuing so override all commands
        SystemStatus.sw.bits.isSwReverseCommand = 0;
    }
    if (SystemStatus.sw.bits.isSwReverseCommandHist && SystemStatus.sw.bits.isSwReverseCommand) { //reverse continuing so override all commands
        SystemStatus.sw.bits.isSwForwardCommand = 0;
    }
    SystemStatus.sw.bits.isSwStopCommandHist = SystemStatus.sw.bits.isSwStopCommand;
    SystemStatus.sw.bits.isSwForwardCommandHist = SystemStatus.sw.bits.isSwForwardCommand;
    SystemStatus.sw.bits.isSwReverseCommandHist = SystemStatus.sw.bits.isSwReverseCommand;

    if (!I_TORQUE_FULL_OPEN_GetValue()) {
        SystemStatus.digital.bits.isTorqueFullOpen = 1;
    } else {
        SystemStatus.digital.bits.isTorqueFullOpen = 0;
    }

    if (!I_TORQUE_FULL_CLOSE_GetValue()) {
        SystemStatus.digital.bits.isTorqueFullClose = 1;
    } else {
        SystemStatus.digital.bits.isTorqueFullClose = 0;
    }

    if (!I_VALVE_FULL_OPEN_GetValue()) {
        SystemStatus.digital.bits.isValveFullOpen = 1;
    } else {
        SystemStatus.digital.bits.isValveFullOpen = 0;
    }

    if (!I_VALVE_FULL_CLOSE_GetValue()) {
        SystemStatus.digital.bits.isValveFullClose = 1;
    } else {
        SystemStatus.digital.bits.isValveFullClose = 0;
    }

    if (!I_AUTO_MAN_GetValue()) {
        SystemStatus.digital.bits.isRemoteOrLocalMode = 1;
    } else {
        SystemStatus.digital.bits.isRemoteOrLocalMode = 0;
    }

    if (!I_MOTOR_TRIP_GetValue()) {
        SystemStatus.digital.bits.isMotorTempTrip = 1;
    } else {
        SystemStatus.digital.bits.isMotorTempTrip = 0;
    }

    if (!I_MOTOR_OL_GetValue()) {
        SystemStatus.digital.bits.isMotorOL = 1;
    } else {
        SystemStatus.digital.bits.isMotorOL = 0;
    }

    if (!I_PLC_FORWD_GetValue()) {
        SystemStatus.plc.bits.isPlcForwardCommand = 1;
    } else {
        SystemStatus.plc.bits.isPlcForwardCommand = 0;
    }
    if (!I_PLC_REV_GetValue()) {
        SystemStatus.plc.bits.isPlcReverseCommand = 1;
    } else {
        SystemStatus.plc.bits.isPlcReverseCommand = 0;
    }
    if (!I_PLC_STOP_GetValue()) {
        SystemStatus.plc.bits.isPlcStopCommand = 1;
    } else {
        SystemStatus.plc.bits.isPlcStopCommand = 0;
    }
    if (SystemStatus.plc.bits.isPlcStopCommandHist && SystemStatus.plc.bits.isPlcStopCommand) { //stop continuing so override all commands
        SystemStatus.plc.bits.isPlcForwardCommand = 0;
        SystemStatus.plc.bits.isPlcReverseCommand = 0;
    }
    if (SystemStatus.plc.bits.isPlcForwardCommandHist && SystemStatus.plc.bits.isPlcForwardCommand) { //forward continuing so override all commands
        SystemStatus.plc.bits.isPlcReverseCommand = 0;
    }
    if (SystemStatus.plc.bits.isPlcReverseCommandHist && SystemStatus.plc.bits.isPlcReverseCommand) { //reverse continuing so override all commands
        SystemStatus.plc.bits.isPlcForwardCommand = 0;
    }
    SystemStatus.plc.bits.isPlcStopCommandHist = SystemStatus.plc.bits.isPlcStopCommand;
    SystemStatus.plc.bits.isPlcForwardCommandHist = SystemStatus.plc.bits.isPlcForwardCommand;
    SystemStatus.plc.bits.isPlcReverseCommandHist = SystemStatus.plc.bits.isPlcReverseCommand;


}

void SystemOutput(void) {

    if (SystemStatus.status.bits.isMoveForward) {
        RelayOut.bits.RELAY_OUT_FORWARD = 1;
        RelayOut.bits.RELAY_OUT_REVERSE = 0;
        //        O_ = 1;
        //        RELAY_OUT_REVERSE = 0;
    } else if (SystemStatus.status.bits.isMoveReverse) {
        //        RELAY_OUT_FORWARD = 0;
        //        RELAY_OUT_REVERSE = 1;
        RelayOut.bits.RELAY_OUT_FORWARD = 0;
        RelayOut.bits.RELAY_OUT_REVERSE = 1;
    } else {
        //        RELAY_OUT_FORWARD = 0;
        //        RELAY_OUT_REVERSE = 0;
        RelayOut.bits.RELAY_OUT_FORWARD = 0;
        RelayOut.bits.RELAY_OUT_REVERSE = 0;
        //SystemStatus.status.bits.isStop = 1;
    }
    if (SystemStatus.digital.bits.isRemoteOrLocalMode) {
        RelayOut.bits.AUTO_MAN = 1;

        //O_AUTO_MAN_SetHigh();
    } else {
        //O_AUTO_MAN_SetLow();
        RelayOut.bits.AUTO_MAN = 0;
    }
    directAssignLED2(RelayOut.ucValue);
}

void LEDOutput(void) {
    unsigned char ucLEDStatus = 0x00;
    if (SystemStatus.status.bits.isMoveForward) {
        ucLEDStatus |= 0x20;
        //ucLEDStatus |= 0x01;
    }
    if (SystemStatus.status.bits.isMoveReverse) {
        ucLEDStatus |= 0x10;
        //ucLEDStatus |= 0x02;
    }
    if (SystemStatus.status.bits.isStop) {
        ucLEDStatus |= 0x08;
        //ucLEDStatus |= 0x04;
    }
    if (SystemStatus.digital.bits.isValveFullOpen) {
        ucLEDStatus |= 0x04;
        //ucLEDStatus |= 0x08;
    }
    if (SystemStatus.digital.bits.isValveFullClose) {
        ucLEDStatus |= 0x02;
        //ucLEDStatus |= 0x10;
    }
    if (SystemStatus.digital.bits.isRemoteOrLocalMode) {
        ucLEDStatus |= 0x01;
        //ucLEDStatus |= 0x20;
    }
    directAssignLED(ucLEDStatus, 0);
}

void controllerAlgo(void) {
    //SystemStatus.status.bits.isMoveForward = 0;
    //SystemStatus.status.bits.isMoveReverse = 0;
    //SystemStatus.status.bits.isStop = 0;
    unsigned char isForward = 0x00;
    unsigned char isReverse = 0x00;

    if (SystemStatus.digital.bits.isTorqueFullOpen || SystemStatus.digital.bits.isValveFullOpen
            || SystemStatus.digital.bits.isTorqueFullClose || SystemStatus.digital.bits.isValveFullClose) {
        SystemStatus.status.bits.isStop = 1;
    }

    if (SystemStatus.digital.bits.isRemoteOrLocalMode) { //remote
        if (SetPoint.isAnalogOrDigitalMode) {
            SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostionSPAuto;
            if (SystemStatus.uiValvePostion > (SystemStatus.uiValvePostionSP + (unsigned int) SetPoint.ucHysteresis)) {
                isReverse = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            } else if ((SystemStatus.uiValvePostion + (unsigned int) SetPoint.ucHysteresis) < SystemStatus.uiValvePostionSP) {
                isForward = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            } else {
                isForward = 0;
                isReverse = 0;
                SystemStatus.status.bits.isStop = 1; //latch
            }            
        } else {
            SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostion;
            if (SystemStatus.plc.bits.isPlcStopCommand) {
                isForward = 0;
                isReverse = 0;
                SystemStatus.status.bits.isStop = 1; //latch
            } else if (SystemStatus.plc.bits.isPlcForwardCommand) {
                isForward = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            } else if (SystemStatus.plc.bits.isPlcReverseCommand) {
                isReverse = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            }
        }
    } else { //local
        SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostion;
        if (SystemStatus.sw.bits.isSwStopCommand) {
            isForward = 0;
            isReverse = 0;
            SystemStatus.status.bits.isStop = 1; //latch
        } else if (SystemStatus.sw.bits.isSwForwardCommand) {
            isForward = 1;
            SystemStatus.status.bits.isStop = 0; //remove latch
        } else if (SystemStatus.sw.bits.isSwReverseCommand) {
            isReverse = 1;
            SystemStatus.status.bits.isStop = 0; //remove latch
        }
    }

    if (isForward) {
        SystemStatus.status.bits.isMoveForward = 1;
        SystemStatus.status.bits.isMoveReverse = 0;
        isReverse = 0;
    } else if (isReverse) {
        SystemStatus.status.bits.isMoveForward = 0;
        SystemStatus.status.bits.isMoveReverse = 1;
        isForward = 0;
    } else {
        SystemStatus.status.bits.isMoveForward = 0;
        SystemStatus.status.bits.isMoveReverse = 0;
    }

    if (SystemStatus.digital.bits.isMotorTempTrip || SystemStatus.digital.bits.isMotorOL) {
        SystemStatus.status.bits.isStop = 1;
    }

    if (SystemStatus.status.bits.isStop) {
        SystemStatus.status.bits.isMoveForward = 0;
        SystemStatus.status.bits.isMoveReverse = 0;
    }
    
    if (SystemStatus.digital.bits.isTorqueFullOpen || SystemStatus.digital.bits.isValveFullOpen) {
        SystemStatus.status.bits.isMoveForward = 0;
    }

    if (SystemStatus.digital.bits.isTorqueFullClose || SystemStatus.digital.bits.isValveFullClose) {
        SystemStatus.status.bits.isMoveReverse = 0;
    }

    LEDOutput();
}

void controllerAlgo1(void) {
    //SystemStatus.status.bits.isMoveForward = 0;
    //SystemStatus.status.bits.isMoveReverse = 0;
    //SystemStatus.status.bits.isStop = 0;
    unsigned char isForward = 0x00;
    unsigned char isReverse = 0x00;

    if (SystemStatus.digital.bits.isTorqueFullOpen || SystemStatus.digital.bits.isValveFullOpen
            || SystemStatus.digital.bits.isTorqueFullClose || SystemStatus.digital.bits.isValveFullClose
            || SystemStatus.digital.bits.isMotorTempTrip ||
            SystemStatus.digital.bits.isMotorOL) {
        SystemStatus.status.bits.isStop = 1;
    }

    if (SystemStatus.digital.bits.isRemoteOrLocalMode) { //remote
        if (SetPoint.isAnalogOrDigitalMode) {
            //			if(SystemStatus.uiValvePostionSP < SystemStatus.uiValvePostionSPAuto){
            //				if(tick200mSec){
            //					tick200mSec = 0;
            //					SystemStatus.uiValvePostionSP++;
            //				}
            //			}else if(SystemStatus.uiValvePostionSP > SystemStatus.uiValvePostionSPAuto){
            //				if(tick200mSec){
            //					tick200mSec = 0;
            //					SystemStatus.uiValvePostionSP--;
            //				}
            //			}else{
            //				SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostionSPAuto;
            //			}
            SystemStatus.status.bits.isStop = 0; //latch
            SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostionSPAuto;
        } else {
            if (SystemStatus.plc.bits.isPlcStopCommand) {
                isForward = 0;
                isReverse = 0;
                SystemStatus.status.bits.isStop = 1; //latch
            } else if (SystemStatus.plc.bits.isPlcForwardCommand) {
                isForward = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            } else if (SystemStatus.plc.bits.isPlcReverseCommand) {
                isReverse = 1;
                SystemStatus.status.bits.isStop = 0; //remove latch
            }
        }
    } else { //local
        if (SystemStatus.sw.bits.isSwStopCommand) {
            isForward = 0;
            isReverse = 0;
            SystemStatus.status.bits.isStop = 1; //latch
        } else if (SystemStatus.sw.bits.isSwForwardCommand) {
            isForward = 1;
            SystemStatus.status.bits.isStop = 0; //remove latch
        } else if (SystemStatus.sw.bits.isSwReverseCommand) {
            isReverse = 1;
            SystemStatus.status.bits.isStop = 0; //remove latch
        }
    }

    if (SystemStatus.status.bits.isStop) {
        SystemStatus.status.bits.isMoveForward = 0;
        SystemStatus.status.bits.isMoveReverse = 0;
    } else {
        if (SetPoint.isAnalogOrDigitalMode && SystemStatus.digital.bits.isRemoteOrLocalMode) {
            if (SystemStatus.uiValvePostion > (SystemStatus.uiValvePostionSP + (unsigned int) SetPoint.ucHysteresis)) {
                SystemStatus.status.bits.isMoveForward = 0;
                SystemStatus.status.bits.isMoveReverse = 1;
            } else if ((SystemStatus.uiValvePostion + (unsigned int) SetPoint.ucHysteresis) < SystemStatus.uiValvePostionSP) {
                SystemStatus.status.bits.isMoveForward = 1;
                SystemStatus.status.bits.isMoveReverse = 0;
            } else {
                SystemStatus.status.bits.isMoveReverse = 0;
                SystemStatus.status.bits.isMoveForward = 0;
            }
        } else {
            SystemStatus.uiValvePostionSP = SystemStatus.uiValvePostion;
            if (isForward) {
                SystemStatus.status.bits.isMoveForward = 1;
                SystemStatus.status.bits.isMoveReverse = 0;
                isReverse = 0;
            } else if (isReverse) {
                SystemStatus.status.bits.isMoveForward = 0;
                SystemStatus.status.bits.isMoveReverse = 1;
                isForward = 0;
            } else {
                SystemStatus.status.bits.isMoveForward = 0;
                SystemStatus.status.bits.isMoveReverse = 0;
            }

        }
    }
    LEDOutput();
}

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

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    TickKeyboardInit();
    SPI_Open(MASTER0_CONFIG);
    resetLCD();
    gotoRCLcd(0, 0);
    putsRomLCD((rom char*) "Power on test..");
    gotoRCLcd(1, 0);
    putsRomLCD((rom char*) "...............");
    initVariables();
    SystemOutput();
    initPWM();
    setPWMDuty(204);
    ClrWdt();

    while (1) {
        if (tick100mSec) {
            tick100mSec = 0;
            inputScanTask();
            DigitalInputScan();
        }
        switch (dispMainState) {
            case 0:
                if (tick6min) {
                    tick6min = 0;
                    resetLCD();
                }
                controllerAlgo();
                displaySubStateMachineScan();
                if (keyDown & PROKEY_MASK) {
                    keyDown = 0x00;
                    keyHold = 0x00;
                    dispMainState++;
                }
                break;
            case 1:
                controllerAlgo();
                if (displaySubStateMachinePro()) {
                    dispMainState++;
                }
                break;
            case 2:
                if (displaySubStateMachineCal()) {
                    dispMainState = 0;
                }
                break;
            default:
                dispMainState = 0;
                break;
        }

        SystemStatus.uiValvePostionOutput = (unsigned int) (((long) 4 * (long) SystemStatus.uiValvePostion) / (long) 5 + (long) 204); //(1024-204)+204;//(SystemStatus.uiValvePostion*(1024-204)+204);
        setPWMDuty(SystemStatus.uiValvePostionOutput);
        SystemOutput();
        ClrWdt();
    }
}
/**
 End of File
 */