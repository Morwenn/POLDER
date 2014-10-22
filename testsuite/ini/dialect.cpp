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
#include <POLDER/ini/dialect.h>
#include "catch.hpp"

using namespace polder;
using namespace ini;

TEST_CASE( "function ini::to_dialect", "[ini][dialect]" )
{
    SECTION( "default dialect" )
    {
        Dialect default_dial;
        REQUIRE( default_dial.delimiter == '=' );
        REQUIRE( default_dial.commentchar == ';' );
        REQUIRE( default_dial.escapechar == '\\' );
        REQUIRE( default_dial.lineterminator == '\n' );
        REQUIRE( default_dial.quotechar == '"' );
        REQUIRE( default_dial.doublequote == false );

        REQUIRE(
            to_dialect("", default_dial)
            == R"("")" );
        REQUIRE(
            to_dialect("foo", default_dial)
            == R"("foo")" );
        REQUIRE(
            to_dialect("\\", default_dial)
            == R"("\\")" );
        REQUIRE(
            to_dialect("foo\"bar", default_dial)
            == R"("foo\"bar")" );
        REQUIRE(
            to_dialect("foo\\bar", default_dial)
            == R"("foo\\bar")" );
        REQUIRE(
            to_dialect("foo\\\"bar", default_dial)
            == R"("foo\\\"bar")" );
        REQUIRE(
            to_dialect("foo\\\\bar", default_dial)
            == R"("foo\\\\bar")" );
        REQUIRE(
            to_dialect("a=;tref", default_dial)
            == R"("a=;tref")" );
    }

    SECTION( "double-quote dialect" )
    {
        Dialect dbquote_dial;
        dbquote_dial.doublequote = true;

        REQUIRE(
            to_dialect("", dbquote_dial)
            == R"("")" );
        REQUIRE(
            to_dialect("foo", dbquote_dial)
            == R"("foo")" );
        REQUIRE(
            to_dialect("\"", dbquote_dial)
            == R"("""")" );
        REQUIRE(
            to_dialect("foo\"bar", dbquote_dial)
            == R"("foo""bar")" );
        REQUIRE(
            to_dialect("foo\\bar", dbquote_dial)
            == R"("foo\bar")" );
        REQUIRE(
            to_dialect("foo\\\"bar", dbquote_dial)
            == R"("foo\""bar")" );
        REQUIRE(
            to_dialect("foo\\\\bar", dbquote_dial)
            == R"("foo\\bar")" );
        REQUIRE(
            to_dialect("a=;tref", dbquote_dial)
            == R"("a=;tref")" );
    }
}
