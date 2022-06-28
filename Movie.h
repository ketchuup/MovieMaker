#ifndef MOVIE_H
#define MOVIE_H

#include <set>
#include "Saver.h"

class Movie final
{
	public:
		Movie();

		void addFrame(Frame &&frame);

		void build();

		void save(Saver &&saver) const;

	private:
		std::set<Frame> frames;
};

#endif