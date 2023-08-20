#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H

#include "sys.h"

#define GET_CLOSER 0
#define GET_AWAY   1

#define RIGHT_MOTOR 1
#define LEFT_MOTOR  0

typedef enum  
{
    SET_LEFT_SPEED = 0,
    SET_RIGHT_SPEED,
    REAL_LEFT_SPEED,
    REAL_RIGHT_SPEED
} MotorItems;

typedef struct 
{
    u16 set_left_speed;     // Left motor speed to be set, equals to reload value of Timer
    u16 set_right_speed;    // Right motor speed to be set, equals to reload value of Timer
    u16 real_left_speed;    // Realtime Left motor speed (reload value of timer), unless it is 0 which means stop
    u16 real_right_speed;   // Realtime Right motor speed (reload value of timer), unless it is 0 which means stop
    u8 direction;    // 0: Get closer; 1: Go reversely
} MotorControlStruct;

extern MotorControlStruct MotorConfig;

u8 MotorInit(void);
u8 ChangeDirection(void);
u8 StopSpecificMotor(u8 the_given_motor);
u8 StartSpecificMotor(u8 the_given_motor);
u16 ChangeSpecificSpeed(u16 set_value, u8 the_given_motor);
u16 UpdateSpecificRealSpeed(u16 new_speed, u8 the_given_motor);
u16 GetMotorConfig(MotorItems item);
u16 SetMotorConfig(MotorItems item, u16 new_state);

char* Int2String(int num,char *str);
int String2Int(char *str);

#endif
