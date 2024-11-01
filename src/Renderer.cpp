#include "Renderer.h"
#include "common.h"
namespace DXShit
{
	IDXGISwapChain *swapChain;
	ID3D11Device *device;
	ID3D11DeviceContext *context;
	ID3D11RenderTargetView *renderTargetView;
}
Renderer::Renderer(Window &window) : window(window)
{
}

void Renderer::init()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = window.getHwnd();
	scd.SampleDesc.Count = 1;
	scd.Windowed = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &swapChain, &device, NULL, &context);

	ID3D11Texture2D *backBuffer = nullptr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBuffer);
	hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = window.getRes()[0];
	depthStencilDesc.Height = window.getRes()[1];
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = window.getRes()[0];
	viewport.Height = window.getRes()[1];
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	DXShit::swapChain = swapChain;
	DXShit::device = device;
	DXShit::context = context;
	DXShit::renderTargetView = renderTargetView;
}

void Renderer::release()
{
	depthStencilBuffer->Release();
	depthStencilView->Release();
	swapChain->Release();
	device->Release();
	context->Release();
	renderTargetView->Release();
}

void Renderer::update()
{

	swapChain->Present(1, 0);

	float bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
	context->ClearRenderTargetView(renderTargetView, bgColor);
	DXShit::context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

IDXGISwapChain *Renderer::getSwapChain()
{
	return swapChain;
}

ID3D11Device *Renderer::getDevice()
{
	return device;
}

ID3D11DeviceContext *Renderer::getContext()
{
	return context;
}

ID3D11RenderTargetView *Renderer::getRenderTargetView()
{
	return renderTargetView;
}
