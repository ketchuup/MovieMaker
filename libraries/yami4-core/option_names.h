// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_OPTION_NAMES_H_INCLUDED
#define YAMICORE_OPTION_NAMES_H_INCLUDED

#include "dll.h"

namespace yami
{

namespace core
{

namespace option_names
{

DLL const char tcp_listen_backlog[] =   "tcp_listen_backlog";
DLL const char tcp_reuseaddr[] =        "tcp_reuseaddr";
DLL const char tcp_nonblocking[] =      "tcp_nonblocking";
DLL const char tcp_connect_timeout[] =  "tcp_connect_timeout";
DLL const char tcp_nodelay[] =          "tcp_nodelay";
DLL const char tcp_keepalive[] =        "tcp_keepalive";
DLL const char tcp_frame_size[] =       "tcp_frame_size";
DLL const char udp_frame_size[] =       "udp_frame_size";
DLL const char unix_listen_backlog[] =  "unix_listen_backlog";
DLL const char unix_nonblocking[] =     "unix_nonblocking";
DLL const char unix_frame_size[] =      "unix_frame_size";
DLL const char file_nonblocking[] =     "file_nonblocking";
DLL const char file_frame_size[] =      "file_frame_size";

#ifdef YAMI4_WITH_QNX
DLL const char qnx_frame_size[] =       "qnx_frame_size";
#endif // YAMI4_WITH_QNX

#ifdef YAMI4_WITH_OPEN_SSL
DLL const char ssl_certificate_file[] = "ssl_certificate_file";
DLL const char ssl_private_key_file[] = "ssl_private_key_file";
#endif // YAMI4_WITH_OPEN_SSL

} // namespace option_names

} // namespace core

} // namespace yami

#endif // YAMICORE_OPTION_NAMES_H_INCLUDED
