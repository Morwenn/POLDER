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
#include <functional>
#include <iostream>
#include <POLDER/functional.h>

using namespace polder;


/**
 * @brief Test function to be memoized.
 */
inline double foo(double a, unsigned b)
{
    return a + b;
}

int main()
{
    ////////////////////////////////////////////////////////////
    // memoized
    {
        auto memo_foo = memoized(foo);

        std::cout << foo(8.5, 42) << '\n'
                  << memo_foo(8.5, 42) << '\n'
                  << memo_foo(8.5, 43) << '\n'
                  << memo_foo(8.5, 44) << '\n'
                  << memo_foo(8.5, 42) << '\n';

        std::function<double(double, unsigned)> ffoo = foo;
        auto memo_ffoo = memoized(ffoo);

        std::cout << ffoo(8.5, 42) << '\n'
                  << memo_ffoo(8.5, 42) << '\n'
                  << memo_ffoo(8.5, 43) << '\n'
                  << memo_ffoo(8.5, 44) << '\n'
                  << memo_ffoo(8.5, 42) << '\n';

        auto lambda = [](double a, unsigned b)
        {
            return a + b;
        };
        auto memo_lambda = memoized(lambda);

        std::cout << lambda(8.5, 42) << '\n'
                  << memo_lambda(8.5, 42) << '\n'
                  << memo_lambda(8.5, 43) << '\n'
                  << memo_lambda(8.5, 44) << '\n'
                  << memo_lambda(8.5, 42) << '\n';
    }
}
