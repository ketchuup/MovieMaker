#include "InvertColors.h"

void InvertColors::applyOn(Image &image)
{
	auto &[width, height, channels] = image.getProperties();

	for (std::ptrdiff_t x = 0; x < width; ++x)
	{
		for (std::ptrdiff_t y = 0; y < height; ++y)
		{
			auto pixel = image.getPixel(x, y);

			for (std::ptrdiff_t channel = 0; channel < channels; ++channel)
			{
				pixel[channel] = 255 - pixel[channel];
			}
		}
	}
}