#include "Linear.h"

std::uint8_t Linear::interpolate(std::uint8_t previous, std::uint8_t next, std::uint16_t begin, std::uint16_t end, std::uint16_t time)
{
	double a = static_cast<double>(next - previous) / (end - begin);
	double b = previous - a * begin;
	return static_cast<std::uint8_t>(std::round(a * time + b));
}