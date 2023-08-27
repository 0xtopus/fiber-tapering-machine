#include "motorcontrol.h"

//////////////////////////////////////////////////////////////////////////////////	 
// 电机控制代码	
// 为emWin图形界面提供控制底层硬件的API
////////////////////////////////////////////////////////////////////////////////// 	

MotorControlStruct MotorConfig;

/**
 * Init MotorConfig
 */
u8 MotorInit(void)
{
    MotorConfig.direction = GET_CLOSER;
    MotorConfig.real_left_speed = 0;
    MotorConfig.real_right_speed = 0;
    MotorConfig.set_left_speed = 5000;
    MotorConfig.set_right_speed = 5000;
    return 0;
}

/**
 * Change the direction
 * @return the latest direction
 */
u8 ChangeDirection(void)
{
    u8 leftflag = 0;
    u8 rightflag = 0;
    u16 temp_real_left_speed = MotorConfig.real_left_speed;
    u16 temp_real_right_speed = MotorConfig.real_right_speed;

    if (MotorConfig.real_left_speed)
    {
        StopSpecificMotor(LEFT_MOTOR);
        leftflag = 1;      
    } 

    if (MotorConfig.real_right_speed)
    {
        StopSpecificMotor(RIGHT_MOTOR);
        rightflag = 1;
    }

    MotorConfig.direction = !MotorConfig.direction;
    
    if (leftflag)
    {
        MotorConfig.real_left_speed = temp_real_left_speed;
        if (MotorConfig.direction)
        {
            TIM4_PWM_Init(MotorConfig.real_left_speed - 1, 108 - 1, GET_AWAY);   // TIM4CLK = APB1 * 2 = 108Mhz
        }
        else
        {
            TIM4_PWM_Init(MotorConfig.real_left_speed - 1, 108 - 1, GET_CLOSER);
        }
    }

    if (rightflag)
    {
        MotorConfig.real_right_speed = temp_real_right_speed;
        if (MotorConfig.direction)
        {
            TIM9_PWM_Init(MotorConfig.real_right_speed - 1, 216 - 1, GET_AWAY);  // TIM9CLK = APB2 * 2 = 216Mhz
        }
        else
        {
            TIM9_PWM_Init(MotorConfig.real_right_speed - 1, 216 - 1, GET_CLOSER);
        }
    }
    
    return MotorConfig.direction;
}

/**
 * Stop the specific motor. 
 * @param the_given_motor 0: the left motor, 1: the right motor.
 */
u8 StopSpecificMotor(u8 the_given_motor)
{
    if (the_given_motor && MotorConfig.real_right_speed) // If the right motor is chosen and running
    {
        if (MotorConfig.direction)
        {
            HAL_TIM_PWM_Stop(TIM_RIGHT_HANDLE, TIM_CHANNEL_1);
        }
        else
        {
            HAL_TIM_PWM_Stop(TIM_RIGHT_HANDLE, TIM_CHANNEL_2);
        }
        MotorConfig.real_right_speed = 0;
    }
    if (!the_given_motor && MotorConfig.real_left_speed) // If the left motor is chosen and running
    {
        if (MotorConfig.direction)
        {
            HAL_TIM_PWM_Stop(TIM_LEFT_HANDLE, TIM_CHANNEL_1);
        }
        else
        {
            HAL_TIM_PWM_Stop(TIM_LEFT_HANDLE, TIM_CHANNEL_2);
        }
        MotorConfig.real_left_speed = 0;
    }

    return 0;
}

/**
 * Start the specific motor. 
 * @param the_given_motor 0 means left motor, 1 means right motor.
 */
u8 StartSpecificMotor(u8 the_given_motor)
{
    // Right motor starts to run
    if (the_given_motor == RIGHT_MOTOR && !MotorConfig.real_right_speed)
    {
        if (MotorConfig.direction)
        {
            TIM9_PWM_Init(MotorConfig.set_right_speed - 1, 216 - 1, GET_AWAY);  // TIM9CLK = APB2 * 2 = 216Mhz
        }
        else
        {
            TIM9_PWM_Init(MotorConfig.set_right_speed - 1, 216 - 1, GET_CLOSER);
        }
        MotorConfig.real_right_speed = MotorConfig.set_right_speed;
    }
    // Left motor starts to run
    else if (the_given_motor == LEFT_MOTOR && !MotorConfig.real_left_speed)
    {
        if (MotorConfig.direction)
        {
            TIM4_PWM_Init(MotorConfig.set_left_speed - 1, 108 - 1, GET_AWAY);   // TIM4CLK = APB1 * 2 = 108Mhz
        }
        else
        {
            TIM4_PWM_Init(MotorConfig.set_left_speed - 1, 108 - 1, GET_CLOSER);
        }
        MotorConfig.real_left_speed = MotorConfig.set_left_speed;
    }


    return 0;
}


