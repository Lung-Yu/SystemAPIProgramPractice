#include <Windows.h>

#define IDX_HOOK_MOUSE	0
#define IDX_HOOK_KEYBOARD	1
#define IDX_HOOK_GET_MESSAGE	2

#define HOOK_LISTEN_GLOBAL 0

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HookMouseProcedure(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HookKeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HookGetMessageProcedure(int nCode, WPARAM wParam, LPARAM lParam);

int mCreateWindow(HINSTANCE hInst);
void mProcessMessage();

HHOOK _hook[2];
HWND _hWnd;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	mCreateWindow(hInst);


	_hook[IDX_HOOK_MOUSE] = SetWindowsHookEx(
		WH_MOUSE_LL, HookMouseProcedure, hInst, HOOK_LISTEN_GLOBAL);
	if (!_hook[IDX_HOOK_MOUSE])MessageBox(NULL, "Hook mouse fails.", "Error", MB_OK);

	_hook[IDX_HOOK_KEYBOARD] = SetWindowsHookEx(
		WH_KEYBOARD_LL, HookKeyboardProcedure, hInst, HOOK_LISTEN_GLOBAL);
	if (!_hook[IDX_HOOK_KEYBOARD])	MessageBox(NULL, "Hook keyboard fails.", "Error", MB_OK);

	_hook[IDX_HOOK_GET_MESSAGE] = SetWindowsHookEx(
		WH_GETMESSAGE, HookGetMessageProcedure, hInst, HOOK_LISTEN_GLOBAL);
	if (!_hook[IDX_HOOK_GET_MESSAGE])	MessageBox(NULL, "Hook message fails.", "Error", MB_OK);

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
	_hWnd = hWnd;

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

LRESULT CALLBACK HookMouseProcedure(int nCode, WPARAM wParam, LPARAM lParam){
	LPMSLLHOOKSTRUCT p = (LPMSLLHOOKSTRUCT)lParam;
	POINT   pt = p->pt;
	DWORD   mouseData = p->mouseData;

	const char *info = NULL;
	HDC hdc = NULL;
	char text[100], pData[50], mData[50];

	if (nCode >= 0){
		switch (wParam)
		{
		case WM_MOUSEMOVE:info = "Mouse move.";
			break;
		case WM_LBUTTONDOWN:	info = "left button down.";
			break;
		case WM_LBUTTONUP:		info = "left button up.";
			break;
		case WM_LBUTTONDBLCLK:	info = "left button double click.";
			break;
		case WM_RBUTTONDOWN:	info = "right button down.";
			break;
		case WM_RBUTTONUP:		info = "right button up.";
			break;
		case WM_RBUTTONDBLCLK:	info = "right button double click.";
			break;
		case WM_MBUTTONDOWN:	info = "Wheel button down.";
			break;
		case WM_MBUTTONUP:		info = "Wheel button up.";
			break;
		case WM_MBUTTONDBLCLK:	info = "Wheel button double click.";
			break;
		case WM_MOUSEWHEEL:	info = "Wheel button roll.";
			break;
		default:
			info = "W.O.";
			break;
		}

		ZeroMemory(text, sizeof(text));
		wsprintf(text, "Mouse status¡G%10s,0x%x - X: [%04d], Y: [%04d] ,data = %16u", info, wParam, pt.x, pt.y, mouseData);
		hdc = GetDC(_hWnd);
		TextOut(hdc, 0, 10, text, strlen(text));

		ReleaseDC(_hWnd, hdc);
	}

	return CallNextHookEx(_hook[IDX_HOOK_MOUSE], nCode, wParam, lParam);
}

LRESULT CALLBACK HookKeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam){
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

	const char *info = NULL;
	HDC hdc = NULL;
	char text[100], pData[50], mData[50];

	if (nCode >= 0){
		switch (wParam)
		{
		case WM_KEYDOWN:info = "key down.";
			break;
		case WM_KEYUP:	info = "key up.";
			break;
		case WM_SYSKEYDOWN:		info = "system key down.";
			break;
		case WM_SYSKEYUP:	info = "system key up.";
			break;
		default:
			info = "W.O.";
			break;
		}

		ZeroMemory(text, sizeof(text));
		wsprintf(text, "Keyboard status¡G%10s,0x%x - key code: [%04d], scan code: [%04d]", info, wParam, p->vkCode, p->scanCode);
		hdc = GetDC(_hWnd);
		TextOut(hdc, 0, 40, text, strlen(text));

		ReleaseDC(_hWnd, hdc);
	}



	return CallNextHookEx(_hook[IDX_HOOK_KEYBOARD], nCode, wParam, lParam);
}

