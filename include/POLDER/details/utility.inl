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
    // std::integer_sequence tools

    template<typename Int, typename, Int Begin>
    struct increasing_integer_range;

    template<typename Int, Int... N, Int Begin>
    struct increasing_integer_range<Int, std::integer_sequence<Int, N...>, Begin>:
        std::integer_sequence<Int, N+Begin...>
    {};

    template<typename Int, typename, Int Begin>
    struct decreasing_integer_range;

    template<typename Int, Int... N, Int Begin>
    struct decreasing_integer_range<Int, std::integer_sequence<Int, N...>, Begin>:
        std::integer_sequence<Int, Begin-N...>
    {};

    ////////////////////////////////////////////////////////////
    // Call function with tuple members as arguments

    template<typename F, typename Tuple, std::size_t... I>
    constexpr auto apply_impl(F&& f, Tuple&& args, std::index_sequence<I...>)
        -> decltype(auto)
    {
        return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...);
    }
}
