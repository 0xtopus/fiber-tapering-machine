# 程序说明文档

本文档针对 `FTM_v1.0` 工程进行说明。其他工程作为历史版本，部分内容的实现也可以参考本文档。

## 程序结构

本工程基于正点原子emWin移植模板工程（“EMWIN实验2 STemWin带UCOS移植”）开发。工程结构粗略可以划分为三个层级，互相隔离，互不影响，提供了良好的可移植性：

1. 用户界面文件：所有和EMWIN相关的文件，提供GUI界面；
2. 中间控制层文件：给用户界面提供接口来操作底层外设和提供数据，主要由`HARDWARE` 目录里的`motorcontrol.c` 实现；
3. 底层文件，除上述文件外的其他文件，是整个工程运行的基础；



## 文件说明

### main.c

初始化系统各项功能，包括led、串口、adc、uCOS等等。

初始化完毕后创建3个任务：LED0任务、触摸屏任务和emWin任务，3个任务分时复用cpu。我们开发的重点在emWin任务。



### adc.c

ADC采样配置文件。

硬件上原计划使用PF8和PF9端口，现程序使用的是PF8。

配置为软件触发，通道是ADC3_IN6。

使用定时器3中断触发，采样420个数据后（因为在`FTM_FrameDLG.c`中将emWin的graph控件设置为420个像素点且绑定的数据大小为420个数据）将在`MainTask()`函数的`while(1)`无限循环中读取并将数据添加给graph控件，在LCD上显示采样波形。



### timer.c

定时器配置文件。总共用到3个定时器：

- 配置了两个定时器产生PWM波，每个定时器2路通道，总共产生4路PWM波控制两个电机的正反转；
- 还配置了一个定时器产生中断触发ADC采样；

原计划使用PE5、PE6、PF6和PF7进行电机控制并在硬件上留出了对应的接口，**但现在程序中使用的是**：

|     端口      |   功能   |
| :-----------: | :------: |
| PE5（右拉锥） | TIM9_CH1 |
| PE6（右复位） | TIM9_CH2 |
| PB6（左拉锥） | TIM4_CH1 |
| PB7（左复位） | TIM4_CH2 |

注意TIM9和TIM4的时钟一个是APB2 * 2，一个是APB1 * 2，因此配置分频系数的时候一个是216，一个是108，详见中文参考手册。

用于产生ADC采样中断的是TIM3，时钟是APB1* 2。相关的初始化在`FTM_FrameDLG.c`中完成（时钟分频为1MHz，重载值由结构体成员`oscilldev.div`定义，当前设置为50，TIM3中断触发一次ADC采样，采样率为20kHz）。



### motorcontrol.c

负责给emWin图形界面提供接口来操作电机的启停，转速，方向等等。

电机的主要数据都由结构体 `MotorConfig` 反映：

```c
typedef struct 
{
    u16 set_left_speed;     // Left motor speed to be set, equals to reload value of Timer
    u16 set_right_speed;    // Right motor speed to be set, equals to reload value of Timer
    u16 real_left_speed;    // Realtime Left motor speed (reload value of timer), unless it is 0 which means stop
    u16 real_right_speed;   // Realtime Right motor speed (reload value of timer), unless it is 0 which means stop
    u8 direction;    // 0: Get closer; 1: Go reversely
} MotorControlStruct;

extern MotorControlStruct MotorConfig;	// 可以不向外暴露这个结构体，如果您不希望外界直接篡改这个结构体的值的话
```

这里的预设速度（set_xxx_speed）表示如果要在此刻让电机开始运转，写入实际速度（real_xxx_speed）的值。**结构体MotorConfig里的速度都是用定时器Arr寄存器的值**（定时器每次的重新装载值，由前面 `timer.c` 的配置可知，设置定时器时钟分频为1MHz，则定时器产生PWM波的频率是 1MHz / Arr）来表示的，而在emWin控件里显示的速度需要进行转换之后才能写入结构体，详情可以见下面emWin程序文件的相关部分。

使用预设速度和实际速度的好处是，所有emWin控件的设定速度和实际速度的读取和写入都来源于这些速度成员，任何时候电机的转速值只会来源于这两个变量，从而免去不同控件修改速度后可能造成的设定混乱，便于统一。

