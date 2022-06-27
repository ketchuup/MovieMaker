// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_ALLOCATOR_H_INCLUDED
#define YAMICORE_ALLOCATOR_H_INCLUDED

#include "dll.h"

#include <cstddef>

namespace yami
{

namespace details
{

class DLL allocator
{
public:
    allocator();

    void set_working_area(void * buf, std::size_t size);

    void * allocate(std::size_t requested_size);

    void deallocate(const void * p);

    void get_free_size(std::size_t & biggest, std::size_t & all) const;

private:
    allocator(const allocator &);
    void operator=(const allocator &);

    void * base_;
    std::size_t size_;

    void * first_free_segment_;
};

} // namespace details

} // namespace yami

#endif // YAMICORE_ALLOCATOR_H_INCLUDED
