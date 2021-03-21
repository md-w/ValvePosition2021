/* 
 * File:   eeprom_wrapper.h
 * Author: user
 *
 * Created on March 21, 2021, 10:18 PM
 */

#ifndef EEPROM_WRAPPER_H
#define	EEPROM_WRAPPER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void readByte(unsigned char* buffer, unsigned char addr, unsigned char nBytes);
    void writeByte(unsigned char* buffer, unsigned char addr, unsigned char nBytes);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_WRAPPER_H */