当你想知道实际速度时，只需要读取 `real_xxx_speed` 的值来获取（可为 0 或 500 ~ 5000）, 为0即代表电机停止，如果为 500 ~ 5000，则代表电机运行时的实际Arr寄存器值。而 `set_xxx_speed` 则提供一个缓冲，是电机开启运转时唯一的参考设定速度，只有在运行时才将 `set_xxx_speed` 的值赋值给 `real_xxx_speed` 。**`set_xxx_speed`的取值范围为500 ~ 5000，<u>不能为0</u>！**

`direction` 成员表示电机运转的方向，0是靠近中心，1是远离中心。一般会用 `motorcontrol.h` 里的宏定义来设定，以避免魔法数字，增加程序的可读性。

#### 宏定义

```c
#define TIM_LEFT_HANDLE &TIM4_Handler	// 用来产生PWM波的定时器句柄，在timer.c里定义
#define TIM_RIGHT_HANDLE &TIM9_Handler	// 用来产生PWM波的定时器句柄，在timer.c里定义

#define GET_CLOSER 0
#define GET_AWAY   1

#define RIGHT_MOTOR 1
#define LEFT_MOTOR  0

typedef enum  
{
    REAL_LEFT_SPEED = 0,
    REAL_RIGHT_SPEED,
    SET_LEFT_SPEED,
    SET_RIGHT_SPEED,
    DIRECTION
} MotorItems;
```

#### API

```c
u8 MotorInit(void);				// 初始化结构体
u8 ChangeDirection(void);		// 改变方向
u8 StopSpecificMotor(u8 the_given_motor);
u8 StartSpecificMotor(u8 the_given_motor);
u16 ChangeSpecificSpeed(u16 set_value, u8 the_given_motor);
u16 UpdateSpecificRealSpeed(u16 new_speed, u8 the_given_motor);
u16 GetMotorConfig(MotorItems item);
u16 SetMotorConfig(MotorItems item, u16 new_state);

char* Int2String(int num,char *str);
int String2Int(char *str);
```



### emWin配置文件

如果需要修改分配给emWin图形界面内存的大小，请至 `EMWIN_CONFIG -- GUIConf.c` 里修改对应的宏定义，如：

```c
#define USE_EXRAM  1	// 0使用内部RAM, 1使用外部RAM
//设置EMWIN内存大小
#define GUI_NUMBYTES  (1024*1024)
#define GUI_BLOCKSIZE 0X80  //块大小
```

- 如果需要修改横屏/竖屏：请先创建适配自己屏幕方向和大小的emWin界面（可以使用GUIBuilder），然后到 `HARDWARE -- tftlcd.c` 里找到`void TFTLCD_Init(void)`函数，修改以下语句：

  ```c
  LCD_Display_Dir(1);		// 1为横屏显示，0为竖屏显示
  ```

​	上述方法适用于MCU LCD，如果你用RGB LCD，方法类似。



### 用户自定义界面文件

用户自行创建的emWin图形界面相关文件在工程目录`EMWIN_DEMO`中。

目录结构如下：

```markdown
FTM_V1.0\EMWIN
├─Demo
│      DualCtrl_WinDLG.c
│      FTM_FrameDLG.c
│      FTM_FrameDLG.h
│      SingCtrl_WinDLG.c
├─FONT
|		MSBlack24.c
```

其中，`FTM_FrameDLG.c`是主页面文件，`DualCtrl_WinDLG.c` 和 `SingCtrl_WinDLG.c` 是两个控制界面的窗口文件，在初始化界面时被生成并绑定在主页面中，可以通过 `模式` 按钮在这两个窗口之间切换。

`MSBlack24.c` 代表24像素的微软雅黑字体文件，里面是汉化界面所要用到的字体文件。

可以使用 Visual Studio 2019来在电脑上运行仿真，具体的方法可以参考本工程的 `note.md` 文档的相关部分或正点原子的《emWin开发手册》相关章节。

注意，仿真仅仅是对显示界面布局进行模拟和微调，与实际的程序文件内容有所不同，也没有实际的功能。你可以在本工程的GUI文件夹下找到用于仿真的文件。

仿真界面示例：

<img src=".\Images\CodingSpec_img\SingCtrl_Simu.png" style="zoom:75%;" />

#### FTM_FrameDLG.c

