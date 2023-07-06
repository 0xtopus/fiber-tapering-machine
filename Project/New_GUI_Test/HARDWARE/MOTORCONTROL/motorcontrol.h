#ifndef __MOTORCONTROL_H
#define __MOTORCONTROL_H

#include "sys.h"

typedef struct 
{
    u8 mode;         // 0: All motors rotate; 1: Left motor rotates; 2: Right motor rotates
    u16 left_speed;  // Left motor speed, actually it is the freqency of PWM wave
    u16 right_speed; // Right motor speed, actually it is the freqency of PWM wave
    u8 direction;    // 0: Get closer; 1: Go reversely
    u8 enable;       // 0: Disable; 1: Enable
} MotorControlStruct;

extern MotorControlStruct MotorConfig;

u8 Motor_Start(MotorControlStruct* MotorConfig);
u8 Motor_Stop(MotorControlStruct* MotorConfig);

#endif
