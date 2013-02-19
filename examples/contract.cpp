#include <cassert>
#include <cmath>
#include <iostream>
#include <POLDER/contract.h>

using namespace polder;


// Simple class with two functions
struct Foo
{
    static unsigned int sum(unsigned int a, unsigned int b)
    {
        return a + b;
    }

    static double sqrt(double a)
    {
        return std::sqrt(a);
    }

    static double bar(int a)
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
    POLDER_MAKE_CONTRACT(Foo)
    {
        POLDER_INVARIANTS(
            assert(0 < 1);
            assert(3 >= 2);
        );

        static unsigned int sum(unsigned int a, unsigned int b)
        {
            check invariants;

            // precondition: none
            auto res = Foo::sum(a, b);
            // postcondition:
            assert(res >= a+b);
            return res;
        }

        static double sqrt(double a)
        {
            check invariants;

            // precondition:
            assert(a >= 0.0);
            auto res = Foo::sqrt(a);
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
    double c = math::sqrt(-2.0); // Should crach here in debug mode

    int d = math::sum(2, 3);
    int e = math::sum(9, 10);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    return 0;
}
