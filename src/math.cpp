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
#include "math.h"


namespace polder
{
namespace math
{

using namespace std;

////////////////////////////////////////////////////////////
// Static variables & Initialization
////////////////////////////////////////////////////////////

// Variables used by the factorial function
static unsigned int* factorial_numbers;
static size_t factorial_size;
static bool factorial_resize;

// Variables used by the fibonacci function
static unsigned int* fibonacci_numbers;
static size_t fibonacci_size;
static bool fibonacci_resize;

// Variables used by the prime function
static unsigned int* prime_numbers;
static size_t prime_size;

// Init function
static int __init__()
{
    // Initialisation of the variables used by the factorial function
    factorial_size = 2;
    factorial_numbers = (unsigned int*) malloc(2 * sizeof(unsigned int));
    factorial_numbers[0] = 1;
    factorial_numbers[1] = 1;
    factorial_resize = true;

    // Initialisation of the variables used by the fibonacci function
    fibonacci_size = 2;
    fibonacci_numbers = (unsigned int*) malloc(2 * sizeof(unsigned int));
    fibonacci_numbers[0] = 0;
    fibonacci_numbers[1] = 1;
    fibonacci_resize = true;

    // Initialisation of the variables used by the prime function
    prime_size = 2;
    prime_numbers = (unsigned int*) malloc(3 * sizeof(unsigned int));
    prime_numbers[0] = 1;
    prime_numbers[1] = 2;
    prime_numbers[2] = 3;

    // Just in case
    return 0;
}
int __init_var___ = __init__(); // Initialization (quite ugly)


////////////////////////////////////////////////////////////
/// Basic functions
////////////////////////////////////////////////////////////

// Radians to degrees conversion
double degree(double rad)
{
    return rad * 180.0f / M_PI;
}

// Degrees to radians conversion
double radian(double deg)
{
    return deg * M_PI / 180.0f;
}


////////////////////////////////////////////////////////////
/// Miscellaneous functions
////////////////////////////////////////////////////////////

// Quadratic solver (if there are two solutions, returns twice the same)
pair<complex<double>, complex<double>> quadratic(double A, double B, double C)
{
    A *= 2; // A is not used alone
    double delta = B*B - 2*A*C;
    B = -B; // Only the opposite of B is used after this
    if (delta < 0)
    {
        double tmp_div = B / A;
        double delta_root = sqrt(-delta);
        return make_pair(complex<double>(tmp_div, delta_root/A),
                         complex<double>(tmp_div, -delta_root/A));
    }
    else if (delta == 0)
    {
        double res = B / A;
        return make_pair(res, res);
    }
    else
    {
        double delta_root = sqrt(delta); // Alias for optimization
        return make_pair((B+delta_root)/A, (B-delta_root)/A);
    }
}

// Factorial
unsigned int factorial(unsigned int N)
{
    // If we do not have enough numbers
    if (factorial_size <= N)
    {
        if (factorial_resize)
        {
            // We resize the table so that it is large enough
            factorial_numbers = (unsigned int*) realloc(factorial_numbers, (N+1) * sizeof(unsigned int));
            factorial_resize = false;
        }
        factorial_numbers[N] = N * factorial(N-1); // Factorial formula
        factorial_size = N;
        factorial_resize = true;
    }
    return factorial_numbers[N];
}

// Stirling factorial approximation
unsigned int stirling(unsigned int N)
{
    return (unsigned int) (sqrt(2*M_PI*N) * pow((N/M_E), N));
}

// Fibonacci number
unsigned int fibonacci(unsigned int N)
{
    // If we do not have enough numbers
    if (fibonacci_size <= N)
    {
        if (fibonacci_resize)
        {
            // We resize the table so that it is large enough
            fibonacci_numbers = (unsigned int*) realloc(fibonacci_numbers, (N+1) * sizeof(unsigned int));
            fibonacci_resize = false;
        }
        fibonacci_numbers[N] = fibonacci(N-1) + fibonacci(N-2); // Fibonacci formula
        fibonacci_size = N;
        fibonacci_resize = true;
    }
    return fibonacci_numbers[N];
}

// Returns the Nth prime number
unsigned int prime(unsigned int N)
{
    // If the prime number is already known
    if (prime_size < N)
    {
        // Reshape the table
        prime_numbers = (unsigned int*) realloc(prime_numbers, (N+1) * sizeof(unsigned int));

        // We search numbers greater than the greatest known prime member
        unsigned int tested_number = prime_numbers[prime_size];

        // While we have less than N prime numbers
        while (prime_size < N)
        {
            // We iterate 2 by 2 (to avoid non-even numbers)
            tested_number += 2;
            float root = sqrt(tested_number);

            // Assume the number is a prime (until we can prove the opposite)
            bool is_prime = true;

            // Try to divide the supposed prime by all the known primes
            for (size_t i = 2 ; i <= prime_size ; ++i)
            {
                // We don't have to search above the square root
                if (prime_numbers[i] > root) break;

                // If the number has an integer divider
                float _div = (float) (tested_number) / (float) (prime_numbers[i]);
                if (_div == (int) _div)
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
                prime_numbers[++prime_size] = tested_number;
            }
        }
    }
    // Return the Nth prime number
    return prime_numbers[N];
}

// Greatest Common Divisor (With the Euclidean Algorithm)
unsigned int gcd(unsigned int a, unsigned int b)
{
    if (a == 0 || b == 0)
    {
        return 0;
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

// Least Common Multiple
unsigned int lcm(unsigned int a, unsigned int b)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }

    return a*b / gcd(a, b);
}

// Determinant
double determinant(unsigned int degree, const double* vals)
{
    double system[degree][degree];

    // Create the matrix corresponding to the system with the given values
    double square = degree*degree;
    for (size_t a = 0 ; a < square ; ++a)
    {
        int i = a / degree;
        int j = a % degree;
        system[i][j] = vals[a];
    }
    if (degree == 2)
    {
        // Return the number corresponding to the determinant of degree two
        return system[0][0]*system[1][1] - system[0][1]*system[1][0];
    }
    else
    {
        double res = 0;
        // For all numbers in the first line
        for (size_t i = 0 ; i < degree ; ++i)
        {
            double values[(degree-1)*(degree-1)];
            size_t count = 0;
            // Fill the argument vector
            for (size_t j = 1 ; j < degree ; ++j)
            {
                for (size_t k = 0 ; k < degree ; ++k)
                {
                    if (k != i)
                    {
                        values[count] = system[j][k];
                        ++count;
                    }
                }
            }
            res += system[0][i] * determinant(degree-1, values) * pow(-1, i);
        }
        return res;
    }
}

// Determinant (alternative writing)
double determinant(unsigned int degree, ...)
{
    unsigned int square = degree*degree;
    double alias[square];
    va_list args;
    va_start(args, degree);
    for (unsigned int i = 0 ; i < square ; ++i)
    {
        alias[i] = va_arg(args, double);
    }
    va_end(args);
    return determinant(degree, alias);
}


} // namespace math
} // namespace polder
