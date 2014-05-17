/*
 * Copyright (C) 2013-2014 Morwenn
 *
 * static_math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * static_math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#include <POLDER/math/formula.h>

using namespace polder;
using namespace math;


int main()
{
    ////////////////////////////////////////////////////////////
    // Tests for the namespace standard
    ////////////////////////////////////////////////////////////

    POLDER_ASSERT(sign(5) == 1);
    POLDER_ASSERT(sign(-3) == -1);
    POLDER_ASSERT(sign(2.0) == 1);
    POLDER_ASSERT(sign(-5.8) == -1);
    POLDER_ASSERT(sign(0) == 0);
    POLDER_ASSERT(sign(0.0) == 0);

    POLDER_ASSERT(is_even(5) == false);
    POLDER_ASSERT(is_even(-4) == true);
    POLDER_ASSERT(is_even(0) == true);

    POLDER_ASSERT(is_odd(8) == false);
    POLDER_ASSERT(is_odd(0) == false);
    POLDER_ASSERT(is_odd(-5) == true);

    POLDER_ASSERT(is_prime(0) == false);
    POLDER_ASSERT(is_prime(1) == false);
    POLDER_ASSERT(is_prime(2) == true);
    POLDER_ASSERT(is_prime(3) == true);
    POLDER_ASSERT(is_prime(4) == false);
    POLDER_ASSERT(is_prime(5) == true);
    POLDER_ASSERT(is_prime(7) == true);
    POLDER_ASSERT(is_prime(8) == false);
    POLDER_ASSERT(is_prime(9) == false);
    POLDER_ASSERT(is_prime(128) == false);

    POLDER_ASSERT(fibonacci(0) == 0);
    POLDER_ASSERT(fibonacci(1) == 1);
    POLDER_ASSERT(fibonacci(2) == 1);
    POLDER_ASSERT(fibonacci(3) == 2);
    POLDER_ASSERT(fibonacci(4) == 3);
    POLDER_ASSERT(fibonacci(5) == 5);
    POLDER_ASSERT(fibonacci(6) == 8);
    POLDER_ASSERT(fibonacci(7) == 13);
    POLDER_ASSERT(fibonacci(8) == 21);

    POLDER_ASSERT(sum(1, 2, 3, 4, 5) == 15);
    POLDER_ASSERT(sum(1.0, 2.0, 3, 4, 5) == 15.0);

    POLDER_ASSERT(mean(2, 2, 2) == 2);
    POLDER_ASSERT(mean(2, 4, 3) == 3);

    POLDER_ASSERT(gcd(1071, 1029) == 21);
    POLDER_ASSERT(gcd(1029, 1071) == 21);
    POLDER_ASSERT(gcd(270, 84) == 6);
    POLDER_ASSERT(gcd(84, 270) == 6);

    POLDER_ASSERT(lcm(60, 168) == 840);
    POLDER_ASSERT(lcm(168, 60) == 840);

    POLDER_ASSERT(clamp(3, 2, 4) == 3);
    POLDER_ASSERT(clamp(1, 2, 4) == 2);
    POLDER_ASSERT(clamp(5, 2, 4) == 4);

    ////////////////////////////////////////////////////////////
    // Tests for the namespace meta
    ////////////////////////////////////////////////////////////

    static_assert(meta::sign(5) == 1, "");
    static_assert(meta::sign(-3) == -1, "");
    static_assert(meta::sign(2.0) == 1, "");
    static_assert(meta::sign(-5.8) == -1, "");
    static_assert(meta::sign(0) == 0, "");
    static_assert(meta::sign(0.0) == 0, "");

    static_assert(meta::is_even(5) == false, "");
    static_assert(meta::is_even(-4) == true, "");
    static_assert(meta::is_even(0) == true, "");

    static_assert(meta::is_odd(8) == false, "");
    static_assert(meta::is_odd(0) == false, "");
    static_assert(meta::is_odd(-5) == true, "");

    static_assert(meta::is_prime(0) == false, "");
    static_assert(meta::is_prime(1) == false, "");
    static_assert(meta::is_prime(2) == true, "");
    static_assert(meta::is_prime(3) == true, "");
    static_assert(meta::is_prime(4) == false, "");
    static_assert(meta::is_prime(5) == true, "");
    static_assert(meta::is_prime(7) == true, "");
    static_assert(meta::is_prime(8) == false, "");
    static_assert(meta::is_prime(9) == false, "");
    static_assert(meta::is_prime(128) == false, "");

    static_assert(meta::fibonacci(0) == 0, "");
    static_assert(meta::fibonacci(1) == 1, "");
    static_assert(meta::fibonacci(2) == 1, "");
    static_assert(meta::fibonacci(3) == 2, "");
    static_assert(meta::fibonacci(4) == 3, "");
    static_assert(meta::fibonacci(5) == 5, "");
    static_assert(meta::fibonacci(6) == 8, "");
    static_assert(meta::fibonacci(7) == 13, "");
    static_assert(meta::fibonacci(8) == 21, "");

    static_assert(
        meta::sum(1, 2, 3, 4, 5) == 15,
    "");
    static_assert(
        meta::sum(1.0, 2.0, 3, 4, 5) == 15.0,
    "");

    static_assert(meta::mean(2, 2, 2) == 2, "");
    static_assert(meta::mean(2, 4, 3) == 3, "");

    static_assert(meta::gcd(1071, 1029) == 21, "");
    static_assert(meta::gcd(1029, 1071) == 21, "");
    static_assert(meta::gcd(270, 84) == 6, "");
    static_assert(meta::gcd(84, 270) == 6, "");

    static_assert(meta::lcm(60, 168) == 840, "");
    static_assert(meta::lcm(168, 60) == 840, "");

    static_assert(meta::clamp(3, 2, 4) == 3, "");
    static_assert(meta::clamp(1, 2, 4) == 2, "");
    static_assert(meta::clamp(5, 2, 4) == 4, "");
}
