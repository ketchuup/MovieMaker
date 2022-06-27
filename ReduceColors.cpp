#include "ReduceColors.h"
#include <iostream>

void pr(Image::Pixel a)
{
	std::cout << static_cast<int>(a[0]) << ' ' << static_cast<int>(a[1]) << ' ' << static_cast<int>(a[2]) << std::endl;
}

void ReduceColors::applyOn(Image& image)
{
	auto& [width, height, channels] = image.getProperties();

	std::array<Position, clusters> positions;

	std::mt19937 generator;
	std::uniform_int_distribution<std::int32_t> rangeX(0, width);
	std::uniform_int_distribution<std::int32_t> rangeY(0, height);

	for (std::ptrdiff_t center = 0; center < clusters; ++center)
	{
		Position position{ rangeX(generator), rangeY(generator) };

		if (std::find(positions.begin(), positions.end(), position) == positions.end())
		{
			centers[center] = image.getPixel(position.x, position.y);
			positions[center] = position;
		}
		else
		{
			--center;
		}
	}

	std::vector<std::size_t> previous;
	previous.resize(width * height);

	std::vector<std::size_t> current;
	current.resize(width * height);

	for (std::ptrdiff_t iteration = 0; iteration < iterations; ++iteration)
	{
		for (std::int32_t x = 0; x < width; ++x)
		{
			for (std::int32_t y = 0; y < height; ++y)
			{
				auto pixel = image.getPixel(x, y);
				std::size_t center = closestCenter(pixel, channels);
				current.at(y * width + x) = center;
			}
		}

		std::array<std::uint64_t, clusters> counts { 0 };
		std::array<std::array<std::uint64_t, 3>, clusters> totals { 0 };

		for (std::ptrdiff_t index = 0; index < current.size(); ++index)
		{
			auto center = current[index];
			counts[center] += 1;

			auto y = index % width, x = (index - y) / width;
			auto pixel = image.getPixel(x, y);
			
			for (std::int32_t channel = 0; channel < channels; ++channel)
			{
				totals[center][channel] += pixel[channel];
			}
		}

		for (std::ptrdiff_t center = 0; center < clusters; ++center)
		{
			if (counts[center] != 0)
			{
				for (std::int32_t channel = 0; channel < channels; ++channel)
				{
					centers[center][channel] = totals[center][channel] / counts[center];
				}
			}
		}

		if (previous == current)
		{
			break;
		}

		previous = current;
	}

	for (std::int32_t x = 0; x < width; ++x)
	{
		for (std::int32_t y = 0; y < height; ++y)
		{
			auto pixel = image.getPixel(x, y);
			std::size_t center = current.at(y * width + x);
			std::copy_n(centers[center], channels, pixel);
		}
	}
}

double ReduceColors::distance(Image::Pixel a, Image::Pixel b, std::int32_t channels)
{
	double accumulator = 0;

	for (std::int32_t channel = 0; channel < channels; ++channel)
	{
		double difference = a[channel] - b[channel];
		accumulator += difference * difference;
	}

	return accumulator;
}

std::size_t ReduceColors::closestCenter(Image::Pixel pixel, std::int32_t channels)
{
	std::array<double, clusters> distances;

	for (std::ptrdiff_t center = 0; center < clusters; ++center)
	{
		distances[center] = distance(centers[center], pixel, channels);
	}

	auto minimal = std::min_element(distances.begin(), distances.end());
	return std::distance(distances.begin(), minimal);
}