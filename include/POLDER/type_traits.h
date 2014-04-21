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
#ifndef _POLDER_TYPE_TRAITS_H
#define _POLDER_TYPE_TRAITS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>
#include <POLDER/details/config.h>
#include <POLDER/type_list.h>

namespace polder
{
    ////////////////////////////////////////////////////////////
    // Function traits
    ////////////////////////////////////////////////////////////

    template<typename T>
    struct function_traits:
        function_traits<decltype(&T::operator())>
    {};

    template<typename Ret, typename... Args>
    struct function_traits<Ret(Args...)>
    {
        /**
         * Number of arguments of the function.
         */
        static constexpr std::size_t arity = sizeof...(Args);

        /**
         * Return type of the function.
         */
        using result_type = Ret;

        /**
         * Type of the Nth argument of the function.
         */
        template<std::size_t N>
        using argument_type = typename type_list<Args...>::template at<N>;
    };

    template<typename Ret, typename... Args>
    struct function_traits<Ret(*)(Args...)>:
        function_traits<Ret(Args...)>
    {};

    template<typename C, typename Ret, typename... Args>
    struct function_traits<Ret(C::*)(Args...)>:
        function_traits<Ret(Args...)>
    {};

    template<typename C, typename Ret, typename... Args>
    struct function_traits<Ret(C::*)(Args...) const>:
        function_traits<Ret(Args...)>
    {};

    template<typename C, typename Ret, typename... Args>
    struct function_traits<Ret(C::*)(Args...) volatile>:
        function_traits<Ret(Args...)>
    {};

    template<typename C, typename Ret, typename... Args>
    struct function_traits<Ret(C::*)(Args...) const volatile>:
        function_traits<Ret(Args...)>
    {};

    template<typename T>
    struct function_traits<T&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<const T&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<volatile T&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<const volatile T&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<T&&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<const T&&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<volatile T&&>:
        function_traits<T>
    {};

    template<typename T>
    struct function_traits<const volatile T&&>:
        function_traits<T>
    {};

    ////////////////////////////////////////////////////////////
    // Size traits
    ////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////
    // Variadic is_same trait
    ////////////////////////////////////////////////////////////

    template<typename T, typename...>
    struct is_same;

    template<typename T, typename U>
    struct is_same<T, U>:
        std::is_same<T, U>
    {};

    template<typename T, typename U, typename... Args>
    struct is_same<T, U, Args...>:
        std::conditional<
            is_same<T, U>::value,
            is_same<U, Args...>,
            std::false_type
        >::type
    {};

    ////////////////////////////////////////////////////////////
    // Iterable/traversable traits
    ////////////////////////////////////////////////////////////

    template<typename...>
    struct is_iterable;

    template<typename T>
    struct is_iterable<T>
    {
        struct yes {};
        struct no {};

        template<typename U>
        static auto test(typename U::iterator*)
            -> yes;

        template<typename>
        static auto test(...)
            -> no;

        static constexpr bool value =
            std::is_same<
                yes,
                decltype(test<typename std::decay<T>::type>(nullptr))
            >::value;
    };

    template<typename T, std::size_t N>
    struct is_iterable<T (&)[N]>:
        std::true_type
    {};

    template<typename T, typename U, typename... Args>
    struct is_iterable<T, U, Args...>:
        std::conditional<
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
        struct yes {};
        struct no {};

        template<typename U>
        static auto test(typename U::reverse_iterator*)
            -> yes;

        template<typename>
        static auto test(...)
            -> no;

        static constexpr bool value =
            std::is_same<
                yes,
                decltype(test<typename std::decay<T>::type>(nullptr))
            >::value;
    };

    template<typename T, std::size_t N>
    struct is_reverse_iterable<T (&)[N]>:
        std::true_type
    {};

    template<typename T, typename U, typename... Args>
    struct is_reverse_iterable<T, U, Args...>:
        std::conditional<
            is_reverse_iterable<T>::value,
            is_reverse_iterable<U, Args...>,
            std::false_type
        >::type
    {};
}

#endif // _POLDER_TYPE_TRAITS_H