1. Graph控件的设置：

   在回调函数 `static void _cbDialog(WM_MESSAGE *pMsg)` 里进行配置。

   控件的总面积为470*400像素，边框大小的宏定义为：

   ```c
   #define BORDER_TOP        	20
   #define BORDER_BOTTOM     	20
   #define BORDER_LEFT       	40
   #define BORDER_RIGHT      	10
   ```

   可计算出**显示区域为420*360**像素；

   

   刻度的宏定义为：

   ```c
   #define SCALE_FACTOR 1
   #define V_SCALE_SETOFF 180
   
   #define V_SCALE_POS 30
   #define H_SCALE_POS 385
   #define V_SCALE_UNIT  20
   #define H_SCALE_UNIT  40
   ```

   其中，刻度的缩放系数为1，即刻度值即为像素值。实际上这是一个float型的参数，如果设置为0.1则为刻度值为像素值缩小10倍。

   垂直坐标偏移量为180像素，即t轴向上平移180像素。

   `x_SCALE_POS` 代表创建刻度时，刻度相对于GRAPH控件的位置。

   `x_SCALE_UNIT` 代表显示的单位刻度，类型为unsigned int，如缩放系数为1，此项设置成20，则刻度显示为：0，20，40，60...

   由于ADC的采样范围为0 ~ 3.3V，因此这样设置后可以假定0V对应y轴-165刻度的位置，3.3V对应+165刻度的位置，单位为mV。t轴范围为0 ~ 420，若数据长度为420，则显示的时间范围为：采样时间 * 数据长度（由结构体成员`oscilldev.div`定义，当前设置为50，TIM3中断触发一次采样（时钟分频为1MHz），因此采样率为20kHz）。

   关于结构体`oscilldev` 的更多细节可以参考正点原子emWin开发手册关于Graph控件的章节。

   设计硬件采样电路时请根据实际需求合理调整电压转换范围和这些参数。

   

2. `MainTask()`函数：

   在`main()`函数创建emWin任务后即跳转到此函数。主要是完成emWin图形界面的初始化，注意界面显示汉字需要使能UTF8编码： `GUI_UC_SetEncodeUTF8()` 。在`while(1)`循环里主要处理ADC采样的数据和根据操作更新图形界面的状态，这里利用了和正点原子例程类似的思路，更多细节可以参考正点原子emWin开发手册关于Graph控件的章节。。

   注意在使用添加数据函数添加数据时对数据进行了处理，您可以根据自己的实际需要来对数据进行处理。

   ```c
   // 向GRAPH图形小工具添加数据,缩20倍并向上平移100格，则y轴-80刻度对应的实际ADC口的电压是0V，80多一点儿的地方对应的实际ADC电压是3.3V
   GRAPH_DATA_YT_AddValue(oscilldev.graphdata, oscilldev.buffer[i] / 20 + 100);
   ```

   

#### SingCtrl_WinDLG.c

单电机控制窗口文件。

**控件名缩写解释：**

- Btn：button
- RRSp：real right speed
- LRSp：real left speed
- SRSp：set right speed
- SLSp：set left speed
- SSp：set speed
- Ldn: left down
- Rdn: right down
- Lup：left up
- Rup：right up



**控件数组：**

可以用来获取对应的控件句柄，如下：

```c
GUI_HWIN _aSingleButton[4];	// 单电机控制窗口文件里的按钮控件句柄数组，分别对应：
							// 0:开始按钮; 1:方向按钮； 2：左开始按钮 3：右开始按钮

GUI_HWIN _aSingleEdit[4];	// 单电机控制窗口文件里的Edit控件句柄数组，分别对应：
							// 0:实际左转速; 1:实际右转速； 2：预设左转速 3：预设右转速

GUI_HWIN _aSingleSlider[2];	// 单电机控制窗口文件里的Slider控件句柄数组，分别对应：
							// 0:左电机转速Slider; 1:右电机转速Slider；
```



要引用数组内的控件，可以利用在`FTM_FrameDLG.h`和`motorcontrol.h`里定义的枚举结构成员和宏定义：

```c
#define SET_DUAL_SPEED 2

#define SINGLE_LEFT_SLIDER 0
#define SINGLE_RIGHT_SLIDER 1

typedef enum  
{
    DualStartBtn = 0,
    DirBtn,
    LStartBtn,
    RStartBtn
} _enumSingleButton;
```

及：

```c
#define RIGHT_MOTOR 1
#define LEFT_MOTOR  0

typedef enum  
{
    REAL_LEFT_SPEED = 0,
    REAL_RIGHT_SPEED,
    SET_LEFT_SPEED,
    SET_RIGHT_SPEED,
    DIRECTION
} MotorItems;
```



**编写原则**

