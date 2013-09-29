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
#ifndef _POLDER_TYPE_TRAITS_H
#define _POLDER_TYPE_TRAITS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdint>
#include <type_traits>
#include <POLDER/config.h>


namespace polder
{
    template<typename T, typename U>
    using greater_of = std::conditional<
        sizeof(T) >= sizeof(U),
        T,
        U
    >;

    template<typename T, typename U>
    using lesser_of = std::conditional<
        sizeof(T) <= sizeof(U),
        T,
        U
    >;

    template<typename...>
    struct is_integral;

    template<typename T>
    struct is_integral<T>:
        public std::conditional<
            std::is_integral<T>::value,
            std::true_type,
            std::false_type
        >::type
    {};

    template<typename T, typename U, typename... Args>
    struct is_integral<T, U, Args...>:
        public std::conditional<
            is_integral<T>::value,
            is_integral<U, Args...>,
            std::false_type
        >::type
    {};

    template<typename...>
    struct is_floating_point;

    template<typename T>
    struct is_floating_point<T>:
        public std::conditional<
            std::is_floating_point<T>::value,
            std::true_type,
            std::false_type
        >::type
    {};

    template<typename T, typename U, typename... Args>
    struct is_floating_point<T, U, Args...>:
        public std::conditional<
            is_floating_point<T>::value,
            is_floating_point<U, Args...>,
            std::false_type
        >::type
    {};

    template<typename T, typename...>
    struct is_same;

    template<typename T, typename U>
    struct is_same<T, U>:
        public std::conditional<
            std::is_same<T, U>::value,
            std::true_type,
            std::false_type
        >::type
    {};

    template<typename T, typename U, typename... Args>
    struct is_same<T, U, Args...>:
        public std::conditional<
            is_same<T, U>::value,
            is_same<U, Args...>,
            std::false_type
        >::type
    {};

    template<typename...>
    struct is_iterable;

    template<typename T>
    struct is_iterable<T>
    {
        using yes   = uint8_t;
        using no    = uint16_t;

        template<typename U>
        static yes& test(typename U::iterator*);

        template<typename>
        static no& test(...);

        static constexpr bool value = sizeof(test<typename std::decay<T>::type>(0)) == sizeof(yes);
    };

    template<typename T, std::size_t N>
    struct is_iterable<T (&)[N]>
    {
        static constexpr bool value = true;
    };

    template<typename T, typename U, typename... Args>
    struct is_iterable<T, U, Args...>:
        public std::conditional<
            is_iterable<T>::value,
            is_iterable<U, Args...>,
            std::false_type
        >::type
    {};

    template<typename...>
    struct is_reverse_iterable;

    template<typename T>
    struct is_reverse_iterable<T>
    {
        using yes   = uint8_t;
        using no    = uint16_t;

        template<typename U>
        static yes& test(typename U::reverse_iterator*);

        template<typename>
        static no& test(...);

        static constexpr bool value = sizeof(test<typename std::decay<T>::type>(0)) == sizeof(yes);
    };

    template<typename T, std::size_t N>
    struct is_reverse_iterable<T (&)[N]>
    {
        static constexpr bool value = true;
    };

    template<typename T, typename U, typename... Args>
    struct is_reverse_iterable<T, U, Args...>:
        public std::conditional<
            is_reverse_iterable<T>::value,
            is_reverse_iterable<U, Args...>,
            std::false_type
        >::type
    {};

} // namespace polder


#endif // _POLDER_TYPE_TRAITS_H

