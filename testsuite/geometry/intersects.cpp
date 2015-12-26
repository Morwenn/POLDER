/*
 * Copyright (C) 2015 Morwenn
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
#include <POLDER/geo2d.h>

using namespace polder::geo2d;

TEST_CASE( "whether a line and a hypersphere intersect", "[geometry][line][hypersphere]" )
{
    Point<int> origin;
    Circle<int> circle = { origin, 2 };

    Point<int> pt1 = { 0, 3 };
    Line<int> line1 = { origin, pt1 };
    CHECK( intersects(line1, circle) );

    Point<int> pt2 = { 3, 3 };
    Line<int> line2 = { pt1, pt2 };
    CHECK( not intersects(line2, circle) );
}

TEST_CASE( "whether two hyperspheres intersect", "[geometry][hypersphere]" )
{
    Point<int> origin;
    Circle<int> cir1 = { origin, 2 };
    Circle<int> cir2 = { origin, 3 };

    CHECK( intersects(cir1, cir1) );
    CHECK( not intersects(cir1, cir2) );

    Circle<int> cir3 = { { 0, 4 }, 1 };
    Circle<int> cir4 = { { 0, 4 }, 2 };
    Circle<int> cir5 = { { 0, 4 }, 3 };

    CHECK( not intersects(cir1, cir3) );
    CHECK( intersects(cir1, cir4) );
    CHECK( intersects(cir1, cir5) );
}
