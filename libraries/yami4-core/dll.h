// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_DLL_H_INCLUDED
#define YAMICORE_DLL_H_INCLUDED

#ifdef _WIN32
#  ifdef YAMI4_DLL_COMPILATION
#    define DLL __declspec(dllexport)
#  endif // YAMI4_DLL_COMPILATION
#  ifdef YAMI4_USE_AS_DLL
#    define DLL __declspec(dllimport)
#  endif // YAMI4_USE_AS_DLL
#endif // _WIN32

#ifndef DLL
#  define DLL
#endif // DLL

#endif // YAMICORE_DLL_H_INCLUDED
