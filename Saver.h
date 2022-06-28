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

#endif