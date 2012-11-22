/*
 * Copyright (C) 2011-2012 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
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
            std::is_integral<T>::value,
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

    template<typename T, typename U, typename... Args>
    struct is_reverse_iterable<T, U, Args...>:
        public std::conditional<
            is_reverse_iterable<T>::value,
            is_reverse_iterable<U, Args...>,
            std::false_type
        >::type
    {};


    template<typename T, typename U, typename... Args>
    struct is_floating_point<T, U, Args...>:
        public std::conditional<
            std::is_floating_point<T>::value,
            is_floating_point<U, Args...>,
            std::false_type
        >::type
    {};

    /**
     * @brief Unisgned type with at least the given number of bits
     *
     * This type is an extension of the standard types
     * uint_leastN_t to give an unsigned integer with at
     * least the required number of bits.
     */
    template<uint8_t nb_bits>
    struct uint_least
    {
        // Biggest standard unsigned integer type
        // intmax_t and uint_least64_t are not supported everywhere
        // hence the use of unsigned long long which is better supported
        using type = unsigned long long int;
    };

    template<> struct uint_least<0>     { using type = uint_least8_t; };
    template<> struct uint_least<1>     { using type = uint_least8_t; };
    template<> struct uint_least<2>     { using type = uint_least8_t; };
    template<> struct uint_least<3>     { using type = uint_least8_t; };
    template<> struct uint_least<4>     { using type = uint_least8_t; };
    template<> struct uint_least<5>     { using type = uint_least8_t; };
    template<> struct uint_least<6>     { using type = uint_least8_t; };
    template<> struct uint_least<7>     { using type = uint_least8_t; };
    template<> struct uint_least<8>     { using type = uint_least8_t; };
    template<> struct uint_least<9>     { using type = uint_least16_t; };
    template<> struct uint_least<10>    { using type = uint_least16_t; };
    template<> struct uint_least<11>    { using type = uint_least16_t; };
    template<> struct uint_least<12>    { using type = uint_least16_t; };
    template<> struct uint_least<13>    { using type = uint_least16_t; };
    template<> struct uint_least<14>    { using type = uint_least16_t; };
    template<> struct uint_least<15>    { using type = uint_least16_t; };
    template<> struct uint_least<16>    { using type = uint_least16_t; };
    template<> struct uint_least<17>    { using type = uint_least32_t; };
    template<> struct uint_least<18>    { using type = uint_least32_t; };
    template<> struct uint_least<19>    { using type = uint_least32_t; };
    template<> struct uint_least<20>    { using type = uint_least32_t; };
    template<> struct uint_least<21>    { using type = uint_least32_t; };
    template<> struct uint_least<22>    { using type = uint_least32_t; };
    template<> struct uint_least<23>    { using type = uint_least32_t; };
    template<> struct uint_least<24>    { using type = uint_least32_t; };
    template<> struct uint_least<25>    { using type = uint_least32_t; };
    template<> struct uint_least<26>    { using type = uint_least32_t; };
    template<> struct uint_least<27>    { using type = uint_least32_t; };
    template<> struct uint_least<28>    { using type = uint_least32_t; };
    template<> struct uint_least<29>    { using type = uint_least32_t; };
    template<> struct uint_least<30>    { using type = uint_least32_t; };
    template<> struct uint_least<31>    { using type = uint_least32_t; };
    template<> struct uint_least<32>    { using type = uint_least32_t; };

} // namespace polder


#endif // _POLDER_TYPE_TRAITS_H

