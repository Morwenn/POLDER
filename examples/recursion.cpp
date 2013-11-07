/*
 * Copyright (C) 2011-2013 Morwenn
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
#include <POLDER/recursion_array.h>

using namespace polder;


class MemoizedFibonacci;
namespace polder
{
    /*
     * We need to tell to the RecursionArray which
     * kind of data it has to store.
     */
    template<>
    struct types_t<MemoizedFibonacci>
    {
        using value_type = unsigned int;
    };
}

/**
 * @brief Fibonacci function class
 *
 * A way to implement the Fibonacci function and to force it
 * to store its results in order to gain some speed with the
 * following calls to the function.
 */
struct MemoizedFibonacci:
    RecursionArray<MemoizedFibonacci>
{
    using super = RecursionArray<MemoizedFibonacci>;

    /**
     * @brief Default constructor
     *
     * To use a Fibonacci function, we need to know at least
     * its first two values (for 0 and 1) which are 0 and 1.
     * We pass those values to the RecursionArray constructor.
     */
    MemoizedFibonacci():
        super( { 0, 1 } )
    {}

    /**
     * @brief Fibonacci function
     *
     * Fibonacci function considering that the first values are
     * already known. Also, "self" will call "function" and
     * memoize its results.
     *
     * @param n Wanted Fibonacci number
     * @return nth Fibonacci number
     */
    auto function(std::size_t n)
        -> unsigned int
    {
        return self(n-1) + self(n-2);
    }
};


int main()
{
    // We must declare the Fibonacci function in order to use it.
    // It is the major design issue of recursion arrays.
    MemoizedFibonacci fibonacci;

    // The Fibonacci numbers up to the nth are computed
    // and stored into the RecursionArray
    std::cout << fibonacci(12) << std::endl;    // 144
    std::cout << fibonacci(0) << std::endl;     // 0
    std::cout << fibonacci(1) << std::endl;     // 1
    std::cout << fibonacci(25) << std::endl;    // 75025
}
