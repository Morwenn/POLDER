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
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "point basic operations", "[geometry][point]" )
{
    using Point = geometry::Point<2u, int>;

    Point origin;
    Point a(48, 23);
    Point b = { 48, 23 };

    SECTION( "indexing and basic observers" )
    {
        // default construction
        REQUIRE( origin[0] == 0 );
        REQUIRE( origin[1] == 0 );
        REQUIRE( origin.x() == 0 );
        REQUIRE( origin.y() == 0 );
        REQUIRE( *(origin.begin()) == 0 );

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
        REQUIRE( Point(2, 3) != a );
    }
}

TEST_CASE( "point relational operators", "[geometry][point]" )
{
    using Point = geometry::Point<3u, int>;

    Point origin;
    Point pt1 = { 2, 1, 1 };
    Point pt2 = { 1, 3, 5 };
    Point pt3 = { 1, 3, 4 };
    Point pt4 = { -5, 2, 6 };

    REQUIRE( origin < pt1 );
    REQUIRE( origin < pt2 );
    REQUIRE( origin > pt4 );
    REQUIRE( origin >= origin );
    REQUIRE( origin <= origin );

    REQUIRE( pt2 >= pt3 );
    REQUIRE( pt3 <= pt2 );
    REQUIRE( pt2 > pt3 );
    REQUIRE( pt3 < pt2 );
}

TEST_CASE( "point-vector arithmetic", "[geometry][point][vector]" )
{
    using Point = geometry::Point<2u, int>;
    using Vector = geometry::Vector<2u, int>;

    Point a = { 2, 3 };
    Point b = { 6, 8 };
    Point c = { 5, -3 };
    Vector vec = { -1, 8 };

    SECTION( "point-point subtraction" )
    {
        REQUIRE( b - a == Vector(4, 5) );
        REQUIRE( a - b == Vector(-4, -5) );
        REQUIRE( b - a == -(a - b) );
    }

    SECTION( "point-vector addition" )
    {
        REQUIRE( c + vec == Point(4, 5) );
        REQUIRE( b + vec == vec + b );
    }

    SECTION( "point-vector subtraction" )
    {
        REQUIRE( a - vec == Point(3, -5) );
        REQUIRE( b - vec == Point(7, 0) );
        REQUIRE( c - vec == Point(6, -11) );
    }
}
