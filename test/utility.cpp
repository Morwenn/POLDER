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
#include <utility>
#include <POLDER/utility.h>

template<std::size_t N>
void test(std::integer_sequence<int>)
{
    static_assert(N == 0, "");
}

template<std::size_t N>
void test(std::integer_sequence<int, 0, 1, 2, 3, 4>)
{
    static_assert(N == 1, "");
}

template<std::size_t N>
void test(std::integer_sequence<int, 5, 4, 3, 2, 1>)
{
    static_assert(N == 2, "");
}

template<std::size_t N>
void test(std::integer_sequence<int, -3, -2, -1, 0, 1>)
{
    static_assert(N == 3, "");
}

template<std::size_t N>
void test(std::integer_sequence<int, -1, -2, -3>)
{
    static_assert(N == 4, "");
}

template<std::size_t N>
void test(std::integer_sequence<int, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7>)
{
    static_assert(N == 5, "");
}

int main()
{
    using namespace polder;

    test<0>(integer_range<int, 8, 8>());
    test<1>(integer_range<int, 0, 5>());
    test<2>(integer_range<int, 5, 0>());
    test<3>(integer_range<int, -3, 2>());
    test<4>(integer_range<int, -1, -4>());
    test<5>(integer_range<int, 3, -8>());
}
