/*
 * Headers
 */
#include <cmap>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <POLDER/itertools.h>

using std::vector;
using std::cout;
using std::endl;
using polder::itertools::range;
using polder::itertools::reversed;
using polder::itertools::map;


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

    vector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7 };
    for (int i in map(vec_1))
    {
        cout << i << endl;
    }


    return EXIT_SUCCESS;
}

