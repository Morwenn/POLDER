/*
 * Copyright (C) 2014 Morwenn
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
#include <list>
#include <map>
#include <tuple>
#include <type_traits>
#include <vector>
#include <POLDER/compiler.h>
#include <POLDER/iterator.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "EBCO for transform_iterator", "[iterator][compiler]" )
{
    using iterator = std::list<int>::iterator;

    auto lambda = [](int dummy)
    {
        return dummy;
    };

    if (compiler::has_ebco_for<std::tuple>())
    {
        REQUIRE(
            sizeof(transform_iterator<iterator, decltype(lambda)>) <
            sizeof(transform_iterator<iterator, int(*)(int)>)
        );
    }
}

TEST_CASE( "get_iterator", "[iterator]" )
{
    std::map<std::string, int> foo = {
        { "foobar",     4  },
        { "borzaz",     8  },
        { "bornibus",   32 },
        { "eggs",       21 },
        { "hamspam",    2  },
        { "polder",     3  },
        { "tempel",     5  }
    };

    using key_it_t      = get_iterator<0, std::map<std::string, int>::iterator>;
    using value_it_t    = get_iterator<1, std::map<std::string, int>::iterator>;

    SECTION( "get_iterator member types" )
    {
        static_assert(std::is_same<
            key_it_t::iterator_type,
            std::map<std::string, int>::iterator
        >::value, "");

        static_assert(std::is_same<
            value_it_t::iterator_type,
            std::map<std::string, int>::iterator
        >::value, "");

        static_assert(std::is_same<
            key_it_t::value_type,
            std::string
        >::value, "");

        static_assert(std::is_same<
            value_it_t::value_type,
            int
        >::value, "");

        static_assert(std::is_same<
            key_it_t::reference,
            const std::string&
        >::value, "");

        static_assert(std::is_same<
            value_it_t::reference,
            int&
        >::value, "");
    }

    auto foo_it = foo.begin();
    key_it_t key_it(foo_it);
    value_it_t value_it(foo_it);

    SECTION( "observers" )
    {
        REQUIRE( key_it.base() == foo_it );
        REQUIRE( value_it.base() == foo_it );
        REQUIRE( *key_it == foo_it->first );
        REQUIRE( *value_it == foo_it->second );
    }

    SECTION( "increment/decrement operators" )
    {
        ++foo_it;
        ++key_it;
        ++value_it;
        REQUIRE( *key_it == foo_it->first );
        REQUIRE( *value_it == foo_it->second );

        foo_it++;
        key_it++;
        value_it++;
        REQUIRE( *key_it == foo_it->first );
        REQUIRE( *value_it == foo_it->second );

        --foo_it;
        --key_it;
        --value_it;
        REQUIRE( *key_it == foo_it->first );
        REQUIRE( *value_it == foo_it->second );

        foo_it--;
        key_it--;
        value_it--;
        REQUIRE( *key_it == foo_it->first );
        REQUIRE( *value_it == foo_it->second );
    }
}

TEST_CASE( "indirect_iterator", "[iterator]" )
{
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7 };

    std::vector<int*> vec_ptr;
    for (int& val: vec)
    {
        vec_ptr.push_back(&val);
    }

    using indirect_it_t = indirect_iterator<std::vector<int*>::iterator>;

    auto int_it = std::begin(vec);
    for (indirect_it_t indirect_it(std::begin(vec_ptr)) ;
         int_it != std::end(vec) ;
         ++int_it, ++indirect_it)
    {
        REQUIRE( *int_it == *indirect_it );
    }
}
