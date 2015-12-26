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
#include <catch.hpp>
#include <POLDER/ini/element.h>

using namespace polder;
using namespace ini;

TEST_CASE( "ini element class",  "[ini][element]" )
{
    SECTION( "std::string" )
    {
        Element a;
        CHECK( a.type_id == typeid(std::string) );
        CHECK( std::string(a) == "" );

        Element b(std::string("foobar"));
        CHECK( b.type_id == typeid(std::string) );
        CHECK( std::string(b) == "foobar" );

        Element c("hameggs");
        CHECK( c.type_id == typeid(std::string) );
        CHECK( std::string(c) == "hameggs" );
    }

    SECTION( "integer types" )
    {
        Element d(45);
        CHECK( d.type_id == typeid(int) );
        CHECK( std::string(d) == "45" );

        Element e(-84L);
        CHECK( e.type_id == typeid(long) );
        CHECK( std::string(e) == "-84" );

        Element f(0LL);
        CHECK( f.type_id == typeid(long long) );
        CHECK( std::string(f) == "0" );

        Element g(456U);
        CHECK( g.type_id == typeid(unsigned) );
        CHECK( std::string(g) == "456" );

        Element h(199UL);
        CHECK( h.type_id == typeid(unsigned long) );
        CHECK( std::string(h) == "199" );

        Element i(78ULL);
        CHECK( i.type_id == typeid(unsigned long long) );
        CHECK( std::string(i) == "78" );
    }

    SECTION( "floating point types" )
    {
        Element j(3.52f);
        CHECK( j.type_id == typeid(float) );
        CHECK( std::string(j) == "3.52" );

        Element k(85.23);
        CHECK( k.type_id == typeid(double) );
        CHECK( std::string(k) == "85.23" );

        Element l(21.57l);
        CHECK( l.type_id == typeid(long double) );
        CHECK( std::string(l) == "21.27" );
    }
}
