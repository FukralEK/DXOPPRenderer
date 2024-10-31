#include "App.h"
#include "Renderer.h"
#include "Window.h"
#include "Triangle.h"

const int WIDTH = 1280, HEIGHT = 720;

void App::run()
{
	Window window(WIDTH, HEIGHT, "Hello, Triangle");
	Renderer renderer(window);

	window.init();
	renderer.init();

	Triangle triangle;

	triangle.init();

	while (running)
	{

		triangle.draw();

		window.update(running);
		renderer.update();
	}

	triangle.release();
	renderer.release();
	window.release();
}
