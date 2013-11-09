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
#ifndef _POLDER_UTILITY_H
#define _POLDER_UTILITY_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <tuple>
#include <POLDER/config.h>

namespace polder
{
    ////////////////////////////////////////////////////////////
    // Integer sequences

    template<std::size_t...>
    struct indices {};

    template<std::size_t N, std::size_t... Indices>
    struct make_indices:
        make_indices<N-1, N-1, Indices...>
    {};

    template<std::size_t... Indices>
    struct make_indices<0, Indices...>:
        indices<Indices...>
    {};

    template<typename T>
    using to_indices =
        make_indices<
            std::tuple_size<
                typename std::decay<T>::type
            >::value
        >;

    ////////////////////////////////////////////////////////////
    // Call function with tuple members as arguments

    template<typename F, typename Tuple, std::size_t... I>
    auto apply_(F&& f, Tuple&& args, indices<I...>)
        -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...))
    {
        return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...);
    }

    template<typename F, typename Tuple, typename Indices=to_indices<Tuple>>
    auto apply(F&& f, Tuple&& args)
        -> decltype(apply_(std::forward<F>(f), std::forward<Tuple>(args), Indices()))
    {
        return apply_(std::forward<F>(f), std::forward<Tuple>(args), Indices());
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
}

namespace std
{
    // Hash function for tuples
    template<typename... Args>
    struct hash<std::tuple<Args...>>
    {
        auto operator()(const std::tuple<Args...>& args) const
            -> std::size_t
        {
            return polder::apply(
                static_cast<std::size_t(*)(Args...)>(polder::hash_all<Args...>),
                args);
        }
    };
}

#endif // _POLDER_UTILITY_H
