#include <GLShape.h>


GLShape::GLShape() 
{
	Destroy();

	VerticesCount = 0;
	IndicesCount = 0;
}

void GLShape::BindBuffers()
{
	if (VAO && VBO && IBO)
	{
		glBindVertexArray(VAO);
	}
}

void GLShape::UnbindBuffers()
{
	if (VAO && VBO && IBO)
	{
		glBindVertexArray(0);
	}
}

void GLShape::Destroy()
{
	if (VBO)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	else
	{
		VBO = 0;
	}

	if (IBO)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	else
	{
		IBO = 0;
	}

	if (VAO)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	else
	{
		VAO = 0;
	}
}

bool GLShape::IsAvailable() 
{
	if (VAO && VBO && IBO)
	{
		return true;
	}

	return false;
}