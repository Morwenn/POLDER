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
#include <type_traits>
#include <utility>
#include <POLDER/utility.h>
#include "catch.hpp"

TEST_CASE( "integer_range", "[utility]" )
{
    static_assert(std::is_same<
        polder::integer_range<int, 8, 8>,
        std::integer_sequence<int>
    >::value, "");

    static_assert(std::is_same<
        polder::integer_range<int, 0, 5>,
        std::integer_sequence<int, 0, 1, 2, 3, 4>
    >::value, "");

    static_assert(std::is_same<
        polder::integer_range<int, 5, 0>,
        std::integer_sequence<int, 5, 4, 3, 2, 1>
    >::value, "");

    static_assert(std::is_same<
        polder::integer_range<int, -3, 2>,
        std::integer_sequence<int, -3, -2, -1, 0, 1>
    >::value, "");

    static_assert(std::is_same<
        polder::integer_range<int, -1, -4>,
        std::integer_sequence<int, -1, -2, -3>
    >::value, "");

    static_assert(std::is_same<
        polder::integer_range<int, 3, -8>,
        std::integer_sequence<int, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7>
    >::value, "");

    static_assert(std::is_same<
        polder::index_range<2, 6>,
        std::index_sequence<2, 3, 4, 5>
    >::value, "");
}
