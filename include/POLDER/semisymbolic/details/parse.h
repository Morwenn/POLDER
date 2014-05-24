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
#ifndef POLDER_SEMISYMBOLIC_PARSE_H_
#define POLDER_SEMISYMBOLIC_PARSE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/details/config.h>

namespace polder
{
namespace semisymbolic
{
namespace details
{
    ////////////////////////////////////////////////////////////
    // Function to

    constexpr auto combine(unsigned long long value)
        -> unsigned long long
    {
        return value;
    }

    template<typename... ULL>
    constexpr auto combine(unsigned long long value, unsigned long long first, ULL... digits)
        -> unsigned long long
    {
        return combine(value*10 + first, digits...);
    }

    ////////////////////////////////////////////////////////////
    // Parsing function

    template<typename T, char C, char... Digits>
    constexpr auto parse()
        -> T
    {
        static_assert(C != '0' || sizeof...(Digits) == 0,
                      "octal literals are not handled");

        return static_cast<T>(
            combine(0, C-'0', Digits-'0'...)
        );
    }
}}}

#endif // POLDER_SEMISYMBOLIC_PARSE_H_
