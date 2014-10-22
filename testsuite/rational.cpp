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
#include <POLDER/rational.h>
#include <POLDER/math/cmath.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "rational construction", "[rational]" )
{
    // Default initialization
    rational<int> r0;
    REQUIRE( r0.numer() == 0 );
    REQUIRE( r0.denom() == 1 );

    auto ratio = make_rational(4, 3);
    REQUIRE( ratio.numer() == 4 );
    REQUIRE( ratio.denom() == 3 );

    auto ratio2 = make_rational(5);
    REQUIRE( ratio2.numer() == 5 );
    REQUIRE( ratio2.denom() == 1 );
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
        REQUIRE( r1 == r2 );
        REQUIRE( r1 != r3 );
        REQUIRE( r5 == r6 );
    }

    SECTION( "rational-integer comparison" )
    {
        REQUIRE( r4 == 5 );
        REQUIRE( 5 == r4 );
        REQUIRE( r1 != 3 );
        REQUIRE( 8 != r2 );
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
        REQUIRE( r1 > r3 );
        REQUIRE( r3 < r2 );
        REQUIRE( r1 >= r2 );
        REQUIRE( r3 <= r2 );
    }

    SECTION( "rational-integer comparison" )
    {
        REQUIRE( 0 < r1 );
        REQUIRE( r2 < 1 );
        REQUIRE( 8 > r4 );
        REQUIRE( r2 > -1 );
        REQUIRE( 5 <= r4 );
        REQUIRE( r3 <= 1 );
        REQUIRE( 1 >= r3 );
        REQUIRE( r1 >= -8 );
        REQUIRE( r5 <= 0 );
        REQUIRE( r6 <= 0 );
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
        REQUIRE( r1 + r2 == 1 );
        REQUIRE( r4 - r1 == make_rational(9, 2) );
        REQUIRE( r2 * r3 == make_rational(1, 6) );
        REQUIRE( r1 / r3 == make_rational(3, 2) );
    }

    SECTION( "rational-integral arithmetic operators" )
    {
        REQUIRE( r1 + 1 == make_rational(3, 2) );
        REQUIRE( 2 + r2 == make_rational(5, 2) );
        REQUIRE( r3 - 3 == make_rational(-8, 3) );
        REQUIRE( 2 - r1 == make_rational(3, 2) );
        REQUIRE( r4 * 2 == 10 );
        REQUIRE( 6 * r2 == r1 * 6 );
        REQUIRE( 1 / r2 == 2 );
        REQUIRE( r3 / 3 == make_rational(1, 9) );
        REQUIRE( r1 / -2 == -1/4_r );
    }
}

TEST_CASE( "rational increment and decrement operators", "[rational]" )
{
    auto r1 = 2/5_r;
    REQUIRE( (r1++).numer() == 2 );
    REQUIRE( r1.numer() == 7 );
    REQUIRE( r1.denom() == 5 );
    REQUIRE( (--r1).numer() == 2 );

    auto r2 = 15/7_r;
    REQUIRE( (r2--).numer() == 15 );
    REQUIRE( r2.numer() == 8 );
    REQUIRE( r2.denom() == 7 );
    REQUIRE( (++r2).numer() == 15 );
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

        REQUIRE( abs(r1) == make_rational(1, 2) );
        REQUIRE( abs(r2) == make_rational(1, 2) );
        REQUIRE( abs(r1) == abs(r2) );
    }

    SECTION( "pow" )
    {
        using math::meta::pow;

        REQUIRE( pow(r1, 0) == make_rational(1, 1) );
        REQUIRE( pow(r2, 1) == r2 );
        REQUIRE( pow(r3, 3) == make_rational(64, 125) );
        REQUIRE( pow(r3, -3) == make_rational(pow(5, 3), pow(4, 3)) );
    }

    SECTION( "sign" )
    {
        using math::meta::sign;

        REQUIRE( sign(r0) == 0 );
        REQUIRE( sign(r1) == -1 );
        REQUIRE( sign(r2) == -1 );
        REQUIRE( sign(r3) == 1 );
        REQUIRE( sign(r1) == sign(r1.numer()) );
        REQUIRE( sign(r2) == sign(r2.numer()) );
    }

    SECTION( "reciprocal" )
    {
        REQUIRE( reciprocal(r1) == reciprocal(r2) );
    }

    SECTION( "invert" )
    {
        REQUIRE( r1.invert() == r2.invert() );
        REQUIRE( r1.numer() == -2 );
        REQUIRE( r2.denom() == 1 );
    }
}

TEST_CASE( "rational implicit casts", "[rational]" )
{
    REQUIRE_FALSE( 0_r );
    REQUIRE( bool(1_r) );
    REQUIRE( not not 8_r );

    REQUIRE( make_rational(1, 2) == make_rational(1L, 2L) );
    REQUIRE( make_rational(3ULL, 2ULL) == rational<unsigned short>(3, 2) );
}

TEST_CASE( "rational automatic normalization", "[rational]" )
{
    auto r0 = make_rational(1, -2);
    REQUIRE( r0.numer() == -1 );
    REQUIRE( r0.denom() == 2 );

    auto r1 = 1/2_r + 1/2_r;
    REQUIRE( r1.numer() == 1 );
    REQUIRE( r1.denom() == 1 );

    auto r2 = 3/2_r - 1/2_r;
    REQUIRE( r2.numer() == 1 );
    REQUIRE( r2.denom() == 1 );

    auto r3 = (2/3_r) * (3/2_r);
    REQUIRE( r3.numer() == 1 );
    REQUIRE( r3.denom() == 1 );

    auto r4 = 1/2_r * 2;
    REQUIRE( r4.numer() == 1 );
    REQUIRE( r4.denom() == 1 );

    auto r5 = (3/4_r) / (3/5_r);
    REQUIRE( r5.numer() == 5 );
    REQUIRE( r5.denom() == 4 );

    auto r6 = (3/4_r) / 3;
    REQUIRE( r6.numer() == 1 );
    REQUIRE( r6.denom() == 4 );

    auto r7 = make_rational(2, 4);
    REQUIRE( r7.numer() == 1 );
    REQUIRE( r7.denom() == 2 );
}

TEST_CASE( "rational integer overflow avoidance", "[rational]" )
{
    auto max = std::numeric_limits<int>::max();

    auto r1 = max/2_r;
    REQUIRE( r1 * 2 == max );

    auto r2 = 2_r / max;
    REQUIRE( r2 / 2 == 1_r / max );
}
