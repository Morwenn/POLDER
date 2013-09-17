/*
 * Copyright (C) 2011-2013 Morwenn
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
#ifndef _POLDER_FUNCTIONAL_H
#define _POLDER_FUNCTIONAL_H


namespace polder
{
    struct plus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs += rhs;
        }
    };

    struct minus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs -= rhs;
        }
    };

    struct multiplies_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs *= rhs;
        }
    };

    struct divides_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs /= rhs;
        }
    };

    struct modulus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs %= rhs;
        }
    };

    struct bit_and_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs &= rhs;
        }
    };

    struct bit_or_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs |= rhs;
        }
    };

    struct bit_xor_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> void
        {
            lhs ^= rhs;
        }
    };
}


#endif // _POLDER_FUNCTIONAL_H
