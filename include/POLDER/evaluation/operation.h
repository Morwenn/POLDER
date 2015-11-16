/*
 * Copyright (C) 2011-2015 Morwenn
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
#ifndef POLDER_EVALUATION_OPERATION_H_
#define POLDER_EVALUATION_OPERATION_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdint>
#include <sstream>
#include <unordered_map>
#include <POLDER/details/config.h>
#include <POLDER/evaluation/error.h>
#include <POLDER/evaluation/operator.h>
#include <POLDER/math/factorial.h>
#include <POLDER/utility.h>

namespace polder
{
namespace evaluation
{
    template<typename Number>
    auto operation(infix_t oper, Number lhs, Number rhs)
        -> Number;

    template<typename Number>
    auto operation(prefix_t oper, Number arg)
        -> Number;

    template<typename Number>
    auto operation(postfix_t oper, Number arg)
        -> Number;

    #include "details/operation.inl"
}}

#endif // POLDER_EVALUATION_OPERATION_H_
