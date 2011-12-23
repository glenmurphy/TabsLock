; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHkexeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hkexe.h"

ClassCount=3
Class1=CHkexeApp
Class2=CHkexeDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_HKEXE_DIALOG
Resource4=IDD_HKEXE_DIALOG (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDR_MENU1

[CLS:CHkexeApp]
Type=0
HeaderFile=hkexe.h
ImplementationFile=hkexe.cpp
Filter=N

[CLS:CHkexeDlg]
Type=0
HeaderFile=hkexeDlg.h
ImplementationFile=hkexeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[CLS:CAboutDlg]
Type=0
HeaderFile=hkexeDlg.h
ImplementationFile=hkexeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_HKEXE_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CHkexeDlg

[DLG:IDD_HKEXE_DIALOG (English (U.S.))]
Type=1
Class=CHkexeDlg
ControlCount=2
Control1=IDSTART,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_TRAYMENU_START
Command2=ID_TRAYMENU_STOP
Command3=ID_TRAYMENU_ABOUT
Command4=ID_TRAYMENU_EXIT
CommandCount=4

