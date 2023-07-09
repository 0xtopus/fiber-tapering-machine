#include "motorcontrol.h"
#include "led.h"
#include "timer.h"

MotorControlStruct MotorConfig = {0, 5000, 5000, 0, 0, 0, 0};

/**
 * Start the motors as configurated.
 * @param *pMotorConfig
 * @return The current mode of MotorConfig
 */
u8 Motor_Start(MotorControlStruct *pMotorConfig)
{

    if (pMotorConfig->enable)
    {
        return pMotorConfig->mode;
    }

    switch (pMotorConfig->mode)
    {
    case 0:
        // Both motors start working
        {
            if (pMotorConfig->direction) // Go reversely
            {
                TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_AWAY);
                TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_AWAY);
                //! The frequency of timer is 108M/108=1M,
                //! if reload value = 1000, then PWM frequency is 1M/1000=1kHZ
                //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            else // Get closer
            {
                TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_CLOSER);
                TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_CLOSER);
                //! The frequency of timer is 108M/108=1M,
                //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            pMotorConfig->real_left_speed = pMotorConfig->set_left_speed;
            pMotorConfig->real_right_speed = pMotorConfig->set_right_speed;
            break;
        }
    case 1:
        // Only left motor starts working
        {
            if (pMotorConfig->direction) // Go reversely
            {
                TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_AWAY); //! The frequency of timer is 108M/108=1M,
                                                                //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            else // Get closer
            {
                TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_CLOSER); //! The frequency of timer is 108M/108=1M,
                                                                  //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                  //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            pMotorConfig->real_left_speed = pMotorConfig->set_left_speed;
            break;
        }
    case 2:
        // Only right motor starts working
        {
            // TODO speed设置
            printf("\r\nhehe\r\n");
            if (pMotorConfig->direction) // Go reversely
            {
                TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_AWAY); //! The frequency of timer is 108M/108=1M,
                                                                //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            else // Get closer
            {
                TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_CLOSER); //! The frequency of timer is 108M/108=1M,
                                                                  //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                  //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            pMotorConfig->real_right_speed = pMotorConfig->set_right_speed;
            break;
        }
    }

    pMotorConfig->enable = 1;
    
    // Flash green LED
    LED1(0);
    LED0(1);
    return pMotorConfig->mode;
}

/**
 * Stop all motors.
 * @param *pMotorConfig
 * @return The current mode of MotorConfig
 */
u8 Motor_Stop(MotorControlStruct *pMotorConfig)
{
    if (!pMotorConfig->enable)
    {
        return pMotorConfig->mode;
    }

    switch (pMotorConfig->mode)
    {
    case 0:
        /* Stop both motors */
        {
            if (pMotorConfig->direction)
            {
                HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
                HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_1);
            }
            else
            {
                HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
                HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_2);
            }
            pMotorConfig->real_left_speed = 0;
            pMotorConfig->real_right_speed = 0;
            break;
        }
    case 1:
        /* Stop left motor */
        {
            if (pMotorConfig->direction)
            {
                HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
            }
            else
            {
                HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
            }
            pMotorConfig->real_left_speed = 0;
            break;
        }
    case 2:
        /* Stop right motor */
        {
            if (pMotorConfig->direction)
            {
                HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_1);
            }
            else
            {
                HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_2);
            }
            pMotorConfig->real_right_speed = 0;
            break;
        }
    }

    // Flash red LED
    LED1(1);
    LED0(0);
    pMotorConfig->enable = 0;

    return pMotorConfig->mode;
}

/**
 * Change the direction
 * @param *pMotorConfig
 * @return the latest direction
 */
u8 ChangeDirection(MotorControlStruct *pMotorConfig)
{
    if (pMotorConfig->enable)
    {
        // Reinit the Motorconfig
        Motor_Stop(pMotorConfig);
        //TODO
        printf("\r\nbefore dir change: %u \r\n", pMotorConfig->set_right_speed);
        pMotorConfig->direction = !pMotorConfig->direction;
        Motor_Start(pMotorConfig);
        printf("\r\nAfter dir change: %u \r\n", pMotorConfig->set_right_speed);
    }
    else
    {
        pMotorConfig->direction = !pMotorConfig->direction;
    }
    return pMotorConfig->direction;
}

/**
 * Receive set speed value from GUI gadgets, which ranges from 500 ~ 5000 (won't be 0!)
 *  and update MotorConfig after the value converted properly.
 * @param pMotorConfig
 * @param set_value
 * @return The set_speed.
 */
u16 ChangeSpeed(MotorControlStruct *pMotorConfig, u16 set_value)
{
    u16 set_speed = -set_value + 5500; //! Convert speed value to reload value for timer

    // TODO printf("\r\nnow speed is: %u\r\nenableis:%u", set_speed, pMotorConfig->enable);
    switch (pMotorConfig->mode)
    {
    case 0:
        pMotorConfig->set_left_speed = set_speed;
        pMotorConfig->set_right_speed = set_speed;
        break;

    case 1:
        pMotorConfig->set_left_speed = set_speed;
        break;

    case 2:
        pMotorConfig->set_right_speed = set_speed;
        break;
    }

    if (pMotorConfig->enable)
    {
        // TODO printf("\r\nwawawawawaw: %u", set_speed);
        UpdateRealSpeed(pMotorConfig, set_value);
    }
    return set_speed;
}

