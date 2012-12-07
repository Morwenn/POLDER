/*
 * Copyright (C) 2011-2012 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_TYPE_LIST_H
#define _POLDER_TYPE_LIST_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>
#include <POLDER/config.h>


namespace polder
{

    template<typename Head, typename... Tail>
    struct type_list:
        type_list<Tail...>
    {
        using size_type = std::size_t;
        static constexpr size_type size = sizeof...(Tail) + 1;

        template<size_type N>
        using at = typename std::conditional<
            N == 0,
            Head,
            typename type_list<Tail...>::template at<N-1>
        >::type;

        using front = Head;
        using back  = at<size-1>;
    };

    template<typename Head>
    struct type_list<Head>
    {
        using size_type = std::size_t;
        static constexpr size_type size = 1;

        template<size_type N>
        using at = typename std::conditional<
            N == 0,
            Head,
            void
        >::type;

        using front = Head;
        using back  = Head;
    };

} // namespace polder


#endif // _POLDER_TYPE_LIST_H



