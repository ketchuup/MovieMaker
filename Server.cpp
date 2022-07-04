#include <queue>
#include <iostream>
#include "Instance.h"

std::int32_t main(std::int32_t count, char *arguments[])
{
	if (count < 2)
	{
		throw std::runtime_error("Too few arguments.");
	}

	std::string address = arguments[1];

	yami::agent agent;
	std::unordered_map<std::string, Instance> instances;
	std::unordered_map<std::string, std::future<void>> previous;

	std::unordered_map<std::string, std::function<void (yami::incoming_message &)>> callbacks;

	callbacks.emplace("connect",	[&](yami::incoming_message &incoming)
									{
										std::string from = incoming.get_source();
										instances.emplace(from, Instance(agent));
									});

	callbacks.emplace("close",	[&](yami::incoming_message &incoming)
								{
									std::string from = incoming.get_source();
									instances.erase(from);
									previous.erase(from);
								});

	callbacks.emplace("algorithms", [&](yami::incoming_message &incoming)
									{
										yami::parameters parameters;
										attachStringKeysToParameters("algorithms", allAlgorithmCreators, parameters);
										incoming.reply(parameters);
									});

	callbacks.emplace("interpolations", [&](yami::incoming_message &incoming)
										{
											yami::parameters parameters;
											attachStringKeysToParameters("interpolations", allInterpolations, parameters);
											incoming.reply(parameters);
										});
	
	agent.register_object("router", [&](yami::incoming_message &incoming)
									{
										std::string name = incoming.get_message_name();
										std::string from = incoming.get_source();

										std::cout << from << ": " << name << std::endl;

										if (name == "connect")
										{
											previous.emplace(from, std::future<void>()); // idk how to insert default future into map before calling "connect" callback
										}

										std::function<void (yami::incoming_message &)> callback;

										try
										{
											callback = callbacks.at(name);
										}
										catch (std::out_of_range)
										{
											using namespace std::placeholders;
											callback = std::bind(Instance::callbacks.at(name), &instances.at(from), _1);
										}

										std::unique_ptr<yami::incoming_message> pointer = std::make_unique<yami::incoming_message>(incoming);

										std::future<void> current = std::async(	[](std::future<void> previous, std::function<void (yami::incoming_message &)> callback, std::unique_ptr<yami::incoming_message> incoming)
																				{
																					if (previous.valid())
																					{
																						previous.wait();
																					}

																					callback(*incoming);
																				}, std::move(previous.at(from)), std::move(callback), std::move(pointer));

										previous.at(from) = std::move(current);
									});

	agent.add_listener(address);
	
	std::cin.get();

	return 0;
}