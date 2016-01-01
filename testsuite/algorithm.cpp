/*
 * Copyright (C) 2014-2016 Morwenn
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
#include <forward_list>
#include <string>
#include <catch.hpp>
#include <POLDER/algorithm.h>

using namespace polder;

TEST_CASE( "compare algorithm", "[algorithm]" )
{
    SECTION( "scalar types" )
    {
        CHECK( compare(-8, 2) == -1 );
        CHECK( compare(3, 3) == 0 );
        CHECK( compare(8u, 3u) == 1 );
        CHECK( compare(0.0, -0.0) == 0 );
    }

    SECTION( "std::string" )
    {
        using namespace std::string_literals;

        CHECK( compare("hello"s, "world"s) == -1 );
        CHECK( compare("kinky"s, "kinko"s) == 1 );
        CHECK( compare("animals"s, "animals"s) == 0 );
        CHECK( compare(""s, "foo"s) == -1 );
        CHECK( compare("bar"s, ""s) == 1 );
        CHECK( compare(""s, ""s) == 0 );
    }
}

TEST_CASE( "is_sorted algorithms", "[algorithm]" )
{
    SECTION( "min_element_and_is_sorted" )
    {
        std::forward_list<int> li1 = { 1, 4, 5, 8, 9 };
        auto res1 = min_element_and_is_sorted(li1.begin(), li1.end());
        CHECK( res1.min == li1.begin() );
        CHECK( *(res1.min) == 1 );
        CHECK( res1.is_sorted );

        std::forward_list<int> li2 = { 4, 8, 3, 2, 1, 5, 6 };
        auto res2 = min_element_and_is_sorted(li2.begin(), li2.end());
        CHECK( *(res2.min) == 1 );
        CHECK( not res2.is_sorted );
    }

    SECTION( "max_element_and_is_sorted" )
    {
        std::forward_list<int> li1 = { 1, 4, 5, 8, 9 };
        auto res1 = max_element_and_is_sorted(li1.begin(), li1.end());
        CHECK( std::next(res1.max) == li1.end() );
        CHECK( *(res1.max) == 9 );
        CHECK( res1.is_sorted );

        std::forward_list<int> li2 = { 4, 8, 3, 2, 1, 5, 6 };
        auto res2 = max_element_and_is_sorted(li2.begin(), li2.end());
        CHECK( res2.max == std::next(li2.begin()) );
        CHECK( *(res2.max) == 8 );
        CHECK( not res2.is_sorted );
    }

    SECTION( "min_element_and_is_sorted_until" )
    {
        std::forward_list<int> li1 = { 1, 4, 5, 8, 9 };
        auto res1 = min_element_and_is_sorted_until(li1.begin(), li1.end());
        CHECK( res1.min == li1.begin() );
        CHECK( *(res1.min) == 1 );
        CHECK( res1.until == li1.end() );

        std::forward_list<int> li2 = { 4, 8, 3, 2, 1, 5, 6 };
        auto res2 = min_element_and_is_sorted_until(li2.begin(), li2.end());
        CHECK( *(res2.min) == 1 );
        CHECK( *(res2.until) == 3 );
    }

    SECTION( "max_element_and_is_sorted_until" )
    {
        std::forward_list<int> li1 = { 1, 4, 5, 8, 9 };
        auto res1 = max_element_and_is_sorted_until(li1.begin(), li1.end());
        CHECK( std::next(res1.max) == li1.end() );
        CHECK( *(res1.max) == 9 );
        CHECK( res1.until == li1.end() );

        std::forward_list<int> li2 = { 4, 8, 3, 2, 1, 5, 6 };
        auto res2 = max_element_and_is_sorted_until(li2.begin(), li2.end());
        CHECK( res2.max == std::next(li2.begin()) );
        CHECK( *(res2.max) == 8 );
        CHECK( *(res2.until) == 3 );
    }
}
