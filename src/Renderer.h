#pragma once
#include "Window.h"
#include <d3d11.h>

class Renderer
{
private:
	Window &window;

private:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;


public:
	Renderer(Window &window);
	void init();
	void release();
	void update();

	IDXGISwapChain* getSwapChain();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getContext();
	ID3D11RenderTargetView* getRenderTargetView();
};

