#include "pwm_handler.h"
#include "mcc_generated_files/pin_manager.h"


void initPWM(void)
{
	/*
	CCP1CON:
	bit 7-6 Unimplemented: Read as '0'
	bit 5-4
		DCxB1:DCxB0: PWM Duty Cycle bit1 and bit0
		Capture mode:Unused
		Compare mode:Unused
		PWM mode:
		These bits are the two LSbs (bit1 and bit0) of the 10-bit PWM duty cycle. The upper eight bits
		(DCx9:DCx2) of the duty cycle are found in CCPRxL.
	bit 3-0
		CCPxM3:CCPxM0: CCPx Mode Select bits
		0000 = Capture/Compare/PWM disabled (resets CCPx module)
		0001 = Reserved
		0010 = Compare mode, toggle output on match (CCPxIF bit is set)
		0011 = Reserved
		0100 = Capture mode, every falling edge
		0101 = Capture mode, every rising edge
		0110 = Capture mode, every 4th rising edge
		0111 = Capture mode, every 16th rising edge
		1000 = Compare mode,
				Initialize CCP pin Low, on compare match force CCP pin High (CCPIF bit is set)
		1001 = Compare mode,
				Initialize CCP pin High, on compare match force CCP pin Low (CCPIF bit is set)
		1010 = Compare mode,
				Generate software interrupt on compare match (CCPIF bit is set, CCP pin is unaffected)
		1011 = Compare mode,
				Trigger special event (CCPIF bit is set)
		11xx = PWM mode
	T2CON:
	bit 7 Unimplemented: Read as '0'
	bit 6-3
		TOUTPS3:TOUTPS0: Timer2 Output Postscale Select bits
			0000 = 1:1 Postscale
			0001 = 1:2 Postscale
			?
			?
			?
			1111 = 1:16 Postscale
	bit 2
		TMR2ON: Timer2 On bit
			1 = Timer2 is on
			0 = Timer2 is off
	bit 1-0
		T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
			00 = Prescaler is 1
			01 = Prescaler is 4
			1x = Prescaler is 16
	Name 	Bit 7	Bit 6	Bit 5	Bit 4	Bit 3	Bit 2	Bit 1	Bit 0	POR/BOR		RESET
	INTCON	GIE		PEIE	TMR0IE	INT0IE	RBIE	TMR0IF	INT0IF	RBIF	0000 000x	0000 000u
			/GIEH	/GIEL
	PIR1	PSPIF	ADIF	RCIF	TXIF	SSPIF 	CP1IF	TMR2IF	TMR1IF	0000 0000	0000 0000
	PIE1	PSPIE	ADIE	RCIE	TXIE	SSPIE	CCP1IE	TMR2IE	TMR1IE	0000 0000	0000 0000
	IPR1	PSPIP	ADIP	RCIP	TXIP	SSPIP	CCP1IP	TMR2IP	TMR1IP	0000 0000	0000 0000
	TMR2	Timer2 Module Register											0000 0000	0000 0000
	T2CON 	? 		TOUTPS3	TOUTPS2	TOUTPS1	TOUTPS0	TMR2ON	T2CKPS1	T2CKPS0 -000 0000	-000 0000
	PR2		Timer2 Period Register											1111 1111	1111 1111

	*/
	PR2 = 0xFF;
			   //76543210			   
	CCP1CON =  0b00001100;
	O_PWM_OUT_SetDigitalOutput();
			   //76543210
	T2CON =    0b01111110;
	CCPR1L = 0xFF;
}
void setPWMDuty(unsigned int iVal)
{
	if(iVal > 1023)
		iVal = 1023;
	if(iVal < 204)
		iVal = 204;
	
	
	CCPR1L = iVal >> 2;
	switch(iVal%2)
	{
		case 3:
			CCP1CONbits.DC1B1 = 1;
			CCP1CONbits.DC1B0 = 1;
		break;
		case 2:
			CCP1CONbits.DC1B1 = 1;
			CCP1CONbits.DC1B0 = 0;
		break;
		case 1:
			CCP1CONbits.DC1B1 = 0;
			CCP1CONbits.DC1B0 = 1;
		break;
		case 0:
			CCP1CONbits.DC1B1 = 0;
			CCP1CONbits.DC1B0 = 0;
		break;
	}	
}	
