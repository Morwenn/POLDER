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
#include <type_traits>
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
    std::cout << types::size << '\n';

    // Type at position 3 in the list
    using type_3        = types::at<3>;
    static_assert(std::is_same<type_3, double>::value, "");
    // First type in the list
    using type_front    = types::front;
    static_assert(std::is_same<type_front, int>::value, "");
    // Last type in the list
    using type_back     = types::back;
    static_assert(std::is_same<type_back, char>::value, "");

    type_3 a        = 5;
    type_front b    = 4;
    type_back c     = a + b;

    std::cout << int(c) << '\n';

    // NOTE: If a type at a position greater
    // than the actual type_list size is asked
    // by the user, the returned type will be
    // void

    // Empty type list
    using empty = type_list<>;
    static_assert(std::is_same<empty::at<0>, void>::value, "");
    static_assert(empty::size == 0, "");
    // Concatenation of empty list
    using temp = types::cat<empty>;
    static_assert(temp::size == types::size, "");
    // Concatenation of lists
    using cat = temp::cat<type_list<int, double>>;
    static_assert(std::is_same<cat::back, double>::value, "");
    static_assert(cat::size == types::size+2, "");

    cat::at<2> d = 1l;
    std::cout << d << '\n';

    // push functions
    struct dummy {};
    using new_1 = types::push_back<dummy>;
    using new_2 = types::push_front<dummy>;
    static_assert(std::is_same<new_1::back, dummy>::value, "");
    static_assert(std::is_same<new_2::front, dummy>::value, "");

    // pop functions
    using new_3 = types::pop_back;
    using new_4 = types::pop_front;
    static_assert(std::is_same<new_3::back, double>::value, "");
    static_assert(std::is_same<new_4::front, long>::value, "");
}
