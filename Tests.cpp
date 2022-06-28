#define CATCH_CONFIG_MAIN
#include <Catch2/catch.hpp>

#include "Image.h"

#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipHorizontally.h"
#include "FlipVertically.h"

TEST_CASE("Algorithms", "[algorithms]")
{
	std::int32_t width = 2, height = 4, channels = 3;
	std::uint8_t white[] { 255, 255, 255 };
	Image initial(width, height, channels, white);

	SECTION("Flip horizontally")
	{
		Image copy(initial);
		FlipHorizontally().applyOn(copy);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto a = initial.getPixel(x, y), b = copy.getPixel(width - x - 1, y);

				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					REQUIRE(a[channel] == b[channel]);
				}
			}
		}
	}

	SECTION("Flip vertically")
	{
		Image copy(initial);
		FlipVertically().applyOn(copy);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto a = initial.getPixel(x, y), b = copy.getPixel(x, height - y - 1);

				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					REQUIRE(a[channel] == b[channel]);
				}
			}
		}
	}

	SECTION("Invert colors")
	{
		Image copy(initial);
		InvertColors().applyOn(copy);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto a = initial.getPixel(x, y), b = copy.getPixel(x, y);

				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					REQUIRE(a[channel] + b[channel] == 255);
				}
			}
		}
	}

	SECTION("Reduce colors")
	{
		constexpr std::size_t colors = 8;

		Image copy(initial);
		ReduceColors<colors>().applyOn(copy);

		std::vector<Image::Pixel> used;

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto pixel = copy.getPixel(x, y);

				if (std::find_if(used.begin(), used.end(),	[=](auto already)
															{
																for (std::int32_t channel = 0; channel < channels; ++channel)
																{
																	if (already[channel] != pixel[channel])
																	{
																		return false;
																	}

																	return true;
																}
															}) == used.end())
				{
					used.push_back(pixel);
				}
			}
		}

		REQUIRE(used.size() <= colors);
	}
}