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

#if !defined(AFX_TRAYDIALOG_H__24C2AEA9_B40D_11D4_BFA7_00C0DF034AED__INCLUDED_)
#define AFX_TRAYDIALOG_H__24C2AEA9_B40D_11D4_BFA7_00C0DF034AED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrayDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrayDialog dialog

#define WM_TRAY_ICON_NOTIFY_MESSAGE (WM_USER + 1)


class CTrayDialog : public CDialog
{

private:
  BOOL m_bMinimizeToTray;

  BOOL      m_bTrayIconVisible;
  NOTIFYICONDATA  m_nidIconData;
  CMenu      m_mnuTrayMenu;
  UINT      m_nDefaultMenuItem;
  UINT      m_nStart;
  UINT      m_nStop;

  // Construction
public:
  void TraySetMinimizeToTray(BOOL bMinimizeToTray = TRUE);
  BOOL TraySetMenu(UINT nResourceID,UINT nDefaultPos=0);  
  BOOL TraySetMenu(HMENU hMenu,UINT nDefaultPos=0);  
  BOOL TraySetMenu(LPCTSTR lpszMenuName,UINT nDefaultPos=0);  
  BOOL TrayUpdate();
  BOOL TrayShow();
  BOOL TrayHide();
  void TraySetToolTip(LPCTSTR lpszToolTip);
  void TraySetIcon(HICON hIcon);
  void TraySetIcon(UINT nResourceID);
  void TraySetIcon(LPCTSTR lpszResourceName);
  
  void TrayPressedStart();
  void TrayPressedStop();

  BOOL TrayIsVisible();
  CTrayDialog(UINT uIDD,CWnd* pParent = NULL);   // standard constructor

  virtual void OnTrayLButtonDown(CPoint pt);
  virtual void OnTrayLButtonDblClk(CPoint pt);
  
  virtual void OnTrayRButtonDown(CPoint pt);

 // Implementation
 protected:
  // Generated message map functions
  //{{AFX_MSG(CTrayDialog)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);  
  private:
  afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYDIALOG_H__24C2AEA9_B40D_11D4_BFA7_00C0DF034AED__INCLUDED_)
