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
#include <POLDER/geometry/vector.h>

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
        CHECK( foo[0] == 0 );
        CHECK( foo[1] == 0 );
        CHECK( foo.x() == 0 );
        CHECK( foo.y() == 0 );
        CHECK( *(foo.begin()) == 0 );

        CHECK( a[0] == 48 );
        CHECK( a[1] == 23 );
        CHECK( a.x() == 48 );
        CHECK( a.y() == 23 );
        CHECK( *(a.begin()) == 48 );

        CHECK( b[0] == 48 );
        CHECK( b[1] == 23 );
        CHECK( b.x() == 48 );
        CHECK( b.y() == 23 );
        CHECK( *(b.begin()) == 48 );
    }

    SECTION( "comparison operators" )
    {
        CHECK( a == b );
        REQUIRE_FALSE( a != b );
        CHECK( Vector(2, 3) != a );
    }
}

TEST_CASE( "vector-scalar operators", "[geometry][vector]" )
{
    using Vector = geometry::Vector<2u, int>;

    SECTION( "multiplication" )
    {
        Vector a = { 3, 5 };

        CHECK( 2 * a == Vector(6, 10) );
        CHECK( a * 3 == Vector(9, 15) );
        CHECK( a * 15 == 15 * a );
    }

    SECTION( "division" )
    {
        Vector a = { 12, 6 };

        CHECK( a / 2 == Vector(6, 3) );
        CHECK( a / 3 == Vector(4, 2) );
        CHECK( a / 2*2 == a );
        CHECK( a == 3*a / 3 );
    }
}

TEST_CASE( "vector dot product", "[geometry][vector]" )
{
    using Vector2 = geometry::Vector<2u, int>;
    using Vector3 = geometry::Vector<3u, int>;

    Vector3 a = { 1, 3, -5 };
    Vector3 b = { 4, -2, -1 };
    CHECK( a * b == 3 );
    CHECK( a * b == b*a );

    Vector3 c = { 1, 2, 3 };
    Vector3 d = { 4, -5, 6 };
    CHECK( c * d == 12 );

    Vector2 e = { -4, -9 };
    Vector2 f = { -1, 2 };
    CHECK( e * f == -14 );
}

TEST_CASE( "vector arithmetic", "[geometry][vector]" )
{
    using Vector = geometry::Vector<2u, int>;

    Vector a = { 2, 3 };
    Vector b = { 6, 8 };

    SECTION( "opposite" )
    {
        CHECK( -a == Vector(-2, -3) );
        CHECK( -b == Vector(-6, -8) );
    }

    SECTION( "addition" )
    {
        CHECK( a + b == Vector(8, 11) );
        CHECK( a + b == b + a );
    }

    SECTION( "subtraction" )
    {
        CHECK( b - a == Vector(4, 5) );
        CHECK( a - b == Vector(-4, -5) );
        CHECK( b - a == -(a - b) );
        CHECK( a - b == a + (-b) );
    }
}

TEST_CASE( "vector norms", "[geometry][vector][distnorm]" )
{
    using namespace polder::geometry;
    using namespace polder::math::norm;

    Vector<3u> test = { 4.0, -2.0, 6.0 };

    CHECK( test.norm()            == Approx(test.norm<euclidean>()) );
    CHECK( test.norm<manhattan>() == Approx(12.0) );
    CHECK( test.norm<euclidean>() == Approx(7.483314773547883) );
    CHECK( test.norm<uniform>()   == Approx(6.0) );

    CHECK( test.norm(3u)    == Approx(test.norm<p>(3u)) );
    CHECK( test.norm<p>(3u) == Approx(6.603854497789253) );
    CHECK( test.norm<p>(5u) == Approx(6.154769770788126) );
}
