# 目标2
显示改进
- [x] 竖屏
- [x] 根据之前的界面重新设计
- [ ] LED灯？
- [ ] 使用两个定时器控制左右电机
- [ ] 显示频率，加微调按钮

<br>

## TODO

- [x] 汉化新界面
- [x] 把新界面移植开发板
- [ ] 新界面初始化
  - Scrollbar和速度显示同步
  - 当停止时显示为0，启动时显示当前转速
- [ ] 界面逻辑处理
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

左右电机独立控制界面（左禁止/启动按钮，右禁止/启动按钮 -->对应 `mode`）

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
