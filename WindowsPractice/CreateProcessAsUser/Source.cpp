#include <Windows.h>
#include <UserEnv.h>
#include <WtsApi32.h>

#pragma comment(lib, "UserEnv.lib")
#pragma comment(lib, "WtsApi32.lib")
#define EXECUTE_FILE "C:\\Users\\lungyu\\Desktop\\HelloWorld.exe"

void __stdcall ServiceMain(DWORD argc, char *argv);
void __stdcall ServiceCtrlHandle(DWORD operateCode);
void DoTask();

void ShowMessage(LPSTR title, LPSTR message);
BOOL CreateUserProcess(char *filename);

char g_szServiceName[MAX_PATH] = "CreateProcessAsUser.exe";
SERVICE_STATUS g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_ServiceStatusHanddle = { 0 };


int main(){

	SERVICE_TABLE_ENTRY stDispatchTable[] = { 
		{ g_szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
		{ NULL, NULL } };

	StartServiceCtrlDispatcher(stDispatchTable);
	return 0;
}

void __stdcall ServiceMain(DWORD argc, char *argv){
	g_ServiceStatus.dwServiceType = SERVICE_WIN32;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;

	g_ServiceStatusHanddle = RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandle);

	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;
	
	SetServiceStatus(g_ServiceStatusHanddle, &g_ServiceStatus);

	DoTask();
}

void __stdcall ServiceCtrlHandle(DWORD operateCode){
	switch (operateCode)
	{
	case SERVICE_CONTROL_PAUSE:
		g_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;

	case SERVICE_CONTROL_CONTINUE:
		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
		g_ServiceStatus.dwWin32ExitCode = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwCheckPoint = 0;
		g_ServiceStatus.dwWaitHint = 0;
		
		SetServiceStatus(g_ServiceStatusHanddle, &g_ServiceStatus);
		break;
	case SERVICE_CONTROL_INTERROGATE:
		//¸ß°Ý
	default:
		break;
	}
}

void DoTask(){
	ShowMessage("Hello", "Hi Lung yu\n This Is From Session 0 Service !\n");

	CreateUserProcess(EXECUTE_FILE);
}

void ShowMessage(LPSTR title, LPSTR message){
	DWORD dwSessionId = WTSGetActiveConsoleSessionId();

	DWORD dwResponse = 0;
	WTSSendMessage(WTS_CURRENT_SERVER_HANDLE, dwSessionId,
		title, (1 + ::lstrlen(title)),
		message, (1 + ::lstrlen(message)),
		0, 0, &dwResponse, FALSE);
}

BOOL CreateUserProcess(char *filename){
	BOOL bRet = TRUE;
	DWORD dwSessionID = 0;
	HANDLE hToken = NULL;
	HANDLE hDuplicatedToken = NULL;
	LPVOID lpEnvironment = NULL;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	si.cb = sizeof(si);

	dwSessionID = WTSGetActiveConsoleSessionId();

	if (FALSE == WTSQueryUserToken(dwSessionID, &hToken)){
		ShowMessage("Error", "WTSQueryUserToken");
		bRet = FALSE;
	}

	if (FALSE == DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL,
		SecurityIdentification, TokenPrimary, &hDuplicatedToken)){
		ShowMessage("Error", "DuplicateTokenEx");
		bRet = FALSE;
	}

	if (FALSE == CreateEnvironmentBlock(&lpEnvironment,
		hDuplicatedToken, FALSE)){
		ShowMessage("Error", "CreateEnvironmentBlock");
		bRet = FALSE;
	}

	if (FALSE == CreateProcessAsUser(hDuplicatedToken,
		filename, NULL, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		lpEnvironment, NULL, &si, &pi)){
		ShowMessage("Error", "CreateEnvironmentBlock");
		bRet = FALSE;
	}


	//release resource
	if (lpEnvironment)
		DestroyEnvironmentBlock(lpEnvironment);
	if (hDuplicatedToken)
		CloseHandle(hDuplicatedToken);
	if (hToken)
		CloseHandle(hToken);
	return bRet;
}