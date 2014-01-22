/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef _POLDER_GRAY_H
#define _POLDER_GRAY_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>
#include <POLDER/config.h>

namespace polder
{
    /**
     * @brief Gray code unsigned integer
     *
     * This class represents a gray code unsigned
     * integer. It can be set by integers
     *
     * auto gr = GrayCode<uint16_t>{ 24 };
     * uint16_t u = gr;         // u == 24 (0b11000)
     * uint16_t g = gr.value;   // g == 20 (0b10100)
     */
    template<typename Unsigned>
    struct GrayCode
    {
        static_assert(std::is_unsigned<Unsigned>::value,
                      "gray code only supports unsigned integers");

        // Type
        using value_type = Unsigned;

        // Variable containing the gray code
        value_type value;

        ////////////////////////////////////////////////////////////
        // Constructors/destructor
        ////////////////////////////////////////////////////////////

        // Standard Constructors/destructor
        constexpr GrayCode();
        constexpr GrayCode(const GrayCode&);
        constexpr GrayCode(GrayCode&&);

        /**
         * @brief Construction from an unsigned integer
         *
         * The integer is converted to gray code. The value
         * is preserved. The representation is not.
         *
         * @param value Unsigned integer to convert
         */
        constexpr explicit GrayCode(value_type value);

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Assignment operators
        auto operator=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
        auto operator=(GrayCode<Unsigned>&& other)
            -> GrayCode&;

        /**
         * @brief Assigns an unsigned integer
         *
         * It works the same way as the equivalent
         * constructor does.
         */
        auto operator=(value_type other)
            -> GrayCode&;

        /**
         * @brief Conversion to the representing type
         */
        operator value_type() const;

        ////////////////////////////////////////////////////////////
        // Arithmetic operations
        ////////////////////////////////////////////////////////////

        auto operator++()
            -> GrayCode&;
        auto operator++(int)
            -> GrayCode&;

        auto operator--()
            -> GrayCode&;
        auto operator--(int)
            -> GrayCode&;

        ////////////////////////////////////////////////////////////
        // Bitwise operations
        ////////////////////////////////////////////////////////////

        auto operator&=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
        auto operator|=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
        auto operator^=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
        auto operator>>=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
        auto operator<<=(const GrayCode<Unsigned>& other)
            -> GrayCode&;
    };

    /**
     * @brief Create a GrayCode instance.
     *
     * @param value Unsigned integer to convert to gay code
     */
    template<typename Unsigned>
    constexpr auto gray(Unsigned value)
        -> GrayCode<Unsigned>;

    ////////////////////////////////////////////////////////////
    // Comparison operators
    ////////////////////////////////////////////////////////////

    template<typename Unsigned>
    constexpr auto operator==(const GrayCode<Unsigned>& lhs, const GrayCode<Unsigned>& rhs)
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(const GrayCode<Unsigned>& lhs, const GrayCode<Unsigned>& rhs)
        -> bool;

    template<typename Unsigned>
    constexpr auto operator==(const GrayCode<Unsigned>& lhs, Unsigned rhs)
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(const GrayCode<Unsigned>& lhs, Unsigned rhs)
        -> bool;

    template<typename Unsigned>
    constexpr auto operator==(Unsigned lhs, const GrayCode<Unsigned>& rhs)
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(Unsigned lhs, const GrayCode<Unsigned>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Bitwise operations
    ////////////////////////////////////////////////////////////

    template<typename Unsigned>
    auto operator&(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
        -> GrayCode<Unsigned>;

    template<typename Unsigned>
    auto operator|(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
        -> GrayCode<Unsigned>;

    template<typename Unsigned>
    auto operator^(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
        -> GrayCode<Unsigned>;

    template<typename Unsigned>
    auto operator>>(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
        -> GrayCode<Unsigned>;

    template<typename Unsigned>
    auto operator<<(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
        -> GrayCode<Unsigned>;

    ////////////////////////////////////////////////////////////
    // Overloaded math functions
    ////////////////////////////////////////////////////////////

    namespace math
    {
        template<typename Unsigned>
        auto is_even(const GrayCode<Unsigned>& code)
            -> bool;

        template<typename Unsigned>
        auto is_odd(const GrayCode<Unsigned>& code)
            -> bool;
    }

    #include "gray.inl"
}

#endif // _POLDER_GRAY_H
