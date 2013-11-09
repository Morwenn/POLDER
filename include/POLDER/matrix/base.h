/*
 * Copyright (C) 2011-2013 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_MATRIX_BASE_H
#define _POLDER_MATRIX_BASE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <utility>
#include <POLDER/config.h>
#include <POLDER/index.h>
#include <POLDER/utility.h>

namespace polder
{
    /**
     * @brief Common base for immutable matrices
     *
     * This class defines the methods that ought to
     * be implemented by all of the immutable matrix
     * classes and uses static polymorphism to provide
     * a common interface to all of them.
     *
     * This mutable/immutable design forces accessors
     * to return results by value instead of returning
     * them by const reference. Generally speaking, the
     * objects contained in a Matrix are small enough
     * not to see any performance difference.
     */
    template<typename Derived>
    struct ImmutableMatrix
    {
        /**
         * Used to call the functions from the derived
         * class instead of the ones from this base
         * class.
         *
         * @return *this converted to const Derived&.
         */
        auto derived() const
            -> const Derived&;

        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////

        // Sizes
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        // Value
        using value_type = typename types_t<Derived>::value_type;
        using reference = typename types_t<Derived>::reference;
        using const_reference = typename types_t<Derived>::const_reference;
        using pointer = typename types_t<Derived>::pointer;
        using const_pointer = typename types_t<Derived>::const_pointer;

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        auto operator()(size_type y, size_type x) const
            -> value_type;

        auto operator[](const index<2>& index) const
            -> value_type;

        ////////////////////////////////////////////////////////////
        // STL-like functions
        ////////////////////////////////////////////////////////////

        // Accessors
        auto at(size_type y, size_type x) const
            -> value_type;

        // Capacity
        auto size() const
            -> size_type;

        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        // Capacity
        auto height() const
            -> size_type;
        auto width() const
            -> size_type;
        auto dimensions() const
            -> std::pair<size_type, size_type>;

        // Properties
        auto is_square() const
            -> bool;
    };

    /**
     * @brief Common base for mutable matrices
     *
     * This class defines the methods that ought to
     * be implemented by all of the mutable matrix
     * classes and uses static polymorphism to provide
     * a common interface to all of them.
     *
     * Mutable matrices implement all the functions
     * that ought to be implement in immutable
     * matrices and also provide some other functions
     * or non-const overloads for some functions.
     */
    template<typename Derived>
    struct MutableMatrix:
        ImmutableMatrix<Derived>
    {
        /**
         * Used to call the functions from the derived
         * class instead of the ones from this base
         * class.
         *
         * @return *this converted to Derived&.
         */
        auto derived()
            -> Derived&;

        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////

        using super = ImmutableMatrix<Derived>;

        // Sizes
        using typename super::size_type;
        using typename super::difference_type;
        // Value
        using typename super::value_type;
        using typename super::reference;
        using typename super::const_reference;
        using typename super::pointer;
        using typename super::const_pointer;

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        auto operator()(size_type y, size_type x)
            -> reference;

        auto operator[](const index<2>& index)
            -> reference;

        ////////////////////////////////////////////////////////////
        // STL-like functions
        ////////////////////////////////////////////////////////////

        // Accessors
        auto at(size_type y, size_type x)
            -> reference;

        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        // Capacity
        using super::height;
        using super::width;

        // Properties
        using super::is_square;
    };

    #include "base.inl"
}

#endif // _POLDER_MATRIX_BASE_H
