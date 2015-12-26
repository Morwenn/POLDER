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
#include <catch.hpp>
#include <POLDER/semisymbolic/number.h>

using namespace polder;
using namespace semisymbolic;

TEST_CASE( "Expression and value_type_t", "[semisymbolic][number]" )
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

TEST_CASE( "Number and type equivalence", "[semisymbolic][number]" )
{
    float a = 2.8f;
    Float b = a;
    float c = b;

    CHECK( a == b );
    CHECK( b == c );
    CHECK( a == c );
}

TEST_CASE( "Number relational operators", "[semisymbolic][number]" )
{
    Float f1 = 2.5f;
    Float f2 = 5.0f;
    auto f3 = f1;

    CHECK( f1 != f2 );
    CHECK( f1 == f3 );
    CHECK( f3 != f2 );
    CHECK_FALSE( f1 == f2 );

    CHECK( f1 < f2 );
    CHECK( f1 <= f3 );
    CHECK( f2 > f3 );
    CHECK( f3 >= f3 );
    CHECK( f2 >= f1 );

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

TEST_CASE( "Number arithmetic operators", "[semisymbolic][number]" )
{
    Float f1 = 2.5f;
    Float f2 = 5.0f;

    CHECK( f1 + f2 == 2.5f + 5.0f );
    CHECK( f1 - f2 == 2.5f - 5.0f );
    CHECK( f2 - f1 == 5.0f - 2.5f );
    CHECK( f1 * f2 == 2.5f * 5.0f );
    CHECK( f1 / f2 == 2.5f / 5.0f );
    CHECK( f2 / f1 == 5.0f / 2.5f );

    CHECK( f1 + f2 - f1 == f2 );
}
