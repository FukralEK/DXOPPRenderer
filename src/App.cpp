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

const int WIDTH = 1280, HEIGHT = 720;

struct cBuffer
{
	DirectX::XMMATRIX wvp;
	float x, y, z, w;
	float rx, ry, rz, rw;
};

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

	shader.LoadFromFile("C:\\Users\\Fabian\\Documents\\DXOPPRenderer\\src\\VertexShader.hlsl", "C:\\Users\\Fabian\\Documents\\DXOPPRenderer\\src\\PixelShader.hlsl");

	vertexBuffer.createLayout(shader);

	objl::Loader loader;
	loader.LoadFile("C:\\Users\\Fabian\\Documents\\monkey.obj");

	auto verticiesObj = loader.LoadedVertices;

	Vertex *verticies = new Vertex[verticiesObj.size()];

	float r = 1.0f;
	float g = 0.95f;
	float b = 0.75f;

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

	DirectX::XMMATRIX WVP;
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX camView;
	DirectX::XMMATRIX camProjection;

	DirectX::XMVECTOR camPosition;
	DirectX::XMVECTOR camTarget;
	DirectX::XMVECTOR camUp;

	camPosition = DirectX::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = DirectX::XMMatrixLookAtLH(camPosition, camTarget, camUp);

	camProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90.0f), (float)window.getRes()[0] / (float)window.getRes()[1], 0.01f, 1000.0f);

	World = DirectX::XMMatrixIdentity();

	WVP = World * camView * camProjection;

	cBuffer cb = {WVP, 0.0f, 0.0f, 0.0f, 0.0f};

	cb.wvp = DirectX::XMMatrixTranspose(WVP);
	while (running)
	{
		ImGuiIO &io = ImGui::GetIO();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("DX Playground");
		ImGui::InputFloat3("Mesh Position", &cb.x);
		ImGui::InputFloat3("Mesh Rotation", &cb.rx);
		ImGui::End();

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
