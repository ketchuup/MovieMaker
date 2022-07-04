#include "Register.h"

const std::unordered_map<std::string, std::function<std::unique_ptr<Algorithm>()>> allAlgorithmCreators
{
	{ "Invert colors", []() { return std::make_unique<InvertColors>(); } },
	{ "Reduce colors", []() { return std::make_unique<ReduceColors<64>>(); } },
	{ "Flip vertically", []() { return std::make_unique<FlipVertically>(); } },
	{ "Flip horizontally", []() { return std::make_unique<FlipHorizontally>(); } }
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