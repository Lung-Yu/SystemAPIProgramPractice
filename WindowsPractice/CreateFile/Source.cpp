#include <windows.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	CreateFile(
		(LPCWSTR)L"test.txt",   // �ɮצW
		GENERIC_WRITE,          // �g�J�v��
		0,                      // �����LProcess �X��
		NULL,                   // Sub process �����~�� Handler
		CREATE_NEW,             // ���s�b�ɫإ��ɮ�
		FILE_ATTRIBUTE_NORMAL,  // ���q���
		NULL);                  // ���A�μҪO���

	system("pause");
	return 0;
}