# 光纤拉锥机
## 简介

光纤拉锥机主要由主控芯片和两个相对的由电机控制的步进电机组成。使用时，我们把光纤两端固定在夹具上，以氢气为燃料，对光纤中心进行点火加热，当光纤受热软化之后，启动电机控制夹具拉伸光纤。我们可以通过在拉伸过程中给光纤内部通入光束来判断光纤是否已经拉伸到位。

## 程序控制

由于缺货，芯片现已更换为STM32ZGT6。

程序的说明文档正在和开发过程同步火热编写中，详见`Docs`目录下的`CodingSpec`文档。

并且设计了新的UI界面：

<img src=".\Docs\Images\GUI_v1.0.png" style="zoom:100%;" />



### 旧界面

我们原计划使用STM32F7IGT6为主控芯片，分别为手动和自动拉伸编写控制程序和图形界面。目前已经完成手动控制的界面和控制逻辑和图形界面的基本开发，用户可以通过LCD触摸屏操作图形界面来控制两个电机。目前支持手动界面逻辑控制电机启停，方向，速度。主要的界面文件在工程文件的"EMWIN/DEMO"目录中，控制及反映电机状态的结构体和函数API位于"HARDWARE"目录下的"motorcontrol.c"文件中。

对俩电机的操作分别使用的是Timer2和Timer5的CH1和CH2，共四路，每个输出对应一个电机和方向：

- 左路电机：Timer2控制，PA5对应通道1，远离中心； PA1对应通道2，接近中心
- 右路电机：Timer5控制，PH10对应通道1，远离中心; PH11对应通道2，接近中心

旧的手动控制界面：

<img src=".\Docs\Images\GUI1.png" style="zoom:75%;" />				<img src=".\Docs\Images\GUI2.png" style="zoom:75%;" />



## 原理图

新原理图和PCB，将芯片更换为了144引脚的STM32ZGT6。

<img src=".\Docs\Images\PCB_PCB_光纤拉锥机-144pin.svg" style="zoom:175%;" />

<img src=".\Docs\Images\Schematic_光纤拉锥机-144pin.svg" style="zoom:100%;" />

## 实物图

正在调试中...

<img src=".\Docs\Images\Photo2.jpg" style="zoom:67%;" />

<img src=".\Docs\Images\Photo1.jpg" style="zoom:67%;" />