//! The frequency of timer is 108M/108=1M or 216M/216 = 1M,
//! if reload value = 1000, then PWM frequency is 1M/1000=1kHZ
//! So the range of PWM frequency is 200Hz ~ 2kHz
/**
 * Change the set speed of the given motor.
 * @param set_value the value set by user, which will be converted to speed.
 * @param the_given_motor 0: the left motor; 1: the right motor
 * @return the speed(actually the reload value for timer) set by user.
 */
u16 ChangeSpecificSpeed(u16 set_value, u8 the_given_motor)
{
    // Convert the set value to reload value
    u16 set_speed = -set_value + 5500;
    // Change the right motor speed
    if (the_given_motor == RIGHT_MOTOR)
    {
        MotorConfig.set_right_speed = set_speed;
        if (MotorConfig.real_right_speed)   // if the motor is operating
        {
            UpdateSpecificRealSpeed(set_speed, the_given_motor);
        }
    }
    // Change the left motor speed
    else if (the_given_motor == LEFT_MOTOR) // if the motor is operating
    {
        MotorConfig.set_left_speed = set_speed;
        if (MotorConfig.real_left_speed)
        {
            UpdateSpecificRealSpeed(set_speed, the_given_motor);
        }
    }
    return set_speed;
}

/**
 * Change realtime speed of the given motor.
 * @param new_speed new realtime speed.
 * @param the_given_motor 0: the left motor; 1: the right motor
 * @return the speed(actually the reload value for timer) set by user.
 */
u16 UpdateSpecificRealSpeed(u16 new_speed, u8 the_given_motor)
{
    StopSpecificMotor(the_given_motor);
    // If new_speed == 0, stop the motor
    if (!new_speed)
    {
        return 0;
    }

    StartSpecificMotor(the_given_motor);
    return new_speed;
}

/**
 * Get the state or value of a specific item of MotorConfig.
 * @param item the item of MotorConfig struct.
 * @return the item's state or value.
 */
u16 GetMotorConfig(MotorItems item)
{
    u16 res;
    switch (item)
    {
    case REAL_LEFT_SPEED:
        /* real_left_speed */
        res = MotorConfig.real_left_speed;
        break;

    case REAL_RIGHT_SPEED:
        /* real_right_speed */
        res = MotorConfig.real_right_speed;
        break;

    case SET_LEFT_SPEED:
        res = MotorConfig.set_left_speed;
        break;

    case SET_RIGHT_SPEED:
        res = MotorConfig.set_right_speed;
        break;

    case DIRECTION:
        res = MotorConfig.direction;
        break;
    }
    return res;
}

/**
 * Set a specific item of MotorConfig with a new state or value.
 * @param item the item of MotorConfig struct.
 * @param new_state new state or value.
 * @return the item's new state or value.
 */
u16 SetMotorConfig(MotorItems item, u16 new_state)
{
    u16 res;
    switch (item)
    {
    case REAL_LEFT_SPEED:
        /* real_left_speed */
        MotorConfig.real_left_speed = new_state;
        res = MotorConfig.real_left_speed;
        break;

    case REAL_RIGHT_SPEED:
        /* real_right_speed */
        MotorConfig.real_right_speed = new_state;
        res = MotorConfig.real_right_speed;
        break;

    case SET_LEFT_SPEED:
        /* set_left_speed  */
        MotorConfig.set_left_speed = new_state;
        res = MotorConfig.set_left_speed;
        break;

    case SET_RIGHT_SPEED:
        /* set_right_speed  */
        MotorConfig.set_right_speed = new_state;
        res = MotorConfig.set_right_speed;
        break;
        
    case DIRECTION:
        MotorConfig.direction = new_state;
        res = MotorConfig.direction;
    }

    return res;
}

/**
 * Integer(positive decimal) to String
 * @ref <https://www.runoob.com/w3cnote/c-int2str.html>
 * @param num
 * @param *str
 * @return The pointer to the converted string
 *
 */
char *Int2String(int num, char *str)
{
    int i = 0;
    int j = 0;
    do
    {
        str[i++] = num % 10 + 48;
        num /= 10;
    } while (num);

    str[i] = '\0';

    for (; j < i / 2; j++)
    {
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }

    return str;
}

/**
 * String to integer(positive decimal)
 * @ref <https://www.runoob.com/w3cnote/c-int2str.html>
 * @param *str
 * @return The integer
 */
int String2Int(char *str)
{
    long res = 0;

    while (*str >= 48 && *str <= 57)
    {
        res = 10 * res + *str++ - 48;
    }

    return (int)res;
}
/*********EOF*********/
