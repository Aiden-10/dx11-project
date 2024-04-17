#pragma once
#include <Windows.h>

class Window
{
public:
	POINT winSize;

	Window(const char name[], int width, int height);
	~Window();
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND getHandle();
private:
	HINSTANCE hInst;
	WNDCLASSEX wc;
	HWND hWnd;
};
