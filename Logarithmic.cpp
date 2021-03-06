#include "Logarithmic.h"

std::uint8_t Logarithmic::interpolate(std::uint8_t previous, std::uint8_t next, std::uint16_t begin, std::uint16_t end, std::uint16_t time)
{
	double a = static_cast<double>(previous - next) / std::log2(static_cast<double>(begin + 1) / (end + 1));
	double b = previous - a * std::log2(begin + 1);
	return static_cast<std::uint8_t>(std::round(a * std::log2(time + 1) + b));
}