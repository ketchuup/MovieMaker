#include <array>
#include <iostream>
#include <functional>
#include <yami4-cpp/yami.h>
#include "Image.h"

template <typename T>
T input(const std::string &prompt);

template <>
std::string input(const std::string &prompt)
{
	std::cout << prompt;
	std::string value;
	std::getline(std::cin, value, '\n');

	return value;
}

template <>
std::uint64_t input(const std::string &prompt)
{
	std::cout << prompt;
	std::int64_t value;
	std::cin >> value;
	std::cin.ignore(512, '\n');

	return value;
}

const yami::parameters &waitForReply(const std::unique_ptr<yami::outgoing_message> &outgoing)
{
	outgoing->wait_for_completion();

	auto state = outgoing->get_state();

	if (state != yami::message_state::replied)
	{
		throw std::runtime_error("Message has not received reply.");
	}

	const yami::parameters &reply = outgoing->get_reply();
}

std::vector<std::string> requestStringArray(yami::agent &agent, const std::string &address, const std::string& name)
{
	std::unique_ptr<yami::outgoing_message> outgoing = agent.send(address, "router", name);
	const yami::parameters &reply = waitForReply(outgoing);

	auto length = reply.get_string_array_length(name);

	std::vector<std::string> array;
	array.reserve(length);

	for (std::ptrdiff_t index = 0; index < length; ++index)
	{
		array.push_back(reply.get_string_in_array(name, index));
	}

	return array;
}

std::int32_t main(std::int32_t count, char *arguments[])
{
	if (count < 2)
	{
		throw std::runtime_error("Too few arguments.");
	}

	std::string address = arguments[1];

	bool running = true;

	yami::agent agent;

	while (running)
	{
		std::cout << "[0] New frame" << std::endl;
		std::cout << "[1] Enough" << std::endl;
		
		auto selection = input<std::uint64_t>(">>> ");

		if (selection == 0)
		{
			auto path = input<std::string>("Path: ");
			auto timecode = input<std::uint64_t>("Timecode: ");

			yami::parameters parameters;
			parameters.set_integer("timecode", timecode);

			std::unique_ptr<yami::outgoing_message> outgoing = agent.send(address, "router", "exists", parameters);
			const yami::parameters &reply = waitForReply(outgoing);

			if (reply.get_boolean("exists"))
			{
				throw std::runtime_error("Frame alredy exists.");
			}

			auto interpolations = requestStringArray(agent, address, "interpolations");

			std::string selectedInterpolation;

			if (interpolations.size() != 0)
			{
				auto length = interpolations.size();

				for (std::ptrdiff_t index = 0; index < length; ++index)
				{
					std::cout << '[' << index << "] " << interpolations.at(index) << std::endl;
				}

				auto selection = input<std::uint64_t>(">>> ");

				if (selection < length)
				{
					selectedInterpolation = interpolations[selection];
				}
				else
				{
					throw std::runtime_error("Unrecognized option.");
				}
			}

			auto algorithms = requestStringArray(agent, address, "algorithms");

			if (algorithms.size() != 0)
			{
				std::vector<std::string> selectedAlgorithms;

				while (true)
				{
					auto length = algorithms.size();

					for (std::ptrdiff_t index = 0; index < length; ++index)
					{
						std::cout << '[' << index << "] " << algorithms.at(index) << std::endl;
					}
					std::cout << '[' << length << "] Enough" << std::endl;

					auto selection = input<std::uint64_t>(">>> ");

					if (selection < length)
					{
						selectedAlgorithms.push_back(algorithms[selection]);
					}
					else if (selection == length)
					{
						yami::parameters frame;

						Image image(path);
						image.attachToParameters(frame);

						frame.set_integer("timecode", timecode);

						frame.set_string("interpolation", selectedInterpolation);

						frame.create_string_array("algorithms", selectedAlgorithms.size());

						for (std::ptrdiff_t index = 0; index < selectedAlgorithms.size(); ++index)
						{
							frame.set_string_in_array("algorithms", index, selectedAlgorithms[index]);
						}

						agent.send_one_way(address, "router", "upload", frame);
						break;
					}
					else
					{
						throw std::runtime_error("Unrecognized option.");
					}
				}
			}
		}
		else if (selection == 1)
		{
			std::unique_ptr<yami::outgoing_message> outgoing = agent.send(address, "router", "export");
			const yami::parameters &reply = waitForReply(outgoing);

			std::size_t length = reply.get_binary_array_length("datas");

			std::int32_t *widths = reply.get_integer_array("widths", length);
			std::int32_t *heights = reply.get_integer_array("heights", length);
			std::int32_t *channelss = reply.get_integer_array("channelss", length);
			std::int32_t *timecodes = reply.get_integer_array("timecodes", length);

			for (std::ptrdiff_t index = 0; index < length; ++index)
			{
				std::size_t size = widths[index] * heights[index] * channelss[index];
				auto data = reinterpret_cast<Image::Pixel>(const_cast<void *>(reply.get_binary_in_array("datas", index, size)));

				Image image(data, widths[index], heights[index], channelss[index]);
				image.write(std::to_string(timecodes[index]) + ".bmp");
			}

			agent.send_one_way(address, "router", "close");

			break;
		}
		else
		{
			throw std::runtime_error("Unrecognized option.");
		}
	}

	return 0;
}