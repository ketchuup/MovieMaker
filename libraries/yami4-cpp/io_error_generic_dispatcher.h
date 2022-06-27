// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_IO_ERROR_GENERIC_DISPATCHER_H_INCLUDED
#define YAMICPP_IO_ERROR_GENERIC_DISPATCHER_H_INCLUDED

#include "connection_event_dispatcher_base.h"

namespace yami
{

namespace details
{

template <typename functor>
class io_error_generic_dispatcher
    : public io_error_dispatcher_base
{
public:
    io_error_generic_dispatcher(functor & f) : f_(f) {}

    virtual void dispatch(int error_code, const char * description)
    {
        f_(error_code, description);
    }

private:
    functor & f_;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_IO_ERROR_GENERIC_DISPATCHER_H_INCLUDED
