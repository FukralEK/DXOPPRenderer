#pragma once
#include "Shader.h"
#include "VertexBuffer.h"

class Triangle
{
private:
    Shader shader;
    VertexBuffer vertexBuffer;

public:
    void init();
    void draw();
    void release();
};