#include "ReduceColors.h"
#include <iostream>

void pr(Image::Pixel a)
{
	std::cout << static_cast<int>(a[0]) << ' ' << static_cast<int>(a[1]) << ' ' << static_cast<int>(a[2]) << std::endl;
}

void ReduceColors::applyOn(Image& image)
{
	auto &[width, height, channels] = image.getProperties();

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