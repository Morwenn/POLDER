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
#include <cstdlib>
#include <functional>
#include <POLDER/evaluation.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "evaluation of mathematical expressions", "[evaluate]" )
{
    SECTION( "simple test cases for expressions" )
    {
        evaluator<double> eval;

        REQUIRE( eval("4") == 4 );
        REQUIRE( eval("4 + 9") == 13 );
        REQUIRE( eval("-4 + -4.2") == -8.2 );
        REQUIRE( eval("4 * 9") == 36 );
        REQUIRE( eval("2 + 7 * 3") == 23 );
        REQUIRE( eval("7 * 3 + 2") == 23 );
        REQUIRE( eval("7 - 3") == 4 );
        REQUIRE( eval("7 / 3") == 7.0 / 3.0 );
        REQUIRE( eval("7 // 3") == 7 / 3 );
        REQUIRE( eval("7 + 3 - 2 * 5 / 8 + 4 * 3 - 9") == 7 + 3 - 2 * 5.0 / 8 + 4 * 3 - 9 );
        REQUIRE( eval("-5 * 2") == -10 );
        REQUIRE( eval("-1 * 5 * 4/2 - 8*9 - 16+1") == -1 * 5 * 4.0/2 - 8*9 - 16+1 );
        REQUIRE( eval("10 - 6 - 4") == 0 );
        REQUIRE( eval("2 * 8 / 4**2 * 2.5") == 2.5 );
        REQUIRE( eval("2 * (3 + 7)") == 20 );
        REQUIRE( eval("5!!=!8") == true );
        REQUIRE( eval("5! = 5*4*3*2*1") == true );
        REQUIRE( eval("5!") == eval("5*4*3*2*1") );
    }

    SECTION( "evaluation of bitwise operations" )
    {
        evaluator<unsigned> eval;

        REQUIRE( eval("0 | 1") == 1u );
        REQUIRE( eval("0 & 1") == 0u );
        REQUIRE( eval("0 ^ 1") == 1u );

        REQUIRE( eval("2 | 5") == 7u );
    }

    SECTION( "evaluation of unary functions" )
    {
        evaluator<int> eval;

        eval.connect("abs", [](int n) {
            return std::abs(n);
        });

        REQUIRE( eval("abs(5)") == 5 );
        REQUIRE( eval("abs(-3)") == 3 );
        REQUIRE( eval("5 * abs(-6) + 2") == 32 );
        REQUIRE( eval("-abs(-3)") == -3 );
    }

    SECTION( "disconnection and reconnection of callbacks" )
    {
        evaluator<int> eval;

        eval.connect("less", [](int a, int b) {
            return a < b;
        });

        REQUIRE( eval("less(1, 2)") == true );
        REQUIRE( eval("less(-3, 5)") == true );
        REQUIRE( eval("less(5, -1)") == false );

        eval.disconnect("less");
        eval.connect("less", std::less<int>{});

        REQUIRE( eval("less(1, 2)") == true );
        REQUIRE( eval("less(-3, 5)") == true );
        REQUIRE( eval("less(5, -1)") == false );
    }

    SECTION( "fun with parenthesis" )
    {
        evaluator<int> eval;

        REQUIRE( eval("(0)") == 0 );
        REQUIRE( eval("((1))") == 1 );
        REQUIRE( eval("(((2)))") == 2 );
        REQUIRE( eval("((((((42))))))") == 42 );

        eval.connect("abs", [](int n) {
            return std::abs(n);
        });

        REQUIRE( eval("abs((2))") == 2 );
        REQUIRE( eval("abs((-3))") == 3 );

        eval.connect("add", std::plus<int>{});

        REQUIRE( eval("(add(2, 3))") == 5 );
        REQUIRE( eval("add((2), 3)") == 5 );
        REQUIRE( eval("add(2, (3))") == 5 );
        REQUIRE( eval("add((2), (3))") == 5 );
        REQUIRE( eval("add(add(2, 5), 3)") == 10 );
        REQUIRE( eval("add(2, add(5, 3))") == 10 );
        REQUIRE( eval("add(add(1, 2), add(3, 4))") == 10 );
    }
}
