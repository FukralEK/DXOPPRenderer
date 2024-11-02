#include "VertexBuffer.h"
#include "common.h"
#include "Shader.h"

void VertexBuffer::use()
{

    DXShit::context->IASetInputLayout(inputLayout);
    DXShit::context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DXShit::context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

void VertexBuffer::createLayout(Shader &shader, UINT stride)
{
    HRESULT hr;
    D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
    ID3DBlob *vsBlob = shader.getVsBlob();

    this->stride = stride;

    hr = DXShit::device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);

    hr = 0;
}

void VertexBuffer::createBuffer(const void *data, size_t size)
{
    HRESULT hr;
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = size;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    hr = DXShit::device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}

void VertexBuffer::release()
{
    inputLayout->Release();
    vertexBuffer->Release();
}
