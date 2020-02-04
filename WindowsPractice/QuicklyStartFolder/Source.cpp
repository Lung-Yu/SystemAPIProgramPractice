#include <Windows.h>
#include <stdio.h>
#include <Shlobj.h>

#define EXECUTE_FILE "C:\\Users\\lungyu\\Desktop\\HelloWorld.exe"

#pragma comment(lib, "shell32.lib")

BOOL autorun_startup(char* srcFilePath,char *DestFileName);

int main(){
	printf_s("autorun startup setup is %s .\n",(autorun_startup(EXECUTE_FILE, "HelloWorld.exe"))?"OK":"NOT OK");
	system("pause");
	return 0;
}

BOOL autorun_startup(char* srcFilePath, char *DestFileName){
	BOOL bRet = FALSE;
	char startupPath[MAX_PATH] = {0};
	char destPath[MAX_PATH] = { 0 };

	bRet = SHGetSpecialFolderPath(NULL, (LPSTR)startupPath, CSIDL_STARTUP, TRUE);
	printf_s("StartupPath = %s\n", startupPath);
	if (FALSE == bRet)
		return FALSE;

	wsprintf(destPath, "%s\\%s", startupPath, DestFileName);
	printf_s("Dest Path = %s \n", destPath);
	bRet = CopyFile(srcFilePath, destPath, FALSE);
	
	if (FALSE == bRet)
		return FALSE;
	return TRUE;
}