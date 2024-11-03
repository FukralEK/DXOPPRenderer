#pragma once
#include <string>
#include <d3d11.h>

class Texture
{
private:
    ID3D11ShaderResourceView *texture;
    ID3D11SamplerState *samplerState;

public:
    void init(std::string file);
    void use();
    void release();
};