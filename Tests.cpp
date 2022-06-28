#define CATCH_CONFIG_MAIN
#include <Catch2/catch.hpp>

#include "Image.h"

#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipHorizontally.h"
#include "FlipVertically.h"

bool equal(Image::Pixel a, Image::Pixel b, std::int32_t channels)
{
	for (std::int32_t channel = 0; channel < channels; ++channel)
	{
		if (a[channel] != b[channel])
		{
			return false;
		}
	}

	return true;
}

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
				REQUIRE(equal(a, b, channels));
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
				REQUIRE(equal(a, b, channels));
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
																return equal(pixel, already, channels);
															}) == used.end())
				{
					used.push_back(pixel);
				}
			}
		}

		REQUIRE(used.size() <= colors);
	}
}

TEST_CASE("Image", "[image]")
{
	std::int32_t width = 2, height = 4, channels = 3;
	std::uint8_t white[]{ 255, 255, 255 };
	Image initial(width, height, channels, white);

	SECTION("Resize")
	{
		std::int32_t newWidth = 4, newHeight = 6;
		std::int32_t offsetX = (newWidth - width) / 2, offsetY = (newHeight - height) / 2;

		Image copy(initial);
		copy.resize(newWidth, newHeight);

		for (std::int32_t x = 0; x < newWidth; ++x)
		{
			for (std::int32_t y = 0; y < newHeight; ++y)
			{
				auto pixel = copy.getPixel(x, y);

				if (x < offsetX || x >= (offsetX + width) || y < offsetY || y >= (offsetY + height))
				{
					REQUIRE(equal(pixel, white, channels));
				}
				else
				{
					REQUIRE(equal(pixel, initial.getPixel(x - offsetX, y - offsetY), channels));
				}
			}
		}
	}
}