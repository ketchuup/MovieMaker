#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <memory>
#include <yami4-cpp/parameters.h>
#include "Interpolation.h"

struct ImageProperties final
{
	std::int32_t width, height, channels;
};

class Image final
{
	public:
		using Pixel = std::uint8_t *;

		explicit Image(const std::string &path);

		Image(std::int32_t width, std::int32_t height, std::int32_t channels, Image::Pixel color);

		Image(Image::Pixel source, std::int32_t width, std::int32_t height, std::int32_t channels);

		Image(const std::unique_ptr<Interpolation> &interpolation, const Image &previous, const Image &next, std::uint16_t begin, std::uint16_t end, std::uint16_t time);

		explicit Image(yami::parameters &parameters);

		Image(const Image &other);

		Image(Image &&other) noexcept;

		~Image();

		Image& operator=(const Image &other);

		Image& operator=(Image &&other) noexcept;

		void write(const std::string &path) const;

		const ImageProperties getProperties() const;

		Pixel getPixel(std::size_t x, std::size_t y) const;

		void resize(std::int32_t width, std::int32_t height);

		void attachToParameters(yami::parameters& parameters) const;

	private:
		ImageProperties properties;
		Pixel data;
};

#endif