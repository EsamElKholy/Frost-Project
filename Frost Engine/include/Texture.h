#pragma once

#include <GL\glew.h>
#include <Utilities.h>

class Texture
{
public:
	Texture();
	Texture(char *path, bool invertY = true);
	void BindTexture(int index = 0);
	void UnbindTexture();
	void UnloadTexture();
	bool IsAvailable();
private:
	void CreateTexture(char *path, bool invertY);
public:
	unsigned int TextureID;
};
