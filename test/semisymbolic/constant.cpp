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
#include <POLDER/math/cmath.h>
#include <POLDER/semisymbolic/constant.h>

int main()
{
    using namespace polder::semisymbolic;

    // TEST: literals
    {
        static_assert(0_c == 0, "");
        static_assert(1_c == 1, "");
        static_assert(-1_c == -1, "");
        static_assert(45_cl == 45l, "");
        static_assert(52_cll() == 52ll, "");
        static_assert(decltype(45_cu)::value == 45u, "");
        static_assert(91_cul == 91ul, "");
        static_assert(23_cull == (long long unsigned)23, "");

        static_assert(
            std::is_same<
                decltype(58_c),
                Constant<int, 58>
            >::value, "");
    }

    // TEST: unary operator+
    {
        constexpr auto a = 42_c;
        constexpr auto b = +a;
        static_assert(b == 42, "");
        static_assert(b == +42_c, "");
        static_assert(b == 42_c, "");

        static_assert(
            std::is_same<
                decltype(+58_c),
                Constant<int, 58>
            >::value, "");
    }

    // TEST: unary operator-
    {
        constexpr auto a = 42_c;
        constexpr auto b = -a;
        static_assert(b == -42, "");
        static_assert(b == -42_c, "");

        static_assert(
            std::is_same<
                decltype(-58_c),
                Constant<int, -58>
            >::value, "");
    }

    // TEST: arithmetic operators
    {
        static_assert(0_c + 0_c == 0_c, "");
        static_assert(1_c + 0_c == 1_c, "");
        static_assert(0_c + 1_c == 1_c, "");
        static_assert(88_c + 22_c == 110_c, "");

        static_assert(0_c - 0_c == 0_c, "");
        static_assert(1_c - 0_c == 1_c, "");
        static_assert(0_c - 1_c == -1_c, "");
        static_assert(88_c - 22_c == 66_c, "");

        static_assert(0_c * 0_c == 0_c, "");
        static_assert(1_c * 0_c == 0_c, "");
        static_assert(0_c * 1_c == 0_c, "");
        static_assert(88_c * 22_c == 1936_c, "");

        static_assert(0_c / 1_c == 0_c, "");
        static_assert(88_c / 22_c == 4_c, "");

        static_assert(0_c + 0_c == 0_c, "");
        static_assert(1_c + 0_c == 1_c, "");
        static_assert(0_c + 1_c == 1_c, "");
        static_assert(88_c + 22_c == 110_c, "");

        static_assert(27_c % 16_c == 11_c, "");
        static_assert(30_c % 3_c == 0_c, "");
        static_assert(35_c % 3_c == 2_c, "");
        static_assert(16_c % 6_c == 4_c, "");
        static_assert(15_c % 12_c == 3_c, "");
    }

    // TEST: equality operators
    {
        static_assert(52_c == 52_c, "");
        static_assert(0_c != 1_c, "");

        static_assert(
            std::is_same<
                decltype(45_c == 23_c),
                Constant<bool, false>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(45_c != 23_c),
                Constant<bool, true>
            >::value, "");
    }

    // TEST: relational operators
    {
        static_assert(51_c < 52_c, "");
        static_assert(23_c <= 42_c, "");
        static_assert(23_c <= 23_c, "");
        static_assert(29_c > 17_c, "");
        static_assert(85_c >= 53_c, "");
        static_assert(87_c >= 87_c, "");

        static_assert(
            std::is_same<
                decltype(45_c < 23_c),
                Constant<bool, false>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(45_c <= 23_c),
                Constant<bool, false>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(45_c > 23_c),
                Constant<bool, true>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(45_c >= 23_c),
                Constant<bool, true>
            >::value, "");
    }

    // TEST: cmath functions
    {
        using namespace polder::math;

        static_assert(meta::abs(-5_c) == 5_c, "");
        static_assert(meta::abs(8_c) == 8_c, "");
        static_assert(meta::abs(-82_cl) == 82_cl, "");

        static_assert(
            meta::min(1_c, 2_c) == 1_c, "");
        static_assert(
            meta::min(0_c, 0_c) == 0_c, "");
        static_assert(
            meta::min(-2_c, -1_c, 0_c, 1_c, 2_c) == -2_c, "");
        static_assert(
            meta::min(2_c, 1_c, 0_c, -1_c, -2_c) == -2_c, "");

        static_assert(
            meta::max(3_c, 8_c) == 8_c, "");
        static_assert(
            meta::max(-8_c, -8_c) == -8_c, "");
        static_assert(
            meta::max(8_c, -1_c, 6_c, 3_c, 5_c, 2_c, -8_c) == 8_c, "");
        static_assert(
            meta::max(-1_c, 0_c, 1_c, 2_c, 3_c, 2_c, 1_c, 0_c, -1_c) == 3_c, "");

        static_assert(meta::pow(2_c, 0_c) == 1_c, "");
        static_assert(meta::pow(2_c, 1_c) == 2_c, "");
        static_assert(meta::pow(5_c, 1_c) == 5_c, "");
        static_assert(meta::pow(5_c, 0_c) == 1_c, "");
        static_assert(meta::pow(2_c, 1_c) == 2_c, "");
        static_assert(meta::pow(2_c, 2_c) == 4_c, "");
    }
}
