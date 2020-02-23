#include <Windows.h>
#include <Dbt.h>

int mCreateWindow(HINSTANCE hInst);
void mProcessMessage();
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT OnDeviceStatusChange(WPARAM wParam, LPARAM lParam);



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
		//MessageBox(NULL,"Message", "USB Device status change.", MB_OK);
		OnDeviceStatusChange(wp,lp);
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

LRESULT OnDeviceStatusChange(WPARAM wParam, LPARAM lParam){
	switch (wParam)
	{
	case DBT_DEVICEARRIVAL:
	{
							  PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
							  if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
							  {
								  // 根據 dbcv_unitmask 計算出設備的代號
								  PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
								  DWORD dwDriverMask = lpdbv->dbcv_unitmask;
								  DWORD dwTemp = 1;
								  char szDriver[4] = "A:\\";
								  for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
								  {
									  if (0 < (dwTemp & dwDriverMask))
									  {
										  MessageBox(NULL, szDriver, "USB Device has been attach.", MB_OK);
									  }
									  // 左移 1 位，接著判斷下一個 Disk 符號
									  dwTemp = (dwTemp << 1);
								  }
							  }
							  break;
	}
	case DBT_DEVICEREMOVECOMPLETE:
	{
									 PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
									 if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
									 {
										 PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
										 DWORD dwDriverMask = lpdbv->dbcv_unitmask;
										 DWORD dwTemp = 1;
										 char szDriver[4] = "A:\\";
										 for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
										 {
											 if (0 < (dwTemp & dwDriverMask))
											 {
												 MessageBox(NULL, szDriver, "USB Device has been remove.", MB_OK);
											 }
											 dwTemp = (dwTemp << 1);
										 }
									 }
									 break;
	}
	}

	return TRUE;
}