#include <Windows.h>

bool WinExec_Test(char , UINT);
bool ShellExecute_Test(LPCWSTR, UINT);
bool CreateProcess_Test(LPWSTR, UINT uiCmdShow);

int main(){

	return 0;
}

bool WinExec_Test(char *pszExePath, UINT uiCmdShow){
	UINT uiRet = NULL;
	uiRet = WinExec(pszExePath, uiCmdShow);
	if (31 > uiRet)
		return TRUE;
	else
		return FALSE;
}

bool ShellExecute_Test(LPCWSTR pszExePath, UINT uiCmdShow){
	HINSTANCE hInstance = NULL;
	hInstance = ShellExecute(NULL, NULL, pszExePath, NULL, NULL, uiCmdShow);
	if (32 < (DWORD)hInstance)
		return TRUE;
	else
		return FALSE;
}

bool CreateProcess_Test(LPWSTR pszExePath, UINT uiCmdShow){
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	bool bRet = FALSE;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;	//指定 wShowWindow 成員有效
	si.wShowWindow = uiCmdShow;
	bRet = CreateProcess(NULL, pszExePath, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	if (bRet){
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	return bRet;
}