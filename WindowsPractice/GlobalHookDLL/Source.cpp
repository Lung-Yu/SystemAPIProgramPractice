#include "Header.h"
#include <fstream>

bool setGlobalHook(){
	g_hook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (NULL == g_hook)
		return FALSE;
	return TRUE;
}
bool UnsetGlobalHook(){
	if (g_hook)
		UnhookWindowsHookEx(g_hook);
	return TRUE;
}

void setModule(HINSTANCE hinstance){
	g_hDllModule = hinstance;
}

LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam){
	return CallNextHookEx(g_hook, code, wParam, lParam);
}



