/*
 * Headers
 */
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <POLDER/itertools.h>

using std::list;
using std::vector;
using std::cout;
using std::endl;
using polder::itertools::range;
using polder::itertools::reversed;
using polder::itertools::map;
using polder::itertools::chain;


/**
 * @def in
 * Python's "in" keyword. Macros are evil.
 * Anyway, that one is fun/ugly.
 */
#define in :


/**
 * @brief Entry point of application
 *
 * @return Application exit code
*/
int main()
{
    ////////////////////////////////////////////////////////////
    cout << "Range Example" << endl;

    // Range of integers
    for (int i in range(20, -35, 5))
    {
        cout << i << endl;
        if (i < -10)
        {
            // Range is a generator.
            // The remaining numbers won't even be computed.
            break;
        }
    }


    ////////////////////////////////////////////////////////////
    cout << endl << "Reversed Example" << endl;

    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7 };
    for (int& i in reversed(vec))
    {
        i *= 2;
        // Will print all the elements of vec
        // in the reversed order.
        cout << i << endl;
    }


    ////////////////////////////////////////////////////////////
    cout << endl << "Map Example" << endl;

    list<int> li = { 1, -2, 3, 4, -5, -6, 7 };
    for (int i in map(&abs, li))
    {
        cout << i << endl;
    }


    ////////////////////////////////////////////////////////////
    cout << endl << "Chain Example" << endl;

    vector<int> v   = { 1, 2, 3, 4, 5  };
    vector<int> l   = { 6, 7, 8, 9, 10 };
    for (int& i in chain(v, l))
    {
        // You can edit a range of iterables
        // as if there was only one of them.
        i *= 5;

        cout << i << endl;
    }


    return EXIT_SUCCESS;
}

