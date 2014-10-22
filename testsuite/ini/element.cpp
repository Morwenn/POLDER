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
#include <typeindex>
#include <POLDER/ini/element.h>
#include "catch.hpp"

using namespace polder;
using namespace ini;

TEST_CASE( "ini element class",  "[ini][element]" )
{
    SECTION( "std::string" )
    {
        Element a;
        REQUIRE( a.type_id == typeid(std::string) );
        REQUIRE( std::string(a) == "" );

        Element b(std::string("foobar"));
        REQUIRE( b.type_id == typeid(std::string) );
        REQUIRE( std::string(b) == "foobar" );

        Element c("hameggs");
        REQUIRE( c.type_id == typeid(std::string) );
        REQUIRE( std::string(c) == "hameggs" );
    }

    SECTION( "integer types" )
    {
        Element d(45);
        REQUIRE( d.type_id == typeid(int) );
        REQUIRE( std::string(d) == "45" );

        Element e(-84L);
        REQUIRE( e.type_id == typeid(long) );
        REQUIRE( std::string(e) == "-84" );

        Element f(0LL);
        REQUIRE( f.type_id == typeid(long long) );
        REQUIRE( std::string(f) == "0" );

        Element g(456U);
        REQUIRE( g.type_id == typeid(unsigned) );
        REQUIRE( std::string(g) == "456" );

        Element h(199UL);
        REQUIRE( h.type_id == typeid(unsigned long) );
        REQUIRE( std::string(h) == "199" );

        Element i(78ULL);
        REQUIRE( i.type_id == typeid(unsigned long long) );
        REQUIRE( std::string(i) == "78" );
    }

    SECTION( "floating point types" )
    {
        Element j(3.52f);
        REQUIRE( j.type_id == typeid(float) );
        //REQUIRE( std::string(j) == "3.52" );

        Element k(85.23);
        REQUIRE( k.type_id == typeid(double) );
        //REQUIRE( std::string(k) == "85.23" );

        Element l(21.57l);
        REQUIRE( l.type_id == typeid(long double) );
        //REQUIRE( std::string(l) == "21.27" );
    }
}
