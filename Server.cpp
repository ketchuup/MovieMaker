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

	std::vector<std::future<void>> futures;

	yami::agent agent;

	std::unordered_map<std::string, Instance> instances;
	
	agent.register_object("router", [&](yami::incoming_message &incoming)
									{
										std::string name = incoming.get_message_name();
										std::string from = incoming.get_source();

										std::cout << from << ": " << name << std::endl;

										if (name == "close")
										{
											instances.erase(from);
										}
										else if (name == "connect")
										{
											instances.emplace(from, Instance(agent));
										}
										else
										{
											instances.at(from).handle(incoming);
										}
									});

	agent.add_listener(address);
	
	std::cin.get();

	return 0;
}