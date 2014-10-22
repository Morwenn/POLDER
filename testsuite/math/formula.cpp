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
        REQUIRE( sign(5) == 1 );
        REQUIRE( sign(-3) == -1 );
        REQUIRE( sign(2.0) == 1 );
        REQUIRE( sign(-5.8) == -1 );
        REQUIRE( sign(0) == 0 );
        REQUIRE( sign(0.0) == 0 );
    }

    SECTION( "sum" )
    {
        REQUIRE( sum(1, 2, 3, 4, 5) == 15 );
        REQUIRE( sum(1.0, 2.0, 3, 4, 5) == 15.0 );
    }

    SECTION( "mean" )
    {
        REQUIRE( mean(2, 2, 2) == 2 );
        REQUIRE( mean(2, 4, 3) == 3 );
    }

    SECTION( "clamp" )
    {
        REQUIRE( clamp(3, 2, 4) == 3 );
        REQUIRE( clamp(1, 2, 4) == 2 );
        REQUIRE( clamp(5, 2, 4) == 4 );
    }

    SECTION( "is_even" )
    {
        REQUIRE( is_even(5) == false );
        REQUIRE( is_even(-4) == true );
        REQUIRE( is_even(0) == true );
    }

    SECTION( "is_odd" )
    {
        REQUIRE( is_odd(8) == false );
        REQUIRE( is_odd(0) == false );
        REQUIRE( is_odd(-5) == true );
    }

    SECTION( "is_prime" )
    {
        REQUIRE( is_prime(0) == false );
        REQUIRE( is_prime(1) == false );
        REQUIRE( is_prime(2) == true );
        REQUIRE( is_prime(3) == true );
        REQUIRE( is_prime(4) == false );
        REQUIRE( is_prime(5) == true );
        REQUIRE( is_prime(7) == true );
        REQUIRE( is_prime(8) == false );
        REQUIRE( is_prime(9) == false );
        REQUIRE( is_prime(128) == false );
    }

    SECTION( "fibonacci" )
    {
        REQUIRE( fibonacci(0) == 0 );
        REQUIRE( fibonacci(1) == 1 );
        REQUIRE( fibonacci(2) == 1 );
        REQUIRE( fibonacci(3) == 2 );
        REQUIRE( fibonacci(4) == 3 );
        REQUIRE( fibonacci(5) == 5 );
        REQUIRE( fibonacci(6) == 8 );
        REQUIRE( fibonacci(7) == 13 );
        REQUIRE( fibonacci(8) == 21 );
    }

    SECTION( "gcd" )
    {
        REQUIRE( gcd(1071, 1029) == 21 );
        REQUIRE( gcd(1029, 1071) == 21 );
        REQUIRE( gcd(270, 84) == 6 );
        REQUIRE( gcd(84, 270) == 6 );

        REQUIRE( gcd(3, 6) == 3 );
        REQUIRE( gcd(-3, 6) == 3 );
        REQUIRE( gcd(3, -6) == 3 );
        REQUIRE( gcd(-3, -6) == 3 );
    }

    SECTION( "lcm" )
    {
        REQUIRE( lcm(60, 168) == 840 );
        REQUIRE( lcm(168, 60) == 840 );
    }

    SECTION( "modpow" )
    {
        REQUIRE( modpow(4, 13, 497) == 445 );
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
