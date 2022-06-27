#ifndef INVERT_COLORS_H
#define INVERT_COLORS_H

#include "Algorithm.h"

class InvertColors final : public Algorithm
{
	public:
		void applyOn(Image &image) override;
};

#endif