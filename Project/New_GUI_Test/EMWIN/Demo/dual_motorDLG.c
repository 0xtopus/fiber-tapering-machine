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
/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_WINDOW_0 (GUI_ID_USER + 0x0D)
#define ID_SLIDER_0 (GUI_ID_USER + 0x0E)
#define ID_TEXT_0 (GUI_ID_USER + 0x0F)
#define ID_BUTTON_0 (GUI_ID_USER + 0x10)
#define ID_BUTTON_1 (GUI_ID_USER + 0x11)
#define ID_EDIT_0 (GUI_ID_USER + 0x12)
#define ID_EDIT_1 (GUI_ID_USER + 0x13)
#define ID_TEXT_1 (GUI_ID_USER + 0x14)
#define ID_BUTTON_2 (GUI_ID_USER + 0x15)
#define ID_TEXT_2 (GUI_ID_USER + 0x16)
#define ID_TEXT_3 (GUI_ID_USER + 0x17)
#define ID_EDIT_2 (GUI_ID_USER + 0x18)
#define ID_TEXT_4 (GUI_ID_USER + 0x19)
#define ID_EDIT_3 (GUI_ID_USER + 0x1A)

#define FontMenuSong24  &GUI_FontMenuSong24
#define FontMenuMSBlack24 &GUI_FontMenuMSBlack24

/*********************************************************************
 *
 *       Global data
 *
 **********************************************************************
 */

extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuSong24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuMSBlack24;
//extern WM_HWIN PageItem;
extern WM_HWIN SingleMotorWIN;

