// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_PARAMETER_TYPE_H_INCLUDED
#define YAMICORE_PARAMETER_TYPE_H_INCLUDED

namespace yami
{

namespace core
{

/// Type of parameter entry.
enum parameter_type
{
    unused,                 ///< Internal mark for unused slots
    boolean,                ///< bool
    integer,                ///< int
    long_long,              ///< long long
    double_float,           ///< double
    string,                 ///< string
    binary,                 ///< Binary block
    boolean_array,          ///< Array of bool
    integer_array,          ///< Array of int
    long_long_array,        ///< Array of long long
    double_float_array,     ///< Array of double
    string_array,           ///< Array of strings
    binary_array,           ///< Array of binary blocks
    nested_parameters,      ///< Nested parameters object
    nested_parameters_array ///< Array of nested parameters object
};

} // namespace core

} // namespace yami

#endif // YAMICORE_PARAMETER_TYPE_H_INCLUDED
