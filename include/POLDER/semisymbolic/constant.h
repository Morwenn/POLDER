/*
 * Copyright (C) 2014 Morwenn
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
#ifndef POLDER_SEMISYMBOLIC_CONSTANT_H_
#define POLDER_SEMISYMBOLIC_CONSTANT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <limits>
#include <type_traits>
#include <POLDER/utility.h>
#include <POLDER/semisymbolic/details/parse.h>

namespace polder
{
namespace semisymbolic
{
    ////////////////////////////////////////////////////////////
    // Constant

    template<typename Int, Int N>
    struct Constant:
        std::integral_constant<Int, N>
    {};

    ////////////////////////////////////////////////////////////
    // Unary arithmetic operators

    template<typename Int, Int N>
    constexpr auto operator+(Constant<Int, N> con)
        -> Constant<Int, N>;

    template<typename Int, Int N>
    constexpr auto operator-(Constant<Int, N> con)
        -> Constant<Int, -N>;

    ////////////////////////////////////////////////////////////
    // Binary arithmetic operators

    template<typename Int, Int N, Int M>
    constexpr auto operator+(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<Int, N+M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator-(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<Int, N-M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator*(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<Int, N*M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator/(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<Int, N/M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator%(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<Int, N%M>;

    ////////////////////////////////////////////////////////////
    // Equality operators

    template<typename Int, Int N, Int M>
    constexpr auto operator==(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, N==M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator!=(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, N!=M>;

    ////////////////////////////////////////////////////////////
    // Relational operators

    template<typename Int, Int N, Int M>
    constexpr auto operator<(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, N<M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator<=(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, N<=M>;

    template<typename Int, Int N, Int M>
    constexpr auto operator>(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, (N>M)>;

    template<typename Int, Int N, Int M>
    constexpr auto operator>=(Constant<Int, N> lhs, Constant<Int, M> rhs)
        -> Constant<bool, N>=M>;

    ////////////////////////////////////////////////////////////
    // User-defined literals

    inline namespace literals
    {
    inline namespace constant_literals
    {
        template<char... Digits>
        constexpr auto operator"" _c()
            -> Constant<
                details::parse_t<int, Digits...>,
                details::parse<int, Digits...>::value
            >;

        template<char... Digits>
        constexpr auto operator"" _cl()
            -> Constant<
                details::parse_t<long, Digits...>,
                details::parse<long, Digits...>::value
            >;

        template<char... Digits>
        constexpr auto operator"" _cll()
            -> Constant<
                details::parse_t<long long, Digits...>,
                details::parse<long long, Digits...>::value
            >;

        template<char... Digits>
        constexpr auto operator"" _cu()
            -> Constant<
                details::parse_t<unsigned, Digits...>,
                details::parse<unsigned, Digits...>::value
            >;

        template<char... Digits>
        constexpr auto operator"" _cul()
            -> Constant<
                details::parse_t<unsigned long, Digits...>,
                details::parse<unsigned long, Digits...>::value
            >;

        template<char... Digits>
        constexpr auto operator"" _cull()
            -> Constant<
                details::parse_t<unsigned long long, Digits...>,
                details::parse<unsigned long long, Digits...>::value
            >;
    }}

    ////////////////////////////////////////////////////////////
    // Alias templates

    using True  = Constant<bool, true>;
    using False = Constant<bool, false>;

    #include "details/constant.inl"
}}

namespace std
{
    ////////////////////////////////////////////////////////////
    // Numeric limits

    template<typename Int, Int N>
    class numeric_limits<polder::semisymbolic::Constant<Int, N>>:
        public std::numeric_limits<Int>
    {};
}

namespace polder
{
    ////////////////////////////////////////////////////////////
    // CRTP value_type propagation

    template<typename Int, Int N>
    struct types_t<semisymbolic::Constant<Int, N>>
    {
        using value_type = Int;
    };
}

#include "details/constant_cmath.h"

#endif // POLDER_SEMISYMBOLIC_CONSTANT_H_
