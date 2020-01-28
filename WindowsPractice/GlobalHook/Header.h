#include <Windows.h>
#include <iostream>

#pragma once
#pragma data_seg("tygr")
	HHOOK g_hook;
	HINSTANCE g_hDllModule;
#pragma data_seg()
#pragma comment(linker,"/SECTUIN:mydata,RWS")

void setModule(HINSTANCE);
bool setGlobalHook();
bool UnsetGlobalHook();

