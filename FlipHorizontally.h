#ifndef FLIP_HORIZONTALLY_H
#define FLIP_HORIZONTALLY_H

#include "Algorithm.h"

class FlipHorizontally final : public Algorithm
{
	public:
		void applyOn(Image &image) override;
};

#endif