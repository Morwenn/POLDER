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
#include <iostream>
#include <string>
#include <POLDER/io.h>

using namespace polder;

int main()
{
    ////////////////////////////////////////////////////////////
    {
        std::cout << "print examples\n";

        int a = 5;
        double b = 6.3;
        std::string c = "Hello";

        // This function is some kind of wrapper around std::ostream.
        // You can pass any type that can be added to an ostream by
        // the << operator.
        print(a, b, c, "World!");

        // The results can be forwarded to the given output stream
        // instead of always being fed to std::cout.
        print(std::cerr, 5.3, 2, "Hey!");
    }
}
