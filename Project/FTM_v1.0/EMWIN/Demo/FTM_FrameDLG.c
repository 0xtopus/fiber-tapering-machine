/*********************************************************************
 *                                                                    *
 *                SEGGER Microcontroller GmbH & Co. KG                *
 *        Solutions for real time microcontroller applications        *
 *                                                                    *
 **********************************************************************
 *                                                                    *
 * C-file generated by:                                               *
 *                                                                    *
 *        GUI_Builder for emWin version 5.28                          *
 *        Compiled Jan 30 2015, 16:41:06                              *
 *        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
 *                                                                    *
 **********************************************************************
 *                                                                    *
 *        Internet: www.segger.com  Support: support@segger.com       *
 *                                                                    *
 **********************************************************************
 */

// USER START (Optionally insert additional includes)
#include "FTM_FrameDLG.h"
#include "malloc.h"
#include "string.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_GRAPH_0 (GUI_ID_USER + 0x01)

// USER START (Optionally insert additional defines)
#define BORDER_TOP 20
#define BORDER_BOTTOM 20
#define BORDER_LEFT 40
#define BORDER_RIGHT 10

#define SCALE_FACTOR 1
#define V_SCALE_SETOFF 180

#define V_SCALE_POS 30
#define H_SCALE_POS 385
#define V_SCALE_UNIT 20
#define H_SCALE_UNIT 40

// USER END

/*********************************************************************
 *
 *       Global data
 *
 **********************************************************************
 */

WM_HWIN DualCtrl_Win;
WM_HWIN SingCtrl_Win;

_oscill_dev oscilldev;
/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static data)

static GRAPH_SCALE_Handle hScaleV; // 垂直刻度句柄
static GRAPH_SCALE_Handle hScaleH; // 水平刻度句柄

static GUI_COLOR LineColor[] = {GUI_RED, GUI_BLACK, GUI_WHITE, GUI_YELLOW, GUI_BLUE, GUI_DARKMAGENTA};
static GUI_COLOR BackColor[] = {GUI_BLACK, GUI_LIGHTRED, GUI_DARKMAGENTA, GUI_WHITE, GUI_GREEN};

// USER END

/*********************************************************************
 *
 *       _aDialogCreate
 */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {FRAMEWIN_CreateIndirect, "FTM_Frame", ID_FRAMEWIN_0, 0, 0, 480, 800, 0, 0x0, 0},
    {GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 0, 0, 470, 400, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    // USER END
};

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
 *
 *       _cbDialog
 */
static void _cbDialog(WM_MESSAGE *pMsg)
{
  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId)
  {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'FTM_Frame'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "Waveform");
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Graph'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
    oscilldev.linecolorindex = 0; // 线条默认红色
    oscilldev.backcolorindex = 2; // 背景默认黑色
    oscilldev.linecolor = LineColor[oscilldev.linecolorindex];
    oscilldev.backcolor = BackColor[oscilldev.backcolorindex];
    oscilldev.graphdata = GRAPH_DATA_YT_Create(oscilldev.linecolor, 420, 0, 0); // 创建YT数据对象
    GRAPH_AttachData(hItem, oscilldev.graphdata);                               // 将数据对象添加到GRAPH控件中

    GRAPH_SetBorder(hItem, BORDER_LEFT, BORDER_TOP, BORDER_RIGHT, BORDER_BOTTOM);
    GRAPH_SetGridDistX(hItem, 20); // Set horizontal interval
    GRAPH_SetGridDistY(hItem, 20); // Set vertical interval
    GRAPH_SetGridVis(hItem, 1);    // Display grid

    hScaleV = GRAPH_SCALE_Create(V_SCALE_POS, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, V_SCALE_UNIT); // 绘制垂直刻度
    GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED);
    GRAPH_AttachScale(hItem, hScaleV);
    GRAPH_SCALE_SetFactor(hScaleV, SCALE_FACTOR); // 设置刻度系数
    GRAPH_SCALE_SetOff(hScaleV, V_SCALE_SETOFF);  // 垂直刻度向上移动,这样垂直刻度会有负值

    hScaleH = GRAPH_SCALE_Create(H_SCALE_POS, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, H_SCALE_UNIT); // 绘制水平刻度
    GRAPH_SCALE_SetTextColor(hScaleH, GUI_RED);
    GRAPH_AttachScale(hItem, hScaleH); // 将刻度对象附加到图形小工具

    oscilldev.resolut = (float)3300 / 4096; // STM32的AD为12位，那么每个AD值为3300/4096=0.806mv
    oscilldev.div = 50;                    // 一格为50 us
    TIM3_Init(oscilldev.div - 1, 108 - 1);  // 初始化TIM3, 采样率20kHz
    MotorInit();
    // USER START (Optionally insert additional code for further widget initialization)
    //
    // Initialization of 'SingCtrl_Win'
    //
    hItem = CreateSingCtrl_Win();
    SingCtrl_Win = hItem;
    WM_AttachWindowAt(hItem, pMsg->hWin, 5, 420);
    //
    // Initialization of 'DualCtrl_Win'
    //
    hItem = CreateDualCtrl_Win();
    DualCtrl_Win = hItem;
    WM_AttachWindowAt(hItem, pMsg->hWin, 5, 420);
    //
    // Initialization of MotorConfig
    //
    MotorInit();

    // USER END
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */
/*********************************************************************
 *
 *       CreateFTM_Frame
 */
WM_HWIN CreateFTM_Frame(void);
WM_HWIN CreateFTM_Frame(void)
{
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
void MainTask(void)
{
  int i;
  WM_HWIN hWin,ClientWin;
	int Graph_xSize,Graph_ySize;   
  /* 窗口自动使用存储设备 */
  WM_SetCreateFlags(WM_CF_MEMDEV);
  /* 初始化 */
  GUI_Init();
  /* 使用UTF8编码 */
	GUI_UC_SetEncodeUTF8();
  /* 创建对话框，使用 GUIBulder5.28 生成的对话框创建函数 */
  hWin = CreateFTM_Frame();
  ClientWin = WM_GetDialogItem(hWin, ID_GRAPH_0);
	Graph_xSize=WM_GetWindowSizeX(ClientWin);
	Graph_ySize=WM_GetWindowSizeY(ClientWin);
	
	oscilldev.dataxsize=Graph_xSize-BORDER_LEFT-BORDER_RIGHT;
	oscilldev.dataysize=Graph_ySize-BORDER_TOP-BORDER_BOTTOM;	
	oscilldev.buffer=mymalloc(SRAMIN,oscilldev.dataxsize*4);	//申请内存
  while (1)
  {
    if (oscilldev.adflag == 1)
    {
      for (i = 0; i < oscilldev.dataxsize; i++)
      {
        // 向GRAPH图形小工具添加数据,缩20倍并向上平移100格，则-80刻度对应的实际ADC口的电压是0V，80多一点儿的地方对应的实际ADC电压是3.3V
        GRAPH_DATA_YT_AddValue(oscilldev.graphdata, oscilldev.buffer[i] / 20 + 100);
      }
      memset(oscilldev.buffer, 0, oscilldev.dataxsize); // 清空buffer
      oscilldev.adflag = 0;
    }
    GUI_Delay(100);
  }
}
// USER END

/*************************** End of file ****************************/