LRESULT CALLBACK HookGetMessageProcedure(int nCode, WPARAM wParam, LPARAM lParam){

	const char *info = NULL;

	HDC hdc = NULL;
	char text[100];

	switch (wParam)
	{
	case WM_NULL:info = "NULL.";
		break;
	case WM_CREATE:info = "Create.";
		break;
	case WM_DESTROY:info = "Destory.";
		break;
	case WM_MOVE:info = "Move.";
		break;
	case WM_SIZE:info = "Size.";
		break;
	case WM_ACTIVATE:info = "Activate.";
		break;
	case WM_SETFOCUS: info = "Set Focus.";
		break;
	case WM_KILLFOCUS: info = "Kill focus.";
		break;
	case WM_ENABLE: info = "Enable.";
		break;
	case WM_SETREDRAW:info = "Set red raw.";
		break;
	case WM_SETTEXT:info = "Set Text.";
		break;
	case WM_GETTEXT:info = "Get Text.";
		break;
	case WM_GETTEXTLENGTH:info = "Get Text Length.";
		break;
	case WM_PAINT: info = "Paint.";
		break;
	case WM_CLOSE: info = "close.";
		break;
	case WM_QUERYENDSESSION: info = "Query end session.";
		break;
	case WM_QUIT: info = "Quit.";
		break;
	case WM_QUERYOPEN: info = "Query open.";
		break;
	case WM_ERASEBKGND: info = "Erease bk GND.";
		break;
	case WM_SYSCOLORCHANGE: info = "Sys color Change.";
		break;
	case WM_ENDSESSION: info = "End Session.";
		break;
	case WM_SHOWWINDOW: info = "Show Window.";
		break;
		//case WM_CTLCOLOR:break;
	case WM_WININICHANGE: info = "Winini change.";
		break;
	case WM_DEVMODECHANGE: info = "Dev mode change.";
		break;
	case WM_ACTIVATEAPP: info = "Activate app.";
		break;
	case WM_FONTCHANGE: info = "Font change.";
		break;
	case WM_TIMECHANGE: info = "Time change.";
		break;
	case WM_CANCELMODE: info = "Cancel mode.";
		break;
	case WM_SETCURSOR: info = "Set cursor.";
		break;
	case WM_MOUSEACTIVATE: info = "Mouse activate.";
		break;
	case WM_CHILDACTIVATE:
		break;
	case WM_QUEUESYNC:
		break;
	case WM_GETMINMAXINFO:
		break;
	case WM_PAINTICON:
		break;
	case WM_ICONERASEBKGND:
		break;
	case WM_NEXTDLGCTL:
		break;
	case WM_SPOOLERSTATUS:
		break;
	case WM_DRAWITEM:
		break;
	case WM_MEASUREITEM:
		break;
	case WM_DELETEITEM:
		break;
	case WM_VKEYTOITEM:
		break;
	case WM_CHARTOITEM:
		break;
	case WM_SETFONT:
		break;
	case WM_GETFONT:
		break;
	case WM_SETHOTKEY:
		break;
	case WM_GETHOTKEY:
		break;
	case WM_QUERYDRAGICON:
		break;
	case WM_COMPAREITEM:
		break;
	case WM_GETOBJECT:
		break;
	case WM_COMPACTING:
		break;
	case WM_COMMNOTIFY:
		break;
	case WM_WINDOWPOSCHANGING:
		break;
	case WM_WINDOWPOSCHANGED:
		break;
	case WM_POWER:
		break;
		//case WM_COPYGLOBALDATA:break;
	case WM_COPYDATA:
		break;
	case WM_CANCELJOURNAL:
		break;
	case WM_NOTIFY:
		break;
	case WM_INPUTLANGCHANGEREQUEST:
		break;
	case WM_INPUTLANGCHANGE:
		break;
	case WM_TCARD:
		break;
	case WM_HELP:
		break;
	case WM_USERCHANGED:
		break;
	case WM_NOTIFYFORMAT:
		break;
	case WM_CONTEXTMENU:
		break;
	case WM_STYLECHANGING:
		break;
	case WM_STYLECHANGED:
		break;
	case WM_DISPLAYCHANGE:
		break;
	case WM_GETICON:
		break;
	case WM_SETICON:
		break;
	case WM_NCCREATE:
		break;
	case WM_NCDESTROY:
		break;
	case WM_NCCALCSIZE:
		break;
	case WM_NCHITTEST:
		break;
	case WM_NCPAINT:
		break;
	case WM_NCACTIVATE:
		break;
	case WM_GETDLGCODE:
		break;
	case WM_SYNCPAINT:
		break;
	case WM_NCMOUSEMOVE:
		break;
	case WM_NCLBUTTONDOWN:
		break;
	case WM_NCLBUTTONUP:
		break;
	case WM_NCLBUTTONDBLCLK:
		break;
	case WM_NCRBUTTONDOWN:
		break;
	case WM_NCRBUTTONUP:
		break;
	case WM_NCRBUTTONDBLCLK:
		break;
	case WM_NCMBUTTONDOWN:
		break;
	case WM_NCMBUTTONUP:
		break;
	case WM_NCMBUTTONDBLCLK:
		break;
	case WM_NCXBUTTONDOWN:
		break;
	case WM_NCXBUTTONUP:
		break;
	case WM_NCXBUTTONDBLCLK:
		break;
	case EM_GETSEL:
		break;
	case EM_SETSEL:
		break;
	case EM_GETRECT:
		break;
	case EM_SETRECT:
		break;
	case EM_SETRECTNP:
		break;
	case EM_SCROLL:
		break;
	case EM_LINESCROLL:
		break;
	case EM_SCROLLCARET:
		break;
	case EM_GETMODIFY:
		break;
	case EM_SETMODIFY:
		break;
	case EM_GETLINECOUNT:
		break;
	case EM_LINEINDEX:
		break;
	case EM_SETHANDLE:
		break;
	case EM_GETHANDLE:
		break;
	case EM_GETTHUMB:
		break;
	case EM_LINELENGTH:
		break;
	case EM_REPLACESEL:
		break;
		//case EM_SETFONT:break;
	case EM_GETLINE:
		break;
	case EM_LIMITTEXT:
		break;
		//case EM_SETLIMITTEXT:break;
	case EM_CANUNDO:
		break;
	case EM_UNDO:
		break;
	case EM_FMTLINES:
		break;
	case EM_LINEFROMCHAR:
		break;
		//case EM_SETWORDBREAK:break;
	case EM_SETTABSTOPS:
		break;
	case WM_MOUSEMOVE:info = "Mouse move.";
		break;
	case WM_LBUTTONDOWN:	info = "left button down.";
		break;
	case WM_LBUTTONUP:		info = "left button up.";
		break;
	case WM_LBUTTONDBLCLK:	info = "left button double click.";
		break;
	case WM_RBUTTONDOWN:	info = "right button down.";
		break;
	case WM_RBUTTONUP:		info = "right button up.";
		break;
	case WM_RBUTTONDBLCLK:	info = "right button double click.";
		break;
	case WM_MBUTTONDOWN:	info = "Wheel button down.";
		break;
	case WM_MBUTTONUP:		info = "Wheel button up.";
		break;
	case WM_MBUTTONDBLCLK:	info = "Wheel button double click.";
		break;
	case WM_MOUSEWHEEL:	info = "Wheel button roll.";
		break;
	default:	info = "W.O.";
		break;
	}


	ZeroMemory(text, sizeof(text));
	wsprintf(text, "Get Message status¡G%10s,", info);
	hdc = GetDC(_hWnd);
	TextOut(hdc, 0, 50, text, strlen(text));


	return CallNextHookEx(_hook[IDX_HOOK_GET_MESSAGE], nCode, wParam, lParam);
}