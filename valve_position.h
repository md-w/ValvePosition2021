/* 
 * File:   valve_position.h
 * Author: user
 *
 * Created on March 21, 2021, 9:48 PM
 */

#ifndef VALVE_POSITION_H
#define	VALVE_POSITION_H

#define PRO_EXIT_STATE				4
#define CAL_EXIT_STATE				11
#define	FIXED_SPAN					100
#define	FIXED_ZERO					100
#define PSWD                        10

#ifdef	__cplusplus
extern "C" {
#endif

    typedef union _SW_STATUS {

        struct {
            unsigned int isSwForwardCommand : 1;
            unsigned int isSwReverseCommand : 1;
            unsigned int isSwStopCommand : 1;
            unsigned int b4 : 1;

            unsigned int isSwForwardCommandHist : 1;
            unsigned int isSwReverseCommandHist : 1;
            unsigned int isSwStopCommandHist : 1;
            unsigned int b8 : 1;

            //unsigned int isSwForwardCommandHold: 	1;
            //unsigned int isSwReverseCommandHold: 	1;
        } bits;
        unsigned char ucValue;
    } SW_STATUS;

    typedef union _DIGITAL_STATUS {

        struct {
            unsigned int isTorqueFullOpen : 1;
            unsigned int isTorqueFullClose : 1;
            unsigned int isValveFullOpen : 1;
            unsigned int isValveFullClose : 1;
            unsigned int isRemoteOrLocalMode : 1;
            unsigned int isMotorTempTrip : 1;
            unsigned int isMotorOL : 1;

        } bits;
        unsigned char ucValue;
    } DIGITAL_STATUS;

    typedef union _PLC_STATUS {

        struct {
            unsigned int isPlcForwardCommand : 1;
            unsigned int isPlcReverseCommand : 1;
            unsigned int isPlcStopCommand : 1;
            unsigned int b4 : 1;
            unsigned int isPlcForwardCommandHist : 1;
            unsigned int isPlcReverseCommandHist : 1;
            unsigned int isPlcStopCommandHist : 1;
            unsigned int b8 : 1;

            //unsigned int isPlcForwardCommandHold:	1;
            //unsigned int isPlcReverseCommandHold:	1;
        } bits;
        unsigned char ucValue;
    } PLC_STATUS;

    typedef union _SYS_STATUS {

        struct {
            unsigned int isMoveForward : 1;
            unsigned int isMoveReverse : 1;
            unsigned int isStop : 1;
        } bits;
        unsigned char ucValue;
    } SYS_STATUS;

    typedef struct _structControllerSP {
        unsigned char ucHysteresis;
        bool isAnalogOrDigitalMode;
    } STRUCT_CONTROLLER_SP;

    typedef struct _stCal {
        unsigned char ucSpan;
        unsigned char ucZero;
    } ST_CAL;

    typedef struct _stSystemStatus {
        unsigned int uiValvePostion;
        unsigned int uiValvePostionSPAuto;
        //unsigned int	uiValvePostionSPManual;
        unsigned int uiValvePostionSP;
        unsigned int uiValvePostionOutput;
        SYS_STATUS status;
        SW_STATUS sw;
        DIGITAL_STATUS digital;
        PLC_STATUS plc;
    } ST_SYSTEM_STATUS;

    typedef struct stSysCalibration {
        ST_CAL ValvePostion;
        ST_CAL ValvePostionSPAuto;
        ST_CAL ValvePostionOutput;
    } ST_SYS_CALIBRATION;
    
    typedef union _RELAY_OUT {

        struct {
            unsigned int RELAY_OUT_FORWARD : 1;
            unsigned int RELAY_OUT_REVERSE : 1;
            unsigned int AUTO_MAN : 1;
            unsigned int b4 : 1;

            //unsigned int isSwForwardCommandHold: 	1;
            //unsigned int isSwReverseCommandHold: 	1;
        } bits;
        unsigned char ucValue;
    } RELAY_OUT;
#ifdef	__cplusplus
}
#endif

#endif	/* VALVE_POSITION_H */

