#include <GLShader.h>


bool OpenGLShader::CreateShaders()
{
	Unload();

	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int geometryShader = 0;

	if (VertexPath && FragmentPath)
	{		
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		char *vertexData = LoadTextFile(VertexPath);
		char *fragmentData = LoadTextFile(FragmentPath);

		glShaderSource(vertexShader, 1, &vertexData, 0);
		glShaderSource(fragmentShader, 1, &fragmentData, 0);

		{
			glCompileShader(vertexShader);

			delete vertexData;
			vertexData = NULL;

			int success;
			char log[512];

			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, 0, log);

				std::cout << "Couldn't compile vertex shader\n";
				std::cout << "Error log: \n" << log << std::endl;
				return false;
			}
		}

		{
			glCompileShader(fragmentShader);

			delete fragmentData;
			fragmentData = NULL;

			int success;
			char log[512];

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, 0, log);

				std::cout << "Couldn't compile fragment shader\n";
				std::cout << "Error log: \n" << log << std::endl;
				return false;
			}
		}
	}
	else
	{
		if (!VertexPath)
		{
			std::cout << "Invalid vertex shader path\n";
		}

		if (!FragmentPath)
		{
			std::cout << "Invalid fragment shader path\n";
		}

		return false;
	}

	if (GeometryPath)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

		char *geometryData = LoadTextFile(GeometryPath);

		glShaderSource(geometryShader, 1, &geometryData, 0);

		glCompileShader(geometryShader);

		delete geometryData;
		geometryData = NULL;

		int success;
		char log[512];

		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(geometryShader, 512, 0, log);

			std::cout << "Couldn't compile geometry shader\n";
			std::cout << "Error log: \n" << log << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid geometry shader path\n";
	}

	Program = glCreateProgram();

	if (vertexShader)
	{
		glAttachShader(Program, vertexShader);
		glDeleteShader(vertexShader);
	}

	if (fragmentShader)
	{
		glAttachShader(Program, fragmentShader);
		glDeleteShader(fragmentShader);
	}

	if (geometryShader)
	{
		glAttachShader(Program, geometryShader);
		glDeleteShader(geometryShader);
	}

	glLinkProgram(Program);

	int success;
	char log[512];
	GLenum e = glGetError();
	glGetProgramiv(Program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(Program, 512, 0, log);

		std::cout << "Couldn't link geometry shader\n";
		std::cout << "Error log: \n" << log << std::endl;

		return false;
	}

	return true;
}

void OpenGLShader::Activate()
{
	glUseProgram(Program);
}

bool OpenGLShader::IsAvailable()
{
	if (Program)
	{
		return true;
	}

	return false;
}

void OpenGLShader::Unload()
{
	if (Program)
	{
		glDeleteProgram(Program);
		Program = 0;
	}
	else
	{
		Program = 0;
	}
}
