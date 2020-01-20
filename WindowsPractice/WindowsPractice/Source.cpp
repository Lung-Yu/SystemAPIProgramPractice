#include <Windows.h>

void mMessageBoxSample();

int main(){

	mMessageBoxSample();
	return 0;
}

void mMessageBoxSample(){
#ifdef _WIN64
	MessageBox(NULL, "Hello x64", "My first GUI", MB_OK);
#elif _WIN32
	MessageBox(NULL, "Hello x86", "My first GUI", MB_OK);
#endif
}