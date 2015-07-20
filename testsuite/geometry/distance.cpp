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
#include <POLDER/geo2d.h>
#include <POLDER/math/distnorm.h>
#include "catch.hpp"

using namespace polder::geo2d;
using namespace polder::math::dist;

TEST_CASE( "Manhattan distance", "[geometry][distnorm]" )
{
    Point<int> x = { 1, -5 };
    Point<int> y = { -2, 3 };
    CHECK( distance<manhattan>(x, y) == distance<manhattan>(y, x) );
    CHECK( distance<manhattan>(x, y) == 11 );
}

TEST_CASE( "Euclidean distance", "[geometry][distnorm]" )
{
    Point<int> x = { 2, -1 };
    Point<int> y = { -2, 2 };
    CHECK( distance(x, y) == distance(y, x) );
    CHECK( distance(x, y) == distance<euclidean>(x, y) );
    CHECK( distance(x, y) == 5 );
}
