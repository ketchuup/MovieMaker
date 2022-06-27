// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_MESSAGE_STATE_H_INCLUDED
#define YAMICPP_MESSAGE_STATE_H_INCLUDED

namespace yami
{

/// Outgoing message state.
enum message_state
{
    posted,      ///< Message was posted for transmission.
    transmitted, ///< Message was fully transmitted.
    abandoned,   ///< Message was abandoned due to error or channel closing.
    replied,     ///< The reply was received for the given message.
    rejected     ///< Message was rejected.
};

} // namespace yami

#endif // YAMICPP_MESSAGE_STATE_H_INCLUDED
