#pragma once

#include <GL\glew.h>
#include <Utilities.h>

class OpenGLShader
{
public:
	OpenGLShader(char *vertex = NULL, char *fragment = NULL, char *geometry = NULL)
		: VertexPath(vertex), FragmentPath(fragment), GeometryPath(geometry)
	{
		Unload();
	}
public:
	bool CreateShaders();
	void Activate();
	bool IsAvailable();
	void Unload();

public:
	unsigned int Program;
private:
	char *VertexPath;
	char *FragmentPath;
	char *GeometryPath;
};
