// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_CONNECTION_EVENT_DISPATCHER_BASE_H_INCLUDED
#define YAMICPP_CONNECTION_EVENT_DISPATCHER_BASE_H_INCLUDED

#include "connection_event.h"
#include <yami4-core/dll.h>

#include <string>

namespace yami
{

namespace details
{

class DLL connection_event_dispatcher_base
{
public:
    virtual ~connection_event_dispatcher_base() {}

    virtual void dispatch(
        const std::string & name, connection_event event) = 0;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_CONNECTION_EVENT_DISPATCHER_BASE_H_INCLUDED
