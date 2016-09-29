#include <Utilities.h>

Image ImageLoader::LoadImage(char *path, bool invertY)
{
	Image image = {};

	image.Data = SOIL_load_image(path, &image.Width, &image.Height, 0, SOIL_LOAD_RGBA);

	if (!image.Data)
	{
		std::cout << "Failed to load image\n";

		image = {};

		return image;
	}

	if (invertY)
	{
		for (int x = 0; x < image.Width * 4; x++)
		{
			for (int y = 0; y < image.Height / 2; y++)
			{
				unsigned char tmp = image.Data[x + (y * image.Width * 4)];

				image.Data[x + (y * image.Width * 4)] = image.Data[x + ((image.Height - y - 1) * image.Width * 4)];

				image.Data[x + ((image.Height - y - 1) * image.Width * 4)] = tmp;
			}
		}

		return image;
	}

	return image;
}

void ImageLoader::UnloadImage(Image *image)
{
	SOIL_free_image_data(image->Data);

	image->Data = 0;
	image->Width = 0;
	image->Height = 0;
}

