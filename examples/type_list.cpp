/*
 * Headers
 */
#include <iostream>
#include <POLDER/type_list.h>

using namespace polder;


/**
 * @brief Entry point of application
 *
 * @return Application exit code
*/
int main()
{
    // The simplest way to create a list of type
    // and use is is to use a simple typedef/using
    using types = type_list<int, long, float, double, char>;

    // Number of types in the list
    std::cout << types::size << std::endl;

    // Type at position 3 in the list
    using type_3        = types::at<3>;
    // First type in the list
    using type_front    = types::front;
    // Last type in the list
    using type_back     = types::back;

    type_3 a        = 5;
    type_front b    = 4;
    type_back c     = a + b;

    std::cout << int(c) << std::endl;

    // NOTE: If a type at a position greater
    // than the actual type_list size is asked
    // by the user, the returned type will be
    // void

    using empty = type_list<>;
    using temp = types::cat<empty>;
    using cat = temp::cat<type_list<int>>;

    cat::at<2> d = 1l;
    (void) d;

    return 0;
}
