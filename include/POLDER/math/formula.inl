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


////////////////////////////////////////////////////////////
// Static variables, Initialization & Helpers
////////////////////////////////////////////////////////////

namespace
{
    // Helper for the is_prime() function
    constexpr bool _is_prime_helper(unsigned long long int n, unsigned long long int div)
    {
        return (div*div > n) ? true :
                             (n % div == 0) ? false :
                                            _is_prime_helper(n, div+2);
    }
}


////////////////////////////////////////////////////////////
// POLDER functions
////////////////////////////////////////////////////////////

constexpr bool is_even(long long int n)
{
    return !((unsigned long long int) n & 1);
}

constexpr bool is_odd(long long int n)
{
    return (unsigned long long int) n & 1;
}

constexpr bool is_prime(unsigned long long int n)
{
    return (n < 2) ? false :
                     (n == 2) ? true :
                              _is_prime_helper(n, 3);
}

constexpr double degree(double rad)
{
    return rad * M_180_PI;
}

constexpr double radian(double deg)
{
    return deg * M_PI_180;
}

constexpr double sinc(double x)
{
    return sin(x) / x;
}

constexpr double normalized_sinc(double x)
{
    return sin(x * M_PI) / (x * M_PI);
}

constexpr unsigned long long int fibonacci(unsigned long long int n)
{
    return (n < 2) ? n : meta::fibonacci(n-2) + meta::fibonacci(n-1);
}
