#include "Window.h"

Window::Window(const char name[], int width, int height)
	: winSize({ width, height })
{
	// Define window style
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (RegisterClassEx(&wc) == 0) { MessageBoxA(NULL, "RegisterClassEx() Failed!", "ERROR!", MB_ICONEXCLAMATION | MB_OK); }

	RECT wr;
	wr.left = 50;
	wr.top = 50;
	wr.right = wr.left + winSize.x;
	wr.bottom = wr.top + winSize.y;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindowEx(
		0,
		"MyWindowClass",
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		NULL,
		NULL,
		hInst,
		NULL
	);

	if (hWnd == NULL) { MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK); }
	else { ShowWindow(hWnd, SW_SHOWDEFAULT); }
}

Window::~Window()
{
	DestroyWindow(hWnd);
	UnregisterClass("MyWindow", hInst);
}

HWND Window::getHandle()
{
	return hWnd;
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}