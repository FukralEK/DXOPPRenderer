#pragma once
#include <d3d11.h>
#include "Shader.h"

class ConstantBuffer
{
private:
    ID3D11Buffer *constantBuffer;

public:
    void createBuffer(size_t size);
    void release();
    void use();
    void update(const void *data, size_t size);
};