/**
 *TODO Update realtime speed of the motors. Also can be useful to stop a specific motor.
 */
u16 UpdateRealSpeed(MotorControlStruct *pMotorConfig, u16 new_speed)
{
    Motor_Stop(pMotorConfig);
    // If new_speed == 0, stop the motor
    if (!new_speed)
    {
        return 0;
    }

    new_speed = -new_speed + 5500; //! Convert speed value to reload value for timer
    switch (pMotorConfig->mode)
    {
    case 0:
        pMotorConfig->real_left_speed = new_speed;
        pMotorConfig->real_right_speed = new_speed;
        break;

    case 1:
        pMotorConfig->real_left_speed = new_speed;
        break;

    case 2:
        pMotorConfig->real_right_speed = new_speed;
        break;
    }
    Motor_Start(pMotorConfig);
    return new_speed;
}

/**
 * Stop the specific motor. 0 means left motor, 1 means right motor.
 * @param pMotorConfig
 * @param the_given_motor 
 * @return The latest mode after the motor stopped.
*/
u8 StopSpecificMotor(MotorControlStruct *pMotorConfig, u8 the_given_motor) {
    if (the_given_motor && pMotorConfig->real_right_speed)    // If the right motor is chosen and running
    {
        if (pMotorConfig->direction)
        {
            HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_1);
        } else
        {
            HAL_TIM_PWM_Stop(&TIM5_Handler, TIM_CHANNEL_2);
        }            
        pMotorConfig->real_right_speed = 0;
    }
    if (!the_given_motor && pMotorConfig->real_left_speed)   // If the left motor is chosen and running
    {
        if (pMotorConfig->direction)
        {
            HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
        } else {
            HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
        }
        pMotorConfig->real_left_speed = 0;
        
    }
    
    // TODO 先不考虑mode
    if (pMotorConfig->real_left_speed && !pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 1;    
    }
    else if (!pMotorConfig->real_left_speed && pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 2;
    } 
    else if (!pMotorConfig->real_left_speed && !pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 0;
    }

    return pMotorConfig->mode;
}

/**
 * Start the specific motor. 0 means left motor, 1 means right motor.
 * @param pMotorConfig
 * @param the_given_motor 
 * @return The latest mode after the motor stopped.
*/
u8 StartSpecificMotor(MotorControlStruct *pMotorConfig, u8 the_given_motor) {
    // Right motor starts to run
    if (the_given_motor == 1 && !pMotorConfig->real_right_speed)
    {
        if (pMotorConfig->direction)
        {
            TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_AWAY);
        } 
        else 
        {
            TIM5_PWM_Init(pMotorConfig->set_right_speed - 1, 108 - 1, GET_CLOSER);
        }
        pMotorConfig->real_right_speed = pMotorConfig->set_right_speed;
    }
    // Left motor starts to run
    else if (the_given_motor == 0 && !pMotorConfig->real_left_speed)
    {
        if (pMotorConfig->direction)
        {
            TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_AWAY);
        } 
        else 
        {
            TIM2_PWM_Init(pMotorConfig->set_left_speed - 1, 108 - 1, GET_CLOSER);
        }
        pMotorConfig->real_left_speed = pMotorConfig->set_left_speed;
    }
    
    // TODO 先不考虑mode
    if (pMotorConfig->real_left_speed && !pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 1;    
    }
    else if (!pMotorConfig->real_left_speed && pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 2;
    } 
    else if (pMotorConfig->real_left_speed && pMotorConfig->real_right_speed)
    {
        pMotorConfig->mode = 0;
    }
    
    return pMotorConfig->mode;
}

u16 ChangeSpecificSpeed(MotorControlStruct *pMotorConfig, u16 set_value, u8 the_given_motor) {
    u16 set_speed = - set_value + 5500;
    // Change the right motor speed
    if (the_given_motor)
    {
        pMotorConfig->set_right_speed = set_speed;
        if (pMotorConfig->real_right_speed)
        {
            UpdateSpecificRealSpeed(pMotorConfig, set_speed, the_given_motor);
        }
        
    }
    // Change the left motor speed
    else
    {
        pMotorConfig->set_left_speed = set_speed;
        if (pMotorConfig->real_left_speed)
        {
            UpdateSpecificRealSpeed(pMotorConfig, set_speed, the_given_motor);
        }
        
    }
    return set_speed;
}

u16 UpdateSpecificRealSpeed(MotorControlStruct *pMotorConfig, u16 new_speed, u8 the_given_motor) {
    StopSpecificMotor(pMotorConfig, the_given_motor);
    // If new_speed == 0, stop the motor
    if (!new_speed)
    {
        return 0;
    }


    StartSpecificMotor(pMotorConfig, the_given_motor);
    return new_speed;
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
