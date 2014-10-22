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
#include <POLDER/geometry/vector.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "vector basic operations", "[geometry][vector]" )
{
    using Vector = geometry::Vector<2u, int>;

    Vector foo;
    Vector a(48, 23);
    Vector b = { 48, 23 };

    SECTION( "indexing and basic observers" )
    {
        // default construction
        REQUIRE( foo[0] == 0 );
        REQUIRE( foo[1] == 0 );
        REQUIRE( foo.x() == 0 );
        REQUIRE( foo.y() == 0 );
        REQUIRE( *(foo.begin()) == 0 );

        REQUIRE( a[0] == 48 );
        REQUIRE( a[1] == 23 );
        REQUIRE( a.x() == 48 );
        REQUIRE( a.y() == 23 );
        REQUIRE( *(a.begin()) == 48 );

        REQUIRE( b[0] == 48 );
        REQUIRE( b[1] == 23 );
        REQUIRE( b.x() == 48 );
        REQUIRE( b.y() == 23 );
        REQUIRE( *(b.begin()) == 48 );
    }

    SECTION( "comparison operators" )
    {
        REQUIRE( a == b );
        REQUIRE_FALSE( a != b );
        REQUIRE( Vector(2, 3) != a );
    }
}

TEST_CASE( "vector-scalar operators", "[geometry][vector]" )
{
    using Vector = geometry::Vector<2u, int>;

    SECTION( "multiplication" )
    {
        Vector a = { 3, 5 };

        REQUIRE( 2 * a == Vector(6, 10) );
        REQUIRE( a * 3 == Vector(9, 15) );
        REQUIRE( a * 15 == 15 * a );
    }

    SECTION( "division" )
    {
        Vector a = { 12, 6 };

        REQUIRE( a / 2 == Vector(6, 3) );
        REQUIRE( a / 3 == Vector(4, 2) );
        REQUIRE( a / 2*2 == a );
        REQUIRE( a == 3*a / 3 );
    }
}

TEST_CASE( "vector dot product", "[geometry][vector]" )
{
    using Vector2 = geometry::Vector<2u, int>;
    using Vector3 = geometry::Vector<3u, int>;

    Vector3 a = { 1, 3, -5 };
    Vector3 b = { 4, -2, -1 };
    REQUIRE( a * b == 3 );
    REQUIRE( a * b == b*a );

    Vector3 c = { 1, 2, 3 };
    Vector3 d = { 4, -5, 6 };
    REQUIRE( c * d == 12 );

    Vector2 e = { -4, -9 };
    Vector2 f = { -1, 2 };
    REQUIRE( e * f == -14 );
}

TEST_CASE( "vector arithmetic", "[geometry][vector]" )
{
    using Vector = geometry::Vector<2u, int>;

    Vector a = { 2, 3 };
    Vector b = { 6, 8 };

    SECTION( "opposite" )
    {
        REQUIRE( -a == Vector(-2, -3) );
        REQUIRE( -b == Vector(-6, -8) );
    }

    SECTION( "addition" )
    {
        REQUIRE( a + b == Vector(8, 11) );
        REQUIRE( a + b == b + a );
    }

    SECTION( "subtraction" )
    {
        REQUIRE( b - a == Vector(4, 5) );
        REQUIRE( a - b == Vector(-4, -5) );
        REQUIRE( b - a == -(a - b) );
        REQUIRE( a - b == a + (-b) );
    }
}

TEST_CASE( "vector norms", "[geometry][vector][distnorm]" )
{
    using namespace polder::geometry;
    using namespace polder::math::norm;

    Vector<3u> test = { 4.0, -2.0, 6.0 };

    REQUIRE( test.norm()            == Approx(test.norm<euclidean>()) );
    REQUIRE( test.norm<manhattan>() == Approx(12.0) );
    REQUIRE( test.norm<euclidean>() == Approx(7.483314773547883) );
    REQUIRE( test.norm<uniform>()   == Approx(6.0) );

    REQUIRE( test.norm(3u)    == Approx(test.norm<p>(3u)) );
    REQUIRE( test.norm<p>(3u) == Approx(6.603854497789253) );
    REQUIRE( test.norm<p>(5u) == Approx(6.154769770788126) );
}
