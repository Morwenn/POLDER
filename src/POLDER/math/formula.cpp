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
#include <POLDER/math/formula.h>


namespace polder
{
namespace math
{

using namespace std;


////////////////////////////////////////////////////////////
// Static variables, Initialization & Helpers
////////////////////////////////////////////////////////////

namespace
{
    // Variable used by the fibonacci function
    unsigned long long int* fibonacci_numbers;

    // Variable used by the prime function
    unsigned long long int* prime_numbers;

    // Init function
    int __init__()
    {
        // Initialisation of the variables used by the fibonacci function
        fibonacci_numbers = (unsigned long long int*) malloc(2 * sizeof(unsigned long long int));
        fibonacci_numbers[0] = 0;
        fibonacci_numbers[1] = 1;

        // Initialisation of the variables used by the prime function
        prime_numbers = (unsigned long long int*) malloc(3 * sizeof(unsigned long long int));
        prime_numbers[0] = 1;
        prime_numbers[1] = 2;
        prime_numbers[2] = 3;

        // Just in case
        return 0;
    }
    int __init_var__ = __init__(); // Initialization (quite ugly)
}


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
        return meta::sinc(x);
    }
    float sinc(float x)
    {
        return sin(x) / x;
    }
    long double sinc(long double x)
    {
        return sin(x) / x;
    }

    double normalized_sinc(double x)
    {
        return meta::normalized_sinc(x);
    }

    pair<complex<double>, complex<double>> quadratic(double A, double B, double C)
    {
        A *= 2; // A is not used alone
        const double delta = B*B - 2*A*C;
        B = -B; // Only the opposite of B is used after this
        if (delta < 0)
        {
            const double tmp_div = B / A;
            const double delta_root = sqrt(delta);
            return make_pair(complex<double>(tmp_div, delta_root/A),
                             complex<double>(tmp_div, -delta_root/A));
        }
        else if (delta == 0)
        {
            const double res = B / A;
            return make_pair(res, res);
        }
        else
        {
            const double delta_root = sqrt(delta); // Alias for optimization
            return make_pair((B+delta_root)/A, (B-delta_root)/A);
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
        return memoized::prime(n);
    }

    unsigned int gcd(unsigned int a, unsigned int b)
    {
        if (a == 0 || b == 0)
        {
            return 0;
        }
        if (b > a)
        {
            swap(a, b);
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


namespace memoized
{
    bool is_prime(unsigned long long int n)
    {
        const unsigned long long int root = (unsigned long long int) sqrt(n);
        unsigned long long int _prime = 2;
        for (unsigned long long int i = 1 ; _prime <= root ; ++i)
        {
            _prime = prime(i);
            if (n % _prime == 0)
            {
                return false;
            }
        }
        return true;
    }

    unsigned long long int fibonacci(unsigned long long int n)
    {
        // Initialization
        static size_t size = 2;
        static bool resize = true;

        // If we do not have enough numbers
        if (size <= n)
        {
            if (resize)
            {
                // We resize the table so that it is large enough
                fibonacci_numbers = (unsigned long long int*) realloc(fibonacci_numbers, (n+1) * sizeof(unsigned long long int));
                resize = false;
            }
            fibonacci_numbers[n] = fibonacci(n-1) + fibonacci(n-2); // Fibonacci formula
            size = n;
            resize = true;
        }
        return fibonacci_numbers[n];
    }

    unsigned long long int prime(unsigned long long int n)
    {
        // Initialization
        static size_t size = 2;

        // If the prime number is already known
        if (size < n)
        {
            // Reshape the table
            prime_numbers = (unsigned long long int*) realloc(prime_numbers, (n+1) * sizeof(unsigned long long int));

            // We search numbers greater than the greatest known prime member
            unsigned long long int tested_number = prime_numbers[size];

            // While we have less than n prime numbers
            while (size < n)
            {
                // We iterate 2 by 2 (to avoid non-even numbers)
                tested_number += 2;
                const double root = sqrt(tested_number);

                // Assume the number is a prime (until we can prove the opposite)
                bool is_prime = true;

                // Try to divide the supposed prime by all the known primes
                for (size_t i = 2 ; i <= size ; ++i)
                {
                    // We don't have to search above the square root
                    if (prime_numbers[i] > root) break;

                    // If the number has an integer divider
                    if (tested_number % prime_numbers[i] == 0)
                    {
                        // It's not a prime number
                        is_prime = false;
                        break;
                    }
                }

                // If the tested number is really a prime number
                if (is_prime)
                {
                    // We put it in the table
                    prime_numbers[++size] = tested_number;
                }
            }
        }
        // Return the Nth prime number
        return prime_numbers[n];
    }
}


} // namespace math
} // namespace polder
