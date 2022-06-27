// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_CONNECTION_EVENT_GENERIC_DISPATCHER_H_INCLUDED
#define YAMICPP_CONNECTION_EVENT_GENERIC_DISPATCHER_H_INCLUDED

#include "connection_event_dispatcher_base.h"
#include <yami4-core/dll.h>

namespace yami
{

namespace details
{

template <typename functor>
class DLL connection_event_generic_dispatcher
    : public connection_event_dispatcher_base
{
public:
    connection_event_generic_dispatcher(functor & f) : f_(f) {}

    virtual void dispatch(const std::string & name, connection_event event)
    {
        f_(name, event);
    }

private:
    functor & f_;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_CONNECTION_EVENT_GENERIC_DISPATCHER_H_INCLUDED
