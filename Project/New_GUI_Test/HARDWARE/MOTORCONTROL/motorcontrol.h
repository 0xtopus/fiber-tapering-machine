#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H

#include "sys.h"

#define GET_CLOSER 0
#define GET_AWAY   1

#define DUAL_MODE  0
#define LEFT_MODE  1
#define RIGHT_MODE 2

typedef struct 
{
    u8 mode;         // 0: All motors rotate; 1: Left motor rotates; 2: Right motor rotates
    u16 set_left_speed;     // Left motor speed to be set, equals to reload value of Timer
    u16 set_right_speed;    // Right motor speed to be set, equals to reload value of Timer
    u16 real_left_speed;    // Realtime Left motor speed (reload value of timer), unless it is 0 which means stop
    u16 real_right_speed;   // Realtime Right motor speed (reload value of timer), unless it is 0 which means stop
    u8 direction;    // 0: Get closer; 1: Go reversely
    u8 enable;       // 0: Disable; 1: Enable
} MotorControlStruct;

extern MotorControlStruct MotorConfig;

u8 Motor_Start(MotorControlStruct* MotorConfig);
u8 Motor_Stop(MotorControlStruct* MotorConfig);
u8 ChangeDirection(MotorControlStruct *pMotorConfig);
u16 ChangeSpeed(MotorControlStruct *pMotorConfig, u16 set_value);
u16 UpdateRealSpeed(MotorControlStruct *pMotorConfig, u16 new_speed);
char* Int2String(int num,char *str);
int String2Int(char *str);

#endif
