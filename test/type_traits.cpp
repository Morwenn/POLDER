/*
 * Copyright (C) 2014 Morwenn
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
#include <cstdint>
#include <type_traits>
#include <POLDER/type_traits.h>

int main()
{
    using namespace polder;

    // TEST: function traits
    {
        auto lambda = [](int a, float b)
        {
            return a + b;
        };
        using ltype = decltype(lambda);

        static_assert(function_traits<ltype>::arity == 2, "");

        static_assert(std::is_same<
            result_type<ltype>,
            float
        >::value, "");

        static_assert(std::is_same<
            argument_type<ltype, 0>,
            int
        >::value, "");

        static_assert(std::is_same<
            argument_type<ltype, 1>,
            float
        >::value, "");
    }

    // TEST: integer fit
    {
        static_assert(can_fit<uint_least8_t>(0u), "");
        static_assert(can_fit<uint_least16_t>(0u), "");
        static_assert(can_fit<uint_least32_t>(0u), "");
        static_assert(can_fit<uint_least64_t>(0u), "");

        static_assert(can_fit<uint_least8_t>(255u), "");
        static_assert(can_fit<uint_least16_t>(65535u), "");
        static_assert(can_fit<uint_least32_t>(4294967295u), "");
        static_assert(can_fit<uint_least64_t>(18446744073709551615u), "");
    }
}
