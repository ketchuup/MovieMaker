#ifndef FRAME_H
#define FRAME_H

#include <thread>
#include <vector>
#include <functional>
#include "Algorithm.h"

class Frame
{
	public:
		Frame(std::unique_ptr<Image> &&image, std::uint16_t timecode, const std::unique_ptr<Interpolation> &interpolation);

		std::thread apply(std::vector<std::shared_ptr<Algorithm>> &&algorithms);

		friend inline bool operator<(const Frame &a, const Frame &b)
		{
			return a.timecode < b.timecode;
		}

		const Image& getImage() const;

		std::uint16_t getTimecode() const;

		friend class Movie;

	private:
		std::unique_ptr<Image> image;
		std::uint16_t timecode;
		const std::unique_ptr<Interpolation> &interpolation;
};

#endif