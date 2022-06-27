// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICPP_IO_ERROR_DISPATCHER_BASE_H_INCLUDED
#define YAMICPP_IO_ERROR_DISPATCHER_BASE_H_INCLUDED

namespace yami
{

namespace details
{

class io_error_dispatcher_base
{
public:
    virtual ~io_error_dispatcher_base() {}

    virtual void dispatch(int error_code, const char * description) = 0;
};

} // namespace details

} // namespace yami

#endif // YAMICPP_IO_ERROR_DISPATCHER_BASE_H_INCLUDED
