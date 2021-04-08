/* 
 * File:   display_lcd.h
 * Author: vadmin
 *
 * Created on March 14, 2021, 4:12 PM
 */

#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H
#define DISP_MODULE_SIZE    3
//#define LED_DISP_OFFSET     0 //This is not working use with caution
//#define LCD_DISP_OFFSET     1
#define rom const
#ifdef	__cplusplus
extern "C" {
#endif

    void directAssignLED(unsigned char segmentValue, unsigned char digitNo);
    void directAssignLED0(unsigned char segmentValue);
    void directAssignLED2(unsigned char segmentValue);
    void directOrWithDisplayLED(unsigned char segmentValue, unsigned char digitNo);
    void directAndWithDisplayLED(unsigned char segmentValue, unsigned char digitNo);
    void gotoRCLcd(unsigned char lineNo, unsigned char col);
    void gotoHomeLCD(void);
    void clearLCD(void);
    void putCharLCD(char byte);
    void putBlank(char byte, char number);
    void putsRomLCD(rom char *s);
    void putsLCD(char *s);
    void putIntLCD(unsigned int hexData, unsigned char digitsToDisplay);
    void putIntLCD0(unsigned int hexData, unsigned char digitsToDisplay);
    void resetLCD(void);
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_LCD_H */

