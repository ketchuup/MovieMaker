#include "Saver.h"

void FileSaver::save(const std::set<Frame> &frames)
{
	for (const auto &frame : frames)
	{
		frame.getImage().write(std::to_string(frame.getTimecode()) + ".bmp");
	}
}

ReplySaver::ReplySaver(yami::incoming_message &incoming) : incoming(incoming)
{

}

void ReplySaver::save(const std::set<Frame> &frames)
{
	yami::parameters parameters;
	parameters.create_binary_array("datas", frames.size());

	std::vector<std::int32_t> widths, heights, channelss, timecodes;

	for (auto frame = frames.begin(); frame != frames.end(); ++frame)
	{
		auto &image = frame->getImage();

		auto &[width, height, channels] = image.getProperties();
		auto data = image.getPixel(0, 0);

		widths.push_back(width);
		heights.push_back(height);
		channelss.push_back(channels);
		timecodes.push_back(frame->getTimecode());

		parameters.set_binary_in_array("datas", std::distance(frames.begin(), frame), data, width * height * channels);
	}

	parameters.set_integer_array("widths", widths.data(), widths.size());
	parameters.set_integer_array("heights", heights.data(), heights.size());
	parameters.set_integer_array("channelss", channelss.data(), channelss.size());
	parameters.set_integer_array("timecodes", timecodes.data(), timecodes.size());

	incoming.reply(parameters);
}