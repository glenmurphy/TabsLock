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

#include "stdafx.h"
#include "hkexe.h"
#include "hkexeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHkexeApp

BEGIN_MESSAGE_MAP(CHkexeApp, CWinApp)
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHkexeApp construction

CHkexeApp::CHkexeApp()
{
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHkexeApp object

CHkexeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHkexeApp initialization

BOOL CHkexeApp::InitInstance() {
  // Kill any existing instances.
  HWND existing = FindWindow("TabsLock_Class", "TabsLock");
  if (existing) {
    PostMessage(existing, WM_QUIT, 0, 0);
  }

  // Register our classname.
  WNDCLASS wc;
	// Get the info for this class.
  // #32770 is the default class name for dialogs boxes.
	::GetClassInfo(AfxGetInstanceHandle(), "#32770", &wc);
	// Change the name of the class.
	wc.lpszClassName = "TabsLock_Class";
	// Register this class so that MFC can use it.
	AfxRegisterClass(&wc);	

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need.
  CHkexeDlg dlg;
  m_pMainWnd = &dlg;

  int nResponse = dlg.DoModal();

  // Since the dialog has been closed, return FALSE so that we exit the
  // application, rather than start the application's message pump.
  return FALSE;
}
