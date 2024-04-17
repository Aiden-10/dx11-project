#include <Windows.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")

#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Timer.h"

#include <chrono>
#include <string>

Vertex vertices[] = {
		{-0.45, -0.45	,0.1, 0.7, 0.1},
		{-0.45, 0.45	,0.1, 0.7, 0.1},
		{0.45 , 0.45	,0.1, 0.7, 0.1}
};

Vertex vertices2[] = {
		{-0.45, -0.45,	0.1, 0.1, 0.7},
		{0.45, 0.45,	0.1, 0.1, 0.7},
		{0.45, -0.45,	0.1, 0.1, 0.7}
};


int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {

	Window window("this is a title!", 800, 600);
	Renderer renderer(window);

	Triangle triangle(renderer, vertices);
	Triangle triangle2(renderer, vertices2);

	Timer timer;
	timer.Start();
	static int fpsCounter = 10;
	static std::string fpsString = "FPS: 0";

	MSG msg = { 0 };
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}

		renderer.beginFrame();
		fpsCounter += 1;
		if (timer.GetMillisecondsElapsed() > 1000.0)
		{
			fpsString = "FPS: " + std::to_string(fpsCounter);
			fpsCounter = 0;
			timer.Restart();
		}
		// Render Scene Here.

		renderer.DrawString(fpsString.c_str());
		
		triangle.draw(renderer);
		triangle2.draw(renderer);
		
		renderer.endFrame();
	}

	return 0;
}