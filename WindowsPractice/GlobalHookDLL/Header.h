#include <Windows.h>
#include <iostream>

#pragma once
#pragma data_seg("tygr")
	HHOOK g_hook;
	HINSTANCE g_hDllModule;
#pragma data_seg()
#pragma comment(linker,"/SECTUIN:mydata,RWS")

//more about this in reference 1
#define DLLDIR  __declspec(dllexport)   // export DLL information

void DLLDIR setModule(HINSTANCE);
bool DLLDIR setGlobalHook();
bool DLLDIR UnsetGlobalHook();
LRESULT GetMsgProc(int, WPARAM, LPARAM);


