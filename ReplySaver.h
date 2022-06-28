#ifndef REPLY_SAVER_H
#define REPLY_SAVER_H

#include "Saver.h"

class ReplySaver final : public Saver
{
public:
	explicit ReplySaver(yami::incoming_message &incoming);

	void save(const std::set<Frame> &frames) override;

private:
	yami::incoming_message &incoming;
};
#endif