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

#define FontMenuSong24  &GUI_FontMenuSong24
#define FontMenuMSBlack24 &GUI_FontMenuMSBlack24
/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */


extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuSong24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontMenuMSBlack24;

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
    {EDIT_CreateIndirect, "Data", ID_EDIT_1, 225, 325, 80, 40, 0, 0x64, 0},
    {TEXT_CreateIndirect, "SampleData:", ID_TEXT_1, 135, 325, 80, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "ChangeMode", ID_BUTTON_2, 185, 450, 100, 60, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    {TEXT_CreateIndirect, "Direction", ID_TEXT_2, 185, 390, 80, 40, 0, 0x0, 0},
    // USER END
};

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static code)
extern WM_HWIN PageItem;
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
  //! USER START (Optionally insert additional variables)
  int v;
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
    // Initialization of 'DualSpeed'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "0");
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    EDIT_SetFont(hItem, GUI_FONT_16_ASCII);
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
    TEXT_SetText(hItem, "转速");
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

    // USER START (Optionally insert additional code for further widget initialization)
    // TODO： 改字模
    //! Initialization of 'Direction'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, FontMenuMSBlack24);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "向左");
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
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
        v = SLIDER_GetValue(hItem);
        printf("%d\r\n", v);
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
    case ID_BUTTON_0: // Notifications sent by 'UP'
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
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
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
        //! Change the manual control page between Dual/Single Motor
        MULTIPAGE_AttachWindow(PageItem, 0, Createsingle_motor());
        // WM_HideWindow(pMsg->hWin);
        // WM_ShowWindow(Createsingle_motor());
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
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/