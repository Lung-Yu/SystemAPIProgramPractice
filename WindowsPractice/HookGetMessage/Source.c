#include <Windows.h>
#include <stdio.h>
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{
	typedef BOOL(*typedef_SetGlobalHook)();
	typedef BOOL(*typedef_UnsetGlobalHook)();
	HMODULE hDll = NULL;
	typedef_SetGlobalHook SetGlobalHook = NULL;
	typedef_UnsetGlobalHook UnsetGlobalHook = NULL;
	BOOL bRet = FALSE;

	do
	{
		hDll = LoadLibrary("DllHookGetMessage.dll");
		if (NULL == hDll)
		{
			printf_s("LoadLibrary Error[%d]\n", GetLastError());
			break;
		}
		SetGlobalHook = (typedef_SetGlobalHook) GetProcAddress(hDll, "SetGlobalHook");
		if (NULL == SetGlobalHook)
		{
			printf_s("GetProcAddress Error[%d]\n", GetLastError());
			break;
		}
		bRet = SetGlobalHook();
		if (bRet)
		{
			printf("SetGlobalHook OK.\n");
		}
		else
		{
			printf("SetGlobalHook ERROR.\n");
		}

		system("pause");

		UnsetGlobalHook = (typedef_UnsetGlobalHook) GetProcAddress(hDll, "UnsetGlobalHook");
		if (NULL == UnsetGlobalHook)
		{
			printf_s("GetProcAddress Error[%d]\n", GetLastError());
			break;
		}
		UnsetGlobalHook();
		printf("UnsetGlobalHook OK.\n");

	} while (FALSE);

	system("pause");
	return 0;
}

