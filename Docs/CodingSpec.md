# 程序说明文档

## 程序结构

本工程基于正点原子emWin移植模板工程（“EMWIN实验2 STemWin带UCOS移植”）开发。工程结构粗略可以划分为三个层级，互相隔离，互不影响，提供了良好的可移植性：

1. 用户界面文件：所有和EMWIN相关的文件，提供GUI界面；
2. 中间控制层文件：给用户界面提供接口来操作底层外设和提供数据，主要由`HARDWARE` 目录里的`motorcontrol.c` 实现；
3. 底层文件，除上述文件外的其他文件，是整个工程运行的基础；

### 一、用户界面文件

emWin图形界面相关文件在工程目录`EMWIN_DEMO`中。

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

其中，`FTM_FrameDLG.c`是主页面文件，`DualCtrl_WinDLG.c` 和 `SingCtrl_WinDLG.c` 是两个控制界面的窗口文件，在初始化界面时被生成并绑定在主页面中，可以通过`mode` 按钮在这两个窗口之间切换。

`MSBlack24.c` 代表24像素的微软雅黑字体文件，里面是汉化界面所要用到的字体文件。

## 文件说明

### main.c

在`main()` 中，使用了 `MY_ADC_Init()`  来初始化ADC，ADC在定时器3中断后采样，采样频率为5000Hz。

### FTM_FrameDLG.c

1. Graph控件的设置：

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

   由于ADC的采样范围为0 ~ 3.3V，因此这样设置后可以假定0V对应y轴-165刻度的位置，3.3V对应+165刻度的位置，单位为mV。<span style="color:orange">t轴范围为0 ~ 450，若数据长度为....，则显示的时间范围为...</span>

   设计硬件采样电路时请根据实际需求合理调整电压转换范围和这些参数。

   

2. 

## API

