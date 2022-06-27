#ifndef REDUCE_COLORS_H
#define REDUCE_COLORS_H

#include <array>
#include <cmath>
#include <random>
#include "Algorithm.h"

class ReduceColors final : public Algorithm
{
public:
	void applyOn(Image& image) override;

private:
	struct Position
	{
		std::int32_t x, y;

		friend bool operator==(const Position& a, const Position& b)
		{
			return a.x == b.x && a.y == b.y;
		}
	};

	static double distance(Image::Pixel a, Image::Pixel b, std::int32_t channels);
	std::size_t closestCenter(Image::Pixel pixel, std::int32_t channels);
		
	constexpr static std::size_t clusters = 64;
	constexpr static std::size_t iterations = 16;

	std::array<Image::Pixel, clusters> centers;
};

#endif