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
#include <type_traits>
#include <POLDER/evaluation/error.h>

namespace polder
{
namespace evaluation
{
    using namespace std::string_literals;

    namespace
    {
        // Default error messages for error codes
        const char* const messages[] = {
            "unknown operator in the expression",
            "unexpected character in the expression",
            "unexpected token in the expression",
            "not enough operands for the operation",
            "several dots in the same number",
            "stray comma outside of a function's parameter list",
            "trying to close a non-opened parenthesis",
            "mismatched parenthesis in the expression"
        };
    }

    error::error(error_type ecode):
        std::runtime_error(
            "polder::evaluation::error: "s +=
            messages[std::underlying_type_t<error_type>(ecode)]
        ),
        ecode(ecode)
    {}

    error::error(error_type ecode, const std::string& arg):
        std::runtime_error(
            "polder::evaluation::error: "s += arg
        ),
        ecode(ecode)
    {}

    auto error::code() const noexcept
        -> error_type
    {
        return ecode;
    }
}}
