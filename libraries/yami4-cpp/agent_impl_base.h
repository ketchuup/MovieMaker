// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_AGENT_IMPL_BASE_H_INCLUDED
#define YAMICPP_AGENT_IMPL_BASE_H_INCLUDED

#include "connection_event_dispatcher_base.h"
#include "incoming_message_dispatcher_base.h"
#include "io_error_dispatcher_base.h"
#include "outgoing_message_dispatcher_base.h"
#include <yami4-core/dll.h>

#include <memory>
#include <string>

namespace yami
{

class serializable;

namespace details
{

class DLL agent_impl_base
{
public:
    virtual ~agent_impl_base() {}

    virtual void register_object(
        const std::string & object_name,
        std::unique_ptr<incoming_message_dispatcher_base> & object) = 0;

    virtual long long send(
        std::unique_ptr<outgoing_message_dispatcher_base> &
            outgoing_message_callback,
        const std::string & target,
        const std::string & object_name,
        const std::string & message_name,
        const serializable & content,
        std::size_t priority,
        bool auto_connect) = 0;

    virtual void register_connection_event_monitor(
        std::unique_ptr<connection_event_dispatcher_base> & monitor) = 0;

    virtual void register_io_error_logger(
        std::unique_ptr<io_error_dispatcher_base> & logger) = 0;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_AGENT_IMPL_BASE_H_INCLUDED
