#include "Register.h"

const std::unordered_map<std::string, std::shared_ptr<Algorithm>> allAlgorithms
{
	{ "Invert colors", std::make_shared<InvertColors>() },
	{ "Flip vertically", std::make_shared<FlipVertically>() },
	{ "Flip horizontally", std::make_shared<FlipHorizontally>() },
	{ "Reduce colors", std::make_shared<ReduceColors<64>>() }
};

const std::unordered_map<std::string, std::unique_ptr<Interpolation>> allInterpolations =
[]()
{
	std::unordered_map<std::string, std::unique_ptr<Interpolation>> map;
	
	map.emplace("Linear", std::make_unique<Linear>());
	map.emplace("Identity", std::make_unique<Identity>());
	map.emplace("Logarithmic", std::make_unique<Logarithmic>());

	return map;
}();

const std::unique_ptr<Interpolation> defaultInterpolation = std::make_unique<Identity>();