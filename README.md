# 光纤拉锥机
## 简介

光纤拉锥机主要由主控芯片和两个相对的由电机控制的步进电机组成。使用时，我们把光纤两端固定在夹具上，以氢气为燃料，对光纤中心进行点火加热，当光纤受热软化之后，启动电机控制夹具拉伸光纤。我们可以通过在拉伸过程中给光纤内部通入光束来判断光纤是否已经拉伸到位。



## 电控

我们计划使用STM32F7IGT6为主控芯片，分别为手动和自动拉伸编写控制程序和图形界面。目前已经完成手动控制的界面和控制逻辑和图形界面的基本开发，用户可以通过LCD触摸屏操作图形界面来控制两个电机。目前支持手动界面逻辑控制电机启停，方向，速度。主要的界面文件在工程文件的"EMWIN/DEMO"目录中，控制及反映电机状态的结构体和函数API位于"HARDWARE"目录下的"motorcontrol.c"文件中。

对俩电机的操作分别使用的是Timer2和Timer5的CH1和CH2，共四路，每个输出对应一个电机和方向：

- 左路电机：Timer2控制，PA5对应通道1，远离中心； PA1对应通道2，接近中心
- 右路电机：Timer5控制，PH10对应通道1，远离中心; PH11对应通道2，接近中心

<img src="C:\Users\Administrator\Desktop\fiber-tapering-machine\Docs\Images\GUI1.png" style="zoom:75%;" />				<img src="C:\Users\Administrator\Desktop\fiber-tapering-machine\Docs\Images\GUI2.png" style="zoom:75%;" />

## 原理图

目前初步对原理图进行了绘制，正在进行微调检查和PCB的绘制。

![](C:\Users\Administrator\Desktop\fiber-tapering-machine\Docs\Images\SCH_v1.0.png)