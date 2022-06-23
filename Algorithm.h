#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Image.h"

class Algorithm
{
	public:
		virtual void applyOn(Image &image) const = 0;
};

#endif