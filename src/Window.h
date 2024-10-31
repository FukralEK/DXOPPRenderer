#pragma once
#include <string>
#include <array>
#include <Windows.h>

class Window
{
private:
	int w, h;
	std::string title;
	HWND hwnd;
public:
	Window(int w, int h, std::string title);
	void init();
	void release();
	void update(bool &running);
	std::array<int, 2> getRes();
	HWND getHwnd();
};

