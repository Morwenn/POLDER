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
#ifndef POLDER_GRAY_H_
#define POLDER_GRAY_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <limits>
#include <type_traits>
#include <POLDER/details/config.h>

namespace polder
{
    /**
     * @brief Gray code unsigned integer.
     *
     * This class represents a gray code unsigned
     * integer. It can be set by integers.
     *
     * auto gr = gray_code<uint16_t>{ 24 };
     * uint16_t u = gr;         // u == 24 (0b11000)
     * uint16_t g = gr.value;   // g == 20 (0b10100)
     */
    template<typename Unsigned>
    struct gray_code
    {
        static_assert(std::is_unsigned<Unsigned>::value,
                      "gray code only supports built-in unsigned integers");

        // Underlying unsigned integer
        using value_type = Unsigned;

        // Variable containing the gray code
        value_type value;

        ////////////////////////////////////////////////////////////
        // Constructors operations

        // Default constructor
        constexpr gray_code() noexcept;

        /**
         * @brief Construction from an unsigned integer.
         *
         * The integer is converted to gray code. The value
         * is preserved. The representation is not.
         *
         * @param value Unsigned integer to convert
         */
        constexpr explicit gray_code(value_type value) noexcept;

        ////////////////////////////////////////////////////////////
        // Assignment operations

        /**
         * @brief Assigns an unsigned integer.
         *
         * It works the same way as the equivalent
         * constructor does.
         */
        auto operator=(value_type other) & noexcept
            -> gray_code&;

        ////////////////////////////////////////////////////////////
        // Conversion operations

        /**
         * @brief Conversion to the underlying type.
         */
        explicit operator value_type() const noexcept;

        ////////////////////////////////////////////////////////////
        // Increment/decrement operations

        auto operator++() noexcept
            -> gray_code&;
        auto operator++(int) noexcept
            -> gray_code;

        auto operator--() noexcept
            -> gray_code&;
        auto operator--(int) noexcept
            -> gray_code;

        ////////////////////////////////////////////////////////////
        // Bitwise assignment operations

        auto operator&=(gray_code other) noexcept
            -> gray_code&;
        auto operator&=(value_type other) noexcept
            -> gray_code&;

        auto operator|=(gray_code other) noexcept
            -> gray_code&;
        auto operator|=(value_type other) noexcept
            -> gray_code&;

        auto operator^=(gray_code other) noexcept
            -> gray_code&;
        auto operator^=(value_type other) noexcept
            -> gray_code&;

        auto operator>>=(std::size_t pos) noexcept
            -> gray_code&;
        auto operator<<=(std::size_t pos) noexcept
            -> gray_code&;
    };

    /**
     * @brief Creates a gray_code instance.
     *
     * The advantage of this function is its ability to
     * deduce the type of its parameter.
     *
     * @param value Unsigned integer to convert to gray code.
     */
    template<typename Unsigned>
    constexpr auto gray(Unsigned value) noexcept
        -> gray_code<Unsigned>;

    ////////////////////////////////////////////////////////////
    // Comparison operations

    template<typename Unsigned>
    constexpr auto operator==(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> bool;

    template<typename Unsigned>
    constexpr auto operator==(gray_code<Unsigned> lhs, Unsigned rhs) noexcept
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(gray_code<Unsigned> lhs, Unsigned rhs) noexcept
        -> bool;

    template<typename Unsigned>
    constexpr auto operator==(Unsigned lhs, gray_code<Unsigned> rhs) noexcept
        -> bool;
    template<typename Unsigned>
    constexpr auto operator!=(Unsigned lhs, gray_code<Unsigned> rhs) noexcept
        -> bool;

    ////////////////////////////////////////////////////////////
    // Arithmetic operations

    template<typename Unsigned>
    auto operator+(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> gray_code<Unsigned>;

    ////////////////////////////////////////////////////////////
    // Bitwise operations

    template<typename Unsigned>
    auto operator&(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> gray_code<Unsigned>;

    template<typename Unsigned>
    auto operator|(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> gray_code<Unsigned>;

    template<typename Unsigned>
    auto operator^(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
        -> gray_code<Unsigned>;

    template<typename Unsigned>
    auto operator~(gray_code<Unsigned> val) noexcept
        -> gray_code<Unsigned>;

    template<typename Unsigned>
    auto operator>>(gray_code<Unsigned> val, std::size_t pos) noexcept
        -> gray_code<Unsigned>;

    template<typename Unsigned>
    auto operator<<(gray_code<Unsigned> val, std::size_t pos) noexcept
        -> gray_code<Unsigned>;

    ////////////////////////////////////////////////////////////
    // Bitwise assignment operations

    template<typename Unsigned>
    auto operator&=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
        -> Unsigned&;

    template<typename Unsigned>
    auto operator|=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
        -> Unsigned&;

    template<typename Unsigned>
    auto operator^=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
        -> Unsigned&;

    ////////////////////////////////////////////////////////////
    // Mathematical functions

    template<typename Unsigned>
    auto is_even(gray_code<Unsigned> code) noexcept
        -> bool;

    template<typename Unsigned>
    auto is_odd(gray_code<Unsigned> code) noexcept
        -> bool;

    #include "details/gray.inl"
}

#endif // POLDER_GRAY_H_
