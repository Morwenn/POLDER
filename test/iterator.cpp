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
#include <map>
#include <type_traits>
#include <POLDER/iterator.h>

int main()
{
    using namespace polder;

    // TEST: get_iterator
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

        auto foo_it = foo.begin();
        key_it_t key_it(foo_it);
        value_it_t value_it(foo_it);

        POLDER_ASSERT(key_it.base() == foo_it);
        POLDER_ASSERT(value_it.base() == foo_it);
        POLDER_ASSERT(*key_it == foo_it->first);
        POLDER_ASSERT(*value_it == foo_it->second);

        ++foo_it;
        ++key_it;
        ++value_it;
        POLDER_ASSERT(*key_it == foo_it->first);
        POLDER_ASSERT(*value_it == foo_it->second);

        foo_it++;
        key_it++;
        value_it++;
        POLDER_ASSERT(*key_it == foo_it->first);
        POLDER_ASSERT(*value_it == foo_it->second);

        --foo_it;
        --key_it;
        --value_it;
        POLDER_ASSERT(*key_it == foo_it->first);
        POLDER_ASSERT(*value_it == foo_it->second);

        foo_it--;
        key_it--;
        value_it--;
        POLDER_ASSERT(*key_it == foo_it->first);
        POLDER_ASSERT(*value_it == foo_it->second);
    }
}
