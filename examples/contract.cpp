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
#include <iostream>
#include <POLDER/contract.h>

using namespace polder;


// Simple class with two functions
struct Foo
{
    static auto sum(unsigned int a, unsigned int b)
        -> unsigned int
    {
        return a + b;
    }

    static auto sqrt(double a)
        -> double
    {
        return std::sqrt(a);
    }

    static auto bar(int a)
        -> double
    {
        return double(a);
    }
};


namespace polder
{
    // We used a little trick to separete implementation
    // from preconditions and postconditions
    //
    // Also, note that the way this is used is non-intrusive
    // and can be used to check conditions on almost any
    // existing class
    //
    // It is also possible to add preprocessor directives not
    // to compile this if NDEBUG is on
    POLDER_CONTRACT(Foo)
    {
        static auto sum(unsigned int a, unsigned int b)
            -> unsigned int
        {
            // precondition: none
            auto res = super::sum(a, b);
            // postcondition:
            POLDER_ASSERT(res >= a+b);
            return res;
        }

        static auto sqrt(double a)
            -> double
        {
            // precondition:
            POLDER_ASSERT(a >= 0.0);
            auto res = super::sqrt(a);
            // postcondition: none
            return res;
        }

        // If a function from Foo is not checked here, the
        // unchecked function will be used instead
        // It is the case of bar in this example
    };
}


int main()
{
    // contract<Foo> checks the conditions in debug mode
    // but is just the same as Foo if NDEBUG is on
    using math = contract<Foo>;

    double a = math::bar(5);

    double b = math::sqrt(4.0);
    double c = math::sqrt(-2.0); // Should crash here in debug mode

    int d = math::sum(2, 3);
    int e = math::sum(9, 10);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
}
