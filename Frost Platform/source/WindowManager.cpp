#include <WindowManager.h>

GLFWwindow *WindowManager::Window = NULL;
int WindowManager::Width = 0, WindowManager::Height = 0;

bool WindowManager::CreateOpenGLWindow(int width, int height, char *title)
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "Failed to initialize GLFW!!\n";

		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	Window = glfwCreateWindow(width, height, title, 0, 0);

	if (!Window)
	{
		glfwTerminate();

		std::cout << "Failed to create window!!\n";

		return false;
	}

	glfwMakeContextCurrent(Window);

	Width = width;
	Height = height;

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!!\n";

		return false;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/*
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthFunc(GL_LESS);
	*/
	return true;
}

void WindowManager::Render()
{
	glfwSwapBuffers(Window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::Update()
{
	glfwPollEvents();
}

void WindowManager::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

bool WindowManager::ShouldClose()
{
	if (glfwWindowShouldClose(Window))
	{
		return true;
	}

	return false;
}

void WindowManager::Destroy()
{
	glfwTerminate();
}

void WindowManager::ResetClearColor()
{
	glClearColor(0, 0, 0, 1);
}