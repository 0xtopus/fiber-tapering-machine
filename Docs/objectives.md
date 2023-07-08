# Ŀ��2
��ʾ�Ľ�
- [x] ����
- [x] ����֮ǰ�Ľ����������
- [ ] LED�ƣ�
- [ ] ʹ��������ʱ���������ҵ��
- [ ] ��ʾƵ�ʣ���΢����ť

<br>

## TODO

- [x] �����½���
- [x] ���½�����ֲ������
- [ ] �½����ʼ��
  - Scrollbar���ٶ���ʾͬ��
  - ��ֹͣʱ��ʾΪ0������ʱ��ʾ��ǰת��
- [ ] �����߼�����
- [ ] <del>AppWizard��ֲ</del>�������������⣩
- [ ] <del>ѧϰ���ʹ��AppWizard����ҳ��</del>

<br>

## Spec

### �ṹ�壺

```c
typedef struct 
{
    u8 mode;         // 0: All motors rotate; 1: Left motor rotates; 2: Right motor rotates
    u16 left_speed;  // Left motor speed, actually it is the freqency of PWM wave
    u16 right_speed; // Right motor speed, actually it is the freqency of PWM wave
    u8 direction;    // 0: Get closer; 1: Go reversely
    u8 enable;       // 0: Disable; 1: Enable
} MotorControlStruct;
```

### ��һ�ֽṹ��

```c
typedef struct 
{
    u8 mode;         		// 0: All motors rotate; 1: Left motor rotates; 2: Right motor rotates
    u16 set_left_speed;  	// Left motor speed, actually it is the freqency of PWM wave
    u16 set_right_speed; 	// Right motor speed, actually it is the freqency of PWM wave
    u16 real_left_speed;
    u16 real_right_speed;
    u8 direction;    // 0: Get closer; 1: Go reversely
    u8 enable;       // 0: Disable; 1: Enable
} MotorControlStruct;
```

�������PWM��������ʱ����ʹ��set_speed��������real_speed��������ʱ��ֻ�е�ʵ�����PWM���趨ֵ��ʱ��һ��ʱ��˫�������ģʽ�͵��������ģʽ�����л�ʱ������ʱ��ʾ��real_speed���䣬ֱ��set_speed�����䶯�Ժ�Ż�ͬ��

### �����߼���

��·�����Timer2���ƣ�PA5��Ӧͨ��1��**Զ������**����Ӧ`direction == 1`�� PA1��Ӧͨ��2��**�ӽ�����**�� ��Ӧ`direction == 0`

��·�����Timer5���ƣ�PH10��Ӧͨ��1��**Զ������**����Ӧ`direction == 1`; PH11��Ӧͨ��2��**�ӽ�����**����Ӧ`direction == 0`

���ҵ���������ƽ��棨���ֹ/������ť���ҽ�ֹ/������ť -->��Ӧ `mode`��

---
# Ŀ��1
## ���Ƶ��

- [x] ��������ƣ���������������ת�٣���Ļ��ť�����ڣ�����ʾ����
- [ ] ˫������ƣ���·PWM�������   
- [x] emwin����������
  
## TODO
- [x] ���ؼ��������ýṹ��
- [x] ˫·pwm���
- [x] pwm����ٶȿ��ƣ����Σ���`pwmout_config`�ṹ���������Ϣ����һ�·��͸�pwm���ú�����
- [x] pwm���ģʽ���ã�����Ҫ�ĳ�ʼ�������Ľṹ����
- [ ] <del>4·pwm�������</del>������δ������



## ����
1. �ı�����ת������Ҫ��ʹ���ֹͣ��No.
2. <del>�����·ʱTimer2��CH2PWM�����Ŷ���</del>
3. <del>��ʼ���ṹ��pwmout_config</del>
4. <del>������Ŀǰ��2khz, �����ڻ��Ǹ�ռ�ձ������٣�</del>
    - <del>�����ռ�ձȣ������Ż��ṹ��pwmout_config����ʹ��ʱռ�ձ�Ϊ0����</del>
    - <del>���Խ��ܵ�Ƶ�ʷ�Χ���õ������һ��</del>

## Spec
1. �ȴ���һ���ṹ�壨������`pwmout.h`�����������ͬ�ؼ���ʱ��ı�ṹ���Ӧ�Ĳ���ֵ
   - ����ת�ؼ�---`rotate_direction`
   - Checkbox�ؼ�---���ѡ��
     - `left_motor`
     - `right_motor`
    - �ٶ�����Slider����Ҫ�о�һ����ô���ڣ�`speed`
    - ʹ��pwm�����`pwm_enable`
```c
typedef struct
{
    uint8_t rotate_direction;// ת���ķ���0����ת��1����ת
    uint8_t left_motor;     // ������Ƿ�ת����0����ת��1��ת��
    uint8_t right_motor;    // ������Ƿ�ת����0����ת��1��ת��
    uint16_t speed;         // ���ת�ٵĵ���
    uint8_t pwm_enable;     // ʹ��pwm�����0����ʹ�ܣ�1��ʹ��
}pwmout_struct;
```

2. ����`Timer2`������PWM�ź� 

3. ��`pwmout.c`�ﶨ����صĿ��ƺ�����
   - `void PWM_Gen(pwmout_struct pwmout_config)`����ȡ�ṹ��`pwmout_struct`������ݣ���PWM����������ã�
   - `void PWM_Start(void)`������PWM���
   - 

4. �����°�ťʱ���������λ�ֹͣ�����ı�״̬
   - ʵ�ַ�ʽ����`motordemo.c`��Ӧ�ؼ�����Ϣ���޸Ľṹ��ı��������ߵ��ö�����`pwmout.c`��ĺ������ı������״̬
   - ��ťPWN_GEN
     - ���º󷢲���LED1���̵ƣ���
     - �ٴΰ���ֹͣ������LED0����ƣ���
     - ʹ������������
   - Checkbox��һ��һ�ң���Ӧ�����ṹ�����
   - Listbox������ת����Ӧ�ṹ�����`rotate_direction`
   - Slider: �ٶȣ�0 ~ 100
