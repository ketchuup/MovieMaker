#include <unordered_map>
#include <yami4-cpp/yami.h>
#include "Movie.h"

#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipVertically.h"
#include "FlipHorizontally.h"

#include "Identity.h"
#include "Linear.h"
#include "Logarithmic.h"

#include "ReplySaver.h"

std::int32_t main(std::int32_t count, char *arguments[])
{
	if (count < 2)
	{
		throw std::runtime_error("Too few arguments.");
	}

	std::string address = arguments[1];

	bool running = true;
	
	Movie movie;

	std::unordered_map<std::string, std::unique_ptr<Algorithm>> algorithms;
	algorithms.emplace("Reduce colors", std::make_unique<ReduceColors<64>>());
	algorithms.emplace("Invert colors", std::make_unique<InvertColors>());
	algorithms.emplace("Flip vertically", std::make_unique<FlipVertically>());
	algorithms.emplace("Flip horizontally", std::make_unique<FlipHorizontally>());

	std::unordered_map<std::string, std::unique_ptr<Interpolation>> interpolations;
	interpolations.emplace("Identity", std::make_unique<Identity>());
	interpolations.emplace("Linear", std::make_unique<Linear>());
	interpolations.emplace("Logarithmic", std::make_unique<Logarithmic>());

	std::unique_ptr<Interpolation> defaultInterpolation = std::make_unique<Identity>();

	yami::agent agent;

	std::unordered_map<std::string, std::function<void (yami::incoming_message &)>> callbacks;
	
	callbacks.emplace("upload",	[&](yami::incoming_message &incoming)
								{
									yami::parameters parameters = incoming.get_parameters();
									
									Image image(parameters);
									std::uint16_t timecode = parameters.get_integer("timecode");
									std::string interpolation = parameters.get_string("interpolation");
									
									Frame frame(std::move(image), timecode, interpolation.empty() ? defaultInterpolation : interpolations.at(interpolation));

									auto length = parameters.get_string_array_length("algorithms");

									for (std::ptrdiff_t index = 0; index < length; ++index)
									{
										std::string algorithm = parameters.get_string_in_array("algorithms", index);
										frame.apply(*(algorithms.at(algorithm).get()));
									}

									movie.addFrame(std::move(frame));
 								});

	callbacks.emplace("exists", [&](yami::incoming_message &incoming)
								{
									yami::parameters parameters;
									parameters.set_boolean("exists", movie.exists(incoming.get_parameters().get_integer("timecode")));
									incoming.reply(parameters);
								});

	callbacks.emplace("export", [&](yami::incoming_message &incoming)
								{
									std::string back = incoming.get_source();
									movie.build();
									movie.save(ReplySaver(incoming));
									
								});

	callbacks.emplace("close", [&](yami::incoming_message &)
								{
									running = false;
								});

	callbacks.emplace("algorithms", [&](yami::incoming_message &incoming)
									{
										yami::parameters parameters;
										parameters.create_string_array("algorithms", algorithms.size());
										
										for (auto iterator = algorithms.begin(); iterator != algorithms.end(); ++iterator)
										{
											auto index = std::distance(algorithms.begin(), iterator);
											parameters.set_string_in_array("algorithms", index, iterator->first);
										}

										incoming.reply(parameters);
									});

	callbacks.emplace("interpolations", [&](yami::incoming_message& incoming)
										{
											yami::parameters parameters;
											parameters.create_string_array("interpolations", interpolations.size());

											for (auto iterator = interpolations.begin(); iterator != interpolations.end(); ++iterator)
											{
												auto index = std::distance(interpolations.begin(), iterator);
												parameters.set_string_in_array("interpolations", index, iterator->first);
											}

											incoming.reply(parameters);
										});

	agent.register_object("router", [&](yami::incoming_message &incoming)
									{
										callbacks.at(incoming.get_message_name())(incoming);
									});

	agent.add_listener(address);
	
	while (running)
	{

	}

	return 0;
}