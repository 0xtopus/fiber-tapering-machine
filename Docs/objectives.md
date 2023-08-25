# 目标7

两个单片机的地可以接一起吗？面包板？

控制逻辑更新：选错排针间距了，所以更新电机控制如下：

PE5、PE6：TIM9_CH1，CH2，Rpull, Rrtn

PB6、PB7：TIM4_CH1，CH2

启动后direction = 0，靠近中心

PF9采样：

更新PCB和原理图：排针！





- 程序构想
  - 自动来不及？
  - 在已有手动基础上，加入示波模块
- 如果无法调试，自动？
- 采样电路
- 光耦





# 目标6

问题：

- 电源10KΩ电阻，计算出来FB=0.83，原来：0.80
- 

## 目标6.1

- [x] 由于芯片突然没货，将IGT6换成ZGT6（176引脚 --> 144引脚）
- [x] 测试修改后的引脚程序！
- [x] 重绘原理图和PCB

  - 将所有需要用到引脚映射找出来，根据PCB好画的原则选择
  - 补齐剩下未连接的线（见原理图）BL、触摸屏
  - USART1：136，137
  - 触摸屏引脚
  - 背光引脚
- [x] 在程序中查看如何修改引脚映射

**需要修改的外设模块有：**

  - [x] 拉锥机的外设引脚
  - [x] RGB LCD引脚
  - [x] MCU LCD引脚
  - [x] USART引脚
  - [x] 保证引出IO口尽可能多
  - [x] LED
  - [ ] 蜂鸣器
  - [x] 测试点

### 新控制逻辑：

左路电机：

Timer9控制，PE5对应通道1，**远离中心拉锥**，对应`direction == 1`； PE6对应通道2，**接近中心归位**， 对应`direction == 0`

右路电机：

Timer10控制，PF6对应通道1，**远离中心拉锥**，对应`direction == 1`; 

Timer11，控制PF7对应通道1，**接近中心归位**，对应`direction == 0`；

### 新ADC采样

ADC3_IN6（PF8）和ADC3_IN7（PF9）

## 新引脚对应

|  信号线   |      对应I/O       |
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



## 进度总览

- [x] PCB --> **修改**

**采购** --> 自动

**机械设计（夹具）** --> 自动调试

- [x] **焊接工具** --> 焊接

*测试*

焊接

## 焊接注意事项

- 二极管别焊接反了
- 模块的焊接顺序
- 如何测试焊接是否正确？

## 程序ADC+DMA＋FFT＋OS

定时器设置采样频率

采样数据DMA到存储器里

- [x] ADC + FFT采集频率
  - 怎么处理0频率？（直流分量）
  - 有的时候会采集到互补的分量
- [ ] 

# 目标5

## 后续程序设计设想

目前自动程序的目标还不太明朗，调试所需器件也没有到位，因此将未来需要搞清楚的问题暂记于此：

1. 采样的要求？
   - 判断拉锥情况的依据：采样频率？采样幅值？采样的波形是什么波？
2. 电机转速的调节范围？
3. PID算法应该如何调节？

可能在未来需要根据实际情况扩展/改进的程序要求：

- 是否使用系统来避免卡顿？
- 是否使用DMA来避免系统卡顿？（仅仅在采样时，数据处理时如何避免？）
- ADC采样频率实现：
  - 可以参考正点原子 *emWin例程21-Graph小工具*，使用Timer的中断来触发**一次**ADC采样，这样定时器的计时时间就是ADC的采样率。
  - 在采集到足够多的点数（比如说1024）后，进行fft计算，可以参考正点原子*DSP实验例程*，大概思想就是利用DSP库里的函数来进行计算，主要可能会用到的函数如下：`arm_cfft_f32`, `arm_cmplx_mag_f32`, `arm_max_f32`。具体的用法可以参考*STM32Cube_FW_F7_V1.4.0\Drivers\CMSIS* 文件夹下的`index.html`以及DSP库里的example: `arm_fft_bin_example`。
    - 这种做法可能要耗时几百us ("1024 point FFT runtime:0.374ms")，可能会造成LCD的延迟
  - 计算出幅值最大的频率，即为当前采样信号的主频率？
- 参考正点原子 *emWin例程21-Graph小工具*，直接做一个示波器图表，允许用户自己观察判断是否完成拉锥？



