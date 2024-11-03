#include "Texture.h"
#include "common.h"
#include "std_image.h"

void Texture::init(std::string file)
{
    D3D11_SAMPLER_DESC sampDesc;
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    DXShit::device->CreateSamplerState(&sampDesc, &samplerState);

    int width, height, channels;
    unsigned char *imageData = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = imageData;
    initData.SysMemPitch = width * 4;

    ID3D11Texture2D *textureTemp = nullptr;
    HRESULT hr = DXShit::device->CreateTexture2D(&textureDesc, &initData, &textureTemp);

    DXShit::device->CreateShaderResourceView(textureTemp, nullptr, &texture);

    textureTemp->Release();

    stbi_image_free(imageData);
}

void Texture::use()
{
    DXShit::context->PSSetShaderResources(0, 1, &texture);
    DXShit::context->PSSetSamplers(0, 1, &samplerState);
}

void Texture::release()
{
    texture->Release();
    samplerState->Release();
}
