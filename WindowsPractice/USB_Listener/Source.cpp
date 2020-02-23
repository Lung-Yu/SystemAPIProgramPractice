#include <Windows.h>
#include <Dbt.h>

int mCreateWindow(HINSTANCE hInst);
void mProcessMessage();
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

	mCreateWindow(hInst);

	mProcessMessage();
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

void mProcessMessage(){
	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}



LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_DEVICECHANGE:
		MessageBox(NULL,"Message", "USB Device status change.", MB_OK);
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}
