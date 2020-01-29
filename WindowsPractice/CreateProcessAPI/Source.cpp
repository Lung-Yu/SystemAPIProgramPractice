#include <Windows.h>
#include <iostream>

bool WinExec_Test(LPCSTR pszExePath, UINT uiCmdShow);
bool ShellExecute_Test(LPCWSTR pszExePath, UINT uiCmdShow);
BOOL CreateProcess_Test(LPWSTR pszExePath, UINT uiCmdShow);

int main(){
	
	if (WinExec_Test("HelloWorld.exe", SW_SHOWNORMAL))
		std::cout << "Win exec successful." << std::endl;
		
	if (ShellExecute_Test(L"HelloWorld.exe", SW_SHOWNORMAL))
		std::cout << "Shell execute successful." << std::endl;
	
	//不知明原因無法成功,待解決.
	//if (CreateProcess_Test(L"HelloWorld.exe", SW_SHOWNORMAL))
	//	std::cout << "Create process successful." << std::endl;

	system("pause");
	return 0;
}

bool WinExec_Test(LPCSTR pszExePath, UINT uiCmdShow){
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

BOOL CreateProcess_Test(LPWSTR pszExePath, UINT uiCmdShow){
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	BOOL bRet = FALSE;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW; //指定 wShowWindow 成員有效
	si.wShowWindow = uiCmdShow;

	bRet = CreateProcess(NULL,   // No module name (use command line)
		pszExePath,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi);           // Pointer to PROCESS_INFORMATION structure
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (bRet)
	{
		::CloseHandle(pi.hThread);
		::CloseHandle(pi.hProcess);
		return TRUE;
	}
	

	return FALSE;
}