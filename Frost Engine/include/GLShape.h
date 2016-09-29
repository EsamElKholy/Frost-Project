#pragma once

#include <GL\glew.h>
#include <Texture.h>

class GLShape
{
public:
	GLShape();
public:
	void BindBuffers();
	void UnbindBuffers();
	void Destroy();
	bool IsAvailable();
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

	unsigned int VerticesCount;
	unsigned int IndicesCount;
};
