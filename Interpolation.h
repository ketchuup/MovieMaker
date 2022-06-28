#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <cstdint>
#include <cmath>

class Interpolation
{
	public:
		virtual std::uint8_t interpolate(std::uint8_t previous, std::uint8_t next, std::uint16_t begin, std::uint16_t end, std::uint16_t time) = 0;
};

#endif