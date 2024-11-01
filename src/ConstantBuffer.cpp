#include "ConstantBuffer.h"
#include "common.h"

void ConstantBuffer::createBuffer(size_t size)
{
    D3D11_BUFFER_DESC constantBufferDesc = {};
    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.ByteWidth = size;
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = DXShit::device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);

    hr = 0;
}

void ConstantBuffer::release()
{
    constantBuffer->Release();
}

void ConstantBuffer::use()
{
    DXShit::context->VSSetConstantBuffers(0, 1, &constantBuffer);
    DXShit::context->PSSetConstantBuffers(0, 1, &constantBuffer);
}

void ConstantBuffer::update(const void *data, size_t size)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT result = DXShit::context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, data, size);
    DXShit::context->Unmap(constantBuffer, 0);
}
