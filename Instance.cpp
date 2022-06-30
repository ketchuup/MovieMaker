#include "Instance.h"

Instance::Instance(yami::agent &agent) : agent(agent)
{
}

void Instance::handle(yami::incoming_message &incoming)
{
	std::unique_ptr<yami::incoming_message> pointer = std::make_unique<yami::incoming_message>(incoming);

	std::future<void> current = std::async(	[](std::future<void> previous, Instance *instance, std::unique_ptr<yami::incoming_message> incoming)
											{
												std::unique_ptr<yami::incoming_message> moved = std::move(incoming);
												
												if (previous.valid())
												{
													previous.wait();
												}

												auto &callback = Instance::callbacks.at(moved->get_message_name());
												callback(instance, *moved);
											}, std::move(previous), this, std::move(pointer));

	previous = std::move(current);
}

void Instance::upload(yami::incoming_message &incoming)
{
	yami::parameters parameters = incoming.get_parameters();

	std::unique_ptr<Image> image = std::make_unique<Image>(parameters);
	std::uint16_t timecode = parameters.get_integer("timecode");
	std::string interpolation = parameters.get_string("interpolation");

	Frame frame(std::move(image), timecode, interpolation.empty() ? defaultInterpolation : allInterpolations.at(interpolation));

	auto length = parameters.get_string_array_length("algorithms");
	std::vector<std::shared_ptr<Algorithm>> unapplied;

	for (std::ptrdiff_t index = 0; index < length; ++index)
	{
		std::string algorithm = parameters.get_string_in_array("algorithms", index);
		unapplied.push_back(allAlgorithms.at(algorithm));
	}

	std::future future = frame.apply(std::move(unapplied));
	futures.emplace_back(std::move(future));

	movie.addFrame(std::move(frame));
}

void Instance::exists(yami::incoming_message &incoming)
{
	yami::parameters parameters;
	parameters.set_boolean("exists", movie.exists(incoming.get_parameters().get_integer("timecode")));
	incoming.reply(parameters);
}

void Instance::export_(yami::incoming_message &incoming)
{
	for (auto &future : futures)
	{
		future.wait();
	}

	movie.build();

	movie.save(ReplySaver(incoming));
}

void Instance::algorithms(yami::incoming_message &incoming)
{
	yami::parameters parameters;
	attachStringKeysToParameters("algorithms", allAlgorithms, parameters);
	incoming.reply(parameters);
}

void Instance::interpolations(yami::incoming_message &incoming)
{
	yami::parameters parameters;
	attachStringKeysToParameters("interpolations", allInterpolations, parameters);
	incoming.reply(parameters);
}

const std::unordered_map<std::string, std::function<void (Instance *, yami::incoming_message &)>> Instance::callbacks
{
	{ "upload", &Instance::upload },
	{ "exists", &Instance::exists },
	{ "export", &Instance::export_ },
	{ "algorithms", &Instance::algorithms },
	{ "interpolations", &Instance::interpolations }
};