#include "HelloDLL.h"
#include <iostream>

using namespace std;


void normalFunc(){
	cout << "normal hello" << endl;
}

HelloDLL::HelloDLL(void)
{
}

HelloDLL::~HelloDLL(void)
{
}

void HelloDLL::hello()
{
	cout << "Hello World of DLL" << endl;
}

void HelloDLL::helloStatic()
{
	cout << "Hello World of DLL static" << endl;
}
 