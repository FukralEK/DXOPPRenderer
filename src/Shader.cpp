#include "Shader.h"
#include "common.h"
#include <d3d11.h>
#include <d3dcompiler.h>


void Shader::LoadFromFile(std::string vertexShaderPath, std::string pixelShaderPath)
{
	HRESULT hr;
	ID3DBlob *psBlob;

	std::wstring wVertexShaderPath(vertexShaderPath.begin(), vertexShaderPath.end());
	std::wstring wPixelShaderPath(pixelShaderPath.begin(), pixelShaderPath.end());

	hr = D3DCompileFromFile(wVertexShaderPath.c_str(), NULL, NULL, "main", "vs_5_0", NULL, NULL, &vsBlob, NULL);
	hr = D3DCompileFromFile(wPixelShaderPath.c_str(), NULL, NULL, "main", "ps_5_0", NULL, NULL, &psBlob, NULL);

	hr = DXShit::device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vs);
	hr = DXShit::device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &ps);

	psBlob->Release();
}

void Shader::use()
{
	DXShit::context->VSSetShader(vs, NULL, NULL);
	DXShit::context->PSSetShader(ps, NULL, NULL);
}

void Shader::release()
{
	vs->Release();
	ps->Release();
	vsBlob->Release();
}

ID3DBlob* Shader::getVsBlob()
{
	return vsBlob;
}
