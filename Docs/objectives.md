# Ŀ��7

������Ƭ���ĵؿ��Խ�һ��������壿

�����߼����£�ѡ���������ˣ����Ը��µ���������£�

PE5��PE6��TIM9_CH1��CH2��Rpull, Rrtn

PB6��PB7��TIM4_CH1��CH2

������direction = 0����������

PF9������

����PCB��ԭ��ͼ�����룡





- ������
  - �Զ���������
  - �������ֶ������ϣ�����ʾ��ģ��
- ����޷����ԣ��Զ���
- ������·
- ����





# Ŀ��6

���⣺

- ��Դ10K�����裬�������FB=0.83��ԭ����0.80
- 

## Ŀ��6.1

- [x] ����оƬͻȻû������IGT6����ZGT6��176���� --> 144���ţ�
- [x] �����޸ĺ�����ų���
- [x] �ػ�ԭ��ͼ��PCB

  - ��������Ҫ�õ�����ӳ���ҳ���������PCB�û���ԭ��ѡ��
  - ����ʣ��δ���ӵ��ߣ���ԭ��ͼ��BL��������
  - USART1��136��137
  - ����������
  - ��������
- [x] �ڳ����в鿴����޸�����ӳ��

**��Ҫ�޸ĵ�����ģ���У�**

  - [x] ��׶������������
  - [x] RGB LCD����
  - [x] MCU LCD����
  - [x] USART����
  - [x] ��֤����IO�ھ����ܶ�
  - [x] LED
  - [ ] ������
  - [x] ���Ե�

### �¿����߼���

��·�����

Timer9���ƣ�PE5��Ӧͨ��1��**Զ��������׶**����Ӧ`direction == 1`�� PE6��Ӧͨ��2��**�ӽ����Ĺ�λ**�� ��Ӧ`direction == 0`

��·�����

Timer10���ƣ�PF6��Ӧͨ��1��**Զ��������׶**����Ӧ`direction == 1`; 

Timer11������PF7��Ӧͨ��1��**�ӽ����Ĺ�λ**����Ӧ`direction == 0`��

### ��ADC����

ADC3_IN6��PF8����ADC3_IN7��PF9��

## �����Ŷ�Ӧ

|  �ź���   |      ��ӦI/O       |
| :-------: | :----------------: |
|    PE2    |        LED1        |
|    PE3    |        LED0        |
|    PE5    | TIM9_CH1 (L_PULL)  |
|    PE6    |  TIM9_CH2 (L_RTN)  |
|    PF0    |       FMC_A0       |
|    PF1    |       FMC_A1       |
|    PF2    |       FMC_A2       |
|    PF3    |       FMC_A3       |
|    PF4    |       FMC_A4       |
|    PF5    |       FMC_A5       |
|    PF6    | TIM10_CH1 (R_PULL) |
|    PF7    | TIM11_CH1 (R_RTN)  |
|    PF8    |      ADC3_IN6      |
|    PF9    |      ADC3_IN7      |
|   PF10    |       LCD_DE       |
|  26...29  |                    |
|  34...36  |                    |
|    PA3    |       LCD_B5       |
|    PA4    |     LCD_VSYNC      |
|    41     |                    |
|    PA6    |       LCD_G2       |
|    PA7    |     FMC_SDNWE      |
|    PC4    |     FMC_SDNE0      |
|    PC5    |     FMC_SDCKE0     |
|    PB0    |       LCD_R3       |
|  47...48  |                    |
|   PF11    |     FMC_SDNRAS     |
|   PF12    |       FMC_A6       |
|   PF13    |       FMC_A7       |
|   PF14    |       FMC_A8       |
|   PF15    |       FMC_A9       |
|    PG0    |      FMC_A10       |
|    PG1    |      FMC_A11       |
|    PE7    |       FMC_D4       |
|    PE8    |       FMC_D5       |
|    PE9    |       FMC_D6       |
|   PE10    |       FMC_D7       |
|   PE11    |       FMC_D8       |
|   PE12    |       FMC_D9       |
|   PE13    |      FMC_D10       |
|   PE14    |      FMC_D11       |
|   PE15    |      FMC_D12       |
|   PB10    |       LCD_G4       |
|   PB11    |       LCD_G5       |
|   PB12    |    T_SCK (GPIO)    |
|   PB13    |   T_MISO (GPIO)    |
|  75...76  |                    |
|    PD8    |      FMC_D13       |
|    PD9    |      FMC_D14       |
|   PD10    |      FMC_D15       |
|   PD11    |    T_PEN (GPIO)    |
|    81     |                    |
|   PD13    |      FMC_A18       |
|   PD14    |       FMC_D0       |
|   PD15    |       FMC_D1       |
|    PG2    |      FMC_A12       |
|    PG3    |   LCD_BL (GPIO)    |
|    PG4    |      FMC_BA0       |
|    PG5    |      FMC_BA1       |
|    PG6    |       LCD_R7       |
|    PG7    |      LCD_CLK       |
|    PG8    |     FMC_SDCLK      |
|    PC6    |     LCD_HSYNC      |
|    PC7    |       LCD_G6       |
|    PC8    |   T_MOSI (GPIO)    |
|    PC9    |    T_CS (GPIO)     |
|    PA8    |       LCD_R6       |
|    PA9    |       LCD_R5       |
|    102    |                    |
|   PA11    |       LCD_R4       |
|    104    |                    |
|   PA13    |     JTMS-SWDIO     |
|   PA14    |    JTC K-SWCLK     |
|   PA15    |        JTDI        |
| 111...113 |                    |
|    PD0    |       FMC_D2       |
|    PD1    |       FMC_D3       |
| 116...117 |                    |
|    PD4    |      FMC_NOE       |
|    PD5    |      FMC_NWE       |
|    122    |                    |
|    PD7    |      FMC_NE1       |
|    124    |                    |
|   PG10    |       LCD_G3       |
|   PG11    |       LCD_B3       |
|   PG12    |       LCD_B4       |
| 128...129 |                    |
|   PG15    |     FMC_SDNCAS     |
|    PB3    |   JTDO/TRACESWO    |
|    PB4    |       NJTRST       |
|    PB5    |       LCD_G7       |
|    PB6    |     USART1_TX      |
|    PB7    |     USART1_RX      |
|    138    |       BOOT0        |
|    PB8    |       LCD_B6       |
|    PB9    |       LCD_B7       |
|    PE0    |      FMC_NBL0      |
|    PE1    |      FMC_NBL1      |



