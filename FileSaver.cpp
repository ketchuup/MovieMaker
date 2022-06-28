#include "FileSaver.h"

void FileSaver::save(const std::set<Frame> &frames)
{
	for (const auto &frame : frames)
	{
		frame.getImage().write(std::to_string(frame.getTimecode()) + ".bmp");
	}
}