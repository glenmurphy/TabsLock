// Code from:
// http://www.experts-exchange.com/Programming/Programming_Languages/Cplusplus/Q_20453601.html

#include <windows.h>
#include "intercept.h"

#pragma data_seg(".shared")
// These have to be initialized, else they won't be shared!
HHOOK hKeyhook = 0;
HWND hwndKeyTarget = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,RWS")

HINSTANCE hDll;

/* MISC FUNCTIONS */

/*************************************************************
* Messages to be sent to the main application
**************************************************************/

LRESULT CALLBACK KeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  bool simulatedKey = ((lParam & 0xFF0000L) == 0L);

  int keyUp = 0;
  if((HIWORD(lParam) & (KF_UP))) {
    keyUp = KEYEVENTF_KEYUP;
  }

  if(nCode == HC_ACTION && simulatedKey == false) {
    if(wParam == VK_CAPITAL && GetKeyState(VK_SHIFT) >= 0) {
      if (hwndKeyTarget)
        PostMessage(hwndKeyTarget, WM_KEY_HOOK_TRIGGERED, (WPARAM)keyUp, NULL);
      return -1;
    }
  }

  return CallNextHookEx(hKeyhook, nCode, wParam, lParam);
}

/*************************************************************
* Main DLL function
**************************************************************/

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID) {
  if ( dwReason == DLL_PROCESS_ATTACH)
    hDll = hInstance;
  return (int)(DisableThreadLibraryCalls (hDll));
}

/*************************************************************
* Set the keyboard hook
**************************************************************/

_declspec(dllexport) void SetKeyHook() {
  if(hKeyhook == NULL) {
    hKeyhook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, hDll, 0);
    if (hKeyhook == NULL) {
      MessageBox(NULL, TEXT("Couldn't set the keyboard hook.."), TEXT("Fail Hook"), MB_OK);
    }
  }
}

/*************************************************************
* Remove the keyboard hook
**************************************************************/

_declspec(dllexport) void RemoveKeyHook() {
  if (hKeyhook != NULL)  {
    UnhookWindowsHookEx(hKeyhook);
    hKeyhook = NULL;
  }
}

_declspec(dllexport) void IdentifyMe(HWND w) {
  hwndKeyTarget = w;
}

/*************************************************************
* WEP
**************************************************************/
// FUNCTION:  WEP(int)
// PURPOSE:  Performs cleanup tasks when the DLL is unloaded. WEP() is called
// automatically by Windows when the DLL is unloaded (no remaining tasks still
// have the DLL loaded). It is strongly recommended that a DLL have a WEP() function,
// even if it does nothing but returns success (1).

_declspec(dllexport) int _WEP (int bSystemExit) {
  RemoveKeyHook();
  return(1);
}