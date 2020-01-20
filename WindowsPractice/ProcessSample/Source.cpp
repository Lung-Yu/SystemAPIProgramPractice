#include <windows.h>
#include <stdio.h>

#include <TlHelp32.h>	//for processList

void killPorcess(DWORD ProcessID);
int processList();

int main(int argc, char const *argv[])
{
	DWORD ProcessID;	//notepade.exe process id on my computer
	
	ProcessID = processList();

	killPorcess(ProcessID);
	
	printf("Killed %d.\n", ProcessID);
	system("pause");
	return 0;
}

void killPorcess(DWORD ProcessID){
	// 取得Process Handler
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	// 中止目標Process
	TerminateProcess(hProcess, 0);
}

int processList(){
	HANDLE hSnapshot;
	HANDLE hProcess;
	int pid = 0;
	PROCESSENTRY32 pe32;


	// 取得Process 快照
	hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		0);	//獲取特定(Process Id)的快照, 當參數為0時代表取得系統當下全部的Process 快照
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of processes) 失败");
		return 0;
	}
	// 設定結構大小
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// 開始列舉 Process
	if (!Process32First(hSnapshot, &pe32))
	{
		printf("Process32First() 失敗");
		CloseHandle(hSnapshot);
		return 0;
	}

	printf("Process ID\tParent\tThread\tpriority\tProcessName");
	do {
		// 列印 Process 相關資訊
		printf("\n%u", pe32.th32ProcessID);   // Process id
		printf("\t%u", pe32.th32ParentProcessID); // Parent Process id
		printf("\t%d", pe32.cntThreads);      // Thread count      
		printf("\t%d", pe32.pcPriClassBase);  // priority
		printf("\t%s", pe32.szExeFile);       // ProcessName

	} while (Process32Next(hSnapshot, &pe32));

	printf("\n 請輸入要關閉之Process.\n");
	CloseHandle(hSnapshot);


	scanf_s("%d", &pid);

	return pid;
}