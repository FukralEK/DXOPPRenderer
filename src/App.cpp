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
#include "Camera.h"
#include "Mesh.h"
#include <vector>

const int WIDTH = 1280,
		  HEIGHT = 720;

bool spinning = true;

std::vector<Mesh> meshes;

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

	bool invert = false;

	Camera &camera = Camera::getInstance();

	float fov = 120.0f;

	camera.setCamera(DirectX::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f), DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	camera.setProjection(fov, (float)window.getRes()[0] / (float)window.getRes()[1], 0.01f, 1000.0f);

	char buffer[255];
	buffer[0] = '\0';

	int select = 0;

	while (running)
	{
		ImGuiIO &io = ImGui::GetIO();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("DX Playground");
		ImGui::SliderFloat("FOV", &fov, 10.0f, 180.0f);

		if (meshes.size() != 0)
		{
			ImGui::SliderInt("Mesh index", &select, 0, meshes.size() - 1);
			ImGui::InputFloat3("Mesh Position", &meshes[select].position.x);
			ImGui::InputFloat3("Mesh Rotation", &meshes[select].rotation.x);
			ImGui::Checkbox("Spinning", &spinning);
		}

		ImGui::InputText("Model File", buffer, 255);

		if (ImGui::Button("Load Model") && buffer[0] != '\0')
		{
			meshes.push_back(Mesh());

			meshes[meshes.size() - 1].init(buffer);

			meshes[meshes.size() - 1].position = {0.0f, 0.0f, 2.0f};
			meshes[meshes.size() - 1].rotation = {0.0f, 0.0f, 0.0f};

			buffer[0] = '\0';
		}
		ImGui::End();

		camera.setProjection(fov, (float)window.getRes()[0] / (float)window.getRes()[1], 0.01f, 1000.0f);

		ImGui::Render();

		for (auto &mesh : meshes)
		{
			mesh.draw();
		}

		if (spinning)
		{
			for (auto &mesh : meshes)
			{
				mesh.rotation.y += 0.05f;
			}
		}

		window.update(running);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		renderer.update();
	}

	for (auto &mesh : meshes)
	{
		mesh.release();
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	renderer.release();
	window.release();
}
