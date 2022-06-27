// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_CHANNEL_DESCRIPTOR_H_INCLUDED
#define YAMICORE_CHANNEL_DESCRIPTOR_H_INCLUDED

#include "dll.h"

#include <cstddef>

namespace yami
{

namespace core
{

/// \brief Descriptor handle for the physical channel.
///
/// The descriptor handle for the physical channel that provides
/// immediate access to the underlying channel object.
///
/// The descriptor provides safe access in the sense that
/// dangling descriptors are recognized and reported.
///
class DLL channel_descriptor
{
public:
    /// \brief Constructor.
    ///
    /// Creates a default descriptor that is not associated with
    /// any existing channel.
    ///
    /// Two default descriptors are considered equal.
    channel_descriptor()
        : index_(0), sequence_number_(0)
    {
    }

    // used internally to create the descriptor that is then
    // returned to the user code
    channel_descriptor(std::size_t index, std::size_t sequence_number)
        : index_(index), sequence_number_(sequence_number)
    {
    }

    // used internally
    void get_details(std::size_t & index, std::size_t & sequence_number) const
    {
        index = index_;
        sequence_number = sequence_number_;
    }

    /// \brief Comparison operator.
    ///
    /// Compares two descriptors for equality.
    /// @return
    ///         - <code>true</code> if the other descriptor points
    ///           to the same physical channel
    ///         - <code>false</code> otherwise
    bool operator==(const channel_descriptor & other) const
    {
        return index_ == other.index_ &&
            sequence_number_ == other.sequence_number_;
    }

    /// \brief Comparison operator.
    ///
    /// Compares two descriptors.
    /// @return Reverse to operator==
    bool operator!=(const channel_descriptor & other) const
    {
        return (*this == other) == false;
    }

private:
    std::size_t index_;
    std::size_t sequence_number_;
};

} // namespace core

} // namespace yami

#endif // YAMICORE_CHANNEL_DESCRIPTOR_H_INCLUDED
