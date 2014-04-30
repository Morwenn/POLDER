/*
 * Copyright (C) 2014 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <string>
#include <POLDER/ini/dialect.h>

int main()
{
    using namespace polder;
    using namespace ini;

    // TEST: default dialect
    {
        Dialect default_dial;
        POLDER_ASSERT(default_dial.delimiter == '=');
        POLDER_ASSERT(default_dial.commentchar == ';');
        POLDER_ASSERT(default_dial.escapechar == '\\');
        POLDER_ASSERT(default_dial.lineterminator == '\n');
        POLDER_ASSERT(default_dial.quotechar == '"');
        POLDER_ASSERT(default_dial.doublequote == false);

        POLDER_ASSERT(
            to_dialect("", default_dial)
            == R"("")");
        POLDER_ASSERT(
            to_dialect("foo", default_dial)
            == R"("foo")");
        POLDER_ASSERT(
            to_dialect("\\", default_dial)
            == R"("\\")");
        POLDER_ASSERT(
            to_dialect("foo\"bar", default_dial)
            == R"("foo\"bar")");
        POLDER_ASSERT(
            to_dialect("foo\\bar", default_dial)
            == R"("foo\\bar")");
        POLDER_ASSERT(
            to_dialect("foo\\\"bar", default_dial)
            == R"("foo\\\"bar")");
        POLDER_ASSERT(
            to_dialect("foo\\\\bar", default_dial)
            == R"("foo\\\\bar")");
        POLDER_ASSERT(
            to_dialect("a=;tref", default_dial)
            == R"("a=;tref")");
    }

    // TEST: double-quote dialect
    {
        Dialect dbquote_dial;
        dbquote_dial.doublequote = true;

        POLDER_ASSERT(
            to_dialect("", dbquote_dial)
            == R"("")");
        POLDER_ASSERT(
            to_dialect("foo", dbquote_dial)
            == R"("foo")");
        POLDER_ASSERT(
            to_dialect("\"", dbquote_dial)
            == R"("""")");
        POLDER_ASSERT(
            to_dialect("foo\"bar", dbquote_dial)
            == R"("foo""bar")");
        POLDER_ASSERT(
            to_dialect("foo\\bar", dbquote_dial)
            == R"("foo\bar")");
        POLDER_ASSERT(
            to_dialect("foo\\\"bar", dbquote_dial)
            == R"("foo\""bar")");
        POLDER_ASSERT(
            to_dialect("foo\\\\bar", dbquote_dial)
            == R"("foo\\bar")");
        POLDER_ASSERT(
            to_dialect("a=;tref", dbquote_dial)
            == R"("a=;tref")");
    }
}
