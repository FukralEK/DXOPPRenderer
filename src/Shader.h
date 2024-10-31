#pragma once
#include <d3d11.h>
#include <string>

class Shader
{
private:
	ID3D11VertexShader *vs = nullptr;
	ID3D11PixelShader *ps = nullptr;
	ID3DBlob* vsBlob = nullptr;
public:
	void LoadFromFile(std::string vertexShaderPath, std::string pixelShaderPath);
	void use();
	void release();

	ID3DBlob* getVsBlob();
};

