#include "ServiceOperate.h"

void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error!\nError Code Is:%d\n", lpszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}

BOOL SystemServiceOperate(char *lpszExePath, OperateType iOperateType)
{
	BOOL bRet = TRUE;
	char szName[MAX_PATH] = { 0 };

	lstrcpy(szName, lpszExePath);
	PathStripPath(szName);

	SC_HANDLE shOSCM = NULL, shCS = NULL;
	SERVICE_STATUS ss;
	DWORD dwErrorCode = 0;
	BOOL bSuccess = FALSE;
	
	shOSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!shOSCM)
	{
		ShowError("OpenSCManager");
		return FALSE;
	}

	if (CREATE_SERVICE != iOperateType)
	{
		shCS = OpenService(shOSCM, szName, SERVICE_ALL_ACCESS);
		if (!shCS)
		{
			ShowError("OpenService");
			CloseServiceHandle(shOSCM);
			shOSCM = NULL;
			return FALSE;
		}
	}

	switch (iOperateType)
	{
	case CREATE_SERVICE:
			  shCS = CreateService(shOSCM, szName, szName,
				  SERVICE_ALL_ACCESS,
				  SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
				  SERVICE_AUTO_START,
				  SERVICE_ERROR_NORMAL,
				  lpszExePath, NULL, NULL, NULL, NULL, NULL);
			  if (!shCS)
			  {
				  ShowError("CreateService");
				  bRet = FALSE;
			  }
			  break;
	case START_SERVICE:
			  if (!StartService(shCS, 0, NULL))
			  {
				  ShowError("StartService");
				  bRet = FALSE;
			  }
			  break;
	case STOP_SERVICE:
			  if (!ControlService(shCS, SERVICE_CONTROL_STOP, &ss))
			  {
				  ShowError("ControlService");
				  bRet = FALSE;
			  }
			  break;
	case DELETE_SERVICE:
			  if (!DeleteService(shCS))
			  {
				  ShowError("DeleteService");
				  bRet = FALSE;
			  }
			  break;
	default:
		break;
	}

	if (shCS)
	{
		CloseServiceHandle(shCS);
		shCS = NULL;
	}
	if (shOSCM)
	{
		CloseServiceHandle(shOSCM);
		shOSCM = NULL;
	}

	return bRet;
}