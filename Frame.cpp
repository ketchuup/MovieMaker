#include "Frame.h"

Frame::Frame(std::unique_ptr<Image>	&&image, std::uint16_t timecode, const std::unique_ptr<Interpolation> &interpolation) : image(std::move(image)), timecode(timecode), interpolation(interpolation)
{

}

std::future<void> Frame::apply(std::vector<std::shared_ptr<Algorithm>> &&algorithms)
{
	return std::async(	[](std::vector<std::shared_ptr<Algorithm>> &&algorithms, Image *image)
						{
							std::vector<std::shared_ptr<Algorithm>> unapplied = std::move(algorithms);

							for (const auto &algorithm : unapplied)
							{
								algorithm->applyOn(*image);
							}

						}, algorithms, image.get());
}

const Image& Frame::getImage() const
{
	return *image;
}

std::uint16_t Frame::getTimecode() const
{
	return timecode;
}