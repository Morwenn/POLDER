/*
 * Copyright (C) 2011 Morwenn
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
#include <POLDER/math/factorial.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    unsigned int factorial(unsigned int N)
    {
        unsigned int result = 1;
        for (unsigned int i = 2 ; i <= N ; ++i)
        {
            result *= i;
        }
        return result;
    }

    constexpr unsigned int stirling(unsigned int N)
    {
        return (unsigned int) (sqrt(M_2PI*N) * pow((N/M_E), N));
    }
}

namespace meta
{
    constexpr unsigned int factorial(unsigned int N)
    {
        return (N > 1) ? N * meta::factorial(N - 1) : 1;
    }

    constexpr unsigned int stirling(unsigned int N)
    {
        return (unsigned int) (sqrt(M_2PI*N) * pow((N/M_E), N));
    }
}

namespace memoized
{
    unsigned int factorial(unsigned int N)
    {
        /// TODO
        return 0;
    }
}


} // namespace math
} // namespace polder
