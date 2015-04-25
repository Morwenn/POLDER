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
#include <POLDER/evaluate.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "evaluation of mathematical expressions", "[evaluate]" )
{
    SECTION( "simple test cases for expressions" )
    {
        REQUIRE( evaluate("4") == 4 );
        REQUIRE( evaluate("4 + 9") == 13 );
        REQUIRE( evaluate("-4 + -4.2") == -8.2 );
        REQUIRE( evaluate("4 * 9") == 36 );
        REQUIRE( evaluate("2 + 7 * 3") == 23 );
        REQUIRE( evaluate("7 * 3 + 2") == 23 );
        REQUIRE( evaluate("7 - 3") == 4 );
        REQUIRE( evaluate("7 / 3") == 7.0 / 3.0 );
        REQUIRE( evaluate("7 // 3") == 7 / 3 );
        REQUIRE( evaluate("7 + 3 - 2 * 5 / 8 + 4 * 3 - 9") == 7 + 3 - 2 * 5.0 / 8 + 4 * 3 - 9 );
        REQUIRE( evaluate("-5 * 2") == -10 );
        REQUIRE( evaluate("-1 * 5 * 4/2 - 8*9 - 16+1") == -1 * 5 * 4.0/2 - 8*9 - 16+1 );
        REQUIRE( evaluate("10 - 6 - 4") == 0 );
        REQUIRE( evaluate("2 * 8 / 4**2 * 2.5") == 2.5 );
        REQUIRE( evaluate("2 * (3 + 7)") == 20 );
        REQUIRE( evaluate("5!!=!8") == true );
        REQUIRE( evaluate("5! = 5*4*3*2*1") == true );
        REQUIRE( evaluate("5!") == evaluate("5*4*3*2*1") );
    }
}
