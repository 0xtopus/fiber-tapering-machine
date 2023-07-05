#ifndef __PWMOUT_H
#define __PWMOUT_H
#include "sys.h"
/* 
 * �Կ���pwm���״̬���п��Ƶ�ͷ�ļ�
 */

typedef struct
{
    uint8_t rotate_direction;// ת���ķ���0����ת��1����ת
    uint8_t left_motor;     // ������Ƿ�ת����0����ת��1��ת��
    uint8_t right_motor;    // ������Ƿ�ת����0����ת��1��ת��
    uint16_t speed;         // ���ת�ٵĵ���
    uint8_t pwm_enable;     // ʹ��pwm�����0����ʹ�ܣ�1��ʹ��
}pwmout_struct;


void PWM_Gen(pwmout_struct pwmout_config);
void PWM_Stop(void);
void PWM_Change_Speed(pwmout_struct pwmout_config);

#endif
/**********************************EOF*******************************/
