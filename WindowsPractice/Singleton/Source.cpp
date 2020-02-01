#include <Windows.h>
#include <iostream>

bool IsAlreadyRun();

int main(int argc, char const *argv[])
{
	if (IsAlreadyRun())
		std::cout << "Already Run !" << std::endl;
	else
		std::cout << "Not Already Run !" << std::endl;

	while (true);

	return 0;
}

bool IsAlreadyRun(){
	HANDLE hMutex = NULL;

	hMutex = CreateMutex(NULL, FALSE, L"TEST");
	if (hMutex){
		if (ERROR_ALREADY_EXISTS == GetLastError())
			return TRUE;
	}
	return FALSE;
}