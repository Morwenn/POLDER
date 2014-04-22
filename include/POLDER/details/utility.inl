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

namespace details
{
    ////////////////////////////////////////////////////////////
    // Hack

    template<typename T>
    struct minus_helper;
    template<typename T, T val>
    struct minus_helper<std::integral_constant<T, val>>
    {
        using type = std::integral_constant<T, val-1>;
    };
    template<typename T>
    using minus = typename minus_helper<T>::type;

    template<typename T>
    struct plus_helper;
    template<typename T, T val>
    struct plus_helper<std::integral_constant<T, val>>
    {
        using type = std::integral_constant<T, val+1>;
    };
    template<typename T>
    using plus = typename plus_helper<T>::type;

    ////////////////////////////////////////////////////////////
    // std::integer_sequence tools

    template<typename Int, typename C, Int P, Int... N>
    struct increasing_integer_range:
        increasing_integer_range<Int, minus<C>, P+1, N..., P>
    {};

    template<typename Int, typename C, Int P, Int... N>
    struct decreasing_integer_range:
        decreasing_integer_range<Int, plus<C>, P-1, N..., P>
    {};

    template<typename Int, Int P, Int... N>
    struct increasing_integer_range<Int, std::integral_constant<Int, 0>, P, N...>:
        std::integer_sequence<Int, N...>
    {};

    template<typename Int, Int P, Int... N>
    struct decreasing_integer_range<Int, std::integral_constant<Int, 0>, P, N...>:
        std::integer_sequence<Int, N...>
    {};

    ////////////////////////////////////////////////////////////
    // Call function with tuple members as arguments

    template<typename F, typename Tuple, std::size_t... I>
    auto apply_impl(F&& f, Tuple&& args, std::index_sequence<I...>)
        -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...))
    {
        return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...);
    }
}
