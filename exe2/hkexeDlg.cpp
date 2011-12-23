// Copyright (c) 2011 Google, Inc. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//    http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <windows.h>
#include <shlobj.h>
#include <WinAble.h>

#include "stdafx.h"
#include "hkexe.h"
#include "hkexeDlg.h"
#include "..\dll\intercept.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CHkexeDlg dialog

CHkexeDlg::CHkexeDlg(CWnd* pParent /*=NULL*/)
  : CTrayDialog(CHkexeDlg::IDD, pParent) {
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  hooked = false;
}

void CHkexeDlg::DoDataExchange(CDataExchange* pDX) {
  CTrayDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDSTART, h_StartButton);
}

BEGIN_MESSAGE_MAP(CHkexeDlg, CTrayDialog)
  //{AFX_MSG
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDSTART, OnStart)
  ON_COMMAND(ID_TRAYMENU_START, OnTrayStart)
  ON_COMMAND(ID_TRAYMENU_STOP, OnTrayStop)
  ON_COMMAND(ID_TRAYMENU_EXIT, OnTrayExit)
  //}AFX_MSG

  ON_MESSAGE(WM_KEY_HOOK_TRIGGERED, OnKeyHookTriggered)
END_MESSAGE_MAP()


BOOL Run(const int CSIDL, const char *path) {
  CHAR strPath[MAX_PATH];
  SHGetSpecialFolderPath(0, strPath, CSIDL, FALSE);
  strcat_s(strPath, MAX_PATH, path);

  if ((int)(ShellExecute(NULL, NULL, strPath, NULL, NULL, SW_SHOW)) <= 32)
    return false;
  
  return true;
}

HWND FindChrome() {
  HWND chrome = FindWindow("Chrome_XPFrame", NULL);
  if (!chrome) 
    chrome = FindWindow("Chrome_VistaFrame", NULL);

  return chrome;
}

void DisableCapslock() {
  if (GetKeyState(VK_CAPITAL)) {
    INPUT input[2];
    ZeroMemory(input, sizeof(input));        
    input[0].type = input[1].type = INPUT_KEYBOARD;
    input[0].ki.wVk  = input[1].ki.wVk = VK_CAPITAL;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
  }
}

void SendNewTabKeyPress() {
  keybd_event(VK_CONTROL, 0x1D, 0, 0); 
  keybd_event(0x54, 0x94, 0, 0) ;
  keybd_event(0x54, 0x94, KEYEVENTF_KEYUP, 0) ;
  keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_KEYUP, 0); 
}

void SendFocusLocationBarPress() {
  keybd_event(VK_CONTROL, 0x1D, 0, 0); 
  keybd_event(0x4C, 0xA6, 0, 0) ;
  keybd_event(0x4C, 0xA6, KEYEVENTF_KEYUP, 0) ;
  keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_KEYUP, 0); 
}

HWND FocusChrome() {
  HWND chrome = FindChrome();
  if (!chrome)
    return NULL;

  SetForegroundWindow(chrome);
  SetActiveWindow(chrome);
  return chrome;
}

void DetectNewTab() {
  TCHAR title[14];
  TCHAR newtab[14] = "New Tab - Goo";
  TCHAR loading[14] = "Google Chrome";

  HWND chrome = FocusChrome();

  // Wait for the default title (Google Chrome) to disappear
  // we give up pretty quickly, as that title can appear
  // in other situations (janky!).
  int attempts = 0;
  while (attempts < 5) {
    GetWindowText(chrome, title, 14);
    if (strcmp(title, loading) == 0) {
      Sleep(100);
      attempts++;
    } else if (strcmp(title, newtab) != 0) {
      SendNewTabKeyPress();
      return;
    } else {
      SendFocusLocationBarPress();
      return;
    }
  }
}

void RunChrome() {
  if (!Run(CSIDL_DESKTOPDIRECTORY, "\\Chromespace.lnk"))
    if (!Run(CSIDL_DESKTOPDIRECTORY, "\\Google Chrome.lnk"))
      Run(CSIDL_LOCAL_APPDATA, "\\Google\\Chrome\\Application\\Chrome.exe");

  // Relying on timers makes Glen cry.
  int attempts = 0;

  HWND chrome = NULL;
  while(chrome == NULL) {
    Sleep(50);
    chrome = FocusChrome();
    if (++attempts > 10)
      break;
  }

  if (chrome)
    DetectNewTab();
}


/////////////////////////////////////////////////////////////////////////////
// CHkexeDlg message handlers

BOOL CHkexeDlg::OnInitDialog() {
  PostMessage(WM_SYSCOMMAND, SC_MINIMIZE); 
  CTrayDialog::OnInitDialog();

  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  
  TraySetIcon(IDR_MAINFRAME);
  TraySetToolTip("TabsLock");
  TraySetMenu(IDR_MENU1);
  
  OnStart();

  TrayShow();
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHkexeDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  CTrayDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.
void CHkexeDlg::OnPaint()  {
  if (IsIconic()) {
    CPaintDC dc(this); // device context for painting
    
    SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);
    
    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    
    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  } else {
    CTrayDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHkexeDlg::OnQueryDragIcon() {
  return (HCURSOR) m_hIcon;
}

void CHkexeDlg::StartFilter() {
  IdentifyMe(m_hWnd);
  SetKeyHook();
  hooked = true;
  h_StartButton.SetWindowText("Stop");
  TrayPressedStart();
  TraySetIcon(IDI_RUNNING);
  TraySetToolTip("TabsLock Running");
  TrayUpdate();
}

void CHkexeDlg::StopFilter() {
  RemoveKeyHook();
  hooked = false;
  h_StartButton.SetWindowText("Start");
  TrayPressedStop();
  TraySetIcon(IDI_STOPPED);
  TraySetToolTip("TabsLock Stopped");
  TrayUpdate();
}

void CHkexeDlg::OnStart() {
  if(hooked == true) {
    StopFilter();
  } else {
    StartFilter();
  }
}

void CHkexeDlg::OnTrayStart() {
  StartFilter();
}

void CHkexeDlg::OnTrayStop() {
  StopFilter();
}

void CHkexeDlg::OnTrayExit() {
  TrayHide();
  exit(1);
}

LRESULT CHkexeDlg::OnKeyHookTriggered(WPARAM wParam, LPARAM lParam) {
  HWND chrome = FindChrome();
  bool keyDown = !wParam;

  if (keyDown) {
    if (chrome) {
      ::SetForegroundWindow(chrome); 
      SendNewTabKeyPress();
    } else {
      RunChrome();
    }
  } else {
    DisableCapslock();
  }

  return 0;
}
