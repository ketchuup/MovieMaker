#include "Image.h"

#define STBI_ONLY_BMP
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Image::Image(const std::string &path)
{
	data = stbi_load(path.c_str(), &properties.width, &properties.height, &properties.channels, 0);
}

Image::Image(Image &&other) noexcept
{
	data = std::exchange(other.data, nullptr);
	properties = std::exchange(other.properties, { });
}

Image::~Image()
{
	stbi_image_free(data);
}

Image& Image::operator=(Image &&other) noexcept
{
	if (&other != this)
	{
		stbi_image_free(data);

		data = std::exchange(other.data, nullptr);
		properties = std::exchange(other.properties, { });
	}
	
	return *this;
}

void Image::write(const std::string &path) const
{
	stbi_write_bmp(path.c_str(), properties.width, properties.height, properties.channels, data);
}

const ImageProperties& Image::getProperties() const
{
	return properties;
}

std::uint8_t* Image::getPixelPointer(std::size_t x, std::size_t y) const
{
	return data + (y * properties.width + x) * properties.channels;
}