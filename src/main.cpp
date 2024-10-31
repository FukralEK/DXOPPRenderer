#include <Windows.h>
#include <stdexcept>
#include "App.h"
#include "common.h"

App app;

namespace WinMainShit
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPSTR lpCmdLine;
	int nCmdShow;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WinMainShit::hInstance = hInstance;
	WinMainShit::hPrevInstance = hPrevInstance;
	WinMainShit::lpCmdLine = lpCmdLine;
	WinMainShit::nCmdShow = nCmdShow;

	try
	{
		app.run();
	}
	catch (std::runtime_error e)
	{
		MessageBoxA(NULL, e.what(), "Error", MB_ICONERROR);
	}
	return 0;
}