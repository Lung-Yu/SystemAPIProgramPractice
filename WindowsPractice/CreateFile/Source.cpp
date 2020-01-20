#include <windows.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	CreateFile(
		(LPCWSTR)L"test.txt",   // 檔案名
		GENERIC_WRITE,          // 寫入權限
		0,                      // 阻止其他Process 訪問
		NULL,                   // Sub process 不能繼承 Handler
		CREATE_NEW,             // 不存在時建立檔案
		FILE_ATTRIBUTE_NORMAL,  // 普通文件
		NULL);                  // 不適用模板文件

	system("pause");
	return 0;
}