// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_VERSION_H_INCLUDED
#define YAMICPP_VERSION_H_INCLUDED

#include <yami4-core/dll.h>

namespace yami
{

/// Library version name.
extern DLL const char * const version_name;

/// Library version number (X * 10000 + Y * 100 + Z).
extern DLL const int version_number;

} // namespace yami

#endif // YAMICPP_VERSION_H_INCLUDED
