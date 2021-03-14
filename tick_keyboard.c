/*
 * File:   tick.c
 * Author: vadmin
 *
 * Created on March 14, 2021, 1:58 PM
 */

#include "tick_keyboard.h"
unsigned char keyDown = 0x00;
unsigned char keyHold = 0x00;
unsigned char keyStatus = 0x00;
unsigned char keyStateSaved = 0x00;
unsigned char keyPressCounter = KEY_PRESS_COUNT;
bool tick100mSec = 0;
bool tick3000mSec = 0;
bool tick3000mSec2 = 0;
bool tick200mSec = 0;
bool tick1000mSec = 0;
bool tick3min = 0;
bool tick6min = 0;
bool bToggleBitFast = 0;
bool bToggleBitSlow = 0;

void TickKeyboardInit(void) {
    TMR0_SetInterruptHandler(TickUpdate);
}

void TickUpdate(void) {
    static unsigned int uiTickCount = 0;
    if (uiTickCount < 3600 - 1) { //6*60*10ms = 6min
        uiTickCount++;
    } else {
        uiTickCount = 0;
        tick3000mSec = 1;
        tick3000mSec2 = 1;
        tick3min = 1;
        tick6min = 1;
    }
    tick100mSec = 1;
    if ((uiTickCount % 1800) == 0) {
        tick3min = 1;
    }
    if ((uiTickCount % 30) == 0) {
        tick3000mSec = 1;
        tick3000mSec2 = 1;
    }
    if ((uiTickCount % 10) == 0) { //1sec
        tick1000mSec = 1;
        bToggleBitSlow = !bToggleBitSlow;
    }
    if ((uiTickCount % 5) == 0) { //500msec
        bToggleBitFast = !bToggleBitFast;
    }
    if ((uiTickCount % 2) == 0) { //200msec
        tick200mSec = 1;
    }


    keyStatus = 0b00000000;
    if (!I_SW1_GetValue())
        keyStatus |= 0b00000001;
    if (!I_SW2_GetValue())
        keyStatus |= 0b00000010;
    if (!I_SW3_GetValue())
        keyStatus |= 0b00000100;
    if (!I_SW4_GetValue())
        keyStatus |= 0b00001000;

    keyDown |= (~keyStateSaved & keyStatus);
    keyStateSaved = keyStatus;

    if (keyStatus != 0x00) {
        if (keyPressCounter == 0x00) {
            keyPressCounter = KEY_PRESS_COUNT;
            keyHold |= keyStatus;
        } else {
            keyPressCounter--;
        }
    } else {
        keyPressCounter = KEY_PRESS_COUNT;
    }
}

unsigned char checkAndInrDcrInt(unsigned int* value, unsigned int upperLimit, unsigned int lowerLimit) { //Smooth
    if (!(((*value) >= lowerLimit) && ((*value) <= upperLimit))) {
        (*value) = (upperLimit + lowerLimit) / 2;
    }
    if ((keyDown & UPKEY_MASK) || (keyHold & UPKEY_MASK)) { //up key
        keyDown = 0x00;
        keyHold = 0x00;
        if ((*value) < upperLimit)
            (*value)++;
        else
            (*value) = upperLimit;
        return 1;
    }
    if ((keyDown & DNKEY_MASK) || (keyHold & DNKEY_MASK)) { //down key
        keyDown = 0x00;
        keyHold = 0x00;
        if ((*value) > lowerLimit)
            (*value)--;
        else
            (*value) = lowerLimit;
        return 1;
    }
    return 0;
}

unsigned char checkAndInrDcrChar(unsigned char* value, unsigned char upperLimit, unsigned char lowerLimit) { //Smooth

    if (!(((*value) >= lowerLimit) && ((*value) <= upperLimit))) {
        (*value) = (upperLimit + lowerLimit) / 2;
    }
    if ((keyDown & UPKEY_MASK) || (keyHold & UPKEY_MASK)) { //up key
        keyDown = 0x00;
        keyHold = 0x00;
        if ((*value) < upperLimit)
            (*value)++;
        else
            (*value) = upperLimit;
        return 1;
    }
    if ((keyDown & DNKEY_MASK) || (keyHold & DNKEY_MASK)) { //down key
        keyDown = 0x00;
        keyHold = 0x00;
        if ((*value) > lowerLimit)
            (*value)--;
        else
            (*value) = lowerLimit;
        return 1;
    }
    return 0;

}