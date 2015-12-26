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
#include <limits>
#include <catch.hpp>
#include <POLDER/rational.h>
#include <POLDER/math/cmath.h>

using namespace polder;

TEST_CASE( "rational construction", "[rational]" )
{
    // Default initialization
    rational<int> r0;
    CHECK( r0.numer() == 0 );
    CHECK( r0.denom() == 1 );

    auto ratio = make_rational(4, 3);
    CHECK( ratio.numer() == 4 );
    CHECK( ratio.denom() == 3 );

    auto ratio2 = make_rational(5);
    CHECK( ratio2.numer() == 5 );
    CHECK( ratio2.denom() == 1 );
}

TEST_CASE( "rational comparison operators", "[rational]" )
{
    auto r1 = make_rational(1, 2);
    auto r2 = make_rational(2, 4);
    auto r3 = make_rational(1, 3);
    auto r4 = make_rational(5, 1);
    auto r5 = make_rational(-1, 2);
    auto r6 = make_rational(1, -2);

    SECTION( "rational-rational comparison" )
    {
        CHECK( r1 == r2 );
        CHECK( r1 != r3 );
        CHECK( r5 == r6 );
    }

    SECTION( "rational-integer comparison" )
    {
        CHECK( r4 == 5 );
        CHECK( 5 == r4 );
        CHECK( r1 != 3 );
        CHECK( 8 != r2 );
    }
}

TEST_CASE( "rational relational operators", "[rational]" )
{
    auto r1 = make_rational(1, 2);
    auto r2 = make_rational(2, 4);
    auto r3 = make_rational(1, 3);
    auto r4 = make_rational(5, 1);
    auto r5 = make_rational(-1, 2);
    auto r6 = make_rational(1, -2);

    SECTION( "rational-rational comparison" )
    {
        CHECK( r1 > r3 );
        CHECK( r3 < r2 );
        CHECK( r1 >= r2 );
        CHECK( r3 <= r2 );
    }

    SECTION( "rational-integer comparison" )
    {
        CHECK( 0 < r1 );
        CHECK( r2 < 1 );
        CHECK( 8 > r4 );
        CHECK( r2 > -1 );
        CHECK( 5 <= r4 );
        CHECK( r3 <= 1 );
        CHECK( 1 >= r3 );
        CHECK( r1 >= -8 );
        CHECK( r5 <= 0 );
        CHECK( r6 <= 0 );
    }
}

TEST_CASE( "rational arithmetic operators", "[rational]" )
{
    auto r1 = make_rational(1, 2);
    auto r2 = make_rational(2, 4);
    auto r3 = make_rational(1, 3);
    auto r4 = make_rational(5, 1);

    SECTION( "rational-rational arithmetic operators" )
    {
        CHECK( r1 + r2 == 1 );
        CHECK( r4 - r1 == make_rational(9, 2) );
        CHECK( r2 * r3 == make_rational(1, 6) );
        CHECK( r1 / r3 == make_rational(3, 2) );
    }

    SECTION( "rational-integral arithmetic operators" )
    {
        CHECK( r1 + 1 == make_rational(3, 2) );
        CHECK( 2 + r2 == make_rational(5, 2) );
        CHECK( r3 - 3 == make_rational(-8, 3) );
        CHECK( 2 - r1 == make_rational(3, 2) );
        CHECK( r4 * 2 == 10 );
        CHECK( 6 * r2 == r1 * 6 );
        CHECK( 1 / r2 == 2 );
        CHECK( r3 / 3 == make_rational(1, 9) );
        CHECK( r1 / -2 == -1/4_r );
    }
}

TEST_CASE( "rational increment and decrement operators", "[rational]" )
{
    auto r1 = 2/5_r;
    CHECK( (r1++).numer() == 2 );
    CHECK( r1.numer() == 7 );
    CHECK( r1.denom() == 5 );
    CHECK( (--r1).numer() == 2 );

    auto r2 = 15/7_r;
    CHECK( (r2--).numer() == 15 );
    CHECK( r2.numer() == 8 );
    CHECK( r2.denom() == 7 );
    CHECK( (++r2).numer() == 15 );
}

TEST_CASE( "math operations for rational", "[rational][math]" )
{
    auto r0 = make_rational(0, 1);
    auto r1 = make_rational(-1, 2);
    auto r2 = make_rational(1, -2);
    auto r3 = make_rational(4, 5);

    SECTION( "abs" )
    {
        using math::meta::abs;

        CHECK( abs(r1) == make_rational(1, 2) );
        CHECK( abs(r2) == make_rational(1, 2) );
        CHECK( abs(r1) == abs(r2) );
    }

    SECTION( "pow" )
    {
        using math::meta::pow;

        CHECK( pow(r1, 0) == make_rational(1, 1) );
        CHECK( pow(r2, 1) == r2 );
        CHECK( pow(r3, 3) == make_rational(64, 125) );
        CHECK( pow(r3, -3) == make_rational(pow(5, 3), pow(4, 3)) );
    }

    SECTION( "sign" )
    {
        using math::meta::sign;

        CHECK( sign(r0) == 0 );
        CHECK( sign(r1) == -1 );
        CHECK( sign(r2) == -1 );
        CHECK( sign(r3) == 1 );
        CHECK( sign(r1) == sign(r1.numer()) );
        CHECK( sign(r2) == sign(r2.numer()) );
    }

    SECTION( "reciprocal" )
    {
        CHECK( reciprocal(r1) == reciprocal(r2) );
    }

    SECTION( "invert" )
    {
        CHECK( r1.invert() == r2.invert() );
        CHECK( r1.numer() == -2 );
        CHECK( r2.denom() == 1 );
    }
}

TEST_CASE( "rational implicit casts", "[rational]" )
{
    REQUIRE_FALSE( 0_r );
    CHECK( bool(1_r) );
    CHECK( not not 8_r );

    CHECK( make_rational(1, 2) == make_rational(1L, 2L) );
    CHECK( make_rational(3ULL, 2ULL) == rational<unsigned short>(3, 2) );
}

TEST_CASE( "rational automatic normalization", "[rational]" )
{
    auto r0 = make_rational(1, -2);
    CHECK( r0.numer() == -1 );
    CHECK( r0.denom() == 2 );

    auto r1 = 1/2_r + 1/2_r;
    CHECK( r1.numer() == 1 );
    CHECK( r1.denom() == 1 );

    auto r2 = 3/2_r - 1/2_r;
    CHECK( r2.numer() == 1 );
    CHECK( r2.denom() == 1 );

    auto r3 = (2/3_r) * (3/2_r);
    CHECK( r3.numer() == 1 );
    CHECK( r3.denom() == 1 );

    auto r4 = 1/2_r * 2;
    CHECK( r4.numer() == 1 );
    CHECK( r4.denom() == 1 );

    auto r5 = (3/4_r) / (3/5_r);
    CHECK( r5.numer() == 5 );
    CHECK( r5.denom() == 4 );

    auto r6 = (3/4_r) / 3;
    CHECK( r6.numer() == 1 );
    CHECK( r6.denom() == 4 );

    auto r7 = make_rational(2, 4);
    CHECK( r7.numer() == 1 );
    CHECK( r7.denom() == 2 );
}

TEST_CASE( "rational integer overflow avoidance", "[rational]" )
{
    auto max = std::numeric_limits<int>::max();

    auto r1 = max/2_r;
    CHECK( r1 * 2 == max );

    auto r2 = 2_r / max;
    CHECK( r2 / 2 == 1_r / max );
}
