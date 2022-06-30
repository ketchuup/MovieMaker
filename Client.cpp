#include <array>
#include <limits>
#include <iostream>
#include <functional>
#include <yami4-cpp/yami.h>
#include "Image.h"
#include "NetworkUtilities.h"

using Send = std::function<std::unique_ptr<yami::outgoing_message> (const std::string &, const yami::parameters &)>;
using SendOneWay = std::function<void (const std::string &, const yami::parameters &)>;

template <typename T>
T input(const std::string &prompt);

template <>
std::string input(const std::string &prompt)
{
	std::cout << prompt;

	std::string value;
	std::getline(std::cin, value);

	return value;
}

template <>
std::uint64_t input(const std::string &prompt)
{
	std::cout << prompt;

	std::int64_t value;
	std::cin >> value;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return value;
}

std::vector<std::string> requestStringList(const Send &send, const std::string &name)
{
	std::unique_ptr<yami::outgoing_message> outgoing = send(name, yami::parameters());
	const yami::parameters &reply = waitForReply(outgoing);
	return extractStringsFromParameters(name, reply);
}

void checkIfFrameExists(const Send &send, std::uint16_t timecode)
{
	yami::parameters parameters;
	parameters.set_integer("timecode", timecode);

	std::unique_ptr<yami::outgoing_message> outgoing = send("exists", parameters);
	const yami::parameters &reply = waitForReply(outgoing);

	if (reply.get_boolean("exists"))
	{
		throw std::runtime_error("Frame alredy exists.");
	}
}

std::string chooseInterpolation(const Send &send)
{
	std::vector<std::string> interpolations = requestStringList(send, "interpolations");
	std::size_t number = interpolations.size();

	if (number != 0)
	{
		for (std::ptrdiff_t index = 0; index < number; ++index)
		{
			std::cout << '[' << index << "] " << interpolations.at(index) << std::endl;
		}

		auto chosen = input<std::uint64_t>(">>> ");

		if (chosen < number)
		{
			return interpolations[chosen];
		}
		else
		{
			throw std::runtime_error("Unrecognized option.");
		}
	}
}

std::vector<std::string> chooseAlgorithms(const Send &send)
{
	std::vector<std::string> all = requestStringList(send, "algorithms");
	std::size_t number = all.size();

	if (number != 0)
	{
		std::vector<std::string> algorithms;

		while (true)
		{
			for (std::ptrdiff_t index = 0; index < number; ++index)
			{
				std::cout << '[' << index << "] " << all.at(index) << std::endl;
			}
			std::cout << '[' << number << "] Enough" << std::endl;

			auto chosen = input<std::uint64_t>(">>> ");

			if (chosen < number)
			{
				algorithms.push_back(all[chosen]);
			}
			else if (chosen == number)
			{
				return algorithms;
			}
			else
			{
				throw std::runtime_error("Unrecognized option.");
			}
		}
	}
}

std::int32_t main(std::int32_t count, char *arguments[])
{
	if (count < 2)
	{
		throw std::runtime_error("Too few arguments.");
	}

	std::string address = arguments[1];

	yami::agent agent;

	Send send = [&](const std::string &destination, const yami::parameters &parameters = yami::parameters()) -> std::unique_ptr<yami::outgoing_message>
				{
					return agent.send(address, "router", destination, parameters);
				};

	SendOneWay sendOneWay =	[&](const std::string &destination, const yami::parameters &parameters = yami::parameters())
							{
								agent.send_one_way(address, "router", destination, parameters);
							};

	sendOneWay("connect", yami::parameters());

	while (true)
	{
		std::cout << "[0] New frame" << std::endl;
		std::cout << "[1] Enough" << std::endl;
		
		auto chosen = input<std::uint64_t>(">>> ");

		if (chosen == 0)
		{
			yami::parameters frame;

			auto path = input<std::string>("Path: ");
			Image image(path);
			image.attachToParameters(frame);

			auto timecode = input<std::uint64_t>("Timecode: ");
			checkIfFrameExists(send, timecode);
			frame.set_integer("timecode", timecode);

			std::string interpolation = chooseInterpolation(send);
			frame.set_string("interpolation", interpolation);

			std::vector<std::string> algorithms = chooseAlgorithms(send);
			attachStringsToParameters("algorithms", algorithms, frame);

			sendOneWay("upload", frame);
		}
		else if (chosen == 1)
		{
			std::unique_ptr<yami::outgoing_message> outgoing = send("export", yami::parameters());
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

			sendOneWay("close", yami::parameters());

			break;
		}
		else
		{
			throw std::runtime_error("Unrecognized option.");
		}
	}

	return 0;
}