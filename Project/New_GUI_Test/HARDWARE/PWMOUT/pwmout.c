#include "pwmout.h"
#include "timer.h"

// TODO : PWM_Gen()
void PWM_Gen(pwmout_struct pwmout_config)
{
    TIM2_PWM_Init(-pwmout_config.speed + 5500 - 1, 108 - 1, pwmout_config); //! 108M/108=1M的计数频率，自动重装载为1000，那么PWM频率为1M/1000=1kHZ
    printf("\r\npwmout.dir:%u\r\n", pwmout_config.rotate_direction);
    printf("\r\npwmout.left:%u\r\n", pwmout_config.left_motor);
    printf("\r\npwmout.right:%u\r\n", pwmout_config.right_motor);
    printf("\r\npwmout.speed:%u\r\n", pwmout_config.speed);
    printf("\r\npwmout.enable:%u\r\n", pwmout_config.pwm_enable);
    printf("\r\n**********************\r\n");
}

void PWM_Stop(void)
{
    HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
}

// 改变电机的速度
// 参数：speed, 由Slider的值决定
void PWM_Change_Speed(pwmout_struct pwmout_config)
{
    HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
    // printf("\r\nThe current speed is: %u\r\n", -speed + 5500);
    TIM2_PWM_Init((-pwmout_config.speed + 5500) - 1, 108 - 1, pwmout_config); //! 108M/108=1M的计数频率，如果自动重装载为1000，那么PWM频率为1M/1000=1kHZ
}

/**********************************EOF*******************************/
