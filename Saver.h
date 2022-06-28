#ifndef SAVER_H
#define SAVER_H

#include <set>
#include <yami4-cpp/yami.h>
#include "Frame.h"

class Saver
{
public:
	virtual void save(const std::set<Frame> &frames) = 0;
};

class FileSaver final : public Saver
{
public:
	void save(const std::set<Frame> &frames) override;
};

class ReplySaver final : public Saver
{
public:
	explicit ReplySaver(yami::incoming_message &incoming);

	void save(const std::set<Frame> &frames) override;

private:
	yami::incoming_message &incoming;
};

#endif