// hkexe.h : main header file for the HKEXE application
//

#if !defined(AFX_HKEXE_H__D6E42B98_80CC_4C10_A88D_74C931BE72B8__INCLUDED_)
#define AFX_HKEXE_H__D6E42B98_80CC_4C10_A88D_74C931BE72B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"    // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHkexeApp:
// See hkexe.cpp for the implementation of this class
//

class CHkexeApp : public CWinApp {
 public:
  CHkexeApp();
  virtual BOOL InitInstance();
  DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HKEXE_H__D6E42B98_80CC_4C10_A88D_74C931BE72B8__INCLUDED_)
