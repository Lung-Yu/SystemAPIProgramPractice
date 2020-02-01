#pragma once

//more about this in reference 1
#ifdef DLLDIR_EX
#define DLLDIR  __declspec(dllexport)   // export DLL information

#else
#define DLLDIR  __declspec(dllimport)   // import DLL information

#endif 

void DLLDIR normalFunc();

class DLLDIR HelloDLL
{
public:
	HelloDLL(void);
	~HelloDLL(void);

	void hello();
	static void helloStatic();

};