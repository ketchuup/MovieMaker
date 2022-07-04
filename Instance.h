#ifndef INSTANCE_H
#define INSTANCE_H

#include <unordered_map>
#include <yami4-cpp/yami.h>
#include "Movie.h"
#include "ReplySaver.h"
#include "NetworkUtilities.h"
#include "Register.h"

class Instance final
{
public:
	explicit Instance(yami::agent &agent);

private:
	void upload(yami::incoming_message &incoming);

	void exists(yami::incoming_message &incoming);

	void export_(yami::incoming_message &incoming);

	yami::agent &agent;

	Movie movie;
	std::vector<std::future<void>> futures;
	std::future<void> previous;

public:
	static const std::unordered_map<std::string, std::function<void (Instance *, yami::incoming_message &)>> callbacks;
};

#endif