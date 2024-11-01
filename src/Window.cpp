#include "Window.h"
#include "common.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::Window(int w, int h, std::string title) : w(w), h(h), title(title)
{
}

void Window::init()
{
	WNDCLASSEX wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = WinMainShit::hInstance;
	wc.lpszClassName = L"TheWindowsWindow";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, L"TheWindowsWindow", L"DX11", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, NULL, NULL, WinMainShit::hInstance, NULL);
	ShowWindow(hwnd, WinMainShit::nCmdShow);
}

void Window::release()
{
}

void Window::update(bool &running)
{
	MSG msg = {};

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			running = false;
			return;
		}
	}

	running = true;
}

std::array<int, 2> Window::getRes()
{
	return {w, h};
}

HWND Window::getHwnd()
{
	return hwnd;
}
