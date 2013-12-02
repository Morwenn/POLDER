/*
 * Copyright (C) 2011-2013 Morwenn
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

inline namespace standard
{
    template<typename Unsigned>
    auto factorial(Unsigned n)
        -> Unsigned
    {
        Unsigned result = 1;
        for (Unsigned i = 2 ; i <= n ; ++i)
        {
            result *= i;
        }
        return result;
    }

    template<typename Unsigned>
    auto double_factorial(Unsigned n)
        -> Unsigned
    {
        POLDER_ASSERT(is_odd(n));
        Unsigned k = (n + 1) / 2;
        Unsigned res = 1;
        for (Unsigned i = 1 ; i <= k ; ++i)
        {
            res *= 2 * i - 1;
        }
        return res;
    }

    template<typename Unsigned>
    auto stirling(Unsigned n)
        -> Unsigned
    {
        return Unsigned(std::sqrt(M_2PI*n) * std::pow((n/M_E), n));
    }
}

namespace meta
{
    template<typename Unsigned>
    constexpr auto factorial(Unsigned n)
        -> Unsigned
    {
        return (n > 1) ? n * meta::factorial(n - 1) : 1;
    }
}
