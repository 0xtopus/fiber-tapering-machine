#ifndef FTMFRAMEDLG_H
#define FTMFRAMEDLG_H

#include "GUI.h"
#include "WM.h"
#include "sys.h"
#include "GRAPH.h"
#include "motorcontrol.h"
#include "timer.h"

#define SET_DUAL_SPEED 2

#define SINGLE_LEFT_SLIDER 0
#define SINGLE_RIGHT_SLIDER 1

typedef struct 
{
	int *buffer;				        //AD数据存放区
	u8 	adflag;					        //AD采集是否完成标志
	int dataxsize,dataysize;	        //示波器数据区X,Y大小
	u8 	linecolorindex,backcolorindex;	//线条颜色索引值和背景颜色索引值
	GUI_COLOR linecolor,backcolor;		//线条颜色和背景颜色
	GRAPH_DATA_Handle  graphdata; 	    //GRAHP_DATA的数据句柄
	int div;					        //一格代表几秒
    float resolut;                      //每个AD原始值代表多大的电压(单位为mv)
}_oscill_dev;

extern WM_HWIN DualCtrl_Win;
extern WM_HWIN SingCtrl_Win;
extern _oscill_dev oscilldev;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontMSBlack24;

WM_HWIN CreateDualCtrl_Win(void);
WM_HWIN CreateSingCtrl_Win(void);

typedef enum  
{
    DualStartBtn = 0,
    DirBtn,
    LStartBtn,
    RStartBtn
} _enumSingleButton;

// SingleCtrl Window items

// 单电机控制窗口文件里的按钮控件句柄数组，分别对应：
// 0:开始按钮; 1:方向按钮； 2：左开始按钮 3：右开始按钮
extern GUI_HWIN _aSingleButton[4]; 
  
// 单电机控制窗口文件里的Edit控件句柄数组，分别对应：
// 0:实际左转速; 1:实际右转速； 2：预设左转速 3：预设右转速
extern GUI_HWIN _aSingleEdit[4]; 

// 单电机控制窗口文件里的Slider控件句柄数组，分别对应：
// 0:左电机转速Slider; 1:右电机转速Slider；
extern GUI_HWIN _aSingleSlider[2];

// DualCtrl Window items

// 双电机控制窗口文件里的按钮控件句柄数组，分别对应：
// 0:开始按钮; 1:方向按钮
extern GUI_HWIN _aDualButton[2];   

  
// 双电机控制窗口文件里的Edit控件句柄数组，分别对应：
// 0:实际左转速; 1:实际右转速； 2：预设双电机转速 
extern GUI_HWIN _aDualEdit[3];    

// 双电机滑块
extern GUI_HWIN DualSlider;
#endif
