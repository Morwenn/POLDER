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

////////////////////////////////////////////////////////////
// Unary arithmetic operators

template<typename Int, Int N>
constexpr auto operator+(Constant<Int, N>)
    -> Constant<Int, N>
{
    return {};
}

template<typename Int, Int N>
constexpr auto operator-(Constant<Int, N>)
    -> Constant<Int, -N>
{
    return {};
}

////////////////////////////////////////////////////////////
// Binary arithmetic operators

template<typename Int, Int N, Int M>
constexpr auto operator+(Constant<Int, N>, Constant<Int, M>)
    -> Constant<Int, N+M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator-(Constant<Int, N>, Constant<Int, M>)
    -> Constant<Int, N-M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator*(Constant<Int, N>, Constant<Int, M>)
    -> Constant<Int, N*M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator/(Constant<Int, N>, Constant<Int, M>)
    -> Constant<Int, N/M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator%(Constant<Int, N>, Constant<Int, M>)
    -> Constant<Int, N%M>
{
    return {};
}

////////////////////////////////////////////////////////////
// Equality operators

template<typename Int, Int N, Int M>
constexpr auto operator==(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, N==M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator!=(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, N!=M>
{
    return {};
}

////////////////////////////////////////////////////////////
// Relational operators

template<typename Int, Int N, Int M>
constexpr auto operator<(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, N<M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator<=(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, N<=M>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator>(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, (N>M)>
{
    return {};
}

template<typename Int, Int N, Int M>
constexpr auto operator>=(Constant<Int, N>, Constant<Int, M>)
    -> Constant<bool, N>=M>
{
    return {};
}

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
        >
    {
        return {};
    }

    template<char... Digits>
    constexpr auto operator"" _cl()
        -> Constant<
            details::parse_t<long, Digits...>,
            details::parse<long, Digits...>::value
        >
    {
        return {};
    }

    template<char... Digits>
    constexpr auto operator"" _cll()
        -> Constant<
            details::parse_t<long long, Digits...>,
            details::parse<long long, Digits...>::value
        >
    {
        return {};
    }

    template<char... Digits>
    constexpr auto operator"" _cu()
        -> Constant<
            details::parse_t<unsigned, Digits...>,
            details::parse<unsigned, Digits...>::value
        >
    {
        return {};
    }

    template<char... Digits>
    constexpr auto operator"" _cul()
        -> Constant<
            details::parse_t<unsigned long, Digits...>,
            details::parse<unsigned long, Digits...>::value
        >
    {
        return {};
    }

    template<char... Digits>
    constexpr auto operator"" _cull()
        -> Constant<
            details::parse_t<unsigned long long, Digits...>,
            details::parse<unsigned long long, Digits...>::value
        >
    {
        return {};
    }
}}
