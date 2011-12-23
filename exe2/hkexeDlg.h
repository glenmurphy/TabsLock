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

#if !defined(AFX_HKEXEDLG_H__7258F36C_A8AF_4BFE_8FC2_BFE935F1D4B8__INCLUDED_)
#define AFX_HKEXEDLG_H__7258F36C_A8AF_4BFE_8FC2_BFE935F1D4B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHkexeDlg dialog

#include "TrayDialog.h"

class CHkexeDlg : public CTrayDialog {
 // Construction
 public:
  CHkexeDlg(CWnd* pParent = NULL);
  CButton  h_StartButton;

  CMenu  h_Tray;
  enum { IDD = IDD_HKEXE_DIALOG };

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);

 protected:
  HICON m_hIcon;
  bool hooked;

  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  
  afx_msg void StartFilter();
  afx_msg void StopFilter();

  afx_msg void OnStart();
  //afx_msg void OnClose();
  afx_msg void OnTrayStart();
  afx_msg void OnTrayStop();
  afx_msg void OnTrayAbout();
  afx_msg void OnTrayExit();

  LRESULT OnKeyHookTriggered(WPARAM wParam, LPARAM lParam);

  DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_HKEXEDLG_H__7258F36C_A8AF_4BFE_8FC2_BFE935F1D4B8__INCLUDED_)
