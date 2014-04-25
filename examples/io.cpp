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
#include <cstdio>
#include <iostream>
#include <string>
#include <POLDER/io.h>

using namespace polder;
using namespace io;

/**
 * @brief Entry point of application
 *
 * @return Application exit code
 */
int main()
{
    ////////////////////////////////////////////////////////////
    {
        std::cout << "fgetl example\n";

        // Open a file
        FILE* f = std::fopen("io_example.txt", "r");
        if (f == nullptr)
        {
            std::cerr << "Can't open the file.\n";
            exit(1);
        }

        // line is the file reader.
        // Be sure to set it to nullptr before calling the function;
        // otherwise it "may" work but won't be safe.
        char* line = nullptr;
        // This function reads the file the same way fgets does
        // However, it can read a line, no matter its size.
        while (fgetl(line, f))
        {
            std::cout << line;
        }
    }

    ////////////////////////////////////////////////////////////
    {
        std::cout << "\nprint examples\n";

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

    ////////////////////////////////////////////////////////////
    {
        std::cout << "\nFile and io::open example\n";

        // Open a file
        File f = open("io_example.txt", "r");

        // Read and display all the lines
        for (const std::string& line: f)
        {
            std::cout << line;
        }
        // Close the file
        f.close();
    }
}
