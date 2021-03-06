/* 
 * File:   tick.h
 * Author: vadmin
 *
 * Created on March 14, 2021, 2:46 PM
 */

#ifndef TICK_KEYBOARD_H
#define	TICK_KEYBOARD_H

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr0.h"

#define PROKEY_MASK 	0x08	//switch is not matching with demo board and final
#define ENTERKEY_MASK 	0x04
#define UPKEY_MASK 		0x02
#define DNKEY_MASK 		0x01
#define KEY_PRESS_COUNT		2

#define TICKCOUNT250mSEC	5	//10
#define TICKCOUNT1000mSEC	20
#define TICKCOUNT3000mSEC	60
#define TICKCOUNT10SEC		10
#define TICKCOUNT3MIN		180

#ifdef	__cplusplus
extern "C" {
#endif


    extern unsigned char keyDown;
    extern unsigned char keyHold;
    extern unsigned char keyStatus;

    extern bool tick100mSec;
    extern bool tick200mSec;
    extern bool tick3000mSec;
    extern bool tick1000mSec;
    extern bool tick3000mSec2;
    //extern bool tick36000mSec1;
    //extern bool tick36000mSec2;
    extern bool tick3min;
    extern bool tick6min;
    extern bool bToggleTick6min;
    extern bool bToggleBitFast;
    extern bool bToggleBitSlow;

    void TickKeyboardInit(void);
    void TickUpdate(void);
    unsigned char checkAndInrDcrChar(unsigned char* value, unsigned char upperLimit, unsigned char lowerLimit);
    unsigned char checkAndInrDcrInt(unsigned int* value, unsigned int upperLimit, unsigned int lowerLimit);

#ifdef	__cplusplus
}
#endif

#endif	/* TICK_KEYBOARD_H */