WM_HWIN DualMotorWIN;
WM_HWIN DualDirectionItem;
WM_HWIN EditLeftRealSpeed;
WM_HWIN EditRightRealSpeed;

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
    {WINDOW_CreateIndirect, "dual_motor", ID_WINDOW_0, 5, 45, 470, 675, 0, 0x0, 0},
    {SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 100, 180, 250, 70, 0, 0x0, 0},
    {TEXT_CreateIndirect, "Motors", ID_TEXT_0, 10, 195, 80, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "UP", ID_BUTTON_0, 370, 135, 80, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Down", ID_BUTTON_1, 370, 235, 80, 40, 0, 0x0, 0},
    {EDIT_CreateIndirect, "DualSpeed", ID_EDIT_0, 370, 185, 80, 40, 0, 0x64, 0},
    {EDIT_CreateIndirect, "Data", ID_EDIT_1, 215, 445, 80, 40, 0, 0x64, 0},
    {TEXT_CreateIndirect, "SampleData:", ID_TEXT_1, 130, 445, 80, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "ChangeMode", ID_BUTTON_2, 185, 550, 100, 60, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    {TEXT_CreateIndirect, "Direction", ID_TEXT_2, 190, 495, 80, 40, 0, 0x0, 0},

    {TEXT_CreateIndirect, "LeftRealSpeed", ID_TEXT_3, 95, 305, 80, 40, 0, 0x64, 0},
    {EDIT_CreateIndirect, "LRsp", ID_EDIT_2, 95, 350, 80, 40, 0, 0x64, 0},
    {TEXT_CreateIndirect, "RightRealSpeed", ID_TEXT_4, 310, 305, 80, 40, 0, 0x64, 0},
    {EDIT_CreateIndirect, "RRsp", ID_EDIT_3, 310, 350, 80, 40, 0, 0x64, 0}

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
  WM_HWIN editItem;
  int NCode;
  int Id;
  //! USER START (Optionally insert additional variables)
  int v;
  char str[6] = {0};
  // USER END

  switch (pMsg->MsgId)
  {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Motors'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "双电机");
    //
    // Initialization of 'UP'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, FontMenuSong24);
    BUTTON_SetText(hItem, "▲");
    //BUTTON_SetFont(hItem, GUI_FONT_16_ASCII);
    //
    // Initialization of 'Down'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, FontMenuSong24);
    BUTTON_SetText(hItem, "▼");
    
    //
    // Initialization of 'Data'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'SampleData:'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "采样");
    //
    // Initialization of 'ChangeMode'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, FontMenuMSBlack24);
    BUTTON_SetText(hItem, "模式");
    //
    //! Initialization of 'Slider'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
    SLIDER_SetRange(hItem, 500, 5000);
    SLIDER_SetValue(hItem, 500);
    
    //
    // Initialization of 'DualSpeed'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    EDIT_SetFont(hItem, GUI_FONT_16_ASCII);
    EDIT_SetText(hItem, "500");
    
    // USER START (Optionally insert additional code for further widget initialization)
    // TODO 改字
    //! Initialization of 'Direction'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    DualDirectionItem = hItem;
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "向右");
    //
    //! Initialization of "LeftRealSpeed"
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "左转速");
    //
    //! Initialization of "RightRealSpeed"
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "右转速");
    //
    //! Initialization of "LRsp"
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EditLeftRealSpeed = hItem;
    EDIT_SetFont(hItem, GUI_FONT_16_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    EDIT_SetText(hItem, "0");
    //
    //! Initialization of "RRsp"
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EditRightRealSpeed = hItem;
    EDIT_SetFont(hItem, GUI_FONT_16_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    EDIT_SetText(hItem, "0");
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch (Id)
    {
    case ID_SLIDER_0: // Notifications sent by 'Slider'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        //TODO USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        //TODO: is editItem really useful?
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
        v = SLIDER_GetValue(hItem);
        editItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
        EDIT_SetText(editItem, Int2String(v, str));
        ChangeSpeed(&MotorConfig, (u16)v);
        if (MotorConfig.enable) 
        {
          hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
          EDIT_SetText(hItem, Int2String(v, str));
          hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
          EDIT_SetText(hItem, Int2String(v, str));
        }
        

        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'UP'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
        editItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
        if (MotorConfig.set_left_speed - 100 > 500 && MotorConfig.set_left_speed - 100 > 500)
        {
          EDIT_GetText(editItem, str, 5);
          v = String2Int(str);
          ChangeSpeed(&MotorConfig, (u16)v + 100);
          EDIT_SetText(editItem, Int2String(v + 100, str));
          SLIDER_SetValue(hItem, v + 100);

          if (MotorConfig.enable) 
          {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetText(hItem, Int2String(v, str));
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
            EDIT_SetText(hItem, Int2String(v, str));
          }
        } else {
          // Set to maximum speed if the upper limit is reached
          ChangeSpeed(&MotorConfig, 5000);
          EDIT_SetText(editItem, "5000");
          SLIDER_SetValue(hItem, 5000);

          if (MotorConfig.enable) 
          {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetText(hItem, "5000");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
            EDIT_SetText(hItem, "5000");
          }
        }
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Down'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
        editItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
        if (MotorConfig.set_left_speed + 100 < 5000 && MotorConfig.set_left_speed + 100 < 5000)
        {
          EDIT_GetText(editItem, str, 5);
          v = String2Int(str);
          ChangeSpeed(&MotorConfig, (u16)v - 100);
          EDIT_SetText(editItem, Int2String(v - 100, str));
          SLIDER_SetValue(hItem, v - 100);
          
          if (MotorConfig.enable) 
          {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetText(hItem, Int2String(v, str));
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
            EDIT_SetText(hItem, Int2String(v, str));
          }
        } else {
          // Set to maximum speed if the upper limit is reached
          ChangeSpeed(&MotorConfig, 500);
          EDIT_SetText(editItem, "500");
          SLIDER_SetValue(hItem, 500);

          if (MotorConfig.enable) 
          {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetText(hItem, "500");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
            EDIT_SetText(hItem, "500");
          }          
        }
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_EDIT_0: // Notifications sent by 'DualSpeed'
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
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Data'
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
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'ChangeMode'
      switch (NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
      {
        //MotorConfig.dual_motor_speed = MotorConfig.set_left_speed;
        //! Change the manual control page between Dual/Single Motor
        //MULTIPAGE_AttachWindow(PageItem, 0, Createsingle_motor());
        //WM_DeleteWindow(DualMotorWIN);
        // WM_HideWindow(pMsg->hWin);
        WM_HideWindow(DualMotorWIN);
        WM_ShowWindow(SingleMotorWIN);
        
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
 *       Createdual_motor
 */
WM_HWIN Createdual_motor(void);
WM_HWIN Createdual_motor(void)
{
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  DualMotorWIN = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
