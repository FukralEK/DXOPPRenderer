#include "IndexBuffer.h"
#include "common.h"

void IndexBuffer::createBuffer(DWORD *indices, size_t size)
{
    D3D11_BUFFER_DESC indexBufferDesc;

    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = size;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices;

    HRESULT hr = DXShit::device->CreateBuffer(&indexBufferDesc, &iinitData, &indexBuffer);
    count = size / sizeof(DWORD);

    hr = 0;
}

void IndexBuffer::release()
{
    indexBuffer->Release();
}

void IndexBuffer::use()
{
    DXShit::context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

size_t IndexBuffer::getCount()
{
    return count;
}
