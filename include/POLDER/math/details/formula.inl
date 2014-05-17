/*
 * Copyright (C) 2011-2014 Morwenn
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

template<typename Number>
auto sign(Number val)
    -> int
{
    return meta::sign(val);
}

template<typename Integer>
auto is_even(Integer n)
    -> bool
{
    return meta::is_even(n);
}

template<typename Integer>
auto is_odd(Integer n)
    -> bool
{
    return meta::is_odd(n);
}

template<typename Unsigned>
auto is_prime(Unsigned n)
    -> bool
{
    return meta::is_prime(n);
}

template<typename Float>
auto degrees(Float rad)
    -> Float
{
    return meta::degrees(rad);
}

template<typename Float>
auto radians(Float deg)
    -> Float
{
    return meta::radians(deg);
}

template<typename Float>
auto sinc(Float x)
    -> Float
{
    return std::sin(x) / x;
}

template<typename Float>
auto normalized_sinc(Float x)
    -> Float
{
    return std::sin(x * M_PI) / (x * M_PI);
}

template<typename Float>
auto quadratic(Float A, Float B, Float C)
    -> std::array<std::complex<Float>, 2u>
{
    A *= 2; // A is not used alone
    const Float delta = std::fma(B, B, -2*A*C);
    B = -B; // Only the opposite of B is used after this
    if (delta < 0)
    {
        const Float tmp_div = B / A;
        const Float delta_root = std::sqrt(delta);
        return {
            std::complex<Float>(tmp_div, delta_root/A),
            std::complex<Float>(tmp_div, -delta_root/A)
        };
    }
    else if (delta == 0)
    {
        const Float res = B / A;
        return { res, res };
    }
    else
    {
        const Float delta_root = std::sqrt(delta);
        return {
            (B+delta_root)/A,
            (B-delta_root)/A
        };
    }
}

template<typename Unsigned>
auto fibonacci(Unsigned n)
    -> Unsigned
{
    Unsigned a = 0;
    Unsigned b = 1;
    for (Unsigned i = 0 ; i < n ; ++i)
    {
        b += a;
        a = b - a;
    }
    return a;
}

template<typename Number, typename... Rest>
auto sum(Number first, Number second, Rest... rest)
    -> Number
{
    return meta::sum(first, second, rest...);
}

template<typename... Args>
auto mean(Args... args)
    -> decltype(sum(args...) / sizeof...(args))
{
    return sum(args...) / sizeof...(args);
}

template<typename Unsigned>
auto prime(Unsigned n)
    -> Unsigned
{
    static std::vector<Unsigned> primes = { 1, 2, 3 };

    // If the prime number is not already known,
    // compute and store it
    if (primes.size()-1 < n)
    {
        // We search numbers greater than
        // the greatest known prime member
        Unsigned tested_number = primes.back();

        // While we have less than n prime numbers
        while (primes.size()-1 < n)
        {
            // We iterate 2 by 2 (to avoid non-even numbers)
            tested_number += 2;
            auto root = std::sqrt(tested_number);

            // Assume the number is a prime
            // until the opposite is proven
            bool is_prime = true;

            // Try to divide the supposed prime by all the known primes
            // starting with 3
            for (auto it = primes.cbegin()+2 ; it != primes.cend() ; ++it)
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

template<typename Unsigned>
auto gcd(Unsigned a, Unsigned b)
    -> Unsigned
{
    if (a == 0 || b == 0)
    {
        return 0;
    }
    if (b > a)
    {
        std::swap(a, b);
    }

    Unsigned r = a % b;
    while (r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

template<typename Unsigned>
auto lcm(Unsigned a, Unsigned b)
    -> Unsigned
{
    if (a == 0 || b == 0)
    {
        return 1;
    }
    return a*b / gcd(a, b);
}

template<typename Number>
auto sqr(Number val)
    -> Number
{
    return meta::sqr(val);
}

template<typename Number>
auto clamp(Number val, Number min, Number max)
    -> Number
{
    return meta::clamp(val, min, max);
}

namespace meta
{
    ////////////////////////////////////////////////////////////
    // Helper functions

    namespace details
    {
        // Helper for the is_prime() function
        template<typename Unsigned>
        constexpr auto is_prime_helper(Unsigned n, Unsigned div)
            -> bool
        {
            return (div*div > n) ? true :
                (n % div == 0) ? false :
                    is_prime_helper(n, div+2);
        }

        template<typename Unsigned>
        constexpr auto gcd_helper(Unsigned b, Unsigned r)
            -> Unsigned
        {
            return (r == 0) ? b : gcd_helper(r, b % r);
        }
    }

    ////////////////////////////////////////////////////////////
    // Main functions

    template<typename Number>
    constexpr auto sign(Number value)
        -> int
    {
        return (value > 0) ? 1 : (value < 0) ? -1 : 0;
    }

    template<typename Integer>
    constexpr auto is_even(Integer n)
        -> bool
    {
        return not bool(n % 2);
    }

    template<typename Integer>
    constexpr auto is_odd(Integer n)
        -> bool
    {
        return bool(n % 2);
    }

    template<typename Unsigned>
    constexpr auto is_prime(Unsigned n)
        -> bool
    {
        return (n < 2) ? false :
            (n == 2) ? true :
                (n % 2 == 0) ? false :
                    details::is_prime_helper(n, 3);
    }

    template<typename Float>
    constexpr auto degrees(Float rad)
        -> Float
    {
        return rad * M_180_PI;
    }

    template<typename Float>
    constexpr auto radians(Float deg)
        -> Float
    {
        return deg * M_PI_180;
    }

    template<typename Unsigned>
    constexpr auto fibonacci(Unsigned n)
        -> Unsigned
    {
        return (n < 2) ? n : meta::fibonacci(n-2) + meta::fibonacci(n-1);
    }

    template<typename T, typename U>
    constexpr auto sum(T first, U second)
        -> std::common_type_t<T, U>
    {
        return first + second;
    }

    template<typename T, typename U, typename... Rest>
    constexpr auto sum(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>
    {
        return first + sum(second, rest...);
    }

    template<typename... Numbers>
    constexpr auto mean(Numbers... args)
        -> decltype(sum(args...) / sizeof...(args))
    {
        return sum(args...) / sizeof...(args);
    }

    template<typename Unsigned>
    constexpr auto gcd(Unsigned a, Unsigned b)
        -> Unsigned
    {
        return (a == 0 || b == 0) ? 0 :
            (a >= b) ? details::gcd_helper(b, a % b) :
                details::gcd_helper(a, b % a);
    }

    template<typename Unsigned>
    constexpr auto lcm(Unsigned a, Unsigned b)
        -> Unsigned
    {
        return (a == 0 || b == 0) ? 1 :
            a * b / gcd(a, b);
    }

    template<typename Number>
    constexpr auto sqr(Number val)
        -> Number
    {
        return val * val;
    }

    template<typename Number>
    constexpr auto clamp(Number val, Number min, Number max)
        -> Number
    {
        return (val < min) ? min : (val > max) ? max : val;
    }
}
