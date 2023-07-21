# GPIO配置
http://www.openedv.com/posts/list/32730.htm

</br>

# LCD
RGB LCD和MCU LCD是不一样的。

**主要区别：**

MCU接口方式：显示数据写入DDRAM，常用于静止图片显示。

RGB接口方式：显示数据不写入DDRAM，直接写屏，速度快，常用于显示视频或动画用。

详见：[嵌入式LCD的接口类型详解](https://zhuanlan.zhihu.com/p/408175453#:~:text=%E5%B5%8C%E5%85%A5%E5%BC%8FLCD%E7%9A%84%E6%8E%A5%E5%8F%A3%E7%B1%BB%E5%9E%8B%E8%AF%A6%E8%A7%A3%201%201.MCU%E6%8E%A5%E5%8F%A3%3A%E4%BC%9A%E8%A7%A3%E7%A0%81%E5%91%BD%E4%BB%A4%EF%BC%8C%E7%94%B1timing%20generator%E4%BA%A7%E7%94%9F%E6%97%B6%E5%BA%8F%E4%BF%A1%E5%8F%B7%EF%BC%8C%E9%A9%B1%E5%8A%A8COM%E5%92%8CSEG%E9%A9%B1%E5%99%A8%E3%80%82%20RGB%E6%8E%A5%E5%8F%A3%3A%E5%9C%A8%E5%86%99LCD%20register,setting%E6%97%B6%EF%BC%8C%E5%92%8CMCU%E6%8E%A5%E5%8F%A3%E6%B2%A1%E6%9C%89%E5%8C%BA%E5%88%AB%E3%80%82%20%E5%8C%BA%E5%88%AB%E5%8F%AA%E5%9C%A8%E4%BA%8E%E5%9B%BE%E5%83%8F%E7%9A%84%E5%86%99%E5%85%A5%E6%96%B9%E5%BC%8F%E3%80%82%202%202.%E7%94%A8MCU%E6%A8%A1%E5%BC%8F%E6%97%B6%E7%94%B1%E4%BA%8E%E6%95%B0%E6%8D%AE%E5%8F%AF%E4%BB%A5%E5%85%88%E5%AD%98%E5%88%B0IC%E5%86%85%E9%83%A8GRAM%E5%90%8E%E5%86%8D%E5%BE%80%E5%B1%8F%E4%B8%8A%E5%86%99%EF%BC%8C%E6%89%80%E4%BB%A5%E8%BF%99%E7%A7%8D%E6%A8%A1%E5%BC%8FLCD%E5%8F%AF%E4%BB%A5%E7%9B%B4%E6%8E%A5%E6%8E%A5%E5%9C%A8MEMORY%E7%9A%84%E6%80%BB%E7%BA%BF%E4%B8%8A%E3%80%82%20%E7%94%A8RGB%E6%A8%A1%E5%BC%8F%E6%97%B6%E5%B0%B1%E4%B8%8D%E5%90%8C%E4%BA%86%EF%BC%8C%E5%AE%83%E6%B2%A1%E6%9C%89%E5%86%85%E9%83%A8RAM%EF%BC%8CHSYNC%EF%BC%8CVSYNC%EF%BC%8CENABLE%EF%BC%8CCS%EF%BC%8CRESET%EF%BC%8CRS%E5%8F%AF%E4%BB%A5%E7%9B%B4%E6%8E%A5%E6%8E%A5%E5%9C%A8MEMORY%E7%9A%84GPIO%E5%8F%A3%E4%B8%8A%EF%BC%8C%E7%94%A8GPIO%E5%8F%A3%E6%9D%A5%E6%A8%A1%E6%8B%9F%E6%B3%A2%E5%BD%A2.%203%203.MPU%E6%8E%A5%E5%8F%A3%E6%96%B9%E5%BC%8F%EF%BC%9A%E6%98%BE%E7%A4%BA%E6%95%B0%E6%8D%AE%E5%86%99%E5%85%A5DDRAM%EF%BC%8C%E5%B8%B8%E7%94%A8%E4%BA%8E%E9%9D%99%E6%AD%A2%E5%9B%BE%E7%89%87%E6%98%BE%E7%A4%BA%E3%80%82)

当前使用的 MCU LCD的编号id是5510，可以通过对应的读取指令来读取。

RGB LCD的id：

> STM32F7开发指南-HAL库版本：p391:
>
> ...而LCD_R7/G7/B7则用来设置LCD的ID，由于RGB LCD没有读写寄存器，也就没有所谓的ID，这里我们通过在模块上面，控制R7/G7/B7的上/下拉，来定义LCD模块的ID，帮助MCU判断当前LCD的分辨率和相关参数，以提高程序兼容性。

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

Bank1的256MB = $ {2}^{28} $由HADDR[28:0]来寻址，其中[26:27]是对四个区进行选择。[25:0]是外部存储器的地址，LCD屏使用16位宽度，FMC内部HADDR与存储器寻址地址的关系：HADDR[25:1] -> FMC_A[24:0] (按字寻址，所以要除以2)

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

> 正点原子：p601：
>
> 电容触摸屏一般都需要一个驱动IC来检测电容触摸，且一般都是使用IIC接口输出触摸数据。....本例程除了CPLD方案的V1版本7寸屏幕模块不支持以外，其他所有Alientek的LCD模块都支持。

我们使用的是电容屏幕，使用GT9147集成芯片驱动来检测电容触摸。

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
6. 点击File->Save as...，将你的字体文件保存为`.c`文件，文件名可自取，但不能包含中文
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
14. 你也可以直接移植到MDK5。移植方法和之前类似，就是记得要把`.c`字符文件也添加进工程。然后打开魔法棒工具，在 options->c/c++->Misc controls 栏填写 “`--locale=english`”防止报错。

## 七、其他注意事项

改变Timer的周期时，请先停止再重新初始化，直接改寄存器会出bug



# 原理图绘制

[Getting started with STM32F7 Series MCU hardware development(AN4661)](https://www.st.com/resource/en/application_note/dm00164549-getting-started-with-stm32f7-series-mcu-hardware-development-stmicroelectronics.pdf)



- 最小系统板：minimum system board
- 

- P2576电压转换芯片
- [正点原子STM32F429核心板的插座型号](https://blog.csdn.net/youngwah292/article/details/119495119#:~:text=%E8%BF%99%E4%B8%A4%E4%B8%AA%E6%8F%92%E5%BA%A7%E5%9E%8B%E5%8F%B7%E6%98%AF%E4%BB%80%E4%B9%88%EF%BC%9F%20%E5%9C%A8%E6%A0%B8%E5%BF%83%E6%9D%BF%E4%B8%8A%E5%AE%89%E8%A3%85%E7%9A%84%E8%BF%99%E4%B8%A4%E4%B8%AA%E6%8F%92%E5%BA%A7%EF%BC%8C%E6%98%AF3710F%E6%8F%92%E5%BA%A7%EF%BC%88%E5%85%AC%E5%A4%B4%EF%BC%89%E3%80%82,%E9%82%A3%E4%B9%88%E4%B8%8E%E4%B9%8B%E5%AF%B9%E5%BA%94%E7%9A%84%E6%98%AF3710F%E6%8F%92%E5%BA%A7%EF%BC%88%E6%AF%8D%E5%BA%A7%EF%BC%89%EF%BC%8C%E5%A6%82%E4%B8%8B%E5%9B%BE%E6%89%80%E7%A4%BA%E3%80%82%20%E5%AE%83%E6%9C%8960%E4%B8%AA%E5%BC%95%E8%84%9A%EF%BC%8C%E4%B8%A4%E4%BE%A7%E5%90%8430%E4%B8%AA%E3%80%82%20%E6%AD%A3%E7%82%B9%E5%8E%9F%E5%AD%90%E5%AE%98%E7%BD%91%E6%9C%89%E8%BF%99%E7%A7%8D%E8%B4%AD%E4%B9%B0%E8%BF%9E%E6%8E%A5%EF%BC%8C%E5%8F%AF%E4%BB%A5%E6%90%9C%E7%B4%A2%E2%80%9C3710F%E6%9D%BF%E5%AF%B9%E6%9D%BF%E8%BF%9E%E6%8E%A5%E5%99%A8%E2%80%9D%E6%9F%A5%E6%89%BE%E8%B4%AD%E4%B9%B0%E3%80%82)

## 问题

- [x] EEPROM用来干啥 --- 用于存储一些掉电不能丢失的重要数据，比如系统设置的一些参数/触摸屏的校准数据等等。
- [x] 是否需要电压测试端？

- [ ] BOOT0和BOOT1

- [ ] 中文参考手册：VREF– 如果可用（**取决于封装**），则必须将其连接到 VSSA。？

- [ ] 模拟地和数字地

> 这里还需要说明一下ADC的参考电压，阿波罗STM32F7开发板使用的是STM32F7IGT6，该芯片只有Vref+参考电压引脚，输入范围为：1.8 ~ VDDA。开发板通过P5端口，来设置Vref+的参考电压，默认的是我们通过跳线帽将ref+接到3.3V,参考电压就是3.3V。

- [x] 没有晶振---有，正点原子的开发板的HSE接的是25MHz外部晶振

- [ ] 是否需要USB供电？

## 一、基础器件选型

### 电容

- 贴片电容104，105是什么意思？答：就是10 * 10^4^ pF = 100nF。同理，105就是1uF。[Capacitor Code Calculation with chart](https://easyelectronicsproject.com/testing-components/capacitor-code/)

>电容量由3位字母数字表示。单位皮法（pF）。第1位和第2位数字为有效数字，第3位数字表示有效数字后的0的个数。有小数点时以大写字母“R”表示。此时，所有数字均为有效数字。

参考：https://zhidao.baidu.com/question/241657343543282124.html

举例：225 --> 22 * 10^(5) pF = 2.2uF

## 二、电源部分

### TODO：

- 3.3v power switch 的 VUSB

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

接口是40+2脚，使用RGB565颜色格式。

# PCB绘制



<img src=".\Images\敷铜注意.png" style="zoom:75%;" />

# 焊接与调试

## 热风枪

含铅焊锡：330~350度

无铅焊锡：350~370度 

贴片阻容类：2~3档

贴片IC类：3~4档







## 单片机上电不运行怎么办

1. 首先检查电源电压是否正常：用电压表测量接地引脚和电源引脚之间的电压，看看电压是否正确；
2. 其次检查复位引脚：分别测量按下和松开复位按钮时的电压值，看看是否正确。
3. 然后再检查晶振是否起振了，一般用示波器来看晶振引脚的波形。
4. 检查mcu是否虚焊漏焊或损坏或flash无法下载。

# EMWIN

Since widgets are actually windows with enhanced functionality, it is required to create a window with capabillities to store additional data.

**Warning: The end user must not use the function WM_GetUserData() or WM_SetUserData() with a widget of a custom type as it is implemented using this guide, since the user would either overwrite widget specific data, or not retrieve the expected data.**
