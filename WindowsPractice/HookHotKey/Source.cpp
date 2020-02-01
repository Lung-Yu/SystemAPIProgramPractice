#include <stdio.h>
#include <Windows.h>

#define HOT_KEY_SYMBOLE 245	// HOT KEY 符號 避免衝突

int main()
{
	HWND act = GetActiveWindow();

	if (RegisterHotKey(
		act,	// 註冊快捷鍵的視窗，註冊快捷鍵的HWND
		HOT_KEY_SYMBOLE,
		MOD_CONTROL | MOD_NOREPEAT, // Ctrl 鍵  No Repeat 不重複發送
		// MOD_CONTROL,
		'A'		// A
		))
	{
		printf("快捷鍵Ctrl + A 註冊成功!! \n\n");
	}

	MSG msg = { 0 };
	// 循環取得系統發送的Message
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// 當收到快捷鍵訊息時
		if (msg.message == WM_HOTKEY)
		{
			printf("收到 WN_HOTKEY 快捷鍵消息\t");
			printf("wParam : 0x%x  lParam : 0x%x \n", msg.wParam, msg.lParam);
		}
	}


}