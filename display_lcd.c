#include "display_lcd.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/spi.h"
#include "mcc_generated_files/delay.h"

unsigned char dispBuffer[DISP_MODULE_SIZE] = {0,};

#define EnableLCD() 		O_LCD_EN_SetHigh()
#define DisableLCD()		O_LCD_EN_SetLow()

void SPIStrobeLCD(void) {
    O_LCD_STRB_SetHigh();
    DELAY_microseconds(32);
    O_LCD_STRB_SetLow();
}

void displayShiftInit(void) {
    DisableLCD();
    SPI_Initialize();
    SPI_Open(MASTER0_CONFIG);
}

void displayShift(void) {
    SPI_WriteBlock(dispBuffer, DISP_MODULE_SIZE);
    SPIStrobeLCD();
    EnableLCD();
	DELAY_milliseconds(2);
	DisableLCD();
}

void directAssignLCD(unsigned char segmentValue, unsigned char digitNo) {
    dispBuffer[digitNo + LCD_DISP_OFFSET] = segmentValue;
    dispBuffer[1 + LCD_DISP_OFFSET] &= ~0x40;
}

void directAssignLED(unsigned char segmentValue, unsigned char digitNo) {
    if (digitNo < (DISP_MODULE_SIZE - LED_DISP_OFFSET))
        dispBuffer[digitNo + LED_DISP_OFFSET] = segmentValue;
}

void directOrWithDisplayLED(unsigned char segmentValue, unsigned char digitNo) {
    if (digitNo < (DISP_MODULE_SIZE - LED_DISP_OFFSET))
        dispBuffer[digitNo + LED_DISP_OFFSET] = dispBuffer[digitNo + LED_DISP_OFFSET] | segmentValue;
}

void directAndWithDisplayLED(unsigned char segmentValue, unsigned char digitNo) {
    if (digitNo < (DISP_MODULE_SIZE - LED_DISP_OFFSET))
        dispBuffer[digitNo + LED_DISP_OFFSET] = dispBuffer[digitNo + LED_DISP_OFFSET] & segmentValue;
}

void sendCommandByteToLCD(unsigned char commandByte) {
    dispBuffer[0 + LCD_DISP_OFFSET] = commandByte;
    dispBuffer[1 + LCD_DISP_OFFSET] &= ~0x80;
    displayShift();
}

void sendDataByteToLCD(unsigned char dataByte) {
    dispBuffer[0 + LCD_DISP_OFFSET] = dataByte;
    dispBuffer[1 + LCD_DISP_OFFSET] |= ~0x80;
    displayShift();
}

void initLCD(void) {
    displayShiftInit();
    DELAY_milliseconds(25);
    sendCommandByteToLCD(0x38); //16 bit mode double line.
    DELAY_milliseconds(25);
    sendCommandByteToLCD(0x38);
    DELAY_milliseconds(25);
    sendCommandByteToLCD(0x38);

    //sendCommandByteToLCD(0x0F);	////on display + blink cursor cursor

    sendCommandByteToLCD(0x0C); ////on display + hide cursor
    DELAY_milliseconds(25);
    sendCommandByteToLCD(0x02); //return cursor to home position
    DELAY_milliseconds(25);
    sendCommandByteToLCD(0x01); //clear display
    DELAY_milliseconds(25);
}

void resetLCD16x2(void) {
    //	sendCommandByteToLCD(0x38);	//16 bit mode double line.
    //	DelayMs(5);
    //	sendCommandByteToLCD(0x38);
    //	DelayMs(5);
    dispBuffer[1 + LCD_DISP_OFFSET] |= 0x40;
    displayShift();
    DELAY_milliseconds(20);
    dispBuffer[1 + LCD_DISP_OFFSET] &= ~0x40;
    displayShift();
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x38);
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x38);
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x38);
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x0C); //on display + hide cursor
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x02);
    DELAY_milliseconds(5);
    sendCommandByteToLCD(0x01); //clear display
    DELAY_milliseconds(5);
}

void gotoRCLcd(unsigned char lineNo, unsigned char col) {
    //sendCommandByteToLCD(0x02);	//return cursor to home position
    switch (lineNo) {
        case 0:
            sendCommandByteToLCD(0x00 + col + 0x80);
            break;
        case 1:
            sendCommandByteToLCD(0x40 + col + 0x80);
            break;
        case 2:
            sendCommandByteToLCD(0x10 + col + 0x80);
            break;
        case 3:
            sendCommandByteToLCD(0x50 + col + 0x80);
            break;
        default:
            sendCommandByteToLCD(0x40 + col + 0x80);
            break;
    }
}

void gotoHomeLCD(void) { //and clear
    //	sendCommandByteToLCD(0x01);	//clear display
    sendCommandByteToLCD(0x02); //return cursor to home position
}

void clearLCD(void) {
    sendCommandByteToLCD(0x01); //clear display
    DELAY_milliseconds(5);
}

void putCharLCD(char byte) {
    sendDataByteToLCD(byte);
}

void putBlank(char byte, char number) {
    while (number > 0) {
        putCharLCD(byte);
        number--;
    }
}

void putsRomLCD(char *s) {
    putsLCD(s);
}

void putsLCD(char *s) {
    char i;
    char j = 0;
    while (*s) {
        i = *s;
        putCharLCD(i);
        s++;
        j++;
        if (j > 20)
            break;
    }
}

void putIntLCD(unsigned int hexData, unsigned char digitsToDisplay) {
    unsigned char temp;
    unsigned char i = 1;
    unsigned char displayBuffer[5] = {' ', ' ', ' ', ' ', ' '}; //
    if (digitsToDisplay > 5) //max 5 digits can be displayed
        digitsToDisplay = 5;

    while (i <= 5) {
        if (i > digitsToDisplay)
            break;

        temp = (unsigned char) ((unsigned int) hexData % 10);
        displayBuffer[i - 1 + LCD_DISP_OFFSET] = (unsigned char) (temp) + 0x30;
        hexData = (hexData - (unsigned int) temp) / 10;
        if (hexData == 0) break;
        i++;
    }

    for (i = digitsToDisplay; i > 0; i--) {
        putCharLCD(displayBuffer[i - 1 + LCD_DISP_OFFSET]);
    }
}

void putIntLCD0(unsigned int hexData, unsigned char digitsToDisplay) {
    unsigned char temp;
    unsigned char i = 1;
    unsigned char displayBuffer[5] = {'0', '0', '0', '0', '0'}; //
    if (digitsToDisplay > 5) //max 5 digits can be displayed
        digitsToDisplay = 5;

    while (i <= 5) {
        if (i > digitsToDisplay)
            break;

        temp = (unsigned char) ((unsigned int) hexData % 10);
        displayBuffer[i - 1 + LCD_DISP_OFFSET] = (unsigned char) (temp) + 0x30;
        hexData = (hexData - (unsigned int) temp) / 10;
        if (hexData == 0) break;
        i++;
    }

    for (i = digitsToDisplay; i > 0; i--) {
        putCharLCD(displayBuffer[i - 1 + LCD_DISP_OFFSET]);
    }
}
