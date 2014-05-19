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
    template<typename T>
    constexpr auto parse(T value)
        -> T
    {
        return value;
    }

    template<typename T, typename... Args>
    constexpr auto parse(T value, T first, Args... digits)
        -> T
    {
        return parse(value*10 + first, digits...);
    }
}}}

#endif // POLDER_SEMISYMBOLIC_PARSE_H_
