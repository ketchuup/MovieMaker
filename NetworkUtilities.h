#ifndef NETWORK_UTILITIES_H
#define NETWORK_UTILITIES_H

#include <vector>
#include <unordered_map>
#include <yami4-cpp/yami.h>

const yami::parameters &waitForReply(const std::unique_ptr<yami::outgoing_message> &outgoing);

std::vector<std::string> extractStringsFromParameters(const std::string &name, const yami::parameters &parameters);

void attachStringsToParameters(const std::string &name, const std::vector<std::string> &array, yami::parameters &parameters);

template <typename T>
void attachStringKeysToParameters(const std::string &name, const std::unordered_map<std::string, T> &map, yami::parameters &parameters)
{
	parameters.create_string_array(name, map.size());

	for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
	{
		auto index = std::distance(map.begin(), iterator);
		parameters.set_string_in_array(name, index, iterator->first);
	}
}

#endif