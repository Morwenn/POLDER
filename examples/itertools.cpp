// Headers
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <POLDER/itertools.h>

using std::list;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::get;
using std::abs;
using polder::itertools::range;
using polder::itertools::reversed;
using polder::itertools::map;
using polder::itertools::chain;
using polder::itertools::zip;


/**
 * @def in
 * Python's "in" keyword. Macros are evil.
 * Anyway, that one is funny/ugly.
 */
#define in :


/**
 * @brief Simple wrapper around std::abs
 *
 * Used here to prevent a GCC bug that makes it
 * impossible to deduce a function parameter type
 * if not passed by const reference.
 */
int safe_abs(const int& x);


/**
 * @brief Entry point of application
 *
 * @return Application exit code
 */
int main()
{
    ////////////////////////////////////////////////////////////
    {
        cout << "Range Example" << endl;

        // Range of integers
        for (int i in range(20, -35, 5))
        {
            cout << i << " ";
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
        cout << endl << endl << "Reversed Example" << endl;

        vector<int> vec = { 1, 2, 3, 4, 5, 6, 7 };
        for (int& i in reversed(vec))
        {
            i *= 2;
            // Will print all the elements of vec
            // in the reversed order.
            cout << i << " ";
        }

        cout << endl;
        int tab[] = { 8, 9, 10, 11, 12 };
        for (int& i in reversed(tab))
        {
            // Will print all the elements of vec
            // in the reversed order.
            cout << i << " ";
        }
    }


    ////////////////////////////////////////////////////////////
    {
        cout << endl << endl << "Map Example" << endl;

        list<int> li = { 1, -2, 3, 4, -5, -6, 7 };
        for (int i in map(&safe_abs, li))
        {
            cout << i << " ";
        }
    }


    ////////////////////////////////////////////////////////////
    {
        cout << endl << endl << "Chain Example" << endl;

        vector<int> vec = { 1, 2, 3, 4, 5 };
        list<int>   li  = { 6, 7, 8, 9, 10, 11, 12, 13 };
        for (auto& i in chain(vec, li))
        {
            // You can edit a range of iterables
            // as if there was only one of them.
            i *= 5;

            cout << i << " ";
        }
    }


    ////////////////////////////////////////////////////////////
    {
        cout << endl << endl << "Zip Example" << endl;

        list<int> integers          = { 0, 1, 2 };
        list<const char*> strings   = { "one", "two", "three" };
        for (const auto& i in zip(integers, strings))
        {
            cout << get<0>(i) << " " << get<1>(i) << endl;
        }
    }


    ////////////////////////////////////////////////////////////
    {
        cout << endl << "Mixed Tools Example" << endl;

        vector<int> vec = { 1, 2, 3, 4, 5 };
        list<int>   li  = { 6, 7, 8, 9, 10 };
        for (auto& i in chain(vec, reversed(li)))
        {
            // Some of the tools can be used
            // altogether in order to make the
            // manipulation of them easier.
            i -= 2;

            cout << i << " ";
        }
    }

    return 0;
}


int safe_abs(const int& x)
{
    return abs(x);
}
