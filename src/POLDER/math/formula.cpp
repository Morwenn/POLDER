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
#include <vector>
#include <POLDER/math/formula.h>


namespace polder
{
namespace math
{


////////////////////////////////////////////////////////////
// Mathematical functions
////////////////////////////////////////////////////////////

inline namespace standard
{
    bool is_even(long long int n)
    {
        return meta::is_even(n);
    }

    bool is_odd(long long int n)
    {
        return meta::is_odd(n);
    }

    bool is_prime(unsigned long long int n)
    {
        return meta::is_prime(n);
    }

    double degree(double rad)
    {
        return meta::degree(rad);
    }

    double radian(double deg)
    {
        return meta::radian(deg);
    }

    double sinc(double x)
    {
        return std::sin(x) / x;
    }
    float sinc(float x)
    {
        return std::sin(x) / x;
    }
    long double sinc(long double x)
    {
        return std::sin(x) / x;
    }

    double normalized_sinc(double x)
    {
        return std::sin(x * M_PI) / (x * M_PI);
    }

    auto quadratic(double A, double B, double C)
        -> std::pair<std::complex<double>, std::complex<double>>
    {
        A *= 2; // A is not used alone
        const double delta = std::fma(B, B, -2*A*C);
        B = -B; // Only the opposite of B is used after this
        if (delta < 0)
        {
            const double tmp_div = B / A;
            const double delta_root = std::sqrt(delta);
            return std::make_pair(std::complex<double>(tmp_div, delta_root/A),
                                  std::complex<double>(tmp_div, -delta_root/A));
        }
        else if (delta == 0)
        {
            const double res = B / A;
            return std::make_pair(res, res);
        }
        else
        {
            const double delta_root = std::sqrt(delta); // Alias for optimization
            return std::make_pair((B+delta_root)/A, (B-delta_root)/A);
        }
    }

    unsigned long long int fibonacci(unsigned long long int n)
    {
        unsigned long long int a = 0;
        unsigned long long int b = 1;
        for (unsigned long long int i = 0 ; i < n ; ++i)
        {
            b += a;
            a = b - a;
        }
        return a;
    }

    unsigned long long int prime(unsigned long long int n)
    {
        static std::vector<unsigned long long int> primes = { 1, 2, 3 };

        // If the prime number is not already known,
        // compute and store it
        if (primes.size()-1 < n)
        {
            // We search numbers greater than
            // the greatest known prime member
            unsigned long long int tested_number = primes.back();

            // While we have less than n prime numbers
            while (primes.size()-1 < n)
            {
                // We iterate 2 by 2 (to avoid non-even numbers)
                tested_number += 2;
                const double root = std::sqrt(tested_number);

                // Assume the number is a prime
                // until the opposite is proven
                bool is_prime = true;

                // Try to divide the supposed prime by all the known primes
                // starting with 3
                for (auto it = primes.begin()+2 ; it != primes.end() ; ++it)
                {
                    const auto& pri = *it;
                    // We don't have to search above the square root
                    if (pri > root) break;

                    // If the number has an integer divider
                    if (tested_number % pri == 0)
                    {
                        // It's not a prime number
                        is_prime = false;
                        break;
                    }
                }

                if (is_prime)
                {
                    primes.push_back(tested_number);
                }
            }
        }
        return primes[n];
    }

    unsigned int gcd(unsigned int a, unsigned int b)
    {
        if (a == 0 || b == 0)
        {
            return 0;
        }
        if (b > a)
        {
            std::swap(a, b);
        }

        unsigned int r = a % b;
        while (r != 0)
        {
            a = b;
            b = r;
            r = a % b;
        }
        return b;
    }

    unsigned int lcm(unsigned int a, unsigned int b)
    {
        if (a == 0 || b == 0)
        {
            return 1;
        }

        return a*b / gcd(a, b);
    }
}


} // namespace math
} // namespace polder
