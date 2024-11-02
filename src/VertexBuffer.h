#pragma once
#include <d3d11.h>
#include "Shader.h"

class VertexBuffer
{
private:
	ID3D11Buffer *vertexBuffer = nullptr;
	ID3D11InputLayout *inputLayout = nullptr;

	UINT stride = 0;
	UINT offset = 0;

	int count;

public:
	void use();
	void createLayout(Shader &shader, UINT stride);
	void createBuffer(const void *data, size_t size);

	void release();
};
