// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_INCOMING_MESSAGE_GENERIC_DISPATCHER_H_INCLUDED
#define YAMICPP_INCOMING_MESSAGE_GENERIC_DISPATCHER_H_INCLUDED

#include "incoming_message_dispatcher_base.h"
#include <yami4-core/dll.h>
#include <string>

namespace yami
{

class incoming_message;

namespace details
{

template <typename functor>
class DLL incoming_message_generic_dispatcher
    : public incoming_message_dispatcher_base
{
public:
    incoming_message_generic_dispatcher(functor & f) : f_(f) {}

    virtual void dispatch(incoming_message & im)
    {
        f_(im);
    }

private:
    functor & f_;
};

class DLL incoming_message_raw_dispatcher
    : public incoming_message_dispatcher_base
{
public:
    incoming_message_raw_dispatcher(
        void (* callback)(incoming_message & im, void * hint), void * hint)
        : callback_(callback),
        hint_(hint)
    {
    }

    virtual void dispatch(incoming_message & im)
    {
        callback_(im, hint_);
    }

private:
    void (* callback_)(incoming_message & im, void * hint);
     void * hint_;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_INCOMING_MESSAGE_GENERIC_DISPATCHER_H_INCLUDED
