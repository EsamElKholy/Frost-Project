#pragma once

#include <iostream>

#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class WindowManager
{
public:
	~WindowManager() {}
public:
	static bool CreateOpenGLWindow(int width, int height, char *title);
	static void Update();
	static void Render();
	static void SetClearColor(float r, float g, float b, float a);
	static void ResetClearColor();
	static void ClearWindow();
	static void Destroy();
	static bool ShouldClose();

private:
	WindowManager() {}
	WindowManager(const WindowManager& wm) = default;
	WindowManager& operator=(const WindowManager& wm) = default;

public:
	static GLFWwindow *Window;
	static int Width, Height;
};