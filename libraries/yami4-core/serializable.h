// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_SERIALIZABLE_H_INCLUDED
#define YAMICORE_SERIALIZABLE_H_INCLUDED

#include "core.h"
#include "dll.h"

namespace yami
{

namespace core
{

/// \brief Common interface for serializable data source.
///
/// Serializable data source allows to fill the given set up buffers
/// with binary data that corresponds to the actual data source content.
/// The purpose of this interface is to allow uniform treatment of
/// parameters objects with wrapped raw binary buffers.
class DLL serializable
{
public:

    /// \brief Finds the total size of serialization buffer.
    ///
    /// Computes the total size of serialization buffer(s) for the current
    /// content of this object.
    /// @param size The computed size of buffer.
    /// @return
    ///         - <code>ok</code> if operation was successful
    ///         - <code>nesting_too_deep</code> if the level of nesting
    ///           in this object is deeper than the limit
    virtual result get_serialize_buffer_size(std::size_t & size) const = 0;

    /// \brief Serializes current content into given buffer(s).
    ///
    /// Serializes the current content of this object into the given
    /// buffer(s).
    /// The serialization buffer does not have to be contiguous and any number
    /// of buffer segments is allowed, provided that the size of each buffer
    /// segment is a multiple of 4 (32 bits).<br />
    /// The function scatters the serialized data into subsequent buffers
    /// as they become filled.<br />
    /// The buffers are provided as array of buffer pointers and their sizes.
    /// @param buffers Pointer to the array of buffer pointers
    ///        (each of type <code>char *</code>).
    /// @param buffer_sizes Pointer to the array of buffer sizes.
    /// @param num_of_buffers Number of buffers described by the array.
    /// @return
    ///         - <code>ok</code> if operation was successful
    ///         - <code>not_enough_space</code> if the buffers are not
    ///           big enough for all the data
    ///         - other relevant error code, depending on implementation
    virtual result serialize(char * * buffers,
        const std::size_t * buffer_sizes,
        std::size_t num_of_buffers) const = 0;

    virtual ~serializable() {}
};

} // namespace core

} // namespace yami

#endif // YAMICORE_SERIALIZABLE_H_INCLUDED