- 在回调函数` _cbDialog(WM_MESSAGE *pMsg)` 对应的控件下调用`motorcontrol.c` 里的函数来完成对硬件的控制，通过调用emWin的库函数对图形界面的显示和控件进行操作（emWin的库函数的使用说明请参考《emWin中文手册》）。

- 在页面内的滑块和调速按钮、启停按钮之负责更新自己页面内参数的显示。所有涉及到两个交互逻辑数据显示的更新同步都在点击“模式”按钮时完成，

- **注意**，在设定转速相关逻辑的时候，有时候会看见类似这样的转换形式：

  ```c
  value = SLIDER_GetValue(DualSlider);
  ....
  SetMotorConfig(SET_LEFT_SPEED, (u16)(-value + 5500));
  ```

  这里的value之所以<u>需要取负号加上5500</u>再更新到MotorConfig结构体里，是因为<u>结构体MotorConfig里的速度都是用定时器arr寄存器的值来表示的</u>（即定时器每次的重新装载值，由前面 `timer.c` 的配置可知，设置定时器时钟分频为1MHz，则定时器产生PWM波的频率是 1MHz / Arr），而在emWin界面上显示的是范围由慢到快是500 ~ 5000，这样转换之后PWM波的频率范围为200Hz ~ 2kHz，比较符合各种使用场景的转速需求。

  

#### DualCtrl_WinDLG.c

双电机控制界面，和`SingCtrl_WinDLG.c` 的设计思路是一样的，可以参考上面的说明。只不过一个是控制双电机的页面，一个是控制单电机的页面。

**控件数组和变量**：

可以用来获取对应的控件句柄，如下：

```c
// 双电机控制窗口文件里的Edit控件句柄数组，分别对应：
// 0:实际左转速; 1:实际右转速； 2：预设双电机转速
GUI_HWIN _aDualEdit[3];
// 双电机控制窗口文件里的按钮控件句柄数组，分别对应：
// 0:开始按钮; 1:方向按钮
GUI_HWIN _aDualButton[2];
// 双电机滑块
GUI_HWIN DualSlider;
```



编写原则**

- 在回调函数` _cbDialog(WM_MESSAGE *pMsg)` 对应的控件下调用`motorcontrol.c` 里的函数来完成对硬件的控制，通过调用emWin的库函数对图形界面的显示和控件进行操作（emWin的库函数的使用说明请参考《emWin中文手册》）。

- 在页面内的滑块和调速按钮、启停按钮之负责更新自己页面内参数的显示。所有涉及到两个交互逻辑数据显示的更新同步都在点击“模式”按钮时完成，

- **注意**，在设定转速相关逻辑的时候，有时候会看见类似这样的转换形式：

  ```c
  value = SLIDER_GetValue(DualSlider);
  ....
  SetMotorConfig(SET_LEFT_SPEED, (u16)(-value + 5500));
  ```

  这里的value之所以<u>需要取负号加上5500</u>再更新到MotorConfig结构体里，是因为<u>结构体MotorConfig里的速度都是用定时器Arr寄存器的值来表示的</u>（即定时器每次的重新装载值，由前面 `timer.c` 的配置可知，设置定时器时钟分频为1MHz，则定时器产生PWM波的频率是 1MHz / Arr），而在emWin界面上显示的是范围由慢到快是500 ~ 5000，这样转换之后PWM波的频率范围为200Hz ~ 2kHz，比较符合各种使用场景的转速需求。









## 硬件设计

因为设计问题，**软件上的一些配置可能与下面列出的硬件不一样**，具体可参考上面程序文件说明部分的相关部分。下面列出的是原计划使用的引脚及其对应的功能。

芯片是STM32F767ZGT6.

### 一、串口

用跳线帽连接留出的USART排针即可使用串口。

|   端口    | 引脚 |
| :-------: | :--: |
| USART1_TX | PB6  |
| USART1_RX | PB7  |

### 二、ADC采样

|   端口   | 引脚 |
| :------: | :--: |
| ADC3_IN6 | PF8  |
| ADC3_IN7 | PF9  |

### 三、PWM输出

使用定时器产生PWM波，**原计划使用的端口**是：

|     端口      |   功能    |
| :-----------: | :-------: |
| PE5（右拉锥） | TIM9_CH1  |
| PE6（右复位） | TIM9_CH2  |
| PF6（左拉锥） | TIM10_CH1 |
| PF7（左复位） | TIM11_CH1 |

### 四、MCU LCD

