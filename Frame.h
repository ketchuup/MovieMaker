#ifndef FRAME_H
#define FRAME_H

#include <functional>
#include "Algorithm.h"

class Frame
{
	public:
		Frame(Image &&image, std::uint16_t timecode, const std::unique_ptr<Interpolation> &interpolation);

		void apply(Algorithm &algorithm);

		friend inline bool operator<(const Frame &a, const Frame &b)
		{
			return a.timecode < b.timecode;
		}

		const Image& getImage() const;

		std::uint16_t getTimecode() const;

		friend class Movie;

	private:
		Image image;
		std::uint16_t timecode;
		const std::unique_ptr<Interpolation> &interpolation;
};

#endif