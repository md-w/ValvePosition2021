/* 
 * File:   display_lcd.h
 * Author: vadmin
 *
 * Created on March 14, 2021, 4:12 PM
 */

#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DISP_MODULE_SIZE	2
#define LED_DISP_OFFSET	1
#define LCD_DISP_OFFSET	0

    void initLCD(void);
    void gotoRCLcd(unsigned char lineNo, unsigned char col);
    //void gotoAddrLCD(unsigned char addr);
    void directAssignLED(unsigned char segmentValue, unsigned char digitNo);
    void digitAssignLED(unsigned char segmentValue, unsigned char digitNo);
    void directAssignLCD(unsigned char segmentValue, unsigned char digitNo);

    void directOrWithDisplayLED(unsigned char segmentValue, unsigned char digitNo);
    void directAndWithDisplayLED(unsigned char segmentValue, unsigned char digitNo);

    void displayInt(unsigned int hexData, unsigned char dotPosition);
    void displayShift(void);
    void putsRomLCD(char *s);
    void putsLCD(char *s);
    void putCharLCD(char byte);
    void putBlank(char byte, char number);
    //void putRepeateCharLCD(char byte, unsigned char ucCount);
    void resetLCD16x2(void);
    void putIntLCD(unsigned int hexData, unsigned char digitsToDisplay);
    void putIntLCD0(unsigned int hexData, unsigned char digitsToDisplay);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_LCD_H */

