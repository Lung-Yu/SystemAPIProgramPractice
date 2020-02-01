#include <Windows.h>

VOID WorkerRoutine(){
	MessageBoxA(NULL, "LOL dll Injection Successful.", "DLL TUTORIAL", MB_OK);
}

BOOLEAN __stdcall DllMain(HINSTANCE Dll, DWORD Reason, PVOID Reserved){

	if (Reason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(Dll);

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkerRoutine, NULL, 0, NULL);

	}

	return TRUE;
}