## ��������

- [x] PCB --> **�޸�**

**�ɹ�** --> �Զ�

**��е��ƣ��оߣ�** --> �Զ�����

- [x] **���ӹ���** --> ����

*����*

����

## ����ע������

- �����ܱ𺸽ӷ���
- ģ��ĺ���˳��
- ��β��Ժ����Ƿ���ȷ��

## ����ADC+DMA��FFT��OS

��ʱ�����ò���Ƶ��

��������DMA���洢����

- [x] ADC + FFT�ɼ�Ƶ��
  - ��ô����0Ƶ�ʣ���ֱ��������
  - �е�ʱ���ɼ��������ķ���
- [ ] 

# Ŀ��5

## ���������������

Ŀǰ�Զ������Ŀ�껹��̫���ʣ�������������Ҳû�е�λ����˽�δ����Ҫ������������ݼ��ڴˣ�

1. ������Ҫ��
   - �ж���׶��������ݣ�����Ƶ�ʣ�������ֵ�������Ĳ�����ʲô����
2. ���ת�ٵĵ��ڷ�Χ��
3. PID�㷨Ӧ����ε��ڣ�

������δ����Ҫ����ʵ�������չ/�Ľ��ĳ���Ҫ��

- �Ƿ�ʹ��ϵͳ�����⿨�٣�
- �Ƿ�ʹ��DMA������ϵͳ���٣��������ڲ���ʱ�����ݴ���ʱ��α��⣿��
- ADC����Ƶ��ʵ�֣�
  - ���Բο�����ԭ�� *emWin����21-GraphС����*��ʹ��Timer���ж�������**һ��**ADC������������ʱ���ļ�ʱʱ�����ADC�Ĳ����ʡ�
  - �ڲɼ����㹻��ĵ���������˵1024���󣬽���fft���㣬���Բο�����ԭ��*DSPʵ������*�����˼���������DSP����ĺ��������м��㣬��Ҫ���ܻ��õ��ĺ������£�`arm_cfft_f32`, `arm_cmplx_mag_f32`, `arm_max_f32`��������÷����Բο�*STM32Cube_FW_F7_V1.4.0\Drivers\CMSIS* �ļ����µ�`index.html`�Լ�DSP�����example: `arm_fft_bin_example`��
    - ������������Ҫ��ʱ����us ("1024 point FFT runtime:0.374ms")�����ܻ����LCD���ӳ�
  - �������ֵ����Ƶ�ʣ���Ϊ��ǰ�����źŵ���Ƶ�ʣ�
