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
	int *buffer;				        //AD���ݴ����
	u8 	adflag;					        //AD�ɼ��Ƿ���ɱ�־
	int dataxsize,dataysize;	        //ʾ����������X,Y��С
	u8 	linecolorindex,backcolorindex;	//������ɫ����ֵ�ͱ�����ɫ����ֵ
	GUI_COLOR linecolor,backcolor;		//������ɫ�ͱ�����ɫ
	GRAPH_DATA_Handle  graphdata; 	    //GRAHP_DATA�����ݾ��
	int div;					        //һ�������
    float resolut;                      //ÿ��ADԭʼֵ������ĵ�ѹ(��λΪmv)
}_oscill_dev;

extern WM_HWIN DualCtrl_Win;
extern WM_HWIN SingCtrl_Win;
extern _oscill_dev oscilldev;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontMSBlack24;

WM_HWIN CreateDualCtrl_Win(void);
WM_HWIN CreateSingCtrl_Win(void);

#endif