|       信号线       |                  对应I/O                  |
| :----------------: | :---------------------------------------: |
|    FMC_D0 ~ D3     | PD14(85) / PD15(86) / PD0(114) / PD1(115) |
|    FMC_D4 ~ D6     |        PE7(58) / PE8(59) / PE9(60)        |
|    FMC_D7 ~ D10    | PE10(63) / PE11(64) / PE12(65) / PE13(66) |
|   FMC_D11 ~ D12    |            PE14(67) / PE15(68)            |
|   FMC_D13 ~ D15    |       PD8(77) / PD9(78) / PD10(79)        |
| LCD_BL（普通GPIO） |                 PG3（88）                 |
|  LCD_CS (FMC_NE1)  |                 PD7(123)                  |
|  LCD_RS (FMC_A18)  |                 PD13(82)                  |
|  LCD_WR (FMC_NWE)  |                 PD5(119)                  |
|  LCD_RD (FMC_NOE)  |                 PD4(118)                  |

### 五、触摸芯片引脚

使用的芯片是GT9147。

总共5根线。全部配置为普通GPIO，无需复用。

| 信号线 |  对应I/O   |
| :----: | :--------: |
| T_MOSI | PC8（98）  |
| T_MISO | PB13（74） |
| T_SCK  | PB12（73） |
|  T_CS  | PC9（99）  |
| T_PEN  | PD11（80） |

### 六、SDRAM

- |    信号线     |                  对应I/O                  |
  | :-----------: | :---------------------------------------: |
  |  FMC_D0 ~ D3  | PD14(85) / PD15(86) / PD0(114) / PD1(115) |
  |  FMC_D4 ~ D6  |        PE7(58) / PE8(59) / PE9(60)        |
  | FMC_D7 ~ D10  | PE10(63) / PE11(64) / PE12(65) / PE13(66) |
  | FMC_D11 ~ D12 |            PE14(67) / PE15(68)            |
  | FMC_D13 ~ D15 |       PD8(77) / PD9(78) / PD10(79)        |
  |   FMC_NBL0    |                 PE0(141)                  |
  |   FMC_NBL1    |                 PE1(142)                  |
  |   FMC_SDNWE   |                  PA7(43)                  |
  |  FMC_SDNCAS   |                 PG15(132)                 |
  |   FMC_SDCLK   |                  PG8(93)                  |
  |  FMC_SDNRAS   |                 PF11(49)                  |
  |  FMC_SDCKE0   |                  PC5(45)                  |
  |   FMC_SDNE0   |                  PC4(44)                  |
  |    FMC_BA0    |                  PG4(89)                  |
  |    FMC_BA1    |                  PG5(90)                  |
  |    FMC_A10    |                  PG0(56)                  |
  |  FMC_A0 ~ A2  |        PF0(10) / PF1(11) / PF2(12)        |
  |  FMC_A3 ~ A5  |        PF3(13) / PF4(14) / PF5(15)        |
  |  FMC_A6 ~ A9  | PF12(50) / PF13(53) / PF14(54) / PF15(55) |
  | FMC_A10 ~ A12 |       PG0 (56) / PG1 (57) / PG2(87)       |

### 七、LED

|     端口     | 引脚 |
| :----------: | :--: |
|  LED0 (RED)  | PE3  |
| LED1 (GREEN) | PE2  |

### 八、按键

| 端口 | 引脚 |
| :--: | :--: |
| KEY0 | PC2  |
| KEY1 | PC3  |

### 九、FPC

支持40P的RGB MCU，不过在本项目中没有用到。

|       信号线       |                          I/O                          |
| :----------------: | :---------------------------------------------------: |
|      LCD_CLK       |                        PG7(92)                        |
|     LCD_HSYNC      |                        PC6(96)                        |
|     LCD_VSYNC      |                        PA4(40)                        |
|       LCD_DE       |                       PF10(22)                        |
| LCD_BL（普通GPIO） |                        PG3(88)                        |
|     LCD_R[7:5]     |             PG6(91) / PA8(100 / PA9(101)              |
|     LCD_R[4:3]     |                  PA11(103 / PB0(46)                   |
|     LCD_G[7:5]     |             PB5(135) / PC7(97) / PB11(70)             |
|     LCD_G[4:2]     |            PB10(69) / PG10(125) / PA6(42)             |
|     LCD_B[7:3]     | PB9(140) / PB8(139) / PA3(37) / PG12(127) / PG11(126) |