- �ο�����ԭ�� *emWin����21-GraphС����*��ֱ����һ��ʾ����ͼ�������û��Լ��۲��ж��Ƿ������׶��



- [x] **������ԭ��׶������Ļ�����дһ�����̣��ɼ������PWM����Ȼ�����fft���ҵ���ֵ����Ƶ�ʣ��Ӷ��õ�PWM�����Ƶ�ʣ�**

  **STM32�Ķ�ʱ��������**��[��ô��STM32�������Ҳ���Ƶ��](https://www.icxbk.com/ask/detail/29603.html#:~:text=%E5%A6%82%E6%9E%9C%E6%AD%A3%E5%BC%A6%E6%B3%A2%E7%9A%84%E9%A2%91%E7%8E%87%E4%B8%8D%E9%AB%98%EF%BC%8C%E5%8F%AF%E4%BB%A5%E7%94%A8STM32%E7%9A%84ADC%E7%9B%B4%E6%8E%A5%E9%87%87%E6%A0%B7%EF%BC%8C%E7%84%B6%E5%90%8E%E7%94%A8fft%E6%9D%A5%E8%A7%A3%E7%AE%97%EF%BC%8C%E8%BF%99%E7%A7%8D%E5%8F%AA%E8%83%BD%E7%AE%971M%E4%BB%A5%E4%B8%8B%E7%9A%84,%E5%A6%82%E6%9E%9C%E9%80%9F%E5%BA%A6%E8%BE%83%E9%AB%98%EF%BC%8C%E8%A6%81%E7%AE%97%E9%A2%91%E7%8E%87%EF%BC%8C%E5%8F%AF%E4%BB%A5%E7%94%A8%E4%B8%80%E4%B8%AA%E6%AF%94%E8%BE%83%E5%99%A8%E6%9D%A5%E6%B5%8B%E9%87%8F%EF%BC%8C%E5%A6%82%E6%9E%9C%E9%AB%98%E4%BA%8E%E6%9F%90%E4%B8%AA%E5%80%BC%E5%88%99%E6%AF%94%E8%BE%83%E5%99%A8%E8%BE%93%E5%87%BA%E4%B8%80%E4%B8%AA%E9%AB%98%E7%94%B5%E5%B9%B3%EF%BC%8C%E7%84%B6%E5%90%8ESTM32%E5%8E%BB%E6%8D%95%E8%8E%B7%EF%BC%8C%E7%84%B6%E5%90%8E%E9%80%9A%E8%BF%87%E4%B8%80%E6%AE%B5%E6%97%B6%E9%97%B4%E5%86%85%E9%AB%98%E4%BA%8E%E9%98%88%E5%80%BC%E7%9A%84%E6%AC%A1%E6%95%B0%E4%B9%9F%E8%83%BD%E7%AE%97%E5%87%BA%E9%A2%91%E7%8E%87)

  1. ��adc�����ĵ�ȫ���͵�һ��input buffer��ȥ��ÿ��������֮��ļ���ɲ���Ƶ�ʾ������������Ƶ��Ϊ4096Hz����������Ϊ1024��ʱ��ÿ��������ļ������4Hz����Ҳ��Ƶ�ʷֱ��ʣ�
  2. ��ȡinput buffer������fft������ݣ�����DSP��Ĺ�����ο�����ԭ�ӽ̳�57��������ݣ�
  3. �Ѽ��������Ƶ�ʸ��µ�ͼ�ν�����ȥ

# Ŀ��4

## PCB���

- [x] RESET��25MHz�����е��---�Ѹ���

- [ ] C15�Ĺ����е㲻��

- [x] LED�ĳ�PE2��PB8

- [x] BEEP��PB0

- [x] ��ֹ��Ļ���ϵ�ʱ����������Ԫ������4.3�� ��62.25mm*117.5mm ��[����](http://47.111.11.73/docs/modules/lcd/4.3-TFT%20LCD-800480.html)

- [x] �滻���Ժ��ӵ�����,ʹ��1812��װ

- [ ] �ӹ���
- [ ] �ܷ���Ƭ��

- [x] ��������һ��

[STM32 ֮����ϵͳ���ڲ����յ�ѹ��VREFINT��ʹ�ü�����ADC�ο���](https://shequ.stmicroelectronics.cn/thread-637646-1-1.html)

## �������

- [ ] ADC��emWIN���¹���

  ADC3_IN4��PF6����ADC3_IN5��PF7��
  
  

## ������ϰ

- [x] ��ϰ��������



# Ŀ��3

PCB��ͼ���

- [x] ������������

## ����

0. <span style="color:red;font-weight:bold">���PCB�����̣�</span>��������ʱ�뵽�Ŀ�����Ҫ���ǵ����⣺

1. ��Ҫ����������ţ�<span  style="color:blue">��ɫ</span>�����Ҳ�̫ȷ���Ƿ���Ҫ��<span  style="color:orange">��ɫ</span>�����Ҳ�֪����Ҫ�Ĳ�����񣩣�

   - ��Сϵͳ��

     - оƬ��stm32f7IGT6
- ����ģ��
     - LCD�ӿ�
     - [x] ��λ����
     - [x] ʱ�ӵ�·
     - [x] ��ԴָʾLED
     - [x] <span  style="color:orange">SDRAM</span>�����ǵ�GUIҪ����SDRAM����
     - <span  style="color:blue">FLASH</span>
     - <span  style="color:blue">USBת����</span>���Ƿ���Ҫ���ԣ���
     - [x] <span  style="color:blue">����LED</span>
   - <span  style="color:blue">��ѹ���Ե�</span>(����ԭ�ӵ���������3����5V��3V3��GND�����������Ժ��İ�ĵ�Դ�Ƿ����� ��Ҳ���Ը����İ幩��)
   - <span  style="color:blue">WK_UP����</span>
   - ��Ҫ�õ������ţ�
   
     - Timer2��Timer5��CH1��CH2���ĸ����ſ����������
     - LCD��ص����Ž���Ļ
     - GND����
     - <span  style="color:orange">ADC��������</span>(��Ҫ����·������)

2. PCB��Ĺ����������Ҫ�󣿸���������ѡ�ͣ��Ƿ�Ҫ���һЩ�ⲿ��·�������·�ȣ���

# Ŀ��2.1

## �Ľ��ֶ�����

- [x] �����߼��Ż�������ܹ�
  - [x] ���`get()`��`set()`������ ����ṹ���ҳ�����
  - [x] ��˫�������ʹ���µ�`start()`��`stop()`����
  - [x] �Ѹ���`#define`�ĳ�ö��
- [x] LEDָʾ�Ƿ���Ҫ��
- [x] Ҫ��Ҫ���Ź�ģ�飿
- [ ] �����Ĳ���--��η�ӳ��emWin������ʾ��ȥ�����²�͡��ػ桱�����йأ����߸���ʱ�Ƿ����ʹ���Զ�����û���Ϣ?)

## ȱ��

- ΢������������
- �ӵ������ƽ��浽˫������ƽ���ʱ������������״̬�������Slider�������������ת������
- ���ܴ���δ֪��bug(Ŀǰ��δ���֣�������һ�η�����ԭ��������������������ʱû������������ʱ����)��������ν��в���?

# Ŀ��2

��ʾ�Ľ�
- [x] ����
- [x] ����֮ǰ�Ľ����������
- [x] ʹ��������ʱ���������ҵ��
- [x] ��ʾƵ�ʣ���΢����ť

<br>

## TODO

- [x] �����½���
- [x] ���½�����ֲ������
- [x] �½����ʼ��
  - Scrollbar���ٶ���ʾͬ��
  - ��ֹͣʱ��ʾΪ0������ʱ��ʾ��ǰת��
- [x] �����߼�����
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

<u>�Ѹ�ΪPA2��Ӧͨ��3��PA3��Ӧͨ��4</u> 

��·����ĳ�Timer5��CH3��CH4�����ʹ��RGB��Ļ�Ļ���PA2��PA3

**���ܻ�Ҫ��ΪTIM4_CH1��CH2����Ӧ144���ŵ�136��PB6����137��PB7��**



���ҵ���������ƽ��棨���ֹ/������ť���ҽ�ֹ/������ť -->��Ӧ `mode`��

### ADC����

�ݶ�ADC3_IN4��PF6����ADC3_IN5��PF7��

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
