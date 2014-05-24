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
#ifndef POLDER_TYPE_TRAITS_H_
#define POLDER_TYPE_TRAITS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <limits>
#include <type_traits>
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

    template<typename T>
    using result_type = typename function_traits<T>::result_type;

    template<typename T, std::size_t N>
    using argument_type = typename function_traits<T>::template argument_type<N>;

    ////////////////////////////////////////////////////////////
    // Integer literals trait
    //
    // These functions are meant to help the parsing
    // of integer literals.
    ////////////////////////////////////////////////////////////

    /**
     * @brief Unsigned integer fit.
     *
     * This functions checks whether a given unsigned long long
     * value can fit in a given type of integer.
     */
    template<typename Integer>
    constexpr auto can_fit(unsigned long long n)
    {
        return n <= std::numeric_limits<Integer>::max();
    }

    /**
     * @brief Suitable integer type selection.
     *
     * This class will select the smallest type at least
     * as big as the given one where the given unsigned
     * long long value can fit.
     */
    template<typename T, unsigned long long N>
    struct integer_fit;

    template<typename T, unsigned long long N>
    using integer_fit_t = typename integer_fit<T, N>::type;

    template<unsigned long long N>
    struct integer_fit<int, N>
    {
        using type = std::conditional_t<
            can_fit<int>(N),
            int,
            integer_fit_t<long, N>
        >;
    };

    template<unsigned long long N>
    struct integer_fit<long, N>
    {
        using type = std::conditional_t<
            can_fit<long>(N),
            long,
            long long
        >;
    };

    template<unsigned long long N>
    struct integer_fit<long long, N>
    {
        using type = long long;
    };

    template<unsigned long long N>
    struct integer_fit<unsigned, N>
    {
        using type = std::conditional_t<
            can_fit<unsigned>(N),
            unsigned,
            integer_fit_t<unsigned long long, N>
        >;
    };

    template<unsigned long long N>
    struct integer_fit<unsigned long, N>
    {
        using type = std::conditional_t<
            can_fit<unsigned long>(N),
            unsigned long,
            unsigned long long
        >;
    };

    template<unsigned long long N>
    struct integer_fit<unsigned long long, N>
    {
        using type = unsigned long long;
    };

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
        std::conditional_t<
            is_same<T, U>::value,
            is_same<U, Args...>,
            std::false_type
        >
    {};

    ////////////////////////////////////////////////////////////
    // disable_if
    ////////////////////////////////////////////////////////////

    template<bool B, typename T=void>
    using disable_if = std::enable_if<not B, T>;

    template<bool B, class T=void>
    using disable_if_t = typename disable_if<B, T>::type;

    ////////////////////////////////////////////////////////////
    // Iterable/traversable traits
    ////////////////////////////////////////////////////////////

    template<typename T>
    struct is_iterable_impl
    {
        template<typename U>
        static constexpr auto test(typename U::iterator*)
            -> std::true_type
        { return {}; }

        template<typename>
        static constexpr auto test(...)
            -> std::false_type
        { return {}; }

        static constexpr bool value =
            test<std::decay_t<T>>(nullptr);
    };

    template<typename...>
    struct is_iterable;

    template<typename T>
    struct is_iterable<T>:
        std::integral_constant<
            bool,
            is_iterable_impl<T>::value
        >
    {};

    template<typename T, std::size_t N>
    struct is_iterable<T (&)[N]>:
        std::true_type
    {};

    template<typename T, typename U, typename... Args>
    struct is_iterable<T, U, Args...>:
        std::conditional_t<
            is_iterable<T>::value,
            is_iterable<U, Args...>,
            std::false_type
        >
    {};

    template<typename T>
    struct is_reverse_iterable_impl
    {
        template<typename U>
        static constexpr auto test(typename U::reverse_iterator*)
            -> std::true_type
        { return {}; }

        template<typename>
        static constexpr auto test(...)
            -> std::false_type
        { return {}; }

        static constexpr bool value =
            test<std::decay_t<T>>(nullptr);
    };

    template<typename...>
    struct is_reverse_iterable;

    template<typename T>
    struct is_reverse_iterable<T>:
        std::integral_constant<
            bool,
            is_reverse_iterable_impl<T>::value
        >
    {};

    template<typename T, std::size_t N>
    struct is_reverse_iterable<T (&)[N]>:
        std::true_type
    {};

    template<typename T, typename U, typename... Args>
    struct is_reverse_iterable<T, U, Args...>:
        std::conditional_t<
            is_reverse_iterable<T>::value,
            is_reverse_iterable<U, Args...>,
            std::false_type
        >
    {};
}

#endif // POLDER_TYPE_TRAITS_H_
