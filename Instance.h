#ifndef INSTANCE_H
#define INSTANCE_H

#include <unordered_map>
#include <yami4-cpp/yami.h>
#include "Movie.h"
#include "ReplySaver.h"
#include "NetworkUtilities.h"
#include "Register.h"

#include <iostream>

class Instance final
{
public:
	explicit Instance(yami::agent &agent);

	void handle(yami::incoming_message &incoming);

private:
	void upload(yami::incoming_message &incoming);

	void exists(yami::incoming_message &incoming);

	void export_(yami::incoming_message &incoming);

	void algorithms(yami::incoming_message &incoming);

	void interpolations(yami::incoming_message &incoming);

	yami::agent &agent;

	Movie movie;
	std::vector<std::future<void>> futures;
	std::future<void> previous;

	static const std::unordered_map<std::string, std::function<void (Instance *, yami::incoming_message &)>> callbacks;
};

#endif