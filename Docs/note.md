# GPIO配置
http://www.openedv.com/posts/list/32730.htm

</br>

# LCD
LCD的编号id是5510
## Datasheet 
<a href="https://max.book118.com/html/2020/0724/5132043242002321.shtm">Alientek 4.3' TFTLCD</a>

## 80并口的信号线
CS：片选信号
WR：写入信号
RD: 读取信号
D[15:0]：16位数据线
RST: 硬复位
RS: 数据\命令标志（0表示命令，1表示数据）

## LCD指令
- 0xD3: 读取LCD驱动器的型号
- 0x36：控制9341的读写方向
- 0x2a: 列地址设置指令，用来设置横坐标
- 0x2b: 页地址设置指令，用来设置纵坐标
- 0x2c: 写GRAM指令，写入颜色数据
- 0x2e：读GRAM

## FCM--可变存储控制器
总共管理1.5GB空间，分为6个存储块（bank），每个存储块大小为256MB，分为4个区，每个区大小为64MB。

Bank1的256MB = ${2}^{28}$由HADDR[28:0]来寻址，其中[26:27]是对四个区进行选择。[25:0]是外部存储器的地址，LCD屏使用16位宽度，FMC内部HADDR与存储器寻址地址的关系：HADDR[25:1] -> FMC_A[24:0] (按字寻址，所以要除以2)

HCLK时钟周期为4.6ns左右。读取数据的速度会慢一些，数据保持时间大约为80个HCLK周期，地址保持时间为15个HCLK周期；写数据会快一些，两个时间都只需要4个HCLK周期就可以了。

FMC_BCRx: 片选控制寄存器
FMC_BTRx: 片选时序寄存器
它们被组合成了BTRCR[8]寄存器组
FMC_BWTRx: 闪写时序寄存器
组合成BWTR[7]
<br>
<br>
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

我们使用的是电容屏幕，使用GT9147集成芯片驱动。
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

1、配置仿真工程属性。成功打开工程后，右键单击SimulationTrial项目，在弹出的选项中选择属性，见图 配置emWin仿真工程属性；<br>
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

## 三、GUIBuilder的使用
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



