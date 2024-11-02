#include "App.h"
#include "Renderer.h"
#include "Window.h"
#include "Triangle.h"
#include "IndexBuffer.h"
#include <DirectXMath.h>
#include "ConstantBuffer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "OBJ_Loader.h"
#include "Camera.h"

const int WIDTH = 1280, HEIGHT = 720;

struct Vertex
{
	float x, y, z;
	float r, g, b, a;
};

struct cBuffer
{
	DirectX::XMMATRIX wvp;
	float x, y, z, w;
	float rx, ry, rz, rw;
};

bool spinning = true;

void App::run()
{
	Window window(WIDTH, HEIGHT, "Hello, Triangle");
	Renderer renderer(window);

	window.init();
	renderer.init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	ImGui_ImplWin32_Init(window.getHwnd());
	ImGui_ImplDX11_Init(DXShit::device, DXShit::context);

	Shader shader;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;

	shader.LoadFromFile("src/VertexShader.hlsl", "src/PixelShader.hlsl");

	vertexBuffer.createLayout(shader, sizeof(float) * 7);

	objl::Loader loader;
	loader.LoadFile("monkey.obj");

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

	ConstantBuffer constantBuffer;

	constantBuffer.createBuffer(sizeof(cBuffer));

	bool invert = false;

	Camera &camera = camera.getInstance();

	float fov = 120.0f;

	camera.setCamera(DirectX::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f), DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	camera.setProjection(fov, (float)window.getRes()[0] / (float)window.getRes()[1], 0.01f, 1000.0f);

	cBuffer cb = {camera.getWVP(), 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	std::string fileName;
	fileName.resize(255);

	while (running)
	{
		ImGuiIO &io = ImGui::GetIO();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("DX Playground");
		ImGui::SliderFloat("FOV", &fov, 10.0f, 180.0f);
		ImGui::InputFloat3("Mesh Position", &cb.x);
		ImGui::InputFloat3("Mesh Rotation", &cb.rx);
		ImGui::Checkbox("Spinning", &spinning);
		ImGui::InputText("Model File", &fileName[0], fileName.size());

		if (ImGui::Button("Load Model"))
		{
			fileName = "";
			fileName.resize(255);
		}
		ImGui::End();

		camera.setProjection(fov, (float)window.getRes()[0] / (float)window.getRes()[1], 0.01f, 1000.0f);

		cb.wvp = camera.getWVP();

		if (spinning)
		{
			cb.ry += 0.05;
		}

		ImGui::Render();

		shader.use();
		vertexBuffer.use();
		indexBuffer.use();

		constantBuffer.use();

		constantBuffer.update(&cb, sizeof(cb));
		DXShit::context->DrawIndexed(indexBuffer.getCount(), 0, 0);

		window.update(running);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		renderer.update();
	}

	delete indices;
	delete verticies;

	constantBuffer.release();

	indexBuffer.release();
	shader.release();
	vertexBuffer.release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	renderer.release();
	window.release();
}
