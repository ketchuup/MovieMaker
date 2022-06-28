#include "Frame.h"

Frame::Frame(Image &&image, std::uint16_t timecode, const std::unique_ptr<Interpolation> &interpolation) : image(std::move(image)), timecode(timecode), interpolation(interpolation)
{

}

void Frame::apply(Algorithm &algorithm)
{
	algorithm.applyOn(image);
}

const Image& Frame::getImage() const
{
	return image;
}

std::uint16_t Frame::getTimecode() const
{
	return timecode;
}