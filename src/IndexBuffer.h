#pragma once
#include <d3d11.h>

class IndexBuffer
{
private:
    size_t count;
    ID3D11Buffer *indexBuffer;

public:
    void createBuffer(DWORD *indices, size_t size);
    void release();
    void use();
    size_t getCount();
};