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
#include <POLDER/rational.h>
#include <POLDER/math/cmath.h>

int main()
{
    // TEST: construction
    {
        using namespace polder;

        // Default initialization
        constexpr rational<int> r0;
        static_assert(r0.numer() == 0, "");
        static_assert(r0.denom() == 1, "");

        constexpr auto ratio = make_rational(4, 3);
        static_assert(ratio.numer() == 4, "");
        static_assert(ratio.denom() == 3, "");

        constexpr auto ratio2 = make_rational(5);
        static_assert(ratio2.numer() == 5, "");
        static_assert(ratio2.denom() == 1, "");
    }

    // TEST: relational operators
    {
        using namespace polder;

        constexpr auto r1 = make_rational(1, 2);
        constexpr auto r2 = make_rational(2, 4);
        constexpr auto r3 = make_rational(1, 3);
        constexpr auto r4 = make_rational(5, 1);
        constexpr auto r5 = make_rational(-1, 2);
        constexpr auto r6 = make_rational(1, -2);

        // rational-rational comparison
        static_assert(r1 == r2, "");
        static_assert(r1 != r3, "");
        static_assert(r1 > r3, "");
        static_assert(r3 < r2, "");
        static_assert(r1 >= r2, "");
        static_assert(r3 <= r2, "");
        static_assert(r5 == r6, "");

        // rational-integral comparison
        static_assert(r4 == 5, "");
        static_assert(5 == r4, "");
        static_assert(r1 != 3, "");
        static_assert(8 != r2, "");
        static_assert(0 < r1, "");
        static_assert(r2 < 1, "");
        static_assert(8 > r4, "");
        static_assert(r2 > -1, "");
        static_assert(5 <= r4, "");
        static_assert(r3 <= 1, "");
        static_assert(1 >= r3, "");
        static_assert(r1 >= -8, "");
        static_assert(r5 <= 0, "");
        static_assert(r6 <= 0, "");
    }

    // TEST: arithmetic operators
    {
        using namespace polder;

        constexpr auto r1 = make_rational(1, 2);
        constexpr auto r2 = make_rational(2, 4);
        constexpr auto r3 = make_rational(1, 3);
        constexpr auto r4 = make_rational(5, 1);

        // rational-rational arithmetic operations
        POLDER_ASSERT(r1 + r2 == 1);
        POLDER_ASSERT(r4 - r1 == make_rational(9, 2));
        POLDER_ASSERT(r2 * r3 == make_rational(1, 6));
        POLDER_ASSERT(r1 / r3 == make_rational(3, 2));

        // rational-integral arithmetic operations
        POLDER_ASSERT(r1 + 1 == make_rational(3, 2));
        POLDER_ASSERT(2 + r2 == make_rational(5, 2));
        POLDER_ASSERT(r3 - 3 == make_rational(-8, 3));
        POLDER_ASSERT(2 - r1 == make_rational(3, 2));
        POLDER_ASSERT(r4 * 2 == 10);
        POLDER_ASSERT(6 * r2 == r1 * 6);
        POLDER_ASSERT(1 / r2 == 2);
        POLDER_ASSERT(r3 / 3 == make_rational(1, 9));
    }

    // TEST: math functions
    // - ADL test
    {
        using polder::make_rational;

        // ADL
        using polder::math::meta::abs;
        using polder::math::meta::pow;
        using polder::math::meta::sign;

        constexpr auto r0 = make_rational(0, 1);
        constexpr auto r1 = make_rational(-1, 2);
        constexpr auto r2 = make_rational(1, -2);
        constexpr auto r3 = make_rational(4, 5);

        static_assert(abs(r1) == make_rational(1, 2), "");
        static_assert(abs(r2) == make_rational(1, 2), "");
        static_assert(abs(r1) == abs(r2), "");

        static_assert(pow(r1, 0) == make_rational(1, 1), "");
        static_assert(pow(r2, 1) == r2, "");
        static_assert(pow(r3, 3) == make_rational(64, 125), "");
        static_assert(pow(r3, -3) == make_rational(pow(5, 3), pow(4, 3)), "");

        static_assert(sign(r0) == 0, "");
        static_assert(sign(r1) == -1, "");
        static_assert(sign(r2) == -1, "");
        static_assert(sign(r3) == 1, "");
        static_assert(sign(r1) == sign(r1.numer()), "");
        static_assert(sign(r2) == sign(r2.numer()), "");
    }

    // TEST: cast
    {
        using namespace polder;

        static_assert(make_rational(1, 2) == make_rational(1L, 2L), "");
        static_assert(make_rational(3ULL, 2ULL) == rational<short>(3, 2), "");
    }

    // TEST: normalizing operations
    {
        using namespace polder;

        auto r1 = 1/2_r + 1/2_r;
        POLDER_ASSERT(r1.numer() == 1);
        POLDER_ASSERT(r1.denom() == 1);

        auto r2 = 3/2_r - 1/2_r;
        POLDER_ASSERT(r2.numer() == 1);
        POLDER_ASSERT(r2.denom() == 1);

        auto r3 = (2/3_r) * (3/2_r);
        POLDER_ASSERT(r3.numer() == 1);
        POLDER_ASSERT(r3.denom() == 1);

        auto r4 = 1/2_r * 2;
        POLDER_ASSERT(r4.numer() == 1);
        POLDER_ASSERT(r4.denom() == 1);

        auto r5 = (3/4_r) / (3/5_r);
        POLDER_ASSERT(r5.numer() == 5);
        POLDER_ASSERT(r5.denom() == 4);

        auto r6 = (3/4_r) / 3;
        POLDER_ASSERT(r6.numer() == 1);
        POLDER_ASSERT(r6.denom() == 4);
    }
}
