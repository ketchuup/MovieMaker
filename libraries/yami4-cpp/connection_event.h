// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_CONNECTION_EVENT_H_INCLUDED
#define YAMICPP_CONNECTION_EVENT_H_INCLUDED

namespace yami
{

/// Kind of connection event.
enum connection_event
{
    new_incoming_connection, ///< New incoming connection was created.
    new_outgoing_connection, ///< New outgoing connection was created.
    connection_closed        ///< Connection was closed.
};

} // namespace yami

#endif // YAMICPP_CONNECTION_EVENT_H_INCLUDED
