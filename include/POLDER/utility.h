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
#ifndef POLDER_UTILITY_H_
#define POLDER_UTILITY_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <tuple>
#include <type_traits>
#include <utility>
#include <POLDER/details/config.h>

namespace polder
{
    #include "details/utility.inl"

    ////////////////////////////////////////////////////////////
    // std::integer_sequence tools

    template<typename Int, Int S, Int E,  bool Increasing=(S<E)>
    struct integer_range;

    template<typename Int, Int S, Int E>
    struct integer_range<Int, S, E, true>:
        details::increasing_integer_range<Int, std::integral_constant<Int, E-S>, S>
    {};

    template<typename Int, Int S, Int E>
    struct integer_range<Int, S, E, false>:
        details::decreasing_integer_range<Int, std::integral_constant<Int, E-S>, S>
    {};

    template<std::size_t S, std::size_t E>
    using index_range = integer_range<std::size_t, S, E>;

    template<typename T>
    using to_index_sequence =
        std::make_index_sequence<
            std::tuple_size<
                typename std::decay<T>::type
            >::value
        >;

    ////////////////////////////////////////////////////////////
    // Call function with tuple members as arguments

    template<typename F, typename Tuple,
             typename Indices=to_index_sequence<Tuple>>
    auto apply(F&& f, Tuple&& args)
        -> decltype(details::apply_impl(std::forward<F>(f), std::forward<Tuple>(args), Indices()))
    {
        return details::apply_impl(std::forward<F>(f), std::forward<Tuple>(args), Indices());
    }

    ////////////////////////////////////////////////////////////
    // Combine hash for several arguments

    template<typename First, typename... Rest>
    auto hash_all(First first, Rest... rest)
        -> std::size_t
    {
        auto seed = std::hash<First>()(first);
        seed ^= hash_all(rest...);
        return seed;
    }

    template<typename First, typename Second>
    auto hash_all(First first, Second second)
        -> std::size_t
    {
        return std::hash<First>()(first) ^ std::hash<Second>()(second);
    }

    ////////////////////////////////////////////////////////////
    // Static polymorphism utility

    /**
     * @brief Trait holding a class types
     *
     * Static polymorphism does not allow to import
     * the derived class types in the base class.
     * Therefore, we need a specialized trait to
     * hold these types.
     */
    template<typename T>
    struct types_t;

    ////////////////////////////////////////////////////////////
    // Development tool

    /**
     * @brief Ignores its parameters
     *
     * Can be used as a drop-in replacement for
     * (void) arg. Function to be used whenever
     * an expansion pack has to be extended for
     * a function that returns no value:
     *
     * ignore( (func<Args>(params), 0)... );
     */
    template<typename... Args>
    auto ignore(Args&&...)
        -> void
    {
        // Do exactly nothing
    }
}

namespace std
{
    // Hash function for std::tuple
    template<typename... Args>
    struct hash<std::tuple<Args...>>
    {
        auto operator()(const std::tuple<Args...>& args) const
            -> std::size_t
        {
            return polder::apply(polder::hash_all<Args...>, args);
        }
    };
}

#endif // POLDER_UTILITY_H_
