#ifndef FTMFRAMEDLG_H
#define FTMFRAMEDLG_H

#include "GUI.h"
#include "WM.h"
#include "sys.h"
#include "GRAPH.h"
#include "motorcontrol.h"
#include "timer.h"

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

#endif
