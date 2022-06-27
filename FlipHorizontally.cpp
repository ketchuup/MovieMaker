#include "FlipHorizontally.h"

void FlipHorizontally::applyOn(Image &image)
{
	auto &[width, height, channels] = image.getProperties();

	for (std::ptrdiff_t x = 0; x < width / 2; ++x)
	{
		for (std::ptrdiff_t y = 0; y < height; ++y)
		{
			auto a = image.getPixel(x, y), b = image.getPixel(width - x - 1, y);
			std::swap_ranges(a, a + channels, b);
		}
	}
}