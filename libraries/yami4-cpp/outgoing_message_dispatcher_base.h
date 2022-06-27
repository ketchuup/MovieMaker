// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_OUTGOING_MESSAGE_DISPATCHER_BASE_H_INCLUDED
#define YAMICPP_OUTGOING_MESSAGE_DISPATCHER_BASE_H_INCLUDED

#include <yami4-core/dll.h>

namespace yami
{

class outgoing_message;

namespace details
{

class DLL outgoing_message_dispatcher_base
{
public:
    virtual ~outgoing_message_dispatcher_base() {}

    virtual void dispatch(outgoing_message & om) = 0;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_OUTGOING_MESSAGE_DISPATCHER_BASE_H_INCLUDED
