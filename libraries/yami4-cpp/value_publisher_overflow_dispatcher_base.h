// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_VALUE_PUBLISHER_OVERFLOW_DISPATCHER_BASE_H_INCLUDED
#define YAMICPP_VALUE_PUBLISHER_OVERFLOW_DISPATCHER_BASE_H_INCLUDED

#include "serializable.h"
#include "value_publisher_overflow_action.h"
#include <yami4-core/dll.h>

#include <string>

namespace yami
{

namespace details
{

class DLL value_publisher_overflow_dispatcher_base
{
public:
    virtual ~value_publisher_overflow_dispatcher_base() {}

    virtual value_publisher_overflow_action dispatch(
        const std::string & server_name,
        const std::string & object_name,
        const serializable & value) = 0;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_VALUE_PUBLISHER_OVERFLOW_DISPATCHER_BASE_H_INCLUDED
