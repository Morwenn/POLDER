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
#ifndef POLDER_SEMISYMBOLIC_NUMBER_H_
#define POLDER_SEMISYMBOLIC_NUMBER_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/utility.h>
#include <POLDER/semisymbolic/expression.h>

namespace polder
{
namespace semisymbolic
{
    ////////////////////////////////////////////////////////////
    // Number

    template<typename T>
    struct Number:
        Expression<Number<T>>
    {
        // Member types
        using value_type = T;

        // Default constructor
        Number(value_type val);

        // Expression constructor
        template<typename Expr>
        Number(const Expression<Expr>& expr);

        // Conversion to value_type
        operator value_type() const;

        // Member data
        value_type value;
    };

    ////////////////////////////////////////////////////////////
    // Alias templates

    using Float         = Number<float>;
    using Double        = Number<double>;
    using LongDouble    = Number<long double>;

    #include "details/number.inl"
}}

namespace polder
{
    ////////////////////////////////////////////////////////////
    // CRTP value_type propagation

    template<typename T>
    struct types_t<semisymbolic::Number<T>>
    {
        using value_type = T;
    };
}

#endif // POLDER_SEMISYMBOLIC_NUMBER_H_
