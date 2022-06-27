#include "FlipVertically.h"

void FlipVertically::applyOn(Image &image)
{
	auto &[width, height, channels] = image.getProperties();

	for (std::ptrdiff_t x = 0; x < width; ++x)
	{
		for (std::ptrdiff_t y = 0; y < height / 2; ++y)
		{
			auto a = image.getPixel(x, y), b = image.getPixel(x, height - y - 1);
			std::swap_ranges(a, a + channels, b);
		}
	}
}