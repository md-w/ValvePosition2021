/* 
 * File:   tick.h
 * Author: vadmin
 *
 * Created on March 14, 2021, 2:46 PM
 */

#ifndef TICK_H
#define	TICK_H

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr0.h"

#ifdef	__cplusplus
extern "C" {
#endif


extern unsigned char keyDown;
extern unsigned char keyHold;
extern unsigned char keyStatus;

#define KEY_PRESS_COUNT		2

#define TICKCOUNT250mSEC	5	//10
#define TICKCOUNT1000mSEC	20
#define TICKCOUNT3000mSEC	60
#define TICKCOUNT10SEC		10
#define TICKCOUNT3MIN		180


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

#define PROKEY_MASK 	0x01	//switch is not matching with demo board and final
#define ENTERKEY_MASK 	0x02
#define UPKEY_MASK 		0x04
#define DNKEY_MASK 		0x08

void TickInit(void);
void TickUpdate(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TICK_H */

