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
#include <POLDER/semisymbolic/number.h>

int main()
{
    using namespace polder;
    using namespace semisymbolic;

    // TEST: type checks
    {
        static_assert(
            std::is_same<
                value_type_t<Add<Float, Float>>,
                float
            >::value, "");

        static_assert(
            std::is_same<
                value_type_t<Add<Double, Double>>,
                double
            >::value, "");

        static_assert(
            std::is_same<
                value_type_t<Eq<Float, Float>>,
                bool
            >::value, "");
    }

    // TEST: back and forth construction
    // - Number -> value_type
    // - value_type -> Number
    {
        float a = 2.8f;
        Float b = a;
        float c = b;

        POLDER_ASSERT(a == b);
        POLDER_ASSERT(b == c);
        POLDER_ASSERT(a == c);
    }

    // TEST: relational operators
    {
        Float f1 = 2.5f;
        Float f2 = 5.0f;
        auto f3 = f1;

        POLDER_ASSERT(f1 != f2);
        POLDER_ASSERT(f1 == f3);
        POLDER_ASSERT(f3 != f2);
        POLDER_ASSERT(not (f1 == f2));

        POLDER_ASSERT(f1 < f2);
        POLDER_ASSERT(f1 <= f3);
        POLDER_ASSERT(f2 > f3);
        POLDER_ASSERT(f3 >= f3);
        POLDER_ASSERT(f2 >= f1);

        static_assert(
            std::is_same<
                decltype(f1 == f2),
                Eq<Float, Float>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(f1 != f2),
                Ne<Float, Float>
            >::value, "");

        static_assert(
            std::is_same<
                decltype(f1 == 5.0f),
                bool
            >::value, "");
    }

    // TEST: arithmetic operations
    {
        Float f1 = 2.5f;
        Float f2 = 5.0f;

        POLDER_ASSERT(f1 + f2 == 2.5f + 5.0f);
        POLDER_ASSERT(f1 - f2 == 2.5f - 5.0f);
        POLDER_ASSERT(f2 - f1 == 5.0f - 2.5f);
        POLDER_ASSERT(f1 * f2 == 2.5f * 5.0f);
        POLDER_ASSERT(f1 / f2 == 2.5f / 5.0f);
        POLDER_ASSERT(f2 / f1 == 5.0f / 2.5f);

        POLDER_ASSERT(f1 + f2 - f1 == f2);
    }
}
