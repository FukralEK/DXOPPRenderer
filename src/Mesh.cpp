#include "Mesh.h"
#include "OBJ_Loader.h"
#include <stdexcept>

struct Vertex
{
    float x, y, z;
    float r, g, b, a;
};

void Mesh::init(std::string file)
{
    Camera &camera = Camera::getInstance();

    shader.LoadFromFile("src/VertexShader.hlsl", "src/PixelShader.hlsl");

    vertexBuffer.createLayout(shader, sizeof(float) * 7);

    objl::Loader loader;
    if (!loader.LoadFile(file.c_str()))
    {
        throw std::runtime_error("Model has not been found");
    }

    auto verticiesObj = loader.LoadedVertices;

    Vertex *verticies = new Vertex[verticiesObj.size()];

    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;

    for (int i = 0; i < verticiesObj.size(); i++)
    {
        r = g;
        g = b;
        b = r;
        verticies[i] = {verticiesObj[i].Position.X, verticiesObj[i].Position.Y, verticiesObj[i].Position.Z, r, g, b, 1.0f};
    }

    auto indicesObj = loader.LoadedIndices;

    DWORD *indices = new DWORD[indicesObj.size()];

    for (int i = 0; i < indicesObj.size(); i++)
    {
        indices[i] = (DWORD)indicesObj[i];
    }

    vertexBuffer.createBuffer(verticies, sizeof(Vertex) * verticiesObj.size());

    indexBuffer.createBuffer(indices, sizeof(DWORD) * indicesObj.size());

    constantBuffer.createBuffer(sizeof(cBuffer));

    cb = {camera.getWVP(), 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    loaded = true;

    delete indices;
    delete verticies;
}

void Mesh::draw()
{
    if (!loaded)
    {
        return;
    }
    Camera &camera = Camera::getInstance();
    shader.use();
    vertexBuffer.use();
    indexBuffer.use();

    constantBuffer.use();

    cb.wvp = camera.getWVP();

    cb.x = position.x;
    cb.y = position.y;
    cb.z = position.z;

    cb.rx = rotation.x;
    cb.ry = rotation.y;
    cb.rz = rotation.z;

    constantBuffer.update(&cb, sizeof(cb));

    DXShit::context->DrawIndexed(indexBuffer.getCount(), 0, 0);
}

void Mesh::release()
{
    constantBuffer.release();

    indexBuffer.release();
    shader.release();
    vertexBuffer.release();

    loaded = false;
}

bool Mesh::isLoaded()
{
    return loaded;
}
