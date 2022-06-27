// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_VALUE_PUBLISHER_OVERFLOW_ACTION_H_INCLUDED
#define YAMICPP_VALUE_PUBLISHER_OVERFLOW_ACTION_H_INCLUDED

namespace yami
{

/// User-defined reaction to the overflow condition in value publisher.
enum value_publisher_overflow_action
{
    /// block and wait until previous message is transmitted
    wait_for_previous_message,

    /// abandon the current message and continue with other subscribers
    abandon_message,

    /// abandon the overflowing subscription altogether
    /// and continue with other subscribers
    abandon_subscription
};

} // namespace yami

#endif // YAMICPP_VALUE_PUBLISHER_OVERFLOW_ACTION_H_INCLUDED
