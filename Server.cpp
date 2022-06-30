#include <unordered_map>
#include <yami4-cpp/yami.h>
#include "Movie.h"
#include "ReplySaver.h"
#include "NetworkUtilities.h"
#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipVertically.h"
#include "FlipHorizontally.h"
#include "Identity.h"
#include "Linear.h"
#include "Logarithmic.h"

std::int32_t main(std::int32_t count, char *arguments[])
{
	if (count < 2)
	{
		throw std::runtime_error("Too few arguments.");
	}

	std::string address = arguments[1];

	bool running = true;
	
	Movie movie;
	std::vector<std::future<void>> futures;

	std::unordered_map<std::string, std::shared_ptr<Algorithm>> algorithms;
	algorithms.emplace("Reduce colors", std::make_shared<ReduceColors<64>>());
	algorithms.emplace("Invert colors", std::make_shared<InvertColors>());
	algorithms.emplace("Flip vertically", std::make_shared<FlipVertically>());
	algorithms.emplace("Flip horizontally", std::make_shared<FlipHorizontally>());

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
									
									std::unique_ptr<Image> image = std::make_unique<Image>(parameters);
									std::uint16_t timecode = parameters.get_integer("timecode");
									std::string interpolation = parameters.get_string("interpolation");
									
									Frame frame(std::move(image), timecode, interpolation.empty() ? defaultInterpolation : interpolations.at(interpolation));

									auto length = parameters.get_string_array_length("algorithms");
									std::vector<std::shared_ptr<Algorithm>> unapplied;

									for (std::ptrdiff_t index = 0; index < length; ++index)
									{
										std::string algorithm = parameters.get_string_in_array("algorithms", index);
										unapplied.push_back(algorithms.at(algorithm));
									}

									std::future future = frame.apply(std::move(unapplied));
									futures.emplace_back(std::move(future));

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

									for (auto &future : futures)
									{
										future.wait();
									}

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
										
										attachStringKeysToParameters("algorithms", algorithms, parameters);

										incoming.reply(parameters);
									});

	callbacks.emplace("interpolations", [&](yami::incoming_message& incoming)
										{
											yami::parameters parameters;

											attachStringKeysToParameters("interpolations", interpolations, parameters);

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