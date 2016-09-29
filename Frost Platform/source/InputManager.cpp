#include <InputManager.h>

bool InputManager::KeysDown[500];
bool InputManager::KeysUp[500];

bool InputManager::ButtonsDown[4];
bool InputManager::ButtonsUp[4];

bool InputManager::FirstMouse;

vec2f InputManager::MousePos;
vec2f InputManager::MousePosOffset;
vec2f InputManager::ScrollOffset;
vec2f InputManager::LastScrollOffset;

GLFWwindow *InputManager::Window = NULL;

void InputManager::Init(GLFWwindow *window) 
{
	for (unsigned int i = 0; i < 500; i++)
	{
		KeysDown[i] = false;
		KeysUp[i] = false;
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		ButtonsDown[i] = false;
		ButtonsUp[i] = false;
	}

	FirstMouse = true;
	Window = window;

	glfwSetKeyCallback(window, Key_Callback);
	glfwSetMouseButtonCallback(window, Button_Callback);
	glfwSetCursorPosCallback(window, Mouse_Position_Callback);
	glfwSetScrollCallback(window, Scroll_Callback);
}

void InputManager::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (action == GLFW_RELEASE)
	{
		KeysUp[key] = true;
		KeysDown[key] = false;
	}

	if (action == GLFW_PRESS)
	{
		KeysUp[key] = false;
		KeysDown[key] = true;
	}
}

void InputManager::Button_Callback(GLFWwindow* window, int button, int action, int mode) 
{
	if (action == GLFW_RELEASE)
	{
		ButtonsUp[button] = true;
		ButtonsDown[button] = false;
	}

	if (action == GLFW_PRESS)
	{
		ButtonsUp[button] = false;
		ButtonsDown[button] = true;
	}
} 

void InputManager::Mouse_Position_Callback(GLFWwindow* window, double xPos, double yPos) 
{
	if (FirstMouse)
	{
		MousePos.X = xPos;
		MousePos.Y = yPos;

		FirstMouse = false;
	}

	MousePosOffset.X = xPos - MousePos.X;
	MousePosOffset.Y = MousePos.Y - yPos;

	MousePos.X = xPos;
	MousePos.Y = yPos;
}

void InputManager::Scroll_Callback(GLFWwindow *window, double xOffset, double yOffset)
{
	if (LastScrollOffset != vec2f(0.0f, 0.0f))
	{
		LastScrollOffset.X = ScrollOffset.X;
		LastScrollOffset.Y = ScrollOffset.Y;
	}
	else
	{
		LastScrollOffset.X = ScrollOffset.X + 0.1f;
		LastScrollOffset.Y = ScrollOffset.Y + 0.1f;;
	}

	ScrollOffset.X = (float)xOffset;
	ScrollOffset.Y = (float)yOffset;
}

bool InputManager::IsKeyDown(int key) 
{
	return KeysDown[key];
}

bool InputManager::IsKeyUp(int key) 
{
	bool state = KeysUp[key];
	
	KeysUp[key] = false;

	return state;
}

bool InputManager::IsButtonDown(int button) 
{
	return ButtonsDown[button];
}

bool InputManager::IsButtonUp(int button) 
{
	bool state = ButtonsUp[button];

	ButtonsUp[button] = false;

	return state;
}