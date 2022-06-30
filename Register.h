#ifndef REGISTER_H
#define REGISTER_H

#include <unordered_map>
#include "ReduceColors.h"
#include "InvertColors.h"
#include "FlipVertically.h"
#include "FlipHorizontally.h"
#include "Linear.h"
#include "Identity.h"
#include "Logarithmic.h"

extern const std::unordered_map<std::string, std::shared_ptr<Algorithm>> allAlgorithms;

extern const std::unordered_map<std::string, std::unique_ptr<Interpolation>> allInterpolations;

extern const std::unique_ptr<Interpolation> defaultInterpolation;

#endif