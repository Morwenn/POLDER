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
#include <cassert>
#include <POLDER/math/factorial.h>
#include <POLDER/math/formula.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    unsigned long long int factorial(unsigned long long int N)
    {
        unsigned long long int result = 1;
        for (unsigned int i = 2 ; i <= N ; ++i)
        {
            result *= i;
        }
        return result;
    }

    unsigned long long int double_factorial(unsigned long long int n)
    {
        assert(is_odd(n));
        unsigned long long int k = (n + 1) / 2;
        unsigned long long int res = 1;
        for (unsigned int i = 1 ; i <= k ; ++i)
        {
            res *= 2 * i - 1;
        }
        return res;
    }

    unsigned long long int stirling(unsigned long long int N)
    {
        return (unsigned long long int) (sqrt(M_2PI*N) * pow((N/M_E), N));
    }
}


} // namespace math
} // namespace polder
