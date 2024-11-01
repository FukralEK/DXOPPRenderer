#include "App.h"
#include "Renderer.h"
#include "Window.h"
#include "Triangle.h"
#include "IndexBuffer.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"

const int WIDTH = 1280, HEIGHT = 720;

void App::run()
{
	Window window(WIDTH, HEIGHT, "Hello, Triangle");
	Renderer renderer(window);

	window.init();
	renderer.init();

	Shader shader;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;

	shader.LoadFromFile("C:\\Users\\Fabian\\Documents\\DXOPPRenderer\\src\\VertexShader.hlsl", "C:\\Users\\Fabian\\Documents\\DXOPPRenderer\\src\\PixelShader.hlsl");

	vertexBuffer.createLayout(shader);

	Vertex vertices[] =
		{
			Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
			Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
			Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
		};

	vertexBuffer.createBuffer(vertices, sizeof(vertices));

	DWORD indices[] = {
		0, 1, 2, //
		0, 2, 3, //
	};

	indexBuffer.createBuffer(indices, sizeof(indices));

	while (running)
	{
		shader.use();
		vertexBuffer.use();
		indexBuffer.use();

		DXShit::context->DrawIndexed(indexBuffer.getCount(), 0, 0);

		window.update(running);
		renderer.update();
	}

	indexBuffer.release();
	shader.release();
	vertexBuffer.release();

	renderer.release();
	window.release();
}
