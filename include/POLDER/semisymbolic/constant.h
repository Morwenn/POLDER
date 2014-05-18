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
#include <POLDER/details/config.h>
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
        template<char... Digits>
        constexpr auto operator"" _c()
            -> Constant<
                int,
                details::parse<int>(Digits-'0'...)
            >;

        template<char... Digits>
        constexpr auto operator"" _cl()
            -> Constant<
                long,
                details::parse<long>(Digits-'0'...)
            >;

        template<char... Digits>
        constexpr auto operator"" _cll()
            -> Constant<
                long long,
                details::parse<long long>(Digits-'0'...)
            >;

        template<char... Digits>
        constexpr auto operator"" _cu()
            -> Constant<
                unsigned,
                details::parse<unsigned>(Digits-'0'...)
            >;

        template<char... Digits>
        constexpr auto operator"" _cul()
            -> Constant<
                unsigned long,
                details::parse<unsigned long>(Digits-'0'...)
            >;

        template<char... Digits>
        constexpr auto operator"" _cull()
            -> Constant<
                unsigned long long,
                details::parse<unsigned long long>(Digits-'0'...)
            >;
    }

    #include "details/constant.inl"
}}

namespace std
{
    template<typename Int, Int N>
    class numeric_limits<polder::semisymbolic::Constant<Int, N>>:
        public std::numeric_limits<Int>
    {};
}

#endif // POLDER_SEMISYMBOLIC_CONSTANT_H_
