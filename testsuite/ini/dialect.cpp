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
#include <catch.hpp>
#include <POLDER/ini/dialect.h>

using namespace polder;
using namespace ini;

TEST_CASE( "function ini::to_dialect", "[ini][dialect]" )
{
    SECTION( "default dialect" )
    {
        Dialect default_dial;
        CHECK( default_dial.delimiter == '=' );
        CHECK( default_dial.commentchar == ';' );
        CHECK( default_dial.escapechar == '\\' );
        CHECK( default_dial.lineterminator == '\n' );
        CHECK( default_dial.quotechar == '"' );
        CHECK( default_dial.doublequote == false );

        CHECK(
            to_dialect("", default_dial)
            == R"("")" );
        CHECK(
            to_dialect("foo", default_dial)
            == R"("foo")" );
        CHECK(
            to_dialect("\\", default_dial)
            == R"("\\")" );
        CHECK(
            to_dialect("foo\"bar", default_dial)
            == R"("foo\"bar")" );
        CHECK(
            to_dialect("foo\\bar", default_dial)
            == R"("foo\\bar")" );
        CHECK(
            to_dialect("foo\\\"bar", default_dial)
            == R"("foo\\\"bar")" );
        CHECK(
            to_dialect("foo\\\\bar", default_dial)
            == R"("foo\\\\bar")" );
        CHECK(
            to_dialect("a=;tref", default_dial)
            == R"("a=;tref")" );
    }

    SECTION( "double-quote dialect" )
    {
        Dialect dbquote_dial;
        dbquote_dial.doublequote = true;

        CHECK(
            to_dialect("", dbquote_dial)
            == R"("")" );
        CHECK(
            to_dialect("foo", dbquote_dial)
            == R"("foo")" );
        CHECK(
            to_dialect("\"", dbquote_dial)
            == R"("""")" );
        CHECK(
            to_dialect("foo\"bar", dbquote_dial)
            == R"("foo""bar")" );
        CHECK(
            to_dialect("foo\\bar", dbquote_dial)
            == R"("foo\bar")" );
        CHECK(
            to_dialect("foo\\\"bar", dbquote_dial)
            == R"("foo\""bar")" );
        CHECK(
            to_dialect("foo\\\\bar", dbquote_dial)
            == R"("foo\\bar")" );
        CHECK(
            to_dialect("a=;tref", dbquote_dial)
            == R"("a=;tref")" );
    }
}
