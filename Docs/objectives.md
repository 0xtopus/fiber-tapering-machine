

PCB --> **修改**

**采购** --> 自动

**机械设计（夹具）** --> 自动调试

**焊接工具** --> 焊接

*测试*



RESET和25MHz晶振有点近

C15的过孔有点不好

VUSB？

LED改成PE2和PB6

BEEP：PB0

防止屏幕插上的时候碰到其他元器件：4.3寸 ：62.25mm*117.5mm 见[资料](http://47.111.11.73/docs/modules/lcd/4.3-TFT%20LCD-800480.html)

替换难以焊接的器件,使用1812封装

MCULED去掉

加光耦

分享嘉立创文件

IO: 为了不挡住，拿母头外扩？

适配程序改一下

[STM32 之供电系统及内部参照电压（VREFINT）使用及改善ADC参考电](https://shequ.stmicroelectronics.cn/thread-637646-1-1.html)

# 目标3

PCB版图设计

- [ ] 搞清楚设计流程

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
- [ ] LED指示是否需要？
- [ ] 要不要看门狗模块？
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

右路电机可能改成Timer9的CH1和CH2（如果使用RGB屏幕的话）PE5和PE6

左右电机独立控制界面（左禁止/启动按钮，右禁止/启动按钮 -->对应 `mode`）

### ADC采样

暂定ADC3_IN4（PF6）和ADC_IN5（PF7）

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
