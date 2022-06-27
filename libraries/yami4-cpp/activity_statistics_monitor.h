// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_ACTIVITY_STATISTICS_MONITOR_H_INCLUDED
#define YAMICPP_ACTIVITY_STATISTICS_MONITOR_H_INCLUDED

#include "event_callback.h"
#include <yami4-core/dll.h>

namespace yami
{

class incoming_message;
class parameters;

namespace details
{
class activity_statistics_monitor_impl;
} // namespace details

/// \brief Simple activity statistics monitor.
///
/// This class defines the basic stats monitor that is based on
/// the event notification mechanism. The monitor can also be used for
/// remote inspection of the collected data, as it can directly
/// play the role of regular object that implements the "get" command.
class DLL activity_statistics_monitor : public event_callback
{
public:
    
    activity_statistics_monitor();
    virtual ~activity_statistics_monitor();

    /// \brief Retrieves all collected statistics.
    ///
    /// Retrieves the collected statistics by filling
    /// the given parameters object.
    /// Optional atomic reset of the counters is possible.
    ///
    /// @param params The parameters object to be filled with data.
    /// @param reset_counters Request atomic reset of the counters.
    void get(parameters & params, bool reset_counters = false);

    /// \brief Standard reply to the incoming message.
    ///
    /// Implements the standard reply to the remote "get" command
    /// and replies with a parameters object filled with collected statistics.
    ///
    /// @param msg Incoming message object.
    void operator()(incoming_message & msg);

private:

    virtual void agent_created();
    virtual void agent_closed();
    virtual void listener_added(const char * target);
    virtual void listener_removed(const char * target);
    virtual void incoming_connection_open(const char * target);
    virtual void outgoing_connection_open(const char * target);
    virtual void connection_closed(const char * target);
    virtual void connection_error(const char * target);
    virtual void object_registered(const char * name);
    virtual void object_unregistered(const char * name);
    virtual void message_sent(const char * target, std::size_t size);
    virtual void message_received(const char * target, std::size_t size);
    
    details::activity_statistics_monitor_impl * pimpl_;
};

} // namespace yami

#endif // YAMICPP_ACTIVITY_STATISTICS_MONITOR_H_INCLUDED
