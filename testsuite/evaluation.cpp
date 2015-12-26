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
#include <catch.hpp>
#include <POLDER/evaluation.h>

using namespace polder;

TEST_CASE( "evaluation of mathematical expressions", "[evaluate]" )
{
    SECTION( "simple test cases for expressions" )
    {
        evaluator<double> eval;

        CHECK( eval("4") == 4 );
        CHECK( eval("4 + 9") == 13 );
        CHECK( eval("-4 + -4.2") == -8.2 );
        CHECK( eval("4 * 9") == 36 );
        CHECK( eval("2 + 7 * 3") == 23 );
        CHECK( eval("7 * 3 + 2") == 23 );
        CHECK( eval("7 - 3") == 4 );
        CHECK( eval("7 / 3") == 7.0 / 3.0 );
        CHECK( eval("7 // 3") == 7 / 3 );
        CHECK( eval("7 + 3 - 2 * 5 / 8 + 4 * 3 - 9") == 7 + 3 - 2 * 5.0 / 8 + 4 * 3 - 9 );
        CHECK( eval("-5 * 2") == -10 );
        CHECK( eval("-1 * 5 * 4/2 - 8*9 - 16+1") == -1 * 5 * 4.0/2 - 8*9 - 16+1 );
        CHECK( eval("10 - 6 - 4") == 0 );
        CHECK( eval("2 * 8 / 4**2 * 2.5") == 2.5 );
        CHECK( eval("2 * (3 + 7)") == 20 );
        CHECK( eval("5!!=!8") == true );
        CHECK( eval("5! = 5*4*3*2*1") == true );
        CHECK( eval("5!") == eval("5*4*3*2*1") );
    }

    SECTION( "evaluation of bitwise operations" )
    {
        evaluator<unsigned> eval;

        CHECK( eval("0 | 1") == 1u );
        CHECK( eval("0 & 1") == 0u );
        CHECK( eval("0 ^ 1") == 1u );

        CHECK( eval("2 | 5") == 7u );
    }

    SECTION( "evaluation of unary functions" )
    {
        evaluator<int> eval;

        eval.connect("abs", [](int n) {
            return std::abs(n);
        });

        CHECK( eval("abs(5)") == 5 );
        CHECK( eval("abs(-3)") == 3 );
        CHECK( eval("5 * abs(-6) + 2") == 32 );
        CHECK( eval("-abs(-3)") == -3 );
    }

    SECTION( "disconnection and reconnection of callbacks" )
    {
        evaluator<int> eval;

        eval.connect("less", [](int a, int b) {
            return a < b;
        });

        CHECK( eval("less(1, 2)") == true );
        CHECK( eval("less(-3, 5)") == true );
        CHECK( eval("less(5, -1)") == false );

        eval.disconnect("less");
        eval.connect("less", std::less<int>{});

        CHECK( eval("less(1, 2)") == true );
        CHECK( eval("less(-3, 5)") == true );
        CHECK( eval("less(5, -1)") == false );
    }

    SECTION( "fun with parenthesis" )
    {
        evaluator<int> eval;

        CHECK( eval("(0)") == 0 );
        CHECK( eval("((1))") == 1 );
        CHECK( eval("(((2)))") == 2 );
        CHECK( eval("((((((42))))))") == 42 );

        eval.connect("abs", [](int n) {
            return std::abs(n);
        });

        CHECK( eval("abs((2))") == 2 );
        CHECK( eval("abs((-3))") == 3 );

        eval.connect("add", std::plus<int>{});

        CHECK( eval("(add(2, 3))") == 5 );
        CHECK( eval("add((2), 3)") == 5 );
        CHECK( eval("add(2, (3))") == 5 );
        CHECK( eval("add((2), (3))") == 5 );
        CHECK( eval("add(add(2, 5), 3)") == 10 );
        CHECK( eval("add(2, add(5, 3))") == 10 );
        CHECK( eval("add(add(1, 2), add(3, 4))") == 10 );
    }
}
