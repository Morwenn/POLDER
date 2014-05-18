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
#include <cmath>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <POLDER/itertools.h>

using namespace polder;
using namespace itertools;

/**
 * @brief Simple wrapper around std::abs
 *
 * Used here to prevent a GCC bug that makes it
 * impossible to deduce a function parameter type
 * if not passed by const reference.
 */
int abs(const int& x);
double sin(const double& x);

/**
 * @brief Filter for even number
 *
 * Returns true if \a i is odd.
 */
bool even_filter(const int& i);


/**
 * @brief Entry point of application
 *
 * @return Application exit code
 */
int main()
{
    ////////////////////////////////////////////////////////////
    {
        std::cout << "Range Example\n";

        // Range of integers
        for (int i: range(20, -35, 5))
        {
            std::cout << i << " ";
            if (i < -10)
            {
                // Range is a generator.
                // The remaining numbers won't even be computed.
                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nReversed Example\n";

        std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7 };
        for (int& i: reversed(vec))
        {
            i *= 2;
            // Will print all the elements of vec
            // in the reversed order.
            std::cout << i << " ";
        }

        std::cout << '\n';
        int tab[] = { 8, 9, 10, 11, 12 };
        for (int& i: reversed(tab))
        {
            // Will print all the elements of vec
            // in the reversed order.
            std::cout << i << " ";
        }
    }


    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nMap Example\n";

        std::list<int> li = { 1, -2, 3, 4, -5, -6, 7 };
        for (int i: map(&abs, li))
        {
            std::cout << i << " ";
        }

        std::cout << '\n';
        double tab[] = { 0.0, -0.5, 3.14, -1.1 };
        for (double i: map(&sin, tab))
        {
            std::cout << i << " ";
        }
    }

    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nFilter Example\n";

        std::list<int> li = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        for (int i: filter(&even_filter, li))
        {
            std::cout << i << " ";
        }

        std::cout << '\n';
        double tab[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        for (int i: filter(&even_filter, tab))
        {
            std::cout << i << " ";
        }
    }

    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nChain Example\n";

        std::vector<int> vec = { 1, 2, 3, 4, 5 };
        std::list<int>    li = { 6, 7, 8, 9, 10 };
        std::deque<int>  deq = { 11, 12, 13, 14, 15 };
        for (int& i: chain(vec, li, deq))
        {
            // You can edit a range of iterables
            // as if there was only one of them.
            i *= 5;

            std::cout << i << " ";
        }
    }

    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nNested Chain Example\n";

        std::vector<int> vec = { 1, 2, 3, 4, 5 };
        std::list<int>    li = { 6, 7, 8, 9, 10 };
        std::deque<int>  deq = { 11, 12, 13, 14, 15 };
        for (int& i: chain(vec, chain(li, deq)))
        {
            std::cout << i << " ";
        }

        std::cout << '\n';
        for (int& i: chain(chain(vec, li), deq))
        {
            std::cout << i << " ";
        }
    }


    ////////////////////////////////////////////////////////////
    {
        std::cout << "\n\nZip Example\n";

        std::list<int> integers         = { 0, 1, 2 };
        std::list<const char*> strings  = { "one", "two", "three" };
        for (const auto& i: zip(integers, strings))
        {
            std::cout << std::get<0>(i) << " "
                      << std::get<1>(i) << '\n';
        }
    }


    ////////////////////////////////////////////////////////////
    {
        std::cout << "\nMixed Tools Example\n";

        std::vector<int> vec = { 1, 2, 3, 4, 5 };
        std::list<int>   li  = { 6, 7, 8, 9, 10 };
        for (int& i: chain(vec, reversed(li)))
        {
            // Some of the tools can be used
            // altogether in order to make the
            // manipulation of them easier.
            i -= 2;

            std::cout << i << " ";
        }

        std::cout << '\n';
        std::deque<int> deq = { -11, 12, -13, -14, 15 };
        for (int i: reversed(map(&abs, deq)))
        {
            std::cout << i << " ";
        }
    }
}


int abs(const int& x)
{
    return std::abs(x);
}

double sin(const double& x)
{
    return std::sin(x);
}

bool even_filter(const int& i)
{
    return i % 2;
}
