#include <Windows.h>
#include <stdio.h>

BOOL EnbalePrivileges(HANDLE hProcess, char*pszPrivilegesName);
VOID ShowError(LPCSTR);
int main(){
	if (FALSE == EnbalePrivileges(GetCurrentProcess(), SE_DEBUG_NAME))	printf_s("Enable Privileges Error!\n");
	else printf_s("Enable Privileges OK!\n");
	
	DWORD dwSize = 0, dwResult = 0;
	if (!GetTokenInformation(GetCurrentProcess(), TokenGroups, NULL, dwSize, &dwSize))
	{
		dwResult = GetLastError();
		if (dwResult != ERROR_INSUFFICIENT_BUFFER) {
			printf("GetTokenInformation Error %u\n", dwResult);
		}
	}


	system("pause");
	return 0;
}
VOID ShowError(LPCSTR msg){
	MessageBox(NULL, msg, "ERROR", MB_OK);
}
BOOL EnbalePrivileges(HANDLE hProcess, char*pszPrivilegesName){
	HANDLE hToken = NULL;
	LUID luidValue = { 0 };
	TOKEN_PRIVILEGES tokenPrivileges = { 0 };

	BOOL bRet = FALSE;
	DWORD dwRet = 0;

	bRet = OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken);
	if (FALSE == bRet){
		ShowError("Open Process Token.");
		goto TAG_EXIT;
	}

	bRet = LookupPrivilegeValue(NULL, pszPrivilegesName, &luidValue);
	if (FALSE == bRet){
		ShowError("Lookup Privilege Value.");
		goto TAG_EXIT;
	}

	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Luid = luidValue; 
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	bRet = AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, 0, NULL, NULL);
	if (FALSE == bRet){
		ShowError("Adjust Token Privileges.");
		goto TAG_EXIT;
	}
	dwRet = GetLastError();

	if (ERROR_SUCCESS == dwRet)
		bRet = TRUE;
	else if (ERROR_NOT_ALL_ASSIGNED == dwRet){
		ShowError("ERROR_NOT_ALL_ASSIGNED");
		bRet = FALSE;
	}
	
TAG_EXIT:
	return bRet;
}
