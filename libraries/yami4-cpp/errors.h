// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_ERRORS_H_INCLUDED
#define YAMICPP_ERRORS_H_INCLUDED

#include <yami4-core/dll.h>
#include <string>
#include <stdexcept>

namespace yami
{

/// \brief General exception class for reporting logic errors.
///
/// General exception class for reporting logic errors.
///
/// Logic errors represent misuses of the API
/// like invalid arguments, out of range indexes or type mismatches.
class DLL yami_logic_error : public std::logic_error
{
public:
    explicit yami_logic_error(const std::string & message)
    : std::logic_error(message)
    {
    }
};

/// \brief General exception class for reporting run-time errors.
///
/// General exception class for reporting run-time errors.
///
/// Runtime errors represent problems that might not result
/// from incorrect library usage, but can be related to resource constraints
/// or communication problems.
class DLL yami_runtime_error : public std::runtime_error
{
public:
    explicit yami_runtime_error(const std::string & message)
    : std::runtime_error(message)
    {
    }
};

} // namespace yami

#endif // YAMICPP_ERRORS_H_INCLUDED
