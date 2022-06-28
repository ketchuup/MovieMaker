#ifndef IDENTITY_H
#define IDENTITY_H

#include "Interpolation.h"

class Identity final : public Interpolation
{
public:
	std::uint8_t interpolate(std::uint8_t previous, std::uint8_t next, std::uint16_t begin, std::uint16_t end, std::uint16_t time) override;
};

#endif