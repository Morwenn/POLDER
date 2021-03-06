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
#include <limits>
#include <type_traits>
#include <catch.hpp>
#include <POLDER/gray.h>

using namespace polder;

TEST_CASE( "gray codes convert to and from unsigned integers", "[gray]" )
{
    SECTION( "gray codes convert to and from zero" )
    {
        constexpr auto zero = gray(0u);

        static_assert(zero == 0u, "");
        static_assert(zero.value == 0b0000u, "");
    }

    SECTION( "gray codes convert to and from some unsigned integer" )
    {
        constexpr auto gr = gray(5u);

        static_assert(gr == 5u, "");
        static_assert(gr.value == 0b0111u, "");
    }

    SECTION( "gray codes convert to and from max unsigned integer" )
    {
        constexpr auto max_uint = std::numeric_limits<unsigned>::max();
        constexpr auto max_gr = gray(max_uint);

        static_assert(max_gr == max_uint, "");
    }
}

TEST_CASE( "gray codes value construction", "[gray]" )
{
    gray_code<unsigned> gr1{};
    CHECK( gr1.value == 0u );

    gray_code<unsigned long long> gr2{};
    CHECK( gr2.value == 0ull );
}

TEST_CASE( "gray codes operator=", "[gray]" )
{
    gray_code<unsigned> gr1, gr2;

    SECTION( "assignment from gray codes" )
    {
        gr1 = gray(58u);
        gr2 = gray(22u);

        CHECK( gr1 == gray(58u) );
        CHECK( gr2 == gray(22u) );
        CHECK( gr1 == 58u );
        CHECK( 22u == gr2 );
    }

    SECTION( "assignment from unsigned integers" )
    {
        gr1 = 73u;
        gr2 = 194u;

        CHECK( gr1 == gray(73u) );
        CHECK( gr2 == gray(194u) );
        CHECK( gr1 == 73u );
        CHECK( 194u == gr2 );
    }
}

TEST_CASE( "gray codes comparison operators", "[gray]" )
{
    constexpr auto gr = gray(52u);

    static_assert(gr == gray(52u), "");
    static_assert(gr == 52u, "");
    static_assert(52u == gr, "");
    static_assert(gr != 56u, "");
    static_assert(54u != gr, "");
    static_assert(gr != gray(89u), "");
}

TEST_CASE( "gray codes bitwise operations", "[gray]" )
{
    auto gr1 = gray(42u);
    auto gr2 = gray(28u);

    CHECK( (gr1 & gr2).value == (gr1.value & gr2.value) );
    CHECK( (gr1 | gr2).value == (gr1.value | gr2.value) );
    CHECK( (gr1 ^ gr2).value == (gr1.value ^ gr2.value) );
    CHECK( (~gr1).value == ~(gr1.value) );
    CHECK( (gr1 << 3u).value == (gr1.value << 3u) );
    CHECK( (gr1 >> 2u).value == (gr1.value >> 2u) );
}

TEST_CASE( "unsigned-gray bitwise assignment operations", "[gray]" )
{
    unsigned a = 0b0110u;
    unsigned b = 0b1001u;
    unsigned c = 0b1101u;

    a |= gray(0u);
    CHECK( a == 0b0110u );
    a &= gray(4u);
    CHECK( a == 0b0110u );

    b |= gray(9u);
    CHECK( b == 0b1101u );

    c ^= gray(5u);
    CHECK( c == 0b1010u );
}

TEST_CASE( "gray() function type inference", "[gray]" )
{
    auto llgr = gray(8ull);
    using value_type = decltype(llgr)::value_type;

    static_assert(std::is_same<value_type, unsigned long long>::value, "");
}

TEST_CASE( "math operations for gray codes", "[gray][math]" )
{
    SECTION( "is_even" )
    {
        REQUIRE_FALSE( is_even(gray(5u)) );
        CHECK( is_even(gray(4u)) );
        CHECK( is_even(gray(0u)) );
    }

    SECTION( "is_odd" )
    {
        REQUIRE_FALSE( is_odd(gray(8u)) );
        REQUIRE_FALSE( is_odd(gray(0u)) );
        CHECK( is_odd(gray(5u)) );
    }
}

TEST_CASE( "gray code increment", "[gray]" )
{
    unsigned i = 0u;
    for (auto val = gray(0u) ; val != gray(10u) ; ++val, ++i)
    {
        CHECK( val == i );
    }

    i = 0u;
    for (auto val = gray(0u) ; val != gray(10u) ; val++, i++)
    {
        CHECK( val == i );
    }

    SECTION( "circular overflow on increment" )
    {
        auto max_uint = std::numeric_limits<unsigned>::max();
        auto gr = gray(max_uint);

        ++gr;
        CHECK( gr.value == 0u );
    }
}

TEST_CASE( "gray code decrement", "[gray]" )
{
    unsigned i = 35u;
    for (auto val = gray(35u) ; val != gray(23u) ; --val, --i)
    {
        CHECK( val == i );
    }

    i = 35u;
    for (auto val = gray(35u) ; val != gray(23u) ; val--, i--)
    {
        CHECK( val == i );
    }

    SECTION( "circular overflow on decrement" )
    {
        auto max_uint = std::numeric_limits<unsigned>::max();
        auto gr = gray(0u);

        --gr;
        CHECK( gr == gray(max_uint) );
    }
}
