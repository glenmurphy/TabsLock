_declspec(dllexport) void IdentifyMe(HWND w);
_declspec(dllexport) void SetKeyHook();
_declspec(dllexport) void RemoveKeyHook();
_declspec(dllexport) int _WEP (int bSystemExit);

#define WM_KEY_HOOK_TRIGGERED (WM_APP + 100)