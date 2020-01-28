#include "Header.h"
#include <stdio.h>
#include <iostream>

int main(){
	setModule(LoadLibrary(L"GlobalHookDLL_temp.dll"));

	printf_s("%s is Hook\n", setGlobalHook ()? "true" : "false");
	system("pause");
	UnsetGlobalHook();
	printf_s("unHook.\n");
	system("pause");
	return 0;
}

