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
#ifndef POLDER_EVALUATION_FUNCTIONS_H_
#define POLDER_EVALUATION_FUNCTIONS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cctype>
#include <stack>
#include <string>
#include <vector>
#include <POLDER/details/config.h>
#include <POLDER/evaluation/error.h>
#include <POLDER/evaluation/token.h>

namespace polder
{
namespace evaluation
{
    template<typename Number>
    auto tokenize(const std::string& expr)
        -> std::vector<token<Number>>;

    template<typename Number>
    auto to_postfix(const std::vector<token<Number>>& tokens)
        -> std::stack<token<Number>>;

    #include "details/functions.inl"
}}

#endif // POLDER_EVALUATION_FUNCTIONS_H_
