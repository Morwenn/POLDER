/*
 * Copyright (C) 2011-2014 Morwenn
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

int main()
{
    using namespace polder;

    // TEST: compare
    {
        using namespace std::string_literals;

        // scalar
        POLDER_ASSERT(compare(-8, 2) == -1);
        POLDER_ASSERT(compare(3, 3) == 0);
        POLDER_ASSERT(compare(8u, 3u) == 1);
        POLDER_ASSERT(compare(0.0, -0.0) == 0);

        // std::string
        POLDER_ASSERT(compare("hello"s, "world"s) == -1);
        POLDER_ASSERT(compare("kinky"s, "kinko"s) == 1);
        POLDER_ASSERT(compare("animals"s, "animals"s) == 0);
        POLDER_ASSERT(compare(""s, "foo"s) == -1);
        POLDER_ASSERT(compare("bar"s, ""s) == 1);
        POLDER_ASSERT(compare(""s, ""s) == 0);
    }
}
