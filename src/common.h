#pragma once
#include <Windows.h>
#include <d3d11.h>

namespace WinMainShit
{
	extern HINSTANCE hInstance;
	extern HINSTANCE hPrevInstance;
	extern LPSTR lpCmdLine;
	extern int nCmdShow;
}

namespace DXShit
{
	extern IDXGISwapChain* swapChain;
	extern ID3D11Device* device;
	extern ID3D11DeviceContext* context;
	extern ID3D11RenderTargetView* renderTargetView;
}
