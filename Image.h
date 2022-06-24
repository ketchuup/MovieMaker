#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <memory>
#include "Interpolation.h"

struct ImageProperties final
{
	std::int32_t width, height, channels;
};

class Image final
{
	public:
		explicit Image(const std::string &path);

		Image(std::int32_t width, std::int32_t height, std::int32_t channels, std::uint8_t *color);

		Image(const std::unique_ptr<Interpolation> &interpolation, const Image &previous, const Image &next, std::uint16_t begin, std::uint16_t end, std::uint16_t time);

		Image(const Image &other);

		Image(Image &&other) noexcept;

		~Image();

		Image& operator=(const Image &other);

		Image& operator=(Image &&other) noexcept;

		void write(const std::string &path) const;

		const ImageProperties& getProperties() const;

		std::uint8_t* getPixelPointer(std::size_t x, std::size_t y) const;

		void resize(std::int32_t width, std::int32_t height);

	private:
		ImageProperties properties;
		std::uint8_t *data;
};

#endif