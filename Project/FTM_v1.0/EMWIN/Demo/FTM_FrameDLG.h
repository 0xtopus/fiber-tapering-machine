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

typedef enum  
{
    DualStartBtn = 0,
    DirBtn,
    LStartBtn,
    RStartBtn
} _enumSingleButton;

// SingleCtrl Window items

// ��������ƴ����ļ���İ�ť�ؼ�������飬�ֱ��Ӧ��
// 0:��ʼ��ť; 1:����ť�� 2����ʼ��ť 3���ҿ�ʼ��ť
extern GUI_HWIN _aSingleButton[4]; 
  
// ��������ƴ����ļ����Edit�ؼ�������飬�ֱ��Ӧ��
// 0:ʵ����ת��; 1:ʵ����ת�٣� 2��Ԥ����ת�� 3��Ԥ����ת��
extern GUI_HWIN _aSingleEdit[4]; 

// ��������ƴ����ļ����Slider�ؼ�������飬�ֱ��Ӧ��
// 0:����ת��Slider; 1:�ҵ��ת��Slider��
extern GUI_HWIN _aSingleSlider[2];

// DualCtrl Window items

// ˫������ƴ����ļ���İ�ť�ؼ�������飬�ֱ��Ӧ��
// 0:��ʼ��ť; 1:����ť
extern GUI_HWIN _aDualButton[2];   

  
// ˫������ƴ����ļ����Edit�ؼ�������飬�ֱ��Ӧ��
// 0:ʵ����ת��; 1:ʵ����ת�٣� 2��Ԥ��˫���ת�� 
extern GUI_HWIN _aDualEdit[3];    

// ˫�������
extern GUI_HWIN DualSlider;
#endif
