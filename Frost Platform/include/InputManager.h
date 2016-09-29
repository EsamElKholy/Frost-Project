#pragma once

#include <GLFW\glfw3.h>
#include <cinder\CinderMath.h>

using namespace Cinder::Math;

class InputManager
{
public:
	~InputManager() {}
private:
	InputManager() {}
	InputManager(const InputManager &im) = default;
	InputManager& operator=(const InputManager &other) = default;
public:
	static void Init(GLFWwindow *window);
	static void Key_Callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void Button_Callback(GLFWwindow *window, int button, int action, int mode);
	static void Mouse_Position_Callback(GLFWwindow *window, double xPos, double yPos);
	static void Scroll_Callback(GLFWwindow *window, double xOffset, double yOffset);
	static bool IsKeyDown(int key);
	static bool IsKeyUp(int key);
	static bool IsButtonDown(int button);
	static bool IsButtonUp(int button);

public:
	static vec2f MousePos;
	static vec2f MousePosOffset;
	static vec2f ScrollOffset;
	static vec2f LastScrollOffset;
	static GLFWwindow *Window;
	static bool MouseMoved;

private:
	
	static bool KeysDown[500];
	static bool KeysUp[500];

	static bool ButtonsDown[4];
	static bool ButtonsUp[4];

	static bool FirstMouse;
};
