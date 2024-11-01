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

const int WIDTH = 1280, HEIGHT = 720;

struct cBuffer
{
	DirectX::XMMATRIX wvp;
	float x, y, z, w;
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

	Vertex vertices[] = {
		// Front face
		Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f), // 0
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),	// 1
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),	// 2
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),	// 3

		// Back face
		Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f), // 4
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f),	 // 5
		Vertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f),	 // 6
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f),	 // 7
	};

	DWORD indices[] = {
		// Front face
		0, 2, 1,
		0, 3, 2,

		// Back face
		4, 5, 6,
		4, 6, 7,

		// Left face
		4, 1, 5,
		4, 0, 1,

		// Right face
		3, 6, 2,
		3, 7, 6,

		// Top face
		1, 6, 5,
		1, 2, 6,

		// Bottom face
		0, 7, 3,
		0, 4, 7};

	vertexBuffer.createBuffer(vertices, sizeof(vertices));

	indexBuffer.createBuffer(indices, sizeof(indices));

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
		ImGui::Text("Position");
		ImGui::InputFloat3("Cube Position", &cb.x);
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
