#pragma once
#include <string>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "common.h"

struct Vec3
{
    float x, y, z;
};

struct cBuffer
{
    DirectX::XMMATRIX wvp;
    float x, y, z, w;
    float rx, ry, rz, rw;
};

class Mesh
{
private:
    Shader shader;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    ConstantBuffer constantBuffer;

    cBuffer cb;

    bool loaded = false;

public:
    void init(std::string file);
    void draw();
    void release();
    bool isLoaded();
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};