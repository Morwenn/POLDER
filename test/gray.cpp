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
#include <limits>
#include <type_traits>
#include <POLDER/gray.h>

int main()
{
    using namespace polder;
    using namespace math;

    // TEST: check for zero
    {
        constexpr auto zero = gray(0u);
        static_assert(zero == 0u, "");
        static_assert(zero.value == 0b0000u, "");
    }

    // TEST: check a random number
    {
        constexpr auto gr = gray(5u);
        static_assert(gr == 5u, "");
        static_assert(gr.value == 0b0111u, "");
    }

    // TEST: max value of a type
    {
        constexpr auto max_uint = std::numeric_limits<unsigned>::max();
        constexpr auto max_gr = gray(max_uint);
        static_assert(max_gr == max_uint, "");
    }

    // TEST: operator=
    {
        GrayCode<unsigned> gr1, gr2;

        gr1 = gray(58u);
        gr2 = gray(22u);
        POLDER_ASSERT(gr1 == gray(58u));
        POLDER_ASSERT(gr2 == gray(22u));
        POLDER_ASSERT(gr1 == 58u);
        POLDER_ASSERT(gr2 == 22u);

        gr1 = 73u;
        gr2 = 194u;
        POLDER_ASSERT(gr1 == gray(73u));
        POLDER_ASSERT(gr2 == gray(194u));
        POLDER_ASSERT(gr1 == 73u);
        POLDER_ASSERT(gr2 == 194u);
    }

    // TEST: comparison operators
    {
        constexpr auto gr = gray(52u);
        static_assert(gr == gray(52u), "");
        static_assert(gr == 52u, "");
        static_assert(52u == gr, "");
        static_assert(gr != 56u, "");
        static_assert(54u != gr, "");
        static_assert(gr != gray(89u), "");
    }

    // TEST: bitwise operations
    {
        auto gr1 = gray(42u);
        auto gr2 = gray(28u);
        POLDER_ASSERT((gr1 & gr2).value == (gr1.value & gr2.value));
        POLDER_ASSERT((gr1 | gr2).value == (gr1.value | gr2.value));
        POLDER_ASSERT((gr1 ^ gr2).value == (gr1.value ^ gr2.value));
        POLDER_ASSERT((gr1 << 3u).value == (gr1.value << 3u));
        POLDER_ASSERT((gr1 >> 2u).value == (gr1.value >> 2u));
    }

    // TEST: type inference
    {
        auto llgr = gray(8ull);
        using value_type = typename decltype(llgr)::value_type;
        static_assert(std::is_same<value_type, unsigned long long>::value, "");
    }

    // TEST: math operations
    {
        POLDER_ASSERT(is_even(gray(5u)) == false);
        POLDER_ASSERT(is_even(gray(4u)) == true);
        POLDER_ASSERT(is_even(gray(0u)) == true);

        POLDER_ASSERT(is_odd(gray(8u)) == false);
        POLDER_ASSERT(is_odd(gray(0u)) == false);
        POLDER_ASSERT(is_odd(gray(5u)) == true);
    }

    // TEST: increment operator
    {
        unsigned i = 0u;
        for (auto val = gray(0u) ; val < 10u ; ++val, ++i)
        {
            POLDER_ASSERT(val == i);
        }
    }

    // TEST: decrement operator
    {
        unsigned i = 35u;
        for (auto val = gray(35u) ; val > 23u ; --val, --i)
        {
            POLDER_ASSERT(val == i);
        }
    }
}
