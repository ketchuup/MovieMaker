#ifndef FRAME_H
#define FRAME_H

#include "Algorithm.h"

class Frame
{
	public:
		Frame(const std::string &path, std::uint16_t timecode, std::unique_ptr<Interpolation> &&interpolation);

		Frame(Image &&image, std::uint16_t timecode, std::unique_ptr<Interpolation> &&interpolation);

		void apply(const Algorithm &algorithm);

		void save() const;

		friend inline bool operator<(const Frame &a, const Frame &b)
		{
			return a.timecode < b.timecode;
		}

		friend class Movie;
	private:
		Image image;
		std::uint16_t timecode;
		std::unique_ptr<Interpolation> interpolation;
};

#endif