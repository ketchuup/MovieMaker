// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_FATAL_ERRORS_H_INCLUDED
#define YAMICORE_FATAL_ERRORS_H_INCLUDED

#include "dll.h"

namespace yami
{

namespace core
{

/// Type of function callback for reporting internal fatal errors.
///
/// Note: This function is supposed to be a customization point for
/// reporting assertion errors; even if this function returns,
/// the code calling it will abort immediately after that.
/// The default handler prints the message on standard error channel.
///
/// @param source_file Name of the source file where the error occured.
/// @param line_number Line number of the place where assertion failed.
extern "C" typedef void (*fatal_error_function)(
    const char * source_file, int line_number);

/// Registers the custom handler for reporting fatal errors.
///
/// Note: this function is not thread-safe and should be called (if at all)
/// before any agent is initialized.
DLL void register_fatal_error_handler(fatal_error_function handler);

} // namespace core

namespace details
{

DLL void fatal_failure(const char * source_file, int line_number);

} // namespace details

} // namespace yami

#endif // YAMICORE_FATAL_ERRORS_H_INCLUDED
