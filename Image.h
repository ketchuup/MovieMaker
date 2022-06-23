#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <cstdint>
#include <utility>

struct ImageProperties final
{
	std::int32_t width, height, channels;
};

class Image final
{
	public:
		explicit Image(const std::string &path);

		Image(const Image &other) = delete;

		Image(Image &&other) noexcept;

		~Image();

		Image& operator=(const Image &other) = delete;

		Image& operator=(Image &&other) noexcept;

		void write(const std::string &path) const;

		const ImageProperties& getProperties() const;

		std::uint8_t* getPixelPointer(std::size_t x, std::size_t y) const;

	private:
		ImageProperties properties;
		std::uint8_t *data;
};

#endif