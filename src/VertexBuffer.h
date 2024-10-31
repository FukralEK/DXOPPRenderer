#pragma once
#include <d3d11.h>
#include "Shader.h"

struct Vertex
{
	float x, y, z;
	float r, g, b, a;
};

class VertexBuffer
{
private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

public:
	void use();
	void createLayout(Shader& shader);
	void createBuffer(Vertex* vertices, size_t size);

	void release();
};

