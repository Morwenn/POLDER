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
#include <string>
#include <POLDER/algorithm.h>
#include "catch.hpp"

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
