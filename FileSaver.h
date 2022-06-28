#ifndef FILE_SAVER_H
#define FILE_SAVER_H

#include "Saver.h"

class FileSaver final : public Saver
{
public:
	void save(const std::set<Frame> &frames) override;
};

#endif