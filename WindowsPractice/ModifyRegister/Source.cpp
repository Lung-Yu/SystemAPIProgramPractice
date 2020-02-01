#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#define REG_AUTORUN_CURRENT_USER "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define REG_AUTORUN_LOCAL "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define EXECUTE_FILE "C:\\Users\\lungyu\\Desktop\\HelloWorld.exe"

BOOL RegWriteWithType(HKEY, char *fileName, char * valueName);
BOOL Reg_CurrentUser(char *fileName, char * valueName);
BOOL Reg_LocalMachine( char *fileName, char * valueName);
VOID ShowError(LPCSTR);

int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == Reg_CurrentUser(EXECUTE_FILE, "975"))
	{
		printf_s("Reg_CurrentUser Error!\n");
	}
	if (FALSE == Reg_LocalMachine(EXECUTE_FILE, "975"))
	{
		printf("Reg_LocalMachine Error!\n");
	}

	printf("Reg OK.\n");

	system("pause");
	return 0;
}

VOID ShowError(LPCSTR message){
	MessageBox(NULL, message, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL Reg_LocalMachine(char *fileName, char * valueName){
	return RegWriteWithType(HKEY_LOCAL_MACHINE, fileName, valueName);
}

BOOL Reg_CurrentUser(char *fileName, char * valueName){
	return RegWriteWithType(HKEY_CURRENT_USER, fileName, valueName);
}

BOOL RegWriteWithType(HKEY key, char *fileName, char * valueName){
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(key, REG_AUTORUN_CURRENT_USER, 0, KEY_WRITE, &hKey)){
		ShowError("RegOpenKeyEx");
	}
	if (ERROR_SUCCESS != RegSetValueEx(hKey, valueName, 0, REG_SZ, (BYTE*)fileName, (1 + lstrlen(fileName)))){
		ShowError("RegSetValueEx");
	}

	RegCloseKey(hKey);

	return TRUE;
}