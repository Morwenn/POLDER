/*
 * Headers
 */
#include <cstdlib>
#include <iostream>
#include <POLDER/recursion_array.h>
#include <POLDER/singleton.h>

using namespace polder;


/**
 * Fibonacci function class
 *
 * A way to implement the Fibonacci function and to force it
 * to store its results in order to gain some speed with the
 * following calls to the function.
 */
class _fibo:
    public Singleton<_fibo>,                // Ensure that there will be only one occurence of _fibo
    public RecursionArray<unsigned int>     // "unsigned int" is the returned type of the Fibonacci function
{
    public:

        /**
         * @brief Default constructor
         *
         * To use a Fibonacci function, we need to know at least
         * its two first values (for 0 and 1) which are 0 and 1.
         * We pass those values to the RecursionArray constructor.
         */
        _fibo():
            RecursionArray<unsigned int>( { 0, 1 } )
        {}

    private:

        /**
         * @brief Fibonacci function
         *
         * Fibonacci function considering that the first values are
         * already known. Also, "self" will call "function" and
         * memoize its results.
         *
         * @param n Wanted Fibonacci number
         * @return nth Fibonacci number
         *
         */
        unsigned int function(size_t n)
        {
            return self(n-1) + self(n-2);
        }
};


/**
 * @brief Entry point of application
 *
 * @return Application exit code
*/
int main()
{
    // We must declare the Fibonacci function in order to use it.
    // It is the major design issue of recursion arrays.
    _fibo fibonacci;

    // Should print 144
    // The Fibonacci numbers up to the 12th are computed and
    // stored in the RecursionArray
    std::cout << fibonacci(12) << std::endl;

    // We try to create another _fibo instance
    // The program crashes if you uncomment the following line
    // _fibo fibo2;

    return EXIT_SUCCESS;
}
