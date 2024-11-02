#include "Triangle.h"
#include "common.h"

void Triangle::init()
{
    /*
    shader.LoadFromFile("VertexShader.hlsl", "PixelShader.hlsl");

    vertexBuffer.createLayout(shader);


    Vertex vertices[] = {
        {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},   // Top (Red)
        {0.45f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}, // Right (Green)
        {-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f} // Left (Blue)
    };

    vertexBuffer.createBuffer(vertices, sizeof(vertices));
    */
}

void Triangle::draw()
{
    shader.use();
    vertexBuffer.use();
    DXShit::context->Draw(3, 0);
}

void Triangle::release()
{
    shader.release();
    vertexBuffer.release();
}
