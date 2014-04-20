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
inline int foo(const char* a, unsigned b)
{
    return int(a[0]) + unsigned(b);
}


int main()
{
    auto memo_foo = memoized(foo);

    std::cout << foo("bar", 42) << '\n'
              << memo_foo("bar", 42) << '\n'
              << memo_foo("bar", 43) << '\n'
              << memo_foo("bar", 44) << '\n'
              << memo_foo("bar", 42) << '\n';

    std::function<int(const char*, unsigned)> ffoo = foo;
    auto memo_ffoo = memoized(ffoo);

    std::cout << ffoo("bar", 42) << '\n'
              << memo_ffoo("bar", 42) << '\n'
              << memo_ffoo("bar", 43) << '\n'
              << memo_ffoo("bar", 44) << '\n'
              << memo_ffoo("bar", 42) << '\n';

    auto lambda = [](const char* a, unsigned b)
    {
        return int(a[0]) + unsigned(b);
    };
    auto memo_lambda = memoized(lambda);

    std::cout << lambda("bar", 42) << '\n'
              << memo_lambda("bar", 42) << '\n'
              << memo_lambda("bar", 43) << '\n'
              << memo_lambda("bar", 44) << '\n'
              << memo_lambda("bar", 42) << '\n';
}
