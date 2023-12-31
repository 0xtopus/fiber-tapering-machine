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
// USER END

#include "DIALOG.h"
#include "motorcontrol.h"
#include "adc.h"
#include "timer.h"
#include "arm_math.h"
#include "key.h"
/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_MULTIPAGE_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)

#define MenuFont24 &GUI_FontFontMenu24
#define FontMenuSong24 &GUI_FontMenuSong24
#define FontMenuMSBlack24 &GUI_FontMenuMSBlack24

#define FFT_LENGTH 1024
#define TIM_RELOAD_VALUE 200

float freq_resolution = 4.88;   // freq_resolution = sampling_rate / fft_length
float fft_outputbuf[FFT_LENGTH];

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
 *
 *       Global data
 *
 **********************************************************************
 */

GUI_HWIN StartItem;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontFontMenu24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuSong24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuMSBlack24;

extern WM_HWIN DualDirectionItem;
extern WM_HWIN EditLeftRealSpeed;
extern WM_HWIN EditRightRealSpeed;

extern GUI_HWIN LeftStopItem;
extern GUI_HWIN RightStopItem;

extern WM_HWIN SingleEditLeftRealSpeed;
extern WM_HWIN SingleEditRightRealSpeed;

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       _aDialogCreate
 */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 800, 0, 0x0, 0},
    {MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE_0, 0, 0, 470, 700, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "PWM_Ctrl", ID_BUTTON_0, 70, 710, 100, 50, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Dir", ID_BUTTON_1, 270, 710, 100, 50, 0, 0x0, 0},
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
  int NCode;
  int Id;
  // USER START (Optionally insert additional variables)
  char str[6];
  // USER END

  switch (pMsg->MsgId)
  {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, FontMenuMSBlack24);
    FRAMEWIN_SetText(hItem, "煜霸天牌拉锥机");
    //
    // Initialization of 'Multipage'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE_0);
    // PageItem = hItem;
    MULTIPAGE_SetTabHeight(hItem, 30);
    MULTIPAGE_SetFont(hItem, FontMenuMSBlack24);
    MULTIPAGE_AddEmptyPage(hItem, 0, "手动");
    MULTIPAGE_AddEmptyPage(hItem, 0, "自动");
    MULTIPAGE_SetTabWidth(hItem, 60, 0);
    MULTIPAGE_SetTabWidth(hItem, 60, 1);
    MULTIPAGE_AttachWindow(hItem, 0, Createsingle_motor());
    MULTIPAGE_AttachWindow(hItem, 0, Createdual_motor());

    MULTIPAGE_AttachWindow(hItem, 1, CreateWindow1());

    //
    // Initialization of 'PWM_Ctrl'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    StartItem = hItem;
    BUTTON_SetFont(hItem, FontMenuMSBlack24);
    BUTTON_SetText(hItem, "开始");
    //
    // Initialization of 'Dir'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, FontMenuMSBlack24);
    BUTTON_SetText(hItem, "变向");
    // USER START (Optionally insert additional code for further widget initialization)
    //! ADC由TIM3触发，其采样率为5kHz
    TIM3_Init(TIM_RELOAD_VALUE - 1, 108 - 1);
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (Id)
    {
    case ID_MULTIPAGE_0: // Notifications sent by 'Multipage'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'PWM_Ctrl'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        //! When "Start" is pressed
        {

          hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
          if (GetMotorConfig(REAL_LEFT_SPEED) || GetMotorConfig(REAL_RIGHT_SPEED))
          {
            BUTTON_SetFont(hItem, FontMenuMSBlack24);
            BUTTON_SetText(hItem, "开始");
            BUTTON_SetText(LeftStopItem, "左开始");
            BUTTON_SetText(RightStopItem, "右开始");

            if (GetMotorConfig(REAL_LEFT_SPEED)) // If the left motor is operating
            {
              StopSpecificMotor(LEFT_MOTOR);
            }
            if (GetMotorConfig(REAL_RIGHT_SPEED)) // If the right motor is operating
            {
              StopSpecificMotor(RIGHT_MOTOR);
            }

            EDIT_SetText(EditLeftRealSpeed, "0");
            EDIT_SetText(EditRightRealSpeed, "0");

            EDIT_SetText(SingleEditLeftRealSpeed, "0");
            EDIT_SetText(SingleEditRightRealSpeed, "0");
          }
          else
          {
            BUTTON_SetFont(hItem, FontMenuMSBlack24);
            BUTTON_SetText(hItem, "停止");
            BUTTON_SetText(LeftStopItem, "左停止");
            BUTTON_SetText(RightStopItem, "右停止");
            if (!GetMotorConfig(REAL_LEFT_SPEED)) // If the left motor is not operating
            {
              StartSpecificMotor(LEFT_MOTOR);
              EDIT_SetText(EditLeftRealSpeed, Int2String((int)(-GetMotorConfig(REAL_LEFT_SPEED) + 5500), str));
              EDIT_SetText(SingleEditLeftRealSpeed, Int2String((int)(-GetMotorConfig(REAL_LEFT_SPEED) + 5500), str));
            }

            if (!GetMotorConfig(REAL_RIGHT_SPEED)) // If the right motor is not operating
            {
              StartSpecificMotor(RIGHT_MOTOR);
              EDIT_SetText(EditRightRealSpeed, Int2String((int)(-GetMotorConfig(REAL_RIGHT_SPEED) + 5500), str));
              EDIT_SetText(SingleEditRightRealSpeed, Int2String((int)(-GetMotorConfig(REAL_RIGHT_SPEED) + 5500), str));
            }
          }
        }
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Dir'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
      {
        // Switch the direction of motor
        if (ChangeDirection())
        {
          TEXT_SetFont(DualDirectionItem, FontMenuMSBlack24);
          TEXT_SetTextAlign(DualDirectionItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
          TEXT_SetText(DualDirectionItem, "向左");
        }
        else
        {
          TEXT_SetFont(DualDirectionItem, FontMenuMSBlack24);
          TEXT_SetTextAlign(DualDirectionItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
          TEXT_SetText(DualDirectionItem, "向右");
        }
      }
      break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
      // USER START (Optionally insert additional code for further Ids)
      // USER END
    }
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
 *       CreateFramewin
 */
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void)
{
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

void MainTask(void)
{
  int i;
  u8 key = 0;
  arm_cfft_radix4_instance_f32 scfft;
  float32_t max_value;
  u32 max_index;
  /* 窗口自动使用存储设备 */
  WM_SetCreateFlags(WM_CF_MEMDEV);

  /* 初始化 */
  GUI_Init();
  /* 使用UTF-8编码 */
  GUI_UC_SetEncodeUTF8();
  /* 创建对话框，使用对话框创建函数 */
  CreateFramewin();

  arm_cfft_radix4_init_f32(&scfft, FFT_LENGTH, 0, 1); // 初始化scfft结构体，设定FFT相关参数

  while (1)
  {
    GUI_Delay(100);
    key = KEY_Scan(0);
    if (adc_flag) // ADC采样完成
    {
      // TODO：在这里尝试fft变换
      if (key == KEY0_PRES)
      {
        for (i = 0; i < ADC_BUFF_SIZE; i++)
        {
          printf("adc[%d]:%f\r\n", i, adc_buff[i]);
        }
      }
      arm_cfft_radix4_f32(&scfft, adc_buff);                         // FFT计算（基4）
      arm_cmplx_mag_f32(adc_buff, fft_outputbuf, FFT_LENGTH);        // 把运算结果复数求模得幅值
      fft_outputbuf[0] = 0;
      arm_max_f32(fft_outputbuf, FFT_LENGTH, &max_value, &max_index); //! 求最大幅值
      if (max_index*freq_resolution < 2500)
      {
        printf("freq = %f\r\n", max_index*freq_resolution);
        Display_Freq_Value(max_index*freq_resolution);
      }
      
      if (key == KEY1_PRES)
      {
        for (i = 0; i < FFT_LENGTH; i++)
        {
          printf("fft[%d]:%f\r\n", i, fft_outputbuf[i]);
        }
      }

      //! temp test
      // printf("\r\n max value is: %f .... max frequency is: %f \r\n", max_value, max_index);
      // key == 100 ? key = 0 : key++;
      // if (key == 100)
      //{

      //}

      adc_flag = 0;
    }

    // Display_Adc_Value(ADC_CHANNEL_4, 10);
  }
}

/*************************** End of file ****************************/
