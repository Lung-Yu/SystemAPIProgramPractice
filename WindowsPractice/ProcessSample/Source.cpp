#include <windows.h>
#include <stdio.h>

void killPorcess(DWORD ProcessID);

int main(int argc, char const *argv[])
{
	DWORD ProcessID = 11880;	//notepade.exe process id on my computer
	
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