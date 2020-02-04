#include <Windows.h>
#include <stdio.h>
#include "ServiceOperate.h"




int main(){
	BOOL bRet = FALSE;

	char exePath[] = 
		"C:\\Users\\lungyu\\Documents\\Visual Studio 2013\\Projects\\SystemAPIProgramPractice\\WindowsPractice\\\Debug\\CreateProcessAsUser.exe";

	bRet = SystemServiceOperate(exePath, CREATE_SERVICE);
	if (bRet)
		printf_s("INSTALL OK.\n");
	else
		printf_s("INSTALL ERROR.\n");
	
	bRet = SystemServiceOperate(exePath, START_SERVICE);
	if (bRet)
		printf_s("START OK.\n");
	else
		printf_s("START ERROR.\n");

	system("pause");

	bRet = SystemServiceOperate(exePath, STOP_SERVICE);
	if (bRet)
		printf_s("STOP OK.\n");
	else
		printf_s("STOP ERROR.\n");

	bRet = SystemServiceOperate(exePath, DELETE_SERVICE);
	if (bRet)
		printf_s("UNINSTALL OK.\n");
	else
		printf_s("UNINSTALL ERROR.\n");

	return 0;
}