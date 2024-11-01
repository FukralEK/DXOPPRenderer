#include <Windows.h>
#include <stdexcept>
#include "App.h"
#include "common.h"
#include <stdio.h>

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

	char executablePath[MAX_PATH];
	char directoryPath[MAX_PATH];

	// Get the full path of the executable
	GetModuleFileNameA(NULL, executablePath, MAX_PATH);

	// Extract the directory from the executable path
	// This will look for the last backslash and null-terminate the string there
	for (int i = strlen(executablePath) - 1; i >= 0; i--)
	{
		if (executablePath[i] == '\\')
		{
			executablePath[i] = '\0'; // Replace the backslash with a null terminator
			break;
		}
	}

	SetCurrentDirectoryA(executablePath);

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