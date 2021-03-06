#ifndef REDUCE_COLORS_H
#define REDUCE_COLORS_H

#include <array>
#include <cmath>
#include <random>
#include <limits>
#include "Algorithm.h"

template <std::size_t clusters, std::size_t iterations = 16>
class ReduceColors final : public Algorithm
{
public:
	void applyOn(Image &image) override
	{
		auto [width, height, channels] = image.getProperties();
		
		std::array<Position, clusters> positions;

		std::mt19937 generator;
		std::uniform_int_distribution<std::int32_t> rangeX(0, width - 1);
		std::uniform_int_distribution<std::int32_t> rangeY(0, height - 1);

		for (std::ptrdiff_t center = 0; center < clusters;)
		{
			Position position{ rangeX(generator), rangeY(generator) };

			if (std::find(positions.begin(), positions.end(), position) == positions.end())
			{
				centers[center] = image.getPixel(position.x, position.y);
				positions[center] = position;
				++center;
			}
		}

		std::vector<std::vector<std::size_t>> previous(height, std::vector<std::size_t>(width, 0));
		std::vector<std::vector<std::size_t>> current(height, std::vector<std::size_t>(width, 0));

		for (std::ptrdiff_t iteration = 0; iteration < iterations; ++iteration)
		{
			for (std::int32_t x = 0; x < width; ++x)
			{
				for (std::int32_t y = 0; y < height; ++y)
				{
					auto pixel = image.getPixel(x, y);

					std::uint64_t minimal = std::numeric_limits<std::uint64_t>::max();
					std::size_t closest;

					for (std::ptrdiff_t center = 0; center < clusters; ++center)
					{
						std::uint64_t distance = calculateDistance(centers[center], pixel, channels);

						if (distance < minimal)
						{
							minimal = distance;
							closest = center;
						}
					}

					current.at(y).at(x) = closest;
				}
			}

			{
				std::array<std::uint64_t, clusters> counts{ 0 };
				std::array<std::vector<std::uint64_t>, clusters> totals;
				std::fill(totals.begin(), totals.end(), std::vector<std::uint64_t>(channels, 0));

				for (std::int32_t x = 0; x < width; ++x)
				{
					for (std::int32_t y = 0; y < height; ++y)
					{
						auto pixel = image.getPixel(x, y);
						std::size_t center = current.at(y).at(x);

						++counts[center];

						for (std::int32_t channel = 0; channel < channels; ++channel)
						{
							totals[center][channel] += pixel[channel];
						}
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
			}

			if (current == previous)
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
				std::size_t center = current.at(y).at(x);
				std::copy_n(centers[center], channels, pixel);
			}
		}
	}

private:
	struct Position
	{
		std::int32_t x, y;

		friend bool operator==(const Position& a, const Position& b)
		{
			return a.x == b.x && a.y == b.y;
		}
	};

	static std::uint64_t calculateDistance(Image::Pixel a, Image::Pixel b, std::int32_t channels)
	{
		std::uint64_t accumulator = 0;

		for (std::int32_t channel = 0; channel < channels; ++channel)
		{
			std::uint64_t difference = static_cast<std::uint64_t>(a[channel]) - b[channel];
			accumulator += difference * difference;
		}

		return accumulator;
	}

	std::array<Image::Pixel, clusters> centers;
};

#endif