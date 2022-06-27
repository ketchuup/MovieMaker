#ifndef FLIP_VERTICALLY_H
#define FLIP_VERTICALLY_H

#include "Algorithm.h"

class FlipVertically final : public Algorithm
{
	public:
		void applyOn(Image &image) override;
};

#endif