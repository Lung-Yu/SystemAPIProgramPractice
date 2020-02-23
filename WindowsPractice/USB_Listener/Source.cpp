#include <Windows.h>

int mCreateWindow(HINSTANCE hInst);
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

	mCreateWindow(hInst);

	return 0;
}

int mCreateWindow(HINSTANCE hInst){
	WNDCLASSW wc = { 0 };

	LPCWSTR classNameStr = L"tygr_windowsClass";

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = classNameStr;
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(classNameStr, L"tygr Window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 600, 400,	//show up position x and y, window width and height
		NULL, NULL, NULL, NULL);

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}
