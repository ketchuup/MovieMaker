// Copyright Maciej Sobczak 2008-2019.
// This file is part of YAMI4.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file Boost_Software_License_1_0.txt
// or copy at http://www.opensource.org/licenses/bsl1.0.html)

#ifndef YAMICORE_PARAMETER_ITERATOR_H_INCLUDED
#define YAMICORE_PARAMETER_ITERATOR_H_INCLUDED

#include "core.h"
#include "dll.h"
#include "parameter_entry.h"

namespace yami
{

namespace details
{
class allocator;
struct entry;
} // namespace details

namespace core
{

class parameters;

/// \brief Iterator to parameter entries.
///
/// The iterator to all parameter entries.
/// \sa parameters
///
/// <b>Note:</b> The iterator object can be used only as long as it is valid
/// and every <i>modifying</i> operation on the parameters object should be
/// assumed as invalidating all existing iterators.
class DLL parameter_iterator
{
public:
    /// \brief Checks if there is a subsequent entry.
    ///
    /// Checks if there is a subsequent entry in the associated parameters
    /// object.
    /// @return true if there is some further entry, false otherwise.
    bool has_next() const;

    /// \brief Moves the iterator to the next entry.
    ///
    /// Moves the iterator to the next non-empty entry in the associated
    /// parameters.<br />
    /// This function can be called only when some next entry exists.
    void move_next();

    /// \brief Gets the current entry.
    ///
    /// Gets the current entry.
    parameter_entry current() const;

    /// \brief Removes the current entry.
    ///
    /// Removes the current entry.
    ///
    /// <b>Note:</b> The iterator is not automatically moved
    /// to the next entry after the current one is removed.
    /// The only operations that are allowed after that are
    /// has_next and move_next.
    void remove();

private:
    friend class parameters;

    details::entry * data_;
    std::size_t current_index_;
    std::size_t num_of_entries_;
    details::allocator * allocator_;
};

} // namespace core

} // namespace yami

#endif // YAMICORE_PARAMETER_ITERATOR_H_INCLUDED
