#define CATCH_CONFIG_MAIN

#include <vector>
#include <Catch2/catch.hpp>
#include "Image.h"
#include "NetworkUtilities.h"
#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipHorizontally.h"
#include "FlipVertically.h"
#include "Identity.h"
#include "Linear.h"
#include "Logarithmic.h"

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

bool equal(double a, double b)
{
	constexpr double epsilon = 1.0;
	return std::fabs(a - b) < epsilon;
}

TEST_CASE("Algorithms", "[algorithms]")
{
	std::uint8_t white[] { 255, 255, 255 };
	std::int32_t width = 2, height = 4, channels = 3;

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
	std::uint8_t white[]{ 255, 255, 255 };
	std::int32_t width = 2, height = 4, channels = 3;

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

TEST_CASE("Interpolation", "[interpolation]")
{
	std::uint8_t red[]{ 255, 0, 0 };
	std::uint8_t green[]{ 0, 255, 0 };
	
	std::int32_t width = 2, height = 2, channels = 3;

	Image a(width, height, channels, red), b(width, height, channels, green);
	std::uint16_t timecodeA = 1, timecodeB = 3, resultTimecode = 2;

	SECTION("Identity")
	{
		std::unique_ptr<Interpolation> interpolation = std::make_unique<Identity>();
		Image result(interpolation, a, b, timecodeA, timecodeB, resultTimecode);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto pixelB = b.getPixel(x, y), resultPixel = result.getPixel(width - x - 1, y);
				REQUIRE(equal(pixelB, resultPixel, channels));
			}
		}
	}

	SECTION("Linear")
	{
		std::unique_ptr<Interpolation> interpolation = std::make_unique<Linear>();
		Image result(interpolation, a, b, timecodeA, timecodeB, resultTimecode);

		double progress = static_cast<float>(resultTimecode - timecodeA) / (timecodeB - timecodeA);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto pixelA = a.getPixel(x, y), pixelB = b.getPixel(x, y), resultPixel = result.getPixel(width - x - 1, y);
				
				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					REQUIRE(equal(progress * (pixelB[channel] - pixelA[channel]), resultPixel[channel] - pixelA[channel]));
				}
			}
		}
	}

	SECTION("Logarithmic")
	{
		std::unique_ptr<Interpolation> interpolation = std::make_unique<Logarithmic>();
		Image result(interpolation, a, b, timecodeA, timecodeB, resultTimecode);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto pixelA = a.getPixel(x, y), pixelB = b.getPixel(x, y), resultPixel = result.getPixel(width - x - 1, y);

				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					REQUIRE(equal(std::log2(static_cast<double>(timecodeA + 1) / (timecodeB + 1)) * (pixelA[channel] - resultPixel[channel]), std::log2(static_cast<double>(timecodeA + 1) / (resultTimecode + 1)) * (pixelA[channel] - pixelB[channel])));
				}
			}
		}
	}
}

TEST_CASE("Parameters", "[parameters]")
{
	SECTION("Attach/extract strings to/from parameters")
	{
		std::vector<std::string> values { "a", "b", "c" };
		yami::parameters parameters;

		attachStringsToParameters("strings", values, parameters);

		REQUIRE(extractStringsFromParameters("strings", parameters) == values);
	}

	SECTION("Attach/extract image to/from parameters")
	{
		std::uint8_t white[]{ 255, 255, 255 };
		std::int32_t width = 2, height = 2, channels = 3;

		Image in(width, height, channels, white);

		yami::parameters parameters;
		in.attachToParameters(parameters);

		Image out(parameters);

		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto a = in.getPixel(x, y), b = out.getPixel(x, y);
				REQUIRE(equal(a, b, channels));
			}
		}
	}

	SECTION("Attach string keys to parameters")
	{
		std::vector<std::string> keys = { "a", "b", "c" };
		std::unordered_map<std::string, std::size_t> map;

		for (std::ptrdiff_t index = 0; index < keys.size(); ++index)
		{
			map.emplace(keys[index], index);
		}

		yami::parameters parameters;
		attachStringKeysToParameters("keys", map, parameters);

		REQUIRE(extractStringsFromParameters("keys", parameters) == keys);
	}
}