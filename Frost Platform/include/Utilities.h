#pragma once

#include <iostream>
#include <SOIL\SOIL.h>

char* LoadTextFile(char *path);

struct Image
{
	unsigned char *Data;
	int Width, Height;
};

class ImageLoader
{
public:
	~ImageLoader() {}
	static Image LoadImage(char *path, bool invertY);
	static void UnloadImage(Image *image);
private:
	ImageLoader() {}
	ImageLoader(const ImageLoader &im) = default;
	ImageLoader& operator=(const ImageLoader &im) = default;
};