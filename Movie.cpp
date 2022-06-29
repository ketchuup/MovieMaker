#include "Movie.h"

Movie::Movie()
{
	std::uint8_t white[3] { 255, 255, 255 };
	frames.emplace(std::make_unique<Image>(10, 10, 3, white), 0, std::make_unique<Identity>());
}

void Movie::addFrame(Frame &&frame)
{
	frames.emplace(std::move(frame));
}

void Movie::build()
{
	std::int32_t width = 0, height = 0; std::uint16_t timecode = 0;

	for (const auto &frame : frames)
	{
		width = std::max(width, frame.image->getProperties().width);
		height = std::max(height, frame.image->getProperties().height);
		timecode = std::max(timecode, frame.timecode);
	}

	for (auto &frame : frames)
	{
		const_cast<Frame &>(frame).image->resize(width, height);
	}

	auto get = 	[&](std::uint16_t timecode)
				{
					return std::find_if(frames.begin(), frames.end(), 	[=](const Frame &frame)
																		{
																			return frame.timecode == timecode;
																		});
				};

	auto exists = 	[&](std::uint16_t timecode)
					{
						return get(timecode) != frames.end();
					};

	for (std::uint16_t current = 1; current < timecode; ++current)
	{
		if (!exists(current))
		{
			auto previous = current - 1, next = current + 1;

			while (!exists(next))
			{
				++next;
			}

			auto previousFrame = get(previous);
			auto nextFrame = get(next);

			frames.emplace(std::make_unique<Image>(nextFrame->interpolation, *(previousFrame->image), *(nextFrame->image), previous, next, current), current, std::make_unique<Identity>());
		}
	}
}

void Movie::save(Saver &&saver) const
{
	saver.save(frames);
}

bool Movie::exists(std::uint16_t timecode)
{
	for (const Frame &frame : frames)
	{
		if (timecode == frame.getTimecode())
		{
			return true;
		}
	}

	return false;
}