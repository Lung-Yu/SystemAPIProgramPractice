#include "stdafx.h"
#include <iostream>

extern HMODULE g_hDllModule;

#pragma data_seg("mydata")
HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")



LRESULT GetMsgProc(int code,WPARAM wParam,LPARAM lParam)
{
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}


BOOL SetGlobalHook()
{
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (NULL == g_hHook)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL UnsetGlobalHook()
{
	if (g_hHook)
	{
		UnhookWindowsHookEx(g_hHook);
	}
	return TRUE;
}