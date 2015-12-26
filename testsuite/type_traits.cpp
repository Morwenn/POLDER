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
#include <array>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <list>
#include <type_traits>
#include <vector>
#include <catch.hpp>
#include <POLDER/type_traits.h>

using namespace polder;

TEST_CASE( "function traits", "[type_traits]" )
{
    auto lambda = [](int a, float b)
    {
        return a + b;
    };
    using ltype = decltype(lambda);

    static_assert(function_traits<ltype>::arity == 2, "");

    static_assert(std::is_same<
        result_type<ltype>,
        float
    >::value, "");

    static_assert(std::is_same<
        argument_type<ltype, 0>,
        int
    >::value, "");

    static_assert(std::is_same<
        argument_type<ltype, 1>,
        float
    >::value, "");
}

TEST_CASE( "integer fitting traits", "[type_traits]" )
{
    static_assert(can_fit<uint_least8_t>(0u), "");
    static_assert(can_fit<uint_least16_t>(0u), "");
    static_assert(can_fit<uint_least32_t>(0u), "");
    static_assert(can_fit<uint_least64_t>(0u), "");

    static_assert(can_fit<uint_least8_t>(255u), "");
    static_assert(can_fit<uint_least16_t>(65535u), "");
    static_assert(can_fit<uint_least32_t>(4294967295u), "");
    static_assert(can_fit<uint_least64_t>(18446744073709551615u), "");
}

TEST_CASE( "iterable traits", "[type_traits]" )
{
    int arr[] = { 0, 1, 2, 3, 4 };
    static_assert(is_iterable<decltype(arr)>::value, "");
    static_assert(is_reverse_iterable<decltype(arr)>::value, "");

    static_assert(is_iterable<std::array<int, 5>>::value, "");
    static_assert(is_reverse_iterable<std::array<float, 3>>::value, "");
    static_assert(is_iterable<std::vector<char>>::value, "");
    static_assert(is_reverse_iterable<std::vector<double>>::value, "");
    static_assert(is_iterable<std::deque<int>>::value, "");
    static_assert(is_reverse_iterable<std::deque<std::size_t>>::value, "");
    static_assert(is_iterable<std::list<long double>>::value, "");
    static_assert(is_reverse_iterable<std::list<unsigned>>::value, "");
    static_assert(is_iterable<std::forward_list<unsigned long>>::value, "");
    static_assert(not is_reverse_iterable<std::forward_list<int>>::value, "");
}
