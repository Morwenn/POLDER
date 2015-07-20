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
#include <POLDER/math/formula.h>
#include "catch.hpp"

using namespace polder;
using namespace math;

TEST_CASE( "runtime math formula", "[math]" )
{
    SECTION( "sign" )
    {
        CHECK( sign(5) == 1 );
        CHECK( sign(-3) == -1 );
        CHECK( sign(2.0) == 1 );
        CHECK( sign(-5.8) == -1 );
        CHECK( sign(0) == 0 );
        CHECK( sign(0.0) == 0 );
    }

    SECTION( "sum" )
    {
        CHECK( sum(1, 2, 3, 4, 5) == 15 );
        CHECK( sum(1.0, 2.0, 3, 4, 5) == 15.0 );
    }

    SECTION( "mean" )
    {
        CHECK( mean(2, 2, 2) == 2 );
        CHECK( mean(2, 4, 3) == 3 );
    }

    SECTION( "clamp" )
    {
        CHECK( clamp(3, 2, 4) == 3 );
        CHECK( clamp(1, 2, 4) == 2 );
        CHECK( clamp(5, 2, 4) == 4 );
    }

    SECTION( "is_even" )
    {
        CHECK( is_even(5) == false );
        CHECK( is_even(-4) == true );
        CHECK( is_even(0) == true );
    }

    SECTION( "is_odd" )
    {
        CHECK( is_odd(8) == false );
        CHECK( is_odd(0) == false );
        CHECK( is_odd(-5) == true );
    }

    SECTION( "is_prime" )
    {
        CHECK( is_prime(0) == false );
        CHECK( is_prime(1) == false );
        CHECK( is_prime(2) == true );
        CHECK( is_prime(3) == true );
        CHECK( is_prime(4) == false );
        CHECK( is_prime(5) == true );
        CHECK( is_prime(7) == true );
        CHECK( is_prime(8) == false );
        CHECK( is_prime(9) == false );
        CHECK( is_prime(128) == false );
    }

    SECTION( "fibonacci" )
    {
        CHECK( fibonacci(0) == 0 );
        CHECK( fibonacci(1) == 1 );
        CHECK( fibonacci(2) == 1 );
        CHECK( fibonacci(3) == 2 );
        CHECK( fibonacci(4) == 3 );
        CHECK( fibonacci(5) == 5 );
        CHECK( fibonacci(6) == 8 );
        CHECK( fibonacci(7) == 13 );
        CHECK( fibonacci(8) == 21 );
    }

    SECTION( "gcd" )
    {
        CHECK( gcd(1071, 1029) == 21 );
        CHECK( gcd(1029, 1071) == 21 );
        CHECK( gcd(270, 84) == 6 );
        CHECK( gcd(84, 270) == 6 );

        CHECK( gcd(3, 6) == 3 );
        CHECK( gcd(-3, 6) == 3 );
        CHECK( gcd(3, -6) == 3 );
        CHECK( gcd(-3, -6) == 3 );
    }

    SECTION( "lcm" )
    {
        CHECK( lcm(60, 168) == 840 );
        CHECK( lcm(168, 60) == 840 );
    }

    SECTION( "modpow" )
    {
        CHECK( modpow(4, 13, 497) == 445 );
    }
}

TEST_CASE( "compile time math formula", "[math]" )
{
    SECTION( "sign" )
    {
        static_assert(meta::sign(5) == 1, "");
        static_assert(meta::sign(-3) == -1, "");
        static_assert(meta::sign(2.0) == 1, "");
        static_assert(meta::sign(-5.8) == -1, "");
        static_assert(meta::sign(0) == 0, "");
        static_assert(meta::sign(0.0) == 0, "");
    }

    SECTION( "sum" )
    {
        static_assert(meta::sum(1, 2, 3, 4, 5) == 15, "");
        static_assert(meta::sum(1.0, 2.0, 3, 4, 5) == 15.0, "");
    }

    SECTION( "mean" )
    {
        static_assert(meta::mean(2, 2, 2) == 2, "");
        static_assert(meta::mean(2, 4, 3) == 3, "");
    }

    SECTION( "clamp" )
    {
        static_assert(meta::clamp(3, 2, 4) == 3, "");
        static_assert(meta::clamp(1, 2, 4) == 2, "");
        static_assert(meta::clamp(5, 2, 4) == 4, "");
    }

    SECTION( "is_even" )
    {
        static_assert(meta::is_even(5) == false, "");
        static_assert(meta::is_even(-4) == true, "");
        static_assert(meta::is_even(0) == true, "");
    }

    SECTION( "is_odd" )
    {
        static_assert(meta::is_odd(8) == false, "");
        static_assert(meta::is_odd(0) == false, "");
        static_assert(meta::is_odd(-5) == true, "");
    }

    SECTION( "is_prime" )
    {
        static_assert(meta::is_prime(0) == false, "");
        static_assert(meta::is_prime(1) == false, "");
        static_assert(meta::is_prime(2) == true, "");
        static_assert(meta::is_prime(3) == true, "");
        static_assert(meta::is_prime(4) == false, "");
        static_assert(meta::is_prime(5) == true, "");
        static_assert(meta::is_prime(7) == true, "");
        static_assert(meta::is_prime(8) == false, "");
        static_assert(meta::is_prime(9) == false, "");
        static_assert(meta::is_prime(128) == false, "");
    }

    SECTION( "fibonacci" )
    {
        static_assert(meta::fibonacci(0) == 0, "");
        static_assert(meta::fibonacci(1) == 1, "");
        static_assert(meta::fibonacci(2) == 1, "");
        static_assert(meta::fibonacci(3) == 2, "");
        static_assert(meta::fibonacci(4) == 3, "");
        static_assert(meta::fibonacci(5) == 5, "");
        static_assert(meta::fibonacci(6) == 8, "");
        static_assert(meta::fibonacci(7) == 13, "");
        static_assert(meta::fibonacci(8) == 21, "");
    }

    SECTION( "gcd" )
    {
        static_assert(meta::gcd(1071, 1029) == 21, "");
        static_assert(meta::gcd(1029, 1071) == 21, "");
        static_assert(meta::gcd(270, 84) == 6, "");
        static_assert(meta::gcd(84, 270) == 6, "");
    }

    SECTION( "gcd" )
    {
        static_assert(meta::gcd(3, 6) == 3, "");
        static_assert(meta::gcd(-3, 6) == 3, "");
        static_assert(meta::gcd(3, -6) == 3, "");
        static_assert(meta::gcd(-3, -6) == 3, "");
    }

    SECTION( "lcm" )
    {
        static_assert(meta::lcm(60, 168) == 840, "");
        static_assert(meta::lcm(168, 60) == 840, "");
    }

    SECTION( "modpow" )
    {
        static_assert(meta::modpow(4, 13, 497) == 445, "");
    }
}
