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

Image::Image(std::int32_t width, std::int32_t height, std::int32_t channels, Image::Pixel color) : properties({ width, height, channels })
{
	data = static_cast<Image::Pixel>(malloc(width * height * channels));

	for (std::ptrdiff_t offset = 0; offset < width * height * channels; offset += channels)
	{
		std::copy_n(color, channels, data + offset);
	}
}

Image::Image(Image::Pixel source, std::int32_t width, std::int32_t height, std::int32_t channels) : properties({ width, height, channels })
{
	std::size_t size = properties.width * properties.height * properties.channels;

	data = static_cast<Image::Pixel>(malloc(size));
	std::copy_n(reinterpret_cast<const std::uint8_t *>(source), size, data);
}

Image::Image(const std::unique_ptr<Interpolation> &interpolation, const Image &previous, const Image &next, std::uint16_t begin, std::uint16_t end, std::uint16_t time) : properties(next.properties)
{
	data = static_cast<Image::Pixel>(malloc(properties.width * properties.height * properties.channels));

	for (std::ptrdiff_t x = 0; x < properties.width; ++x)
	{
		for (std::ptrdiff_t y = 0; y < properties.height; ++y)
		{
			auto previousPixel = previous.getPixel(x, y), current = getPixel(x, y), nextPixel = next.getPixel(x, y);

			for (std::ptrdiff_t channel = 0; channel < properties.channels; ++channel)
			{
				current[channel] = interpolation->interpolate(previousPixel[channel], nextPixel[channel], begin, end, time);
			}
		}
	}
}

Image::Image(yami::parameters &parameters)
{
	properties.width = parameters.get_integer("width");
	properties.height = parameters.get_integer("height");
	properties.channels = parameters.get_integer("channels");

	std::size_t size = properties.width * properties.height * properties.channels;
	const void* received = parameters.get_binary("data", size);

	data = static_cast<Image::Pixel>(malloc(size));
	std::copy_n(reinterpret_cast<const std::uint8_t *>(received), size, data);
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

Image::Image(const Image &other) : properties(other.properties)
{
	std::int32_t size = properties.width * properties.height * properties.channels;
	data = static_cast<Image::Pixel>(malloc(size));
	std::copy_n(other.data, size, data);
}

Image& Image::operator=(const Image &other)
{
	if (&other != this)
	{
		stbi_image_free(data);

		properties = other.properties;
		std::int32_t size = properties.width * properties.height * properties.channels;
		data = static_cast<Image::Pixel>(malloc(size));
		std::copy_n(other.data, size, data);
	}

	return *this;
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

Image::Pixel Image::getPixel(std::size_t x, std::size_t y) const
{
	return data + (y * properties.width + x) * properties.channels;
}

void Image::resize(std::int32_t width, std::int32_t height)
{
	std::int32_t size = width * height * properties.channels;
	auto replacement = static_cast<Image::Pixel>(malloc(size));
	std::fill_n(replacement, size, 255);

	std::int32_t offsetX = properties.channels * (width - properties.width) / 2, offsetY = (height - properties.height) / 2;
	std::int32_t bytesPerRowBefore = properties.width * properties.channels, bytesPerRowAfter = width * properties.channels;

	for (std::ptrdiff_t row = 0; row < properties.height; ++row)
	{
		std::copy_n(data + row * bytesPerRowBefore, bytesPerRowBefore, replacement + (offsetY + row) * bytesPerRowAfter + offsetX);
	}

	stbi_image_free(data);

	data = replacement;
	properties.width = width;
	properties.height = height;
}

void Image::attachToParameters(yami::parameters &parameters) const
{
	parameters.set_binary("data", data, properties.width * properties.height * properties.channels);
	parameters.set_integer("width", properties.width);
	parameters.set_integer("height", properties.height);
	parameters.set_integer("channels", properties.channels);
}