- [x] **试着在原拉锥机程序的基础上写一个例程，采集输出的PWM波，然后计算fft，找到幅值最大的频率，从而得到PWM的输出频率？**

  **STM32的定时器捕获功能**：[怎么用STM32测量正弦波的频率](https://www.icxbk.com/ask/detail/29603.html#:~:text=%E5%A6%82%E6%9E%9C%E6%AD%A3%E5%BC%A6%E6%B3%A2%E7%9A%84%E9%A2%91%E7%8E%87%E4%B8%8D%E9%AB%98%EF%BC%8C%E5%8F%AF%E4%BB%A5%E7%94%A8STM32%E7%9A%84ADC%E7%9B%B4%E6%8E%A5%E9%87%87%E6%A0%B7%EF%BC%8C%E7%84%B6%E5%90%8E%E7%94%A8fft%E6%9D%A5%E8%A7%A3%E7%AE%97%EF%BC%8C%E8%BF%99%E7%A7%8D%E5%8F%AA%E8%83%BD%E7%AE%971M%E4%BB%A5%E4%B8%8B%E7%9A%84,%E5%A6%82%E6%9E%9C%E9%80%9F%E5%BA%A6%E8%BE%83%E9%AB%98%EF%BC%8C%E8%A6%81%E7%AE%97%E9%A2%91%E7%8E%87%EF%BC%8C%E5%8F%AF%E4%BB%A5%E7%94%A8%E4%B8%80%E4%B8%AA%E6%AF%94%E8%BE%83%E5%99%A8%E6%9D%A5%E6%B5%8B%E9%87%8F%EF%BC%8C%E5%A6%82%E6%9E%9C%E9%AB%98%E4%BA%8E%E6%9F%90%E4%B8%AA%E5%80%BC%E5%88%99%E6%AF%94%E8%BE%83%E5%99%A8%E8%BE%93%E5%87%BA%E4%B8%80%E4%B8%AA%E9%AB%98%E7%94%B5%E5%B9%B3%EF%BC%8C%E7%84%B6%E5%90%8ESTM32%E5%8E%BB%E6%8D%95%E8%8E%B7%EF%BC%8C%E7%84%B6%E5%90%8E%E9%80%9A%E8%BF%87%E4%B8%80%E6%AE%B5%E6%97%B6%E9%97%B4%E5%86%85%E9%AB%98%E4%BA%8E%E9%98%88%E5%80%BC%E7%9A%84%E6%AC%A1%E6%95%B0%E4%B9%9F%E8%83%BD%E7%AE%97%E5%87%BA%E9%A2%91%E7%8E%87)

  1. 把adc采样的点全部送到一个input buffer里去（每个采样点之间的间隔由采样频率决定，比如采样频率为4096Hz，而采样点为1024个时，每个采样点的间隔就是4Hz，这也叫频率分辨率）
  2. 读取input buffer，计算fft相关数据（配置DSP库的过程请参考正点原子教程57章相关内容）
  3. 把计算出来的频率更新到图形界面上去

# 目标4

## PCB检查

- [x] RESET和25MHz晶振有点近---已改正

- [ ] C15的过孔有点不好

- [x] LED改成PE2和PB8

- [x] BEEP：PB0

- [x] 防止屏幕插上的时候碰到其他元器件：4.3寸 ：62.25mm*117.5mm 见[资料](http://47.111.11.73/docs/modules/lcd/4.3-TFT%20LCD-800480.html)

- [x] 替换难以焊接的器件,使用1812封装

- [ ] 加光耦
- [ ] 能否贴片？

- [x] 适配程序改一下

[STM32 之供电系统及内部参照电压（VREFINT）使用及改善ADC参考电](https://shequ.stmicroelectronics.cn/thread-637646-1-1.html)

## 程序设计

- [ ] ADC与emWIN更新规则

  ADC3_IN4（PF6）和ADC3_IN5（PF7）
  
  

## 焊接练习

- [x] 练习焊接器件



# 目标3

PCB版图设计

- [x] 搞清楚设计流程

## 问题

0. <span style="color:red;font-weight:bold">设计PCB的流程？</span>以下是暂时想到的可能需要考虑的问题：

1. 需要的外设和引脚（<span  style="color:blue">蓝色</span>代表我不太确定是否需要，<span  style="color:orange">橙色</span>代表我不知道需要的参数规格）：

   - 最小系统：

     - 芯片：stm32f7IGT6
- 供电模块
     - LCD接口
     - [x] 复位按键
     - [x] 时钟电路
     - [x] 电源指示LED
     - [x] <span  style="color:orange">SDRAM</span>（我们的GUI要多大的SDRAM？）
     - <span  style="color:blue">FLASH</span>
     - <span  style="color:blue">USB转串口</span>（是否需要调试？）
     - [x] <span  style="color:blue">其它LED</span>
   - <span  style="color:blue">电压测试点</span>(正点原子的主板上有3个：5V，3V3，GND，可用来测试核心板的电源是否正常 。也可以给核心板供电)
   - <span  style="color:blue">WK_UP按键</span>
   - 需要用到的引脚：
   
     - Timer2和Timer5的CH1和CH2，四个引脚控制两个电机
     - LCD相关的引脚接屏幕
     - GND若干
     - <span  style="color:orange">ADC采样引脚</span>(需要多少路采样？)

2. PCB板的规格？有无特殊要求？各种器件的选型？是否要设计一些外部电路（隔离电路等？）

# 目标2.1

## 改进手动程序

- [x] 程序逻辑优化，精简架构
  - [x] 添加`get()`和`set()`方法， 隔离结构体和页面操作
  - [x] 让双电机控制使用新的`start()`和`stop()`函数
  - [x] 把各种`#define`改成枚举
- [x] LED指示是否需要？
- [x] 要不要看门狗模块？
- [ ] 后续的采样--如何反映到emWin界面显示上去？（猜测和“重绘”机制有关，或者更新时是否可以使用自定义的用户消息?)

## 缺陷

- 微调不可以连按
- 从单独控制界面到双电机控制界面时，若处于运行状态，则调整Slider会让两个电机都转起来。
- 可能存在未知的bug(目前暂未发现，除了有一次发生了原因不明的意外重启，但暂时没有在其他测试时复现)，后续如何进行测试?

# 目标2

显示改进
- [x] 竖屏
- [x] 根据之前的界面重新设计
- [x] 使用两个定时器控制左右电机
- [x] 显示频率，加微调按钮

<br>

## TODO

- [x] 汉化新界面
- [x] 把新界面移植开发板
- [x] 新界面初始化
  - Scrollbar和速度显示同步
  - 当停止时显示为0，启动时显示当前转速
- [x] 界面逻辑处理
- [ ] <del>AppWizard移植</del>（兼容性有问题）
- [ ] <del>学习如何使用AppWizard构建页面</del>

<br>

## Spec

### 结构体：

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

### 另一种结构体

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

设置输出PWM波的周期时，都使用set_speed，并更新real_speed；在运行时，只有当实际输出PWM和设定值暂时不一样时（双电机控制模式和单电机控制模式互相切换时），此时显示的real_speed不变，直到set_speed发生变动以后才会同步

### 控制逻辑：

左路电机：Timer2控制，PA5对应通道1，**远离中心**，对应`direction == 1`； PA1对应通道2，**接近中心**， 对应`direction == 0`

右路电机：Timer5控制，PH10对应通道1，**远离中心**，对应`direction == 1`; PH11对应通道2，**接近中心**，对应`direction == 0`	

<u>已改为PA2对应通道3，PA3对应通道4</u> 

右路电机改成Timer5的CH3和CH4（如果使用RGB屏幕的话）PA2和PA3

**可能还要改为TIM4_CH1和CH2：对应144引脚的136（PB6）和137（PB7）**



左右电机独立控制界面（左禁止/启动按钮，右禁止/启动按钮 -->对应 `mode`）

### ADC采样

暂定ADC3_IN4（PF6）和ADC3_IN5（PF7）

---
# 目标1
## 控制电机

- [x] 单电机控制：控制周期来控制转速，屏幕按钮调周期，并显示快慢
- [ ] 双电机控制：四路PWM独立输出   
- [x] emwin来美化界面
  
## TODO
- [x] 各控件操作配置结构体
- [x] 双路pwm输出
- [x] pwm输出速度控制（传参，把`pwmout_config`结构体的配置信息换算一下发送给pwm配置函数。
- [x] pwm输出模式配置（可能要改初始化函数的结构？）
- [ ] <del>4路pwm输出控制</del>（引脚未引出）



## 问题
1. 改变电机旋转方向需要先使电机停止吗？No.
2. <del>输出两路时Timer2的CH2PWM波形扰动大</del>
3. <del>初始化结构体pwmout_config</del>
4. <del>计数器目前是2khz, 改周期还是改占空比来调速？</del>
    - <del>如果改占空比，可以优化结构体pwmout_config（不使用时占空比为0）。</del>
    - <del>可以接受的频率范围？拿电机测试一下</del>

## Spec
1. 先创建一个结构体（定义在`pwmout.h`），当点击不同控件的时候改变结构体对应的参数值
   - 正反转控件---`rotate_direction`
   - Checkbox控件---电机选择：
     - `left_motor`
     - `right_motor`
    - 速度条：Slider：需要研究一下怎么调节：`speed`
    - 使能pwm输出：`pwm_enable`
```c
typedef struct
{
    uint8_t rotate_direction;// 转动的方向，0：正转，1：反转
    uint8_t left_motor;     // 左马达是否转动，0：不转，1：转；
    uint8_t right_motor;    // 右马达是否转动，0：不转，1：转；
    uint16_t speed;         // 电机转速的调节
    uint8_t pwm_enable;     // 使能pwm输出，0：不使能，1：使能
}pwmout_struct;
```

2. 配置`Timer2`来产生PWM信号 

3. 在`pwmout.c`里定义相关的控制函数：
   - `void PWM_Gen(pwmout_struct pwmout_config)`：读取结构体`pwmout_struct`里的数据，对PWM输出进行配置；
   - `void PWM_Start(void)`：启动PWM输出
   - 

4. 当按下按钮时，发生波形或停止输出或改变状态
   - 实现方式：在`motordemo.c`对应控件的消息下修改结构体的变量，或者调用定义在`pwmout.c`里的函数来改变输出的状态
   - 按钮PWN_GEN
     - 按下后发波，LED1（绿灯）亮
     - 再次按下停止发波，LED0（红灯）亮
     - 使用两个函数？
   - Checkbox：一左一右，对应两个结构体变量
   - Listbox：正反转，对应结构体里的`rotate_direction`
   - Slider: 速度，0 ~ 100
