#include <stdio.h>
#include <Windows.h>

#define HOT_KEY_SYMBOLE 245	// HOT KEY �Ÿ� �קK�Ĭ�

int main()
{
	HWND act = GetActiveWindow();

	if (RegisterHotKey(
		act,	// ���U�ֱ��䪺�����A���U�ֱ��䪺HWND
		HOT_KEY_SYMBOLE,
		MOD_CONTROL | MOD_NOREPEAT, // Ctrl ��  No Repeat �����Ƶo�e
		// MOD_CONTROL,
		'A'		// A
		))
	{
		printf("�ֱ���Ctrl + A ���U���\!! \n\n");
	}

	MSG msg = { 0 };
	// �`�����o�t�εo�e��Message
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// ����ֱ���T����
		if (msg.message == WM_HOTKEY)
		{
			printf("���� WN_HOTKEY �ֱ������\t");
			printf("wParam : 0x%x  lParam : 0x%x \n", msg.wParam, msg.lParam);
		}
	}


}