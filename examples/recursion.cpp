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
#include <POLDER/recursion_array.h>

using namespace polder;


// Forward declaration
struct memoized_fibonacci;

namespace polder
{
    /*
     * We need to tell to the recursion_array which
     * kind of data it has to store.
     */
    template<>
    struct types_t<memoized_fibonacci>
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
struct memoized_fibonacci:
    recursion_array<memoized_fibonacci>
{
    using super = recursion_array<memoized_fibonacci>;

    /**
     * @brief Default constructor
     *
     * To use a Fibonacci function, we need to know at least
     * its first two values (for 0 and 1) which are 0 and 1.
     * We pass those values to the recursion_array constructor.
     */
    memoized_fibonacci():
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
        -> types_t<memoized_fibonacci>::value_type
    {
        return self(n-1) + self(n-2);
    }
};


int main()
{
    // We must declare the Fibonacci function in order to use it.
    // It is the major design issue of recursion arrays.
    memoized_fibonacci fibonacci;

    // The Fibonacci numbers up to the nth are computed
    // and stored into the recursion_array
    std::cout << fibonacci(12)  << '\n';    // 144
    std::cout << fibonacci(0)   << '\n';    // 0
    std::cout << fibonacci(1)   << '\n';    // 1
    std::cout << fibonacci(25)  << '\n';    // 75025
}
