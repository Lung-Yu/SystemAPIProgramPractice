#include "HelloDLL.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{

	HelloDLL helloDLL;
	helloDLL.hello();
	HelloDLL::helloStatic();

	normalFunc();

	getchar();

	return 0;
}