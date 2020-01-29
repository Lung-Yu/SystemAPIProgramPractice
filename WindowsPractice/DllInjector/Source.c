#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
void inject_dll(DWORD pid, PCHAR DllName);

int main(int argc, char argv[]){

	DWORD pid = 7540;
	printf("pid:%d\n", pid);

	if (pid){
		inject_dll(pid, "C:\\Users\\lungyu\\Desktop\\DllTest");
	}
	system("pause");
	return 0;
}

void inject_dll(DWORD pid, PCHAR DllName){
	HANDLE processHandle;
	PVOID Alloc;
	SIZE_T DllLen;
	HINSTANCE Kernal32Base;
	PVOID LoadLibAddress;

	if (pid != 0 && DllName != NULL){

		DllLen = strlen(DllName);

		Kernal32Base = GetModuleHandleA("kernel32.dll");
		if (Kernal32Base == NULL)
			goto ExitPoint;

		LoadLibAddress = GetProcAddress(Kernal32Base, "LoadLibraryA");
		if (LoadLibAddress == NULL)
			goto ExitPoint;

		processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (processHandle == NULL)
			goto ExitPoint;

		Alloc = VirtualAllocEx(processHandle, NULL, DllLen + 1, MEM_COMMIT, PAGE_READWRITE);
		if (Alloc == NULL)
			goto ExitPoint;


		if (!WriteProcessMemory(processHandle, Alloc, DllName, DllLen + 1, NULL))
			goto ExitPoint;

		printf("CreateRemoteThread\n");
		CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibAddress, Alloc, 0, NULL);
	}

ExitPoint:
	printf("ExitPoint\n");
	return;
}