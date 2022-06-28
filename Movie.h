#ifndef MOVIE_H
#define MOVIE_H

#include <set>
#include "Identity.h"
#include "Saver.h"

class Movie final
{
	public:
		Movie();

		void addFrame(Frame &&frame);

		void build();

		void save(Saver &&saver) const;

		bool exists(std::uint16_t timecode);

	private:
		std::set<Frame> frames;
};

#endif