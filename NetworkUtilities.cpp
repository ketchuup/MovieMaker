#include "NetworkUtilities.h"

const yami::parameters &waitForReply(const std::unique_ptr<yami::outgoing_message> &outgoing)
{
	outgoing->wait_for_completion();

	auto state = outgoing->get_state();

	if (state != yami::message_state::replied)
	{
		throw std::runtime_error("Message has not received reply.");
	}

	return outgoing->get_reply();
}

std::vector<std::string> extractStringsFromParameters(const std::string &name, const yami::parameters &parameters)
{
	auto length = parameters.get_string_array_length(name);

	std::vector<std::string> array;
	array.reserve(length);

	for (std::ptrdiff_t index = 0; index < length; ++index)
	{
		array.push_back(parameters.get_string_in_array(name, index));
	}

	return array;
}

void attachStringsToParameters(const std::string &name, const std::vector<std::string> &array, yami::parameters &parameters)
{
	parameters.create_string_array(name, array.size());

	for (std::ptrdiff_t index = 0; index < array.size(); ++index)
	{
		parameters.set_string_in_array(name, index, array[index]);
	}
}