#ifndef MOVIE_H
#define MOVIE_H

#include <set>
#include "Frame.h"

class Movie final
{
	public:
		Movie();

		void addFrame(Frame &&frame);

		void build();

		void save() const;

	private:
		std::set<Frame> frames;
};

#endif