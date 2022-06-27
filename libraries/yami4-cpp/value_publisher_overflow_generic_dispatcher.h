// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_VALUE_PUBLISHER_OVERFLOW_GENERIC_DISPATCHER_H_INCLUDED
#define YAMICPP_VALUE_PUBLISHER_OVERFLOW_GENERIC_DISPATCHER_H_INCLUDED

#include "value_publisher_overflow_dispatcher_base.h"
#include <yami4-core/dll.h>

namespace yami
{

namespace details
{

template <typename functor>
class DLL value_publisher_overflow_generic_dispatcher
    : public value_publisher_overflow_dispatcher_base
{
public:
    value_publisher_overflow_generic_dispatcher(functor & f) : f_(f) {}

    virtual value_publisher_overflow_action dispatch(
        const std::string & server_name,
        const std::string & object_name,
        const serializable & value)
    {
        return f_(server_name, object_name, value);
    }

private:
    functor & f_;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_VALUE_PUBLISHER_OVERFLOW_GENERIC_DISPATCHER_H_INCLUDED
