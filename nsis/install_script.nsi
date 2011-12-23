; Copyright (c) 2011 Google, Inc. All rights reserved.
; 
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;    http://www.apache.org/licenses/LICENSE-2.0
; 
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
: limitations under the License.
; This requires the UAC plugin - http://nsis.sourceforge.net/UAC_plug-in

; Define our application classnames so we can detect if it's running on 
; install or uninstall and prompt the user to close it.
!define WNDCLASS "TabsLock_Class"
!define WNDTITLE "TabsLock"
!define SYNC_TERM 0x00100001

!include "MUI.nsh"
!define PRODUCT_NAME "TabsLock"
!define PRODUCT_VERSION "0001"
!define PRODUCT_PUBLISHER "Glen Murphy"
!define PRODUCT_WEB_SITE "http://www/~glen/tabslock/"
!define MUI_ICON "..\exe2\res\hkexe.ico"
!define MUI_FINISHPAGE_TEXT "TabsLock installed - press CapsLock now to create a new Chrome tab."

;--------------------------------

; The name of the installer
Name "TabsLock Setup"

; The file to write
OutFile "output\tabslock_setup.exe"

XPStyle on

; The default installation directory
InstallDir $PROGRAMFILES\TabsLock

SetCompressor /SOLID lzma

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\TabsLock" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel user

;--------------------------------

; Pages
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"
;--------------------------------

; Attempt to give the UAC plug-in a user process and an admin process.
Function .onInit 
UAC_Elevate:
    UAC::RunElevated 
    StrCmp 1223 $0 UAC_ElevationAborted ; UAC dialog aborted by user?
    StrCmp 0 $0 0 UAC_Err ; Error?
    StrCmp 1 $1 0 UAC_Success ;Are we the real deal or just the wrapper?
    Quit
 
UAC_Err:
    MessageBox mb_iconstop "Unable to elevate, error $0"
    Abort
 
UAC_ElevationAborted:
    # elevation was aborted, run as normal?
    MessageBox mb_iconstop "This installer requires admin access, aborting!"
    Abort
 
UAC_Success:
    StrCmp 1 $3 +4 ;Admin?
    StrCmp 3 $1 0 UAC_ElevationAborted ;Try again?
    MessageBox mb_iconstop "This installer requires admin access, try again"
    goto UAC_Elevate 
FunctionEnd

Function .onInstFailed
    UAC::Unload ;Must call unload!
FunctionEnd
 
Function .onInstSuccess
    UAC::Unload ;Must call unload!
FunctionEnd

; Elevate for uninstallation
Function un.onInit 
UAC_Elevate:
    UAC::RunElevated 
    StrCmp 1223 $0 UAC_ElevationAborted ; UAC dialog aborted by user?
    StrCmp 0 $0 0 UAC_Err ; Error?
    StrCmp 1 $1 0 UAC_Success ;Are we the real deal or just the wrapper?
    Quit
 
UAC_Err:
    MessageBox mb_iconstop "Unable to elevate, error $0"
    Abort
 
UAC_ElevationAborted:
    # elevation was aborted, run as normal?
    MessageBox mb_iconstop "This installer requires admin access, aborting!"
    Abort
 
UAC_Success:
    StrCmp 1 $3 +4 ;Admin?
    StrCmp 3 $1 0 UAC_ElevationAborted ;Try again?
    MessageBox mb_iconstop "This installer requires admin access, try again"
    goto UAC_Elevate 
FunctionEnd

Function un.onUnInstFailed
    UAC::Unload ;Must call unload!
FunctionEnd
 
Function un.onUnInstSuccess
    UAC::Unload ;Must call unload!
FunctionEnd

!macro TerminateApp
	Push $0 ; window handle
	Push $1
	Push $2 ; process handle
	FindWindow $0 '${WNDCLASS}' '${WNDTITLE}'
	IntCmp $0 0 done
	
	DetailPrint "Asking existing app to quit..."	
	System::Call 'user32.dll::GetWindowThreadProcessId(i r0, *i .r1) i .r2'
	System::Call 'kernel32.dll::OpenProcess(i ${SYNC_TERM}, i 0, i r1) i .r2'
	
	SendMessage $0 WM_CLOSE 0 0 /TIMEOUT=2000
	SendMessage $0 WM_QUIT 0 0 /TIMEOUT=2000
	
	System::Call 'kernel32.dll::WaitForSingleObject(i r2, i 2000) i .r1'
	IntCmp $1 0 done
	
	DetailPrint "Terminating process..."	
	; If we couldn't close it, terminate it.
	System::Call 'kernel32.dll::TerminateProcess(i r2, i 0) i .r1'
	
	Sleep 2000
 done:
  Pop $2
  Pop $1
  Pop $0
!macroend

; The stuff to install
Section "TabsLock"
  !insertmacro TerminateApp

  SectionIn RO
  
  ; Remove existing files and uninstaller

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "..\exe2\Release\tabslock.dll"
  File "..\exe2\Release\tabslock.exe"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\TabsLock "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TabsLock" "DisplayName" "TabsLock"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TabsLock" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TabsLock" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TabsLock" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
  CreateDirectory "$SMPROGRAMS\TabsLock"
  CreateShortCut "$SMPROGRAMS\TabsLock\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\TabsLock\TabsLock.lnk" "$INSTDIR\tabslock.exe" "" "$INSTDIR\tabslock.exe" 0
  CreateShortCut "$SMPROGRAMS\Startup\TabsLock.lnk" "$INSTDIR\tabslock.exe" "" "$INSTDIR\tabslock.exe" 0

	; ExecShell "" "$INSTDIR\tabslock.exe" SW_SHOWMINIMIZED
	UAC::Exec '' '"$INSTDIR\tabslock.exe"' '' ''
	
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TabsLock"
  DeleteRegKey HKLM SOFTWARE\TabsLock

  ; Remove files and uninstaller
  Delete $INSTDIR\tabslock.exe
  Delete $INSTDIR\tabslock.dll
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Tabslock\*.*"
  Delete "$SMPROGRAMS\Startup\TabsLock.lnk"

  ; Remove directories used
  RMDir "$SMPROGRAMS\TabsLock"
  RMDir "$INSTDIR"

SectionEnd
