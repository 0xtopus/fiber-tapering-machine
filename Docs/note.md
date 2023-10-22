# 资料集合

[STM32分步指南入门(Getting started with STM32: STM32 step-by-step)](https://wiki.stmicroelectronics.cn/stm32mcu/wiki/STM32StepByStep:Getting_started_with_STM32_:_STM32_step_by_step)



# STM32芯片命名规则

可见数据手册datasheet的第八章：《Ordering Information》

ref:

[Understanding STM32 Naming Conventions](https://www.digikey.com/en/maker/blogs/2020/understanding-stm32-naming-conventions)

[STM32命名规则解读](https://zhuanlan.zhihu.com/p/266122494)

# 查询程序大小

[ARM Program Size - ZI data](https://community.arm.com/support-forums/f/keil-forum/20991/arm-program-size---zi-data)

[How size of hex file is calculated?](https://community.arm.com/support-forums/f/keil-forum/34036/how-size-of-hex-file-is-calculated)

# 时钟

总共5个时钟源：HSI，HSE，LSI，LSE，PLL

根据正点原子开发指南：

SYSCLK = 216MHz，系统时钟源为PLL

AHB的分频系数为1，为216MHz

APB1分频系数为4，为54MHz

APB2分频系数为2，为108MHz



# GPIO配置

http://www.openedv.com/posts/list/32730.htm

找各种引脚复用等，请参考datasheet（数据手册）。



# 中断系统

## 一、优先级的配置

**配置中断优先级分组**：修改`main.c`里的初始化函数`HAL_Init()`里的中断优先级分组配置函数代码：

```c
HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_X);
```

**确定相应优先级和抢占优先级**的库函数：

```c
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
```

## 二、定时器中断

### 2.1 定时器时钟

> 计数器时钟可由下列时钟源提供： 
>
> - 内部时钟 (CK_INT) 
> - 外部时钟模式 1：外部输入引脚 (TIx) 
> - 外部时钟模式 2：外部触发输入 (ETR)
> - 外部触发输入 (ITRx)

我们使用**内部时钟**，此时通用定时器TIM2 ~ 5的时钟来源于APB1，当APB1时钟分频数为1时，二者时钟相等；当然，更常见的情况是**APB1的时钟分频不为1，此时定时器的时钟是APB1的2倍**。

TIM9 ~ 14的时钟来源为APB2。



# LCD
RGB LCD和MCU LCD是不一样的。

**主要区别：**

MCU接口方式：显示数据写入DDRAM，常用于静止图片显示。

RGB接口方式：显示数据不写入DDRAM，直接写屏，速度快，常用于显示视频或动画用。

详见：[嵌入式LCD的接口类型详解](https://zhuanlan.zhihu.com/p/408175453#:~:text=%E5%B5%8C%E5%85%A5%E5%BC%8FLCD%E7%9A%84%E6%8E%A5%E5%8F%A3%E7%B1%BB%E5%9E%8B%E8%AF%A6%E8%A7%A3%201%201.MCU%E6%8E%A5%E5%8F%A3%3A%E4%BC%9A%E8%A7%A3%E7%A0%81%E5%91%BD%E4%BB%A4%EF%BC%8C%E7%94%B1timing%20generator%E4%BA%A7%E7%94%9F%E6%97%B6%E5%BA%8F%E4%BF%A1%E5%8F%B7%EF%BC%8C%E9%A9%B1%E5%8A%A8COM%E5%92%8CSEG%E9%A9%B1%E5%99%A8%E3%80%82%20RGB%E6%8E%A5%E5%8F%A3%3A%E5%9C%A8%E5%86%99LCD%20register,setting%E6%97%B6%EF%BC%8C%E5%92%8CMCU%E6%8E%A5%E5%8F%A3%E6%B2%A1%E6%9C%89%E5%8C%BA%E5%88%AB%E3%80%82%20%E5%8C%BA%E5%88%AB%E5%8F%AA%E5%9C%A8%E4%BA%8E%E5%9B%BE%E5%83%8F%E7%9A%84%E5%86%99%E5%85%A5%E6%96%B9%E5%BC%8F%E3%80%82%202%202.%E7%94%A8MCU%E6%A8%A1%E5%BC%8F%E6%97%B6%E7%94%B1%E4%BA%8E%E6%95%B0%E6%8D%AE%E5%8F%AF%E4%BB%A5%E5%85%88%E5%AD%98%E5%88%B0IC%E5%86%85%E9%83%A8GRAM%E5%90%8E%E5%86%8D%E5%BE%80%E5%B1%8F%E4%B8%8A%E5%86%99%EF%BC%8C%E6%89%80%E4%BB%A5%E8%BF%99%E7%A7%8D%E6%A8%A1%E5%BC%8FLCD%E5%8F%AF%E4%BB%A5%E7%9B%B4%E6%8E%A5%E6%8E%A5%E5%9C%A8MEMORY%E7%9A%84%E6%80%BB%E7%BA%BF%E4%B8%8A%E3%80%82%20%E7%94%A8RGB%E6%A8%A1%E5%BC%8F%E6%97%B6%E5%B0%B1%E4%B8%8D%E5%90%8C%E4%BA%86%EF%BC%8C%E5%AE%83%E6%B2%A1%E6%9C%89%E5%86%85%E9%83%A8RAM%EF%BC%8CHSYNC%EF%BC%8CVSYNC%EF%BC%8CENABLE%EF%BC%8CCS%EF%BC%8CRESET%EF%BC%8CRS%E5%8F%AF%E4%BB%A5%E7%9B%B4%E6%8E%A5%E6%8E%A5%E5%9C%A8MEMORY%E7%9A%84GPIO%E5%8F%A3%E4%B8%8A%EF%BC%8C%E7%94%A8GPIO%E5%8F%A3%E6%9D%A5%E6%A8%A1%E6%8B%9F%E6%B3%A2%E5%BD%A2.%203%203.MPU%E6%8E%A5%E5%8F%A3%E6%96%B9%E5%BC%8F%EF%BC%9A%E6%98%BE%E7%A4%BA%E6%95%B0%E6%8D%AE%E5%86%99%E5%85%A5DDRAM%EF%BC%8C%E5%B8%B8%E7%94%A8%E4%BA%8E%E9%9D%99%E6%AD%A2%E5%9B%BE%E7%89%87%E6%98%BE%E7%A4%BA%E3%80%82)

当前使用的 MCU LCD的编号id是5510，可以通过对应的读取指令来读取。

RGB LCD的id：

> 《STM32F7开发指南-HAL库版本》：p391:
>
> ...而LCD_R7/G7/B7则用来设置LCD的ID，由于RGB LCD没有读写寄存器，也就没有所谓的ID，这里我们通过在模块上面，控制R7/G7/B7的上/下拉，来定义LCD模块的ID，帮助MCU判断当前LCD的分辨率和相关参数，以提高程序兼容性。



**TFTLCD：**

> TFT-LCD（Thin Film Transistor-LiquidCrys-talDisplay） -- 薄膜晶体管液晶显示
>
> TFT-LCD是一种本身不发光的被动型显示器件，利用液晶的电光效应、通过交流电场控制显示部位光强度，实现图像显示。用两块特殊的玻璃夹住液晶体，通过8比特驱动电路和高效背灯系统来调节成像，使超薄型化成为可能。TFT-LCD具有图像逼真、画质细腻、层次丰富、立体感强，以及高亮度、宽视角、高清晰、超薄、省电、无闪烁、无辐射等优点。
>
> 来源: [通信百科](https://baike.c114.com.cn/view.asp?id=10602-F702B7AC)



## Datasheet 
<a href="https://max.book118.com/html/2020/0724/5132043242002321.shtm">Alientek 4.3' TFTLCD</a>

4.3寸 ：62.25mm*117.5mm 见[资料](http://47.111.11.73/docs/modules/lcd/4.3-TFT%20LCD-800480.html)

## 80并口的信号线
CS：片选信号
WR：写入信号
RD: 读取信号
D[15:0]：16位数据线
RST: 硬复位
RS: 数据\命令标志（0表示命令，1表示数据）

另外，LCD还需要一个BL背光接口（设置为普通的GPIO，推挽输出即可）

使用的LCD的芯片型号为5510，但这里以9341为例，其具有支持18位模式的显存大小。在16位模式下，使用RGB565格式。MCU的数据线为16位，对应的GRAM关系：

<img src=".\Images\9341GRAMtoMCU.png" style="zoom:90%;" />

D12和D0没有被用到。



**读取过程：**

1. 先根据处理的是命令还是数据，设置RS位，然后决定是读取还是写入。
2. 拉低片选信号CS，选择对应的模块
3. 如果读数据，则在RD的上升沿使得数据所存到数据线上；WR置高位。
4. 如果写数据，则在WR的上升沿把数据写入对应的模块；RD置高位。



数据是16位的，而所有指令都是8位的，即高8位是无效的。



## LCD指令

- 0xD3: 读取LCD驱动器的型号
- 0x36：控制9341的读写方向
- 0x2a: 列地址设置指令，用来设置横坐标
- 0x2b: 页地址设置指令，用来设置纵坐标
- 0x2c: 写GRAM指令，写入颜色数据
- 0x2e：读GRAM
- <img src=".\Images\TFT_workflow.png" style="zoom:80%;" />

我们把LCD当成SRAM来控制，所以用到FMC模块。 

外部SRAM通常有：地址线，信号线，片选信号，读取信号，写信号。 

而LCD具有RS，WR，RD，D0~D15，CS和RST和BL，操作LCD只需要RS，WR，RD，D0~D15，CS。

除了RS之外，控制时序和SRAM完全一致，而RS我们可以使用一根地址线来模拟，为0是命令，为1是数据。

## FCM--可变存储控制器
总共管理1.5GB空间，分为6个存储块（bank），每个存储块大小为256MB，分为4个区，每个区大小为64MB。

Bank1的256MB = $ {2}^{28} $由HADDR[28:0]来寻址，其中[26:27]是对四个区进行选择。[25:0]是外部存储器的地址，LCD屏使用16位宽度，FMC内部HADDR与存储器寻址地址的关系：HADDR[25:1] -> FMC_A[24:0] (按字寻址，所以要除以2)

HCLK时钟周期为4.6ns左右。读取数据的速度会慢一些，数据保持时间大约为80个HCLK周期，地址保持时间为15个HCLK周期；写数据会快一些，两个时间都只需要4个HCLK周期就可以了。

FMC_BCRx: 片选控制寄存器
FMC_BTRx: 片选时序寄存器
它们被组合成了BTRCR[8]寄存器组
FMC_BWTRx: 闪写时序寄存器
组合成BWTR[7]



## 编程
- 字符集点阵数据提取方式：见十六章
- 在`lcd.c`里有一个重要的结构体：
  ```c
    //LCD重要参数集
    typedef struct  
    {		 	 
	    u16 width;		//LCD 宽度
        u16 height;		//LCD 高度
        u16 id;			//LCD ID
        u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
        u16 wramcmd;	    //开始写gram指令
        u16 setxcmd;		//设置x坐标指令
        u16 setycmd;		//设置y坐标指令 
    }_lcd_dev; 	  
  ```
  其中，5510的参数如下：
    ```c
        lcddev.width = 480;
        lcddev.height = 800;
    ```

- `void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)`: 当size和height为32时，一个字母大约宽度为12.5

<br>

# 触摸屏实验

<span style="color:red; font-weight:bold">注：如果你打算使用emWin来创建图形界面那么你会发现emWin<u>操作触摸屏的方式</u>和本节内容<u>操作触摸屏的方式</u>是没什么关联的</span>

> 正点原子：p601：
>
> 电容触摸屏一般都需要一个驱动IC来检测电容触摸，且一般都是使用IIC接口输出触摸数据。....本例程除了CPLD方案的V1版本7寸屏幕模块不支持以外，其他所有Alientek的LCD模块都支持。

我们使用的是电容屏幕，使用GT9147集成芯片驱动来检测电容触摸。**电容屏幕无需校准。**

**其他补充**：FT5206和FT5426的驱动代码是一模一样的，在正点原子的例程里它们共用一个`.c`文件。

## GT9147
四根线：SDA、SCL、RST、INT

IIC对应的两根线，复位一根线，中断输出信号一根线

- IIC地址：复位后5ms内INT为高电平，则为0x14，否则为0x5D
- 只要简单初始化就可以使用：硬复位-->延时10ms -> 结束硬复位--> 设置IIC地址 --> 延时100ns --> 软复位 --> 更新配置 --> 结束软复位; 之后，不停查询0x814E寄存器检查是否有触点按下
- 详情可参考开发指南和GT9147编程指南.pdf



## 软件编程
```c
//触摸屏控制器
typedef struct
{
	u8 (*init)(void);			//初始化触摸屏控制器
	u8 (*scan)(u8);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);		//触摸屏校准 
	u16 x[CT_MAX_TOUCH]; 		//当前坐标
	u16 y[CT_MAX_TOUCH];		//电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
								//x[9],y[9]存储第一次按下时的坐标. 
	u16 sta;					//笔的状态 
								//b15:按下1/松开0; 
	                            //b14:0,没有按键按下;1,有按键按下. 
								//b13~b10:保留
								//b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
/////////////////////触摸屏校准参数(电容屏不需要校准)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
//   1,横屏(适合左右为Y坐标,上下为X坐标的TP) 
//b1~6:保留.
//b7:0,电阻屏
//   1,电容屏 
	u8 touchtype;
}_m_tp_dev;    
```

在电容触摸屏例程里，定义了结构体实例`tp_dev`：
```c
_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//默认为touchtype=0的数据.
```
<br>

## 如何更改横/竖屏
到`tftlcd.c`文件下找到`void TFTLCD_Init(void)`函数，修改以下语句：
```c
LCD_Display_Dir(1);		// 1为横屏显示，0为竖屏显示
```
<br>

# emWin绘制界面
## 一、VS2019 对 emWin 模拟器编译不成功的解决办法

[法1](https://www.jianshu.com/p/bec48e0de882)<br>
[法2](https://blog.csdn.net/zhuw86/article/details/89186272)

1、配置仿真工程属性。成功打开工程后，右键单击SimulationTrial项目，在弹出的选项中选择属性，配置emWin仿真工程属性；<br>
2、选择配置属性 > 链接器 > 输入<br> 
3、在其中的附加依赖项中添加：`legacy_stdio_definitions.lib`，注意添加分号；<br>
4、在忽略所有默认库中填：否；<br>
5、在忽略特定默认库中添加：`LIBC.lib;LIBCMTD.lib`，具体见图 配置工程链接器输入属性 <br>
6、接下来转到链接器选项中的高级设置，修改映像具有安全异常处理程序的值为：否；<br>
<br>

### 补充
1. <a href="https://www.armbbs.cn/forum.php?mod=viewthread&tid=93882">运行【STemWin5.42】有些例子找不到GUIDRV_Lin.h处理办法</a>

<br>

## 二、调整VS2019中模拟界面大小的方法
在`Config`文件夹下的`LCDConf.c`文件中修改`XSIZE_PHYS`和`YSIZE_PHYS	`这两个宏定义:
```c
//
// Physical display size
//
#define XSIZE_PHYS  800
#define YSIZE_PHYS  480
```

## 准备工作？
<del>keil 务必是 5.30 及其以上版本?</del> 似乎不需要。。

<br>

## 三、使用模拟器查看GUIBuilder创建的页面
可以参考《安富莱_STM32-V7开发板第3版emWin教程》第十一章的相关内容。

### 3.1 使用模拟器查看创建的界面
在模拟器上运行时（这里使用vs2019为例），步骤如下所示:
  1. 打开文件夹`SeggerEval_WIN32_MSVC_MinGW_GUI_V530`里的`sln`例程文件，按<a href="https://www.jianshu.com/p/bec48e0de882">此教程</a>配置VS2019;
  2. 将`Application`目录下的文件全部“从生成中排除”；
  3. 到`Sample`目录下新建一个`.c`文件，或者直接将某个例程（比如`BASIC_HelloWorld.c`）的“属性--从生成中排除”改为不排除，然后将内容全部替换为GUIBuilder生成的`xxxxxDLG.c`文件的源码，并在最下面加上如下代码：
```c
void MainTask(void)
{
    /* 窗口自动使用存储设备 */
    WM_SetCreateFlags(WM_CF_MEMDEV);
    /* 初始化 */
    GUI_Init();
    /* 创建对话框，使用 GUIBulder5.28 生成的对话框创建函数 */
    Createxxxxx(); 		// 这里是看你复制过来的代码的最后一个函数叫啥名就写啥，
						// 比如我的是：	 WM_HWIN CreateMotor_Controller(void);
						// 那我这里就写：CreateMotor_Controller();
						// 默认的名字是：CreateFramewin();
    while (1)
    {
        GUI_Delay(10);
    }
}

```
<br>

## 四、移植到开发板
### 4.1 无操作系统
1. 直接复制正点原子的EmWin例程：`EMWIN实验1 STemWin无操作系统移植`；
2. 打开工程，在keil里新建一个`.c`文件，把你的emWin文件里的代码复制进来；
3. 把刚刚创建的c文件保存到`EMWIN\Demo`文件夹下，并添加到keil工程的`EMWIN_DEMO`目录下；
4. 把keil工程的`EMWIN_DEMO`目录下所有的其他文件统统移除（不然有可能编译的时候会冲突报错）；
5. 把`main.c`里的第50行：
   ```c
   GUIDEMO_Main();		//STemWin 演示demo
   ```
   改成：
   ```c
   MainTask();		// 即你刚刚添加的.c文件里的主函数名
   ```
6. 编译下载即可。

<br>

## 五、窗口和消息
### 如何查找需要的API
可以去《emWin中文参考手册》的“窗口对象”章节下找对应的小工具章节里寻找可能对您有用的API。
如果没有什么头绪，也可以去正点原子的《STM32F767 EMWIN开发手册》里看看相关章节的例程。

常用函数：
- `WM_HWIN WM_GetDialogItem(WM_HWIN hDialog, int Id)`：返回对话框项目的窗口句柄
- `LISTBOX_GetItemSel()`：返回checkbox组件的当前状态
- 

<br>

### 如何操作控件来控制单片机的外设

<span style="color:#bfa">前提</span>：你已经通过GUIBuilder绘制好界面并已经移植到了开发板上

<span style="color:#bfa">目标</span>：点击LCD上的按钮（改变按钮的状态）来使单片机上的某个外设执行你需要的功能

<span style="color:#bfa">操作</span>：

1. 在移植后的`EMWIN_DEMO`目录下打开你所创建的图形界面的`.c`文件
2. 请关注以下2个内容：
   - 回调函数：`_cbDialog(pMsg)`
   - 包含了你创建的界面中所有控件信息的数组：`_aDialogCreate[]`

3. 在 `_cbDialog` 函数里你会发现有很多`switch`语句分支结构。简单来说，整个过程就是在  `_cbDialog` 里的`switch`语句里找到对应控件的事件发生时的`case`，然后把你要单片机在这个控件事件发生时要干的事的程序写到对应的`case`下

<span style="color:#bfa">举例</span>：我的界面里有一个checkbox控件，当它打勾时我需要LED0亮起；当它不打勾时，LED0熄灭。

1. 首先根据需求找到`_cbDialog` 下面对应的`case`：我选择在`case WM_NOTIFICATION_VALUE_CHANGED`，即勾选框状态改变的时候，使用一个条件判断`if-else`语句，调用函数`CHECKBOX_IsChecked(hItem)`（你可以到emWin的中文参考手册里面了解相关的API函数）判断是否打勾来设置LED的状态。
   
   <span style="color:red">注意</span>：我在调用`CHECKBOX_IsChecked(hItem)`之前使用了`WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0)`这个函数来获取相应checkbox的句柄, 其中的第二个参数就是`_aDialogCreate[]`数组里对应组件的id(或者你直接看对应父case的id也成)。

```c

...

case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (Id) {
        case ID_CHECKBOX_0: //! Notifications sent by 'Right_Motor'
            switch (NCode) {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_VALUE_CHANGED:
                {
                    //! 当checkbox "Right_Motor"的状态改变时：
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);  
                    if (CHECKBOX_IsChecked(hItem))
                    {
                        LED1(0);  // 这个宏的定义参见led.h文件  
                    } else {
                        LED1(1);
                    }
                    break;
                }
            }
            break;
        }

        ...
```



## 六、汉字显示

### Unicode

> Unicode目前通用的实现方式是 UTF-16 小端序（LE）、UTF-16 大端序（BE）和 UTF-8。在微软公司 Windows XP 附带的记事本（Notepad）中，“另存为”对话框可以选择的四种编码方式除去非 Unicode 编码的 ANSI（对于英文系统即 ASCII 编码，中文系统则为 GB2312 或 Big5 编码）外，其余三种为“**Unicode”（对应 UTF-16 LE）**、“Unicode big endian”（对应 UTF-16 BE）和“UTF-8”。

### 让控件显示中文

详见《安富莱_STM32-V7开发板第3版emWin教程》第28章。

首先可以用GUIBuilder创建一个带有控件的界面。

这里介绍**使用FontConverter对需要使用的某些特定的汉字生成对应的`.c`文件**，而不是生成整个字库的方法，适合使用汉字量较少的情况。

1. 创建一个记事本，在里面输入你需要使用的汉字，这里我输入：`开始停止` 为例。
2. 另存为记事本，文件名可以根据你的需要命名，建议简洁易懂，比如`FontSong16.txt`，编码设置为`Unicode`（Win10请选择`UTF-16 LE`）
3. 打开FontConverter软件，选择字体类型，编码（比如Standard，16 Bit UNICODE)，点击确定，选择字体，字形和大小（比如“宋体”，“常规”，“16”），Unit of Size 可以选择Pixels，这样就可以手动添加点阵字体的大小
4. 之后点击菜单栏上的“Edit”选项，点击“Disable all characters"
5. 点击菜单栏上的“Edit”选项，点击"Read pattern file"，之后找到并选择你刚刚新建的记事本文件，比如我的是`FontSong16.txt`
6. 点击File->Save as...，将你的字体文件保存为`.c`文件，文件名可自取，但不能包含中文。如果出现提示说"This demo version will not produce a usable output file..."，那么你使用的是demo版本的FontConverter，请参考<a href="https://www.amobbs.com/thread-5501172-1-1.html">这个帖子</a>下载正式版。
7. 创建好字体文件后，可以把字体文件放到你的界面文件的工程文件夹里了，下面介绍一下如何编辑代码使你界面里的控件可以显示你的字体
8. 打开生成的字体 `.c ` 文件，你会看到一行类似这样的语句：
```c
extern GUI_CONST_STORAGE GUI_FONT GUI_FontFontSong16;
```
9. 打开GUIBuilder生成的 `.c ` 界面文件，把上面声明外部变量的语句复制到里面。
9. 在`MainTask()`函数里打开UTF8编码：

```c
void MainTask(void)
{
	...
    /* 初始化 */
    GUI_Init();
    /* 使用UTF8编码 */
	GUI_UC_SetEncodeUTF8();

    ...
}
```

11. 假如你的界面里有一个BUTTOM按钮要使用中文字符：

```c
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {FRAMEWIN_CreateIndirect, "Motor_Controller", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0},
    {BUTTON_CreateIndirect, "开始", ID_BUTTON_0, 326, 309, 100, 45, 0, 0x0, 0},	// 设置为中文字体
}
...
static void _cbDialog(WM_MESSAGE *pMsg){
    switch (pMsg->MsgId)
    {
    	case WM_INIT_DIALOG:
            hItem = pMsg->hWin;
            BUTTON_SetFont(WM_GetDialogItem(hItem, ID_BUTTON_0), &GUI_FontFontSong16);	// 设置为中文字体，注意取地址号"&"
            ...
}
```

你也可以使用其他API来设置：

```c
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
		BUTTON_SetFont(WM_GetDialogItem(hItem, ID_BUTTON_0), &GUI_FontFontSong16);	// 设置为中文字体，注意取地址号"&"
		BUTTON_SetText(hItem, "停止");
```



12. 修改GUIBuilder生成的 `.c ` 界面文件为 UTF-8 编码（不是修改 FontCvt 生成的 C文件为 UTF-8 编码！): 用记事本打开，然后另存为的时候把编码改成UTF-8，保存到原位置替换掉原文件即可。
13. 之后你可以使用VS2019来仿真一下。如果出现 “**报错 error C2001:常量中有换行符**” ，请参考：<a href="https://blog.csdn.net/love_0_love/article/details/120024094">这篇帖子</a>解决。( 项目->右键属性->C/C++ -> 命令行，，在下方输入框添加` /utf-8`，就会在编译时采用utf-8编码来编译)
14. 你也可以跳过仿真直接移植到MDK5。移植方法和之前类似，就是记得要把`.c`字符文件也添加进工程。然后打开魔法棒工具，在 options->c/c++->Misc controls 栏填写 “`--locale=english`”防止报错。



## 七、其他注意事项

改变Timer的周期时，请先停止再重新初始化，直接改寄存器会出bug



## 八、存储设备

一般来说要在`GUI_X_Config()`函数里分配内存。

详见：[A way to make emWin use an external SDRAM instead of internal RAM](https://forum.segger.com/index.php/Thread/8827-A-way-to-make-emWin-use-an-external-SDRAM-instead-of-internal-RAM/?s=cb0ab5cd9f4a7923e27d090b604a08f464dc0810)



或者参考正点原子的例程：

在`GUIConf.c`里:

```c
#define USE_EXRAM  0	// 0使用内部RAM, 1使用外部RAM
#define GUI_NUMBYTES  (128*1024)	// 设置EMWIN内存大小, stm32f767igt6自带的片内RAM为512kB
#define GUI_BLOCKSIZE 0X80  //块大小

//GUI_X_Config
//初始化的时候调用,用来设置emwin所使用的内存
void GUI_X_Config(void) {
	if(USE_EXRAM) //使用外部RAM
	{	
		U32 *aMemory = mymalloc(SRAMEX,GUI_NUMBYTES); //从外部SRAM中分配GUI_NUMBYTES字节的内存
		GUI_ALLOC_AssignMemory((void*)aMemory, GUI_NUMBYTES); //为存储管理系统分配一个存储块
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //设置存储快的平均尺寸,该区越大,可用的存储快数量越少
		GUI_SetDefaultFont(GUI_FONT_6X8); //设置默认字体
	} else  //使用内部RAM
	{
		U32 *aMemory = mymalloc(SRAMIN,GUI_NUMBYTES); //从内部RAM中分配GUI_NUMBYTES字节的内存
		GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //为存储管理系统分配一个存储块
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //设置存储快的平均尺寸,该区越大,可用的存储快数量越少
		GUI_SetDefaultFont(GUI_FONT_6X8); //设置默认字体
	}
}
```



# 原理图绘制

### 错误和教训

- 排针间距！
- usb接口！

[Getting started with STM32F7 Series MCU hardware development(AN4661)](https://www.st.com/resource/en/application_note/dm00164549-getting-started-with-stm32f7-series-mcu-hardware-development-stmicroelectronics.pdf)

[电路板铺地时PCB 地加强孔需不需要打](https://zhidao.baidu.com/question/223418452.html)

- P2576电压转换芯片
- [正点原子STM32F429核心板的插座型号](https://blog.csdn.net/youngwah292/article/details/119495119#:~:text=%E8%BF%99%E4%B8%A4%E4%B8%AA%E6%8F%92%E5%BA%A7%E5%9E%8B%E5%8F%B7%E6%98%AF%E4%BB%80%E4%B9%88%EF%BC%9F%20%E5%9C%A8%E6%A0%B8%E5%BF%83%E6%9D%BF%E4%B8%8A%E5%AE%89%E8%A3%85%E7%9A%84%E8%BF%99%E4%B8%A4%E4%B8%AA%E6%8F%92%E5%BA%A7%EF%BC%8C%E6%98%AF3710F%E6%8F%92%E5%BA%A7%EF%BC%88%E5%85%AC%E5%A4%B4%EF%BC%89%E3%80%82,%E9%82%A3%E4%B9%88%E4%B8%8E%E4%B9%8B%E5%AF%B9%E5%BA%94%E7%9A%84%E6%98%AF3710F%E6%8F%92%E5%BA%A7%EF%BC%88%E6%AF%8D%E5%BA%A7%EF%BC%89%EF%BC%8C%E5%A6%82%E4%B8%8B%E5%9B%BE%E6%89%80%E7%A4%BA%E3%80%82%20%E5%AE%83%E6%9C%8960%E4%B8%AA%E5%BC%95%E8%84%9A%EF%BC%8C%E4%B8%A4%E4%BE%A7%E5%90%8430%E4%B8%AA%E3%80%82%20%E6%AD%A3%E7%82%B9%E5%8E%9F%E5%AD%90%E5%AE%98%E7%BD%91%E6%9C%89%E8%BF%99%E7%A7%8D%E8%B4%AD%E4%B9%B0%E8%BF%9E%E6%8E%A5%EF%BC%8C%E5%8F%AF%E4%BB%A5%E6%90%9C%E7%B4%A2%E2%80%9C3710F%E6%9D%BF%E5%AF%B9%E6%9D%BF%E8%BF%9E%E6%8E%A5%E5%99%A8%E2%80%9D%E6%9F%A5%E6%89%BE%E8%B4%AD%E4%B9%B0%E3%80%82)

## 问题

- [x] EEPROM用来干啥 --- 用于存储一些掉电不能丢失的重要数据，比如系统设置的一些参数/触摸屏的校准数据等等。
- [x] 是否需要电压测试端？

- [x] BOOT0和BOOT1 --- 为什么要通过电阻接地: [STM32 programming and BOOT0 pin](https://electronics.stackexchange.com/questions/431871/stm32-programming-and-boot0-pin)

- [x] 中文参考手册：VREF– 如果可用（**取决于封装**），则必须将其连接到 VSSA。？

- [x] 模拟地和数字地

> 这里还需要说明一下ADC的参考电压，阿波罗STM32F7开发板使用的是STM32F7IGT6，该芯片只有Vref+参考电压引脚，输入范围为：1.8 ~ VDDA。开发板通过P5端口，来设置Vref+的参考电压，默认的是我们通过跳线帽将ref+接到3.3V,参考电压就是3.3V。

- [x] 没有晶振---有，正点原子的开发板的HSE接的是25MHz外部晶振

- [x] 是否需要USB供电？

## 一、基础器件选型

### 芯片库存/购买渠道查询

[octopart](https://octopart.com/stm32f767igt6-stmicroelectronics-74146081)

### 电容

- 贴片电容104，105是什么意思？答：就是10 * 10^4^ pF = 100nF。同理，105就是1uF。[Capacitor Code Calculation with chart](https://easyelectronicsproject.com/testing-components/capacitor-code/)

>电容量由3位字母数字表示。单位皮法（pF）。第1位和第2位数字为有效数字，第3位数字表示有效数字后的0的个数。有小数点时以大写字母“R”表示。此时，所有数字均为有效数字。

参考：https://zhidao.baidu.com/question/241657343543282124.html

举例：225 --> 22 * 10^(5) pF = 2.2uF

## 二、电源部分

- 3.3v power switch 的 VUSB

### VDDA and VSSA

[VDDA/VSSA connection to VDD/VSS](https://community.st.com/t5/stm32-mcu-products/vdda-vssa-connection-to-vdd-vss/td-p/341799#:~:text=No%20-%20VDDA%20can%20be%20any%20voltage%20you,diode%20helps%20make%20sure%20this%20isn%27t%20the%20case.)

- > "It is recommended to power VDD and VDDA from the same source. A maximum difference of 300 mV between VDD and VDDA can be tolerated during power-up and power-down operation."

  > 1. *VDDA and VSSA must be connected to VDD and VSS, respectively.*

### 名词解释

VBTN：电源适配器输入的12V电压经电源转换芯片转换后得到的5V电压。

VUSB：通过USB 接口输入的电压。

[EMI、EMS和EMC简述](https://zhuanlan.zhihu.com/p/117604783)

EMI：[How to identify or calculate the electromagnetic interference (EMI) contribution of components on PCB](https://electronics.stackexchange.com/questions/510562/how-to-identify-or-calculate-the-electromagnetic-interference-emi-contribution)



## 布局布线：

#### 去耦电容

去耦和旁路电容：见<a href="https://zhuanlan.zhihu.com/p/98398625">这篇帖子</a>

[去耦电容（3）- 电容该如何布局布线？](https://zhuanlan.zhihu.com/p/97110481) 

[360°详解去耦电容，真正的理解及在真正工程中的使用](https://blog.csdn.net/ima_xu/article/details/85008406#:~:text=%E5%8E%BB%E8%80%A6%E7%94%B5%E5%AE%B9%E7%9A%84PCB%E5%B8%83%E5%B1%80%E5%B8%83%E7%BA%BF%201%201.%E5%8E%9F%E7%90%86%20%E5%85%88%E7%9C%8B%E4%B8%80%E4%B8%AA%E5%BE%88%E5%BD%A2%E8%B1%A1%E7%9A%84%E5%8A%A8%E5%9B%BE%EF%BC%8C%E7%9B%B4%E8%A7%82%E4%BD%93%E4%BC%9A%E4%B8%80%E4%B8%8B%E4%B8%80%E4%B8%AA%E7%94%B5%E5%AE%B9%E6%94%BE%E7%BD%AE%E4%BD%8D%E7%BD%AE%E4%B8%8D%E5%90%8C%E8%B5%B7%E5%88%B0%E7%9A%84%E4%BD%9C%E7%94%A8%E6%9C%89%E5%A4%9A%E5%A4%A7%E7%9A%84%E5%B7%AE%E5%BC%82%E3%80%82%20%E8%BF%99%E5%BC%A0%E5%8A%A8%E5%9B%BE%E4%BC%A0%E9%80%92%E4%BA%86%E5%A6%82%E4%B8%8B%E7%9A%84%E4%BF%A1%E6%81%AF%EF%BC%9A%20%E5%9C%A8%E7%94%B5%E6%BA%90%E7%AE%A1%E8%84%9A%E4%B8%8A%E6%94%BE%E7%BD%AE%E4%B8%80%E4%B8%AA104%EF%BC%880.1%CE%BCF%EF%BC%89%E7%9A%84%E7%94%B5%E5%AE%B9%E8%83%BD%E5%A4%9F%E6%9C%89%E6%95%88%E6%8A%91%E5%88%B6%E7%94%B5%E6%BA%90%E4%B8%8A%E7%9A%84%E5%99%AA%E5%A3%B0%EF%BC%8C%E4%B9%9F%E5%B0%B1%E6%98%AF%E8%83%BD%E5%A4%9F%E5%AF%B9%E7%94%B5%E6%BA%90%E5%99%AA%E5%A3%B0%E5%8E%BB%E8%80%A6%EF%BC%9B%20%E2%80%9C%E7%94%B5%E6%BA%90%20%E2%80%93,%E6%9D%A5%E7%9C%8B%E5%85%B7%E4%BD%93%E7%9A%84%E5%AE%9E%E4%BE%8B%20%E5%9C%A8%E5%B8%B8%E7%94%A8%E5%8D%95%E7%89%87%E6%9C%BAstm32f103c8t6%E6%9C%80%E5%B0%8F%E7%B3%BB%E7%BB%9F%E4%B8%AD%EF%BC%8C%E5%B8%B8%E5%B8%B8%E6%9C%89%E8%BF%99%E6%A0%B7%E5%9B%9B%E4%B8%AA%E5%8E%BB%E8%80%A6%E7%94%B5%E5%AE%B9%EF%BC%8C%E5%88%86%E5%88%AB%E5%AF%B9%E5%BA%94%E8%8A%AF%E7%89%87%E7%9A%84%E5%9B%9B%E5%AF%B9%E4%BE%9B%E7%94%B5%E5%BC%95%E8%84%9A%20...%203%203.%E6%80%BB%E7%BB%93%20%E4%B8%8B%E9%9D%A2%E7%9A%84%E5%9B%BE%E6%98%AF%E5%8E%BB%E8%80%A6%E7%94%B5%E5%AE%B9%E9%80%9A%E8%BF%87%E8%BF%87%E5%AD%94%E4%B8%8E%E5%9C%B0%E8%BF%9B%E8%A1%8C%E8%BF%9E%E9%80%9A%E7%9A%84%E6%96%B9%E6%B3%95%E6%AF%94%E8%BE%83%EF%BC%8C%E4%BB%8E%E6%9C%80%E5%B7%A6%E4%BE%A7%E7%9A%84%E6%95%88%E6%9E%9C%E6%9C%80%E5%B7%AE%E4%BE%9D%E6%AC%A1%E7%BC%96%E5%8F%B7%EF%BC%8C%E7%9B%B4%E5%88%B0%E6%9C%80%E5%8F%B3%E4%BE%A7%E6%95%88%E6%9E%9C%E6%9C%80%E4%BD%B3%EF%BC%8C%E5%BD%93%E7%84%B6%E5%85%B7%E4%BD%93%E9%87%87%E7%94%A8%E9%82%A3%E7%A7%8D%E6%96%B9%E5%BC%8F%E8%BF%98%E8%A6%81%E5%8F%96%E5%86%B3%E4%BA%8E%E5%85%B6%E5%AE%83%E4%B8%80%E4%BA%9B%E5%9B%A0%E7%B4%A0%EF%BC%8C%E7%BB%BC%E5%90%88%E8%80%83%E8%99%91%E5%90%8E%E5%81%9A%E4%B8%80%E4%B8%AA%E6%8A%98%E8%A1%B7%E3%80%82%20%E4%B8%8B%E5%9B%BE%E6%98%AF%E4%B8%80%E4%B8%AA%E5%AE%9E%E9%99%85%E7%94%B5%E5%AD%90%E4%BA%A7%E5%93%81%E7%B3%BB%E7%BB%9F%E7%9A%84%E4%BE%9B%E7%94%B5%E5%88%86%E5%B8%83%E7%BD%91%E7%BB%9C%EF%BC%8C%E4%B8%BA%E4%BA%86%E5%BC%BA%E8%B0%83%E5%99%AA%E5%A3%B0%E7%9A%84%E8%B5%B7%E6%BA%90%EF%BC%88%E6%9C%80%E5%B7%A6%E4%BE%A7%EF%BC%89%EF%BC%8C%E6%8A%8A%E7%94%B5%E6%BA%90%E6%A8%A1%E5%9D%97%EF%BC%88VRM%EF%BC%89%E6%94%BE%E5%88%B0%E4%BA%86%E6%9C%80%E5%8F%B3%E4%BE%A7%E3%80%82%20)

[由多个电容组成的去耦旁路电路，电容怎么布局摆放](https://blog.csdn.net/qq_57148694/article/details/130213657#:~:text=%E5%8F%AF%E8%A7%81%E5%A4%A7%E7%94%B5%E5%AE%B9%EF%BC%881uF%EF%BC%89%E7%9A%84%E8%87%AA%E8%B0%90%E6%8C%AF%E7%82%B9%E4%BD%8E%E4%BA%8E%E5%B0%8F%E7%94%B5%E5%AE%B9,%2810nF%29%EF%BC%8C%E7%9B%B8%E5%BA%94%E7%9A%84%EF%BC%8C%E5%A4%A7%E7%94%B5%E5%AE%B9%E5%AF%B9%E5%AE%89%E8%A3%85%E7%9A%84PCB%E7%94%B5%E8%B7%AF%E6%9D%BF%E4%B8%8A%E4%BA%A7%E7%94%9F%E7%9A%84%E5%AF%84%E7%94%9F%E7%AD%89%E6%95%88%E4%B8%B2%E8%81%94%E7%94%B5%E6%84%9FESL%E7%9A%84%E6%95%8F%E6%84%9F%E5%BA%A6%E5%B0%8F%E4%BA%8E%E5%B0%8F%E7%94%B5%E5%AE%B9%E3%80%82%20%E6%89%80%E4%BB%A5%EF%BC%8C%E5%B0%8F%E7%94%B5%E5%AE%B9%E5%BA%94%E8%AF%A5%E5%B0%BD%E9%87%8F%E9%9D%A0%E8%BF%91IC%E7%9A%84%E7%94%B5%E6%BA%90%E5%BC%95%E8%84%9A%E6%91%86%E6%94%BE%EF%BC%8C%E5%A4%A7%E7%94%B5%E5%AE%B9%E7%9A%84%E6%91%86%E6%94%BE%E4%BD%8D%E7%BD%AE%E7%9B%B8%E5%AF%B9%E5%AE%BD%E6%9D%BE%E4%B8%80%E4%BA%9B%EF%BC%8C%E4%BD%86%E9%83%BD%E5%BA%94%E8%AF%A5%E5%B0%BD%E9%87%8F%E9%9D%A0%E8%BF%91IC%E6%91%86%E6%94%BE%EF%BC%8C%E4%B8%8D%E8%83%BD%E7%A6%BBIC%E8%B7%9D%E7%A6%BB%E5%A4%AA%E8%BF%9C%EF%BC%8C%E8%B6%85%E8%BF%87%E5%85%B6%E5%8E%BB%E8%80%A6%E5%8D%8A%E5%BE%84%EF%BC%8C%E4%BE%BF%E4%BC%9A%E5%A4%B1%E5%8E%BB%E5%8E%BB%E8%80%A6%E4%BD%9C%E7%94%A8%E3%80%82)

#### 晶振

[Oscillator design guide for STM8AF/AL/S, STM32 MCUs and MPUs (AN2867)](https://www.st.com/resource/en/application_note/cd00221665-oscillator-design-guide-for-stm8af-al-s-stm32-mcus-and-mpus-stmicroelectronics.pdf)

[不论小白还是大佬，这篇PCB晶振设计不得不看](https://www.eefocus.com/article/460948.html)

[什么是晶振？晶振在PCB板上如何布局？](https://zhuanlan.zhihu.com/p/582420804)

[Should there be any PCB ground plane under a 16 MHz oscillator?](https://electronics.stackexchange.com/questions/308638/should-there-be-any-pcb-ground-plane-under-a-16-mhz-oscillator)



#### 电源走线

[pcb trace width conversion calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-pcb-trace-width)

> Every block (noisy, low-level sensitive, digital, etc.) should be grounded individually and all ground returns should be to a single point. Loops must be avoided or have a minimum area. The power supply should be implemented close to the ground line to minimize the area of the supply loop. This is due to the fact that the supply loop acts as an antenna, and is therefore the main transmitter and receiver of EMI. All component-free PCB areas must be filled with additional grounding to create a kind of shielding (especially when using singlelayer PCBs). --- AN4661

### DC连接器的选择

- 参考文章：[DC插座的规格分类以及型号选购](https://zhuanlan.zhihu.com/p/101291143)
- 看开发板上应该使用的是DC-005，参考：[DC电源座](https://blog.csdn.net/ktd007/article/details/116230168)，[datasheet](https://atta.szlcsc.com/upload/public/pdf/source/20220407/3CBD1766F01FEBEE4B805AFD8C8D65AF.pdf)

### 开关

常态：2-3和5-6导通

按下：1-2和4-5导通

[开关的datasheet](https://atta.szlcsc.com/upload/public/pdf/source/20211015/75A682A27A424BDE8D93C2CFA14C38FE.pdf)

### Vref

直接接入3.3V

> 正点原子开发板：“...这里还需要说明一下ADC的参考电压，阿波罗STM32F7开发板使用的是STM32F7IGT6，该芯片只有Vref+参考电压引脚，输入范围为：1.8 ~ VDDA。开发板通过P5端口，来设置Vref+的参考电压，默认的是我们通过跳线帽将ref+接到3.3V,参考电压就是3.3V。“

## 三、时钟部分

使用25MHz的晶振作为HSE时钟源。

- 如何选取负载电容：[Choosing the Right Oscillator for Your Microcontroller](https://www.allaboutcircuits.com/technical-articles/choosing-the-right-oscillator-for-your-microcontroller/)
  - 到晶振的Datasheet里查找总负载电容的值（C<sub>LTOTAL</sub>)，然后估计一下寄生电容C<sub>p</sub>的值，最后套用公式：
  - ![](.\Images\OSC-cap-cal.png)

## 四、复位

用于复位STM32芯片

- [x] 把LCD的复位引脚和reset连接到一起

## 五、RGB LCD

### FPC接口

接口是40+2脚，使用RGB565颜色格式。

### 软件修改

在 `ltdc.c`里的 `void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)` 里配置相应的IO口LTDC复用。

IGT6 (176 pins) 控制背光的是**PB5**，在 `void TFTLCD_Init(void)` 里配置。还有`tftlcd.h` 和 `ltdc.h`里的宏定义。

### IO口配置

<p style="color:red;font-weight:bold">注意：当修改GPIO时，您需要注意以下三点：
<ol>
	<li>开启对应GPIO的时钟；</li>
    <li>选择对应的复用！</li>
    <li>配置对应的IO端口</li>
</ol>
</p>




- IGT6 (176 pins)：

  - |   信号线   |             对应I/O             |
    | :--------: | :-----------------------------: |
    |  LCD_CLK   |               PG7               |
    | LCD_HSYNC  |              PI10               |
    | LCD_VSYNC  |               PI9               |
    |   LCD_DE   |              PF10               |
    |   LCD_BL   |               PB5               |
    | LCD_R[7:3] |   PG6、PH12、PH11、PH10、PH9    |
    | LCD_G[7:2] | PI2、PI1、PI0、PH15、PH14、PH13 |
    | LCD_B[7:3] |    PI7、PI6、PI5、PI4、PG11     |

    

- ZGT6 (144 pins)：

    - |       信号线       |                           可用I/O                            |
      | :----------------: | :----------------------------------------------------------: |
      |      LCD_CLK       |         <del>PE14(67) （FMC_D11）</del>，**PG7(92)**         |
      |     LCD_HSYNC      |                         **PC6(96)**                          |
      |     LCD_VSYNC      |                         **PA4(40)**                          |
      |       LCD_DE       |        <del>PE13(66) （FMC_D10）</del>， **PF10(22)**        |
      | LCD_BL（普通GPIO） |                  BL是PG3（88）（普通GPIO）                   |
      |     LCD_R[7:5]     | <del>PE15(68)</del>, **PG6(91)** / PB1(47). <u>PA8(100)</u> / PC0(26), <u>PA9(101)</u>, PA12(104) |
      |     LCD_R[4:3]     |           PA5(41)，<u>PA11(103)</u> / **PB0(46)**            |
      |     LCD_G[7:5]     | <del>PG8(93)</del>、PD3(117)、<u>PB5(135)</u> / **PC7(97)** / **PB11(70)** |
      |     LCD_G[4:2]     | **PB10(69)** / PE11(63) , PC9(99) , <u>PG10(125)</u> / **PA6(42)** |
      |     LCD_B[7:3]     | **PB9(140) / PB8(139)** / **PA3(37)** / <del>PE12(65)</del>, PA10(102), <u>PG12(127)</u> / <del>PD10(79)</del>, PA8(100), **PG11(126)** |



## 六、MCU LCD

21个IO口。

### 软件修改

- 在 `tftlcd.c`里的 `void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)` 里配置相应的IO口MCU LCD复用。

- IGT6 (176 pins) 控制背光的是**PB5**，在 `void TFTLCD_Init(void)` 里配置。还有`tftlcd.h` 和 `ltdc.h`里的宏定义。

- 注意`sdram.c` 里的 `void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)` 里配置FMC所用到的引脚，虽然好像用不到

### IO口配置

<p style="color:red;font-weight:bold">注意：当修改GPIO时，您需要注意以下三点：
<ol>
	<li>开启对应GPIO的时钟；</li>
    <li>选择对应的复用！</li>
    <li>配置对应的IO端口</li>
</ol>
</p>

- IGT6 (176 pins)：

  > 可参考正点原子开发手册p350。
  
  |       信号线       |       对应I/O        |
  | :----------------: | :------------------: |
  |    FMC_D0 ~ D3     | PD14、PD15、PD0、PD1 |
  |    FMC_D4 ~ D12    |      PE7 ~ PE15      |
  |   FMC_D13 ~ D15    |    PD8、PD9、PD10    |
  | LCD_BL（普通GPIO） |         PB5          |
  |       LCD_CS       |         PD7          |
  |       LCD_RS       |         PD13         |
  |       LCD_WR       |         PD5          |
  |       LCD_RD       |         PD4          |

- FMC引脚（**和上面的LCD_XX是对应的。**）：

  | 信号线  | 对应I/O |
  | :-----: | :-----: |
  | FMC_NE1 |   PD7   |
  | FMC_A18 |  PD13   |
  | FMC_NWE |   PD5   |
  | FMC_NOE |   PD4   |


​		



- ZGT6 (144 pins)：
  |       信号线       |                          对应I/O                          |
  | :----------------: | :-------------------------------------------------------: |
  |    FMC_D0 ~ D3     | **PD14(85)** / **PD15(86)** / **PD0(114)** / **PD1(115)** |
  |    FMC_D4 ~ D6     |          **PE7(58)** / **PE8(59)** / **PE9(60)**          |
  |    FMC_D7 ~ D10    | **PE10(63)** / **PE11(64)** / **PE12(65)** / **PE13(66)** |
  |   FMC_D11 ~ D12    |                **PE14(67)** / **PE15(68)**                |
  |   FMC_D13 ~ D15    |         **PD8(77)** / **PD9(78)** / **PD10(79)**          |
  | LCD_BL（普通GPIO） |                       BL是PG3（88）                       |
  |  LCD_CS (FMC_NE1)  |             <del>PC7(97)</del>, **PD7(123)**              |
  |  LCD_RS (FMC_A18)  |                       **PD13(82)**                        |
  |  LCD_WR (FMC_NWE)  |                       **PD5(119)**                        |
  |  LCD_RD (FMC_NOE)  |                       **PD4(118)**                        |




## 七、触摸引脚

使用的芯片是GT9147。

总共5根线。

### 软件修改

需要修改的地方：

`touch.c` 里的 `u8 TP_Init(void)`，注意电阻屏幕支持可能需要删除

`touch.h` 里的宏定义

对应芯片的`.c`和`.h`文件，这里以gt9147为例：

- `gt9147.c` 的 `u8 GT9147_Init(void)` 里对PH7和PI8的操作

- `gt9147.h` 里的宏定义

`ctiic.c`  里面的函数：`void CT_IIC_Init(void)`

`ctiic.h` 的宏定义，注意在设置SDA方向的宏时要根据自己的端口设置MODER寄存器的值，比如：

```c
//IO方向设置
#define CT_SDA_IN()  {GPIOC->MODER&=~(3<<(8*2));GPIOC->MODER|=0<<8*2;}	//PC8输入模式
#define CT_SDA_OUT() {GPIOC->MODER&=~(3<<(8*2));GPIOC->MODER|=1<<8*2;} 	//PC8输出模式
```

上面的操作是将PC8的对应的MODER位置零后写00（输入）或01（输出）。



### IO口配置

**这些端口全部配置为GPIO，不需要复用！**

<p style="color:red;font-weight:bold">注意：当修改GPIO时，您需要注意以下三点：
<ol>
	<li>开启对应GPIO的时钟；</li>
    <li>选择对应的复用！</li>
    <li>配置对应的IO端口</li>
</ol>
</p>

- IGT6 (176 pins)：

  > 参考正点原子开发手册p603

  | 信号线 | 对应I/O |
  | :----: | :-----: |
  | T_MOSI |   PI3   |
  | T_MISO |   PG3   |
  | T_SCK  |   PH6   |
  |  T_CS  |   PI8   |
  | T_PEN  |   PH7   |

  

- ZGT6 (144 pins)：全是普通GPIO，可以随意

| 信号线 |  对应I/O   |
| :----: | :--------: |
| T_MOSI | PC8（98）  |
| T_MISO | PB13（74） |
| T_SCK  | PB12（73） |
|  T_CS  | PC9（99）  |
| T_PEN  | PD11（80） |



## 八、SDRAM

<p style="color:red;font-weight:bold">注意：当修改GPIO时，您需要注意以下三点：
<ol>
	<li>开启对应GPIO的时钟；</li>
    <li>选择对应的复用！</li>
    <li>配置对应的IO端口</li>
</ol>
</p>

- ZGT6 (144 pins)：

  |    信号线     |                          对应I/O                          |
  | :-----------: | :-------------------------------------------------------: |
  |  FMC_D0 ~ D3  | **PD14(85)** / **PD15(86)** / **PD0(114)** / **PD1(115)** |
  |  FMC_D4 ~ D6  |          **PE7(58)** / **PE8(59)** / **PE9(60)**          |
  | FMC_D7 ~ D10  |       **PE10(63) / PE11(64) / PE12(65) / PE13(66)**       |
  | FMC_D11 ~ D12 |                  **PE14(67) / PE15(68)**                  |
  | FMC_D13 ~ D15 |             **PD8(77) / PD9(78) / PD10(79)**              |
  |   FMC_NBL0    |                       **PE0(141)**                        |
  |   FMC_NBL1    |                       **PE1(142)**                        |
  |   FMC_SDNWE   |           PC0(26), **<u>PA7(43)</u>**（原PC0）            |
  |  FMC_SDNCAS   |                       **PG15(132)**                       |
  |   FMC_SDCLK   |                        **PG8(93)**                        |
  |  FMC_SDNRAS   |                       **PF11(49)**                        |
  |  FMC_SDCKE0   |           PC3(29), **<u>PC5(45)</u>** （原PC3）           |
  |   FMC_SDNE0   |           PC2(28), **<u>PC4(44)</u>** （原PC2）           |
  |    FMC_BA0    |                        **PG4(89)**                        |
  |    FMC_BA1    |                        **PG5(90)**                        |
  |  **FMC_A10**  |                        **PG0(56)**                        |
  |  FMC_A0 ~ A2  |              **PF0(10) / PF1(11) / PF2(12)**              |
  |  FMC_A3 ~ A5  |              **PF3(13) / PF4(14) / PF5(15)**              |
  |  FMC_A6 ~ A9  |       **PF12(50) / PF13(53) / PF14(54) / PF15(55)**       |
  | FMC_A10 ~ A12 |             **PG0 (56) / PG1 (57) / PG2(87)**             |



## 九、ADC和PWM

1 2 3 4 5 **7 8 9**

4 5 TIM9_CH1,CH2

18 19 20 21: ADC3. TIM10, 11 12, 13_CH1

113,112,111, 116, 117 122, 129,128, 132

80, 81

41: TIM2_CH1, ADC, DAC

**47**: TIM3_CH4

48

26, 27, 28, 29 ADC

# PCB绘制

[电路板铺地时PCB 地加强孔需不需要打](https://zhidao.baidu.com/question/223418452.html)

[过孔可以打在贴片元件的焊盘上吗](https://www.zhihu.com/question/53848637/answer/2537010208)

<img src=".\Images\敷铜注意.png" style="zoom:75%;" />

[电路设计常用接地方法](https://zhuanlan.zhihu.com/p/549690615)



# 焊接与调试

## 热风枪

含铅焊锡：330~350度

无铅焊锡：350~370度 

贴片阻容类：2~3档

贴片IC类：3~4档

## 单片机焊接教程

[51单片机焊接调试说明](https://max.book118.com/html/2017/0614/115162504.shtm)

[硬件电路焊接----整体焊接布局介绍--海创电子](https://www.bilibili.com/video/BV1XJ41157Sh/?spm_id_from=333.788.recommend_more_video.3)

## 芯片方向

[如何分辨stm32芯片的方向](https://blog.csdn.net/qlexcel/article/details/51114124)

## 单片机上电不运行怎么办

1. 首先检查电源电压是否正常：用电压表测量接地引脚和电源引脚之间的电压，看看电压是否正确；
2. 其次检查复位引脚：分别测量按下和松开复位按钮时的电压值，看看是否正确。
3. 然后再检查晶振是否起振了，一般用示波器来看晶振引脚的波形。
4. 检查mcu是否虚焊漏焊或损坏或flash无法下载。

# EMWIN

Since widgets are actually windows with enhanced functionality, it is required to create a window with capabillities to store additional data.

**Warning: The end user must not use the function WM_GetUserData() or WM_SetUserData() with a widget of a custom type as it is implemented using this guide, since the user would either overwrite widget specific data, or not retrieve the expected data.**

> 在主函数中我们主要完成了外设的初始化和创建 start_task 任务，我们注意到这里并没有初 始化定时器 3 和定时器 4。在无操作系统中我们使用定时器 3 来为 STemWin 提供系统时钟，使用定时器 4 来定时处理触摸事件。在本章中我们移植有 UCOS III 操作系统，我们使用 UCOS III 系 统来为 STemWin 提供系统时钟，对于触摸事件的处理我们可以建立一个任务来完成，因此这里 就不需要使用定时器了。

# ADC

## 一、ADC引脚

可参见芯片自己的datasheet。不过正点原子的指南都列出来了，直接参考配置即可：

<img src="..\Docs\Images\ADC_Pin.png" style="zoom:75%;" />

我们使用ADC3_IN4（PF6）和ADC3_IN5（PF7）。

# DMA

stm32f767有两个DMA控制器，每个控制器各管理8个数据流，数据流的通道之间使用仲裁器来处理DMA请求之间的优先级。

**使用DMA2**：

<img src=".\Images\DMA2_Mapping.png" style="zoom:95%;" />

ADC3是数据流0或1，通道2。

## 配置过程：

可以参考《Description of STM32F7 HAL and low-layer drivers - User manual》第7.2节 ADC Firmware driver API description，以及野火的例程里的例子进行配置。<u>注意：如果你开启了L1缓存，那么可能会无法读出正确的采集值，详情见<a href="#DMA出问题？注意一级缓存">这里</a></u>。

需要注意的点：

1. 在`HAL_ADC_MspInit()`里配置底层资源：

   - 开启GPIO、ADC和DMA对应的时钟；

   - 配置GPIO和DMA
     - 注意DMA的通道，数据流，传输模式和外设和存储的递增模式等等。

   - 使用：`HAL_DMA_Start()`来关联<u>DMA</u>和<u>需要传输的ADC数据寄存器</u>以及<u>用来存储数据的内存地址</u>。（用`__HAL_LINKDMA()`也行，但是不够灵活，我还是喜欢使用前者）

2. 配置ADC初始化函数：
   - ADC的实例(Instance)，是否连续转换，采样周期，触发方式，DMA连续请求，对齐方式等等。
   - 配置ADC的通道。
   - 使用`HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t *)AdcBuff, 1)`开始采样。



## DMA出问题？注意一级缓存！

正点原子的例程里是默认在`main.c`里开启一级缓存的，这可能导致DMA数据一直为0！

DMA不起效果：有可能是L1-Cache的问题，见：[STM32H7 ADC with DMA reading only zeros (using HAL and FreeRTOS)](https://electronics.stackexchange.com/questions/581003/stm32h7-adc-with-dma-reading-only-zeros-using-hal-and-freertos)

> “Make sure that you have [Cortex M7 L1 data cache](https://www.st.com/resource/en/application_note/an4839-level-1-cache-on-stm32f7-series-and-stm32h7-series-stmicroelectronics.pdf) disabled on the DMA area of memory (or invalidate the cache prior to reading). You can also globally disable it (at a performance cost) with:
>
> void SCB_DisableDCache (void);
>
> The DMA writes to the memory, not to the cache so cache coherency is not maintained.
>
> n.b. **<u>declaring the buffer as volatile is not sufficient</u>**.”

# 专用名词

- **mantissa**: 

  ​	1: The part of a number after the "."

  ​	Example: in 2.71828 the **mantissa** is 0.71828


  ​	2: In scientific notation the **mantissa** is the digits without the ×10n part.

  ​	Example: in 5.3266 × 103 the mantissa is 5.3266

  source: https://www.mathsisfun.com/definitions/mantissa.html

  

- **saturation instructions**:

  ​	These instructions are used to limit a variable or a value to a certain number of bits.

  ​	The ARM saturated arithmetic instructions can operate on byte, word or halfword sized values. For example, the 8 of the `QADD8` and `QSUB8` instructions indicate that they operate on byte sized values. The result of the operation is saturated to the largest possible positive or negative number. 

  > For example, if you have an 8 bit variable and for sure if you know that the value of the variable will not exceed a number 127 say, you would like to round off any value above 127 as 127 itself ( saturation) and any value below 0 as zero itself. In this case you need to write a big C code using if-else conditional statement to compare the variable with 127 and take the necessary action. Instead, to simplify this logic, you can make use of the saturation assembly instructions which Cortex-M3 (core of PSoC 5LP) supports. Please note that both GCC and MDK compilers do not append this instruction by itself for an equivalent C code.

  source: [saturation instructions](https://community.infineon.com/t5/PSoC-5-3-1/Importance-of-saturation-instructions/m-p/155653), and the source web has many [interesting projects](https://community.infineon.com/t5/Projects/bg-p/Projects/page/1)!

  source: [Saturated math instructions](https://developer.arm.com/documentation/den0042/a/Unified-Assembly-Language-Instructions/Saturating-arithmetic/Saturated-math-instructions)

- [STM32库标识符命名规则](https://community.st.com/t5/stm32-mcu-products/where-i-can-find-the-stm32-naming-convention-in-order-to/m-p/339607)

- 最小系统板：minimum system board



[介绍各种编程和硬件的专栏，CAN总线的介绍非常不错](https://www.zhihu.com/people/yizhi-bu-gan-xian-zhuang-de-zhu/posts)

[spi介绍](https://www.analog.com/cn/analog-dialogue/articles/introduction-to-spi-interface.html)
