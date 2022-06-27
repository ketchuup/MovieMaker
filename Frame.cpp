#include "Frame.h"

Frame::Frame(const std::string &path, std::uint16_t timecode, std::unique_ptr<Interpolation> &&interpolation) : image(path), timecode(timecode), interpolation(std::move(interpolation))
{

}

Frame::Frame(Image &&image, std::uint16_t timecode, std::unique_ptr<Interpolation>&& interpolation) : image(std::move(image)), timecode(timecode), interpolation(std::move(interpolation))
{

}

void Frame::apply(Algorithm &algorithm)
{
	algorithm.applyOn(image);
}

void Frame::save() const
{
	image.write(std::to_string(timecode) + ".bmp");
}