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
#include <catch.hpp>
#include <POLDER/math/cmath.h>

TEST_CASE( "modern cmath-like functions", "[math]" )
{
    using namespace polder;
    using namespace math;

    SECTION( "abs" )
    {
        CHECK( meta::abs(-5) == 5 );
        CHECK( meta::abs(8) == 8 );
        CHECK( meta::abs(-82L) == 82 );
    }

    SECTION( "min" )
    {
        CHECK( meta::min(1, 2) == 1 );
        CHECK( meta::min(0, 0) == 0 );
        CHECK( meta::min(-2, -1, 0, 1, 2) == -2 );
        CHECK( meta::min(2, 1, 0, -1, -2) == -2 );
    }

    SECTION( "max" )
    {
        CHECK( meta::max(3, 8) == 8 );
        CHECK( meta::max(-8, -8) == -8 );
        CHECK( meta::max(8, -1, 6, 3, 5, 2, -8) == 8 );
        CHECK( meta::max(-1, 0, 1, 2, 3, 2, 1, 0, -1) == 3 );
    }

    SECTION( "floor" )
    {
        CHECK( meta::floor(2.5) == 2.0 );
        CHECK( meta::floor(2.01) == 2.0 );
        CHECK( meta::floor(2.8) == 2.0 );
        CHECK( meta::floor(-2.5) == -3.0 );
    }

    SECTION( "ceil" )
    {
        CHECK( meta::ceil(2.5) == 3.0 );
        CHECK( meta::ceil(2.01) == 3.0 );
        CHECK( meta::ceil(2.8) == 3.0 );
        CHECK( meta::ceil(-2.5) == -2.0 );
    }

    SECTION( "round" )
    {
        CHECK( meta::round(2.5) == 3.0 );
        CHECK( meta::round(2.01) == 2.0 );
        CHECK( meta::round(2.8) == 3.0 );
        CHECK( meta::round(-2.1) == -2.0 );
    }

    SECTION( "trunc" )
    {
        CHECK( meta::trunc(2.5) == 2.0 );
        CHECK( meta::trunc(2.01) == 2.0 );
        CHECK( meta::trunc(2.8) == 2.0 );
        CHECK( meta::trunc(-2.1) == -2.0 );
    }

    SECTION( "pow" )
    {
        CHECK( meta::pow(2, 0) == 1 );
        CHECK( meta::pow(2.0, 1) == 2.0 );
        CHECK( meta::pow(5, 1) == 5 );
        CHECK( meta::pow(5.8, 0) == 1.0 );
        CHECK( meta::pow(2, 1) == 2 );
        CHECK( meta::pow(2, 2) == 4 );
        CHECK( meta::pow(5.0, -6) == 1.0 / meta::pow(5.0, 6) );
        CHECK( meta::pow(2.0, -3) == 1.0 / meta::pow(2.0, 3) );
    }

    SECTION( "sqrt" )
    {
        CHECK(meta::sqrt(4.0) == Approx(2.0) );
        CHECK(meta::sqrt(2.0) == Approx(1.414213562373095) );
        CHECK(meta::sqrt(3.0) == Approx(1.732050807568877) );
    }
}
