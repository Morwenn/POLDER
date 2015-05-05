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
#include <POLDER/evaluation/operator.h>

namespace polder
{
namespace evaluation
{
    namespace
    {
        constexpr unsigned int infix_priority[] = {
            7,   // =
            7,   // !=, <>
            8,   // >=
            8,   // <=
            3,   // &&
            1,   // ||
            2,   // ^^
            12,  // **
            7,   // <=>
            9,   // <<
            9,   // >>
            10,  // +
            10,  // -
            11,  // *
            11,  // /
            11,  // %
            6,   // &
            4,   // |
            8,   // >
            8,   // <
            5,   // ^
            11,  // //
        };

        constexpr const char* infix_str[] = {
            "=",
            "!=",
            ">=",
            "<=",
            "&&",
            "||",
            "^^",
            "**",
            "<=>",
            "<<",
            ">>",
            "+",
            "-",
            "*",
            "/",
            "%",
            "&",
            "|",
            ">",
            "<",
            "^",
            "//"
        };

        constexpr const char* prefix_str[] = {
            "-",
            "!",
            "~"
        };

        constexpr const char* postfix_str[] = {
            "!"
        };
    }

    ////////////////////////////////////////////////////////////
    // Priority of infix operators

    auto priority(infix_t oper)
        -> unsigned int
    {
        return infix_priority[
            std::underlying_type_t<infix_t>(oper)
        ];
    }

    ////////////////////////////////////////////////////////////
    // String conversion functions

    auto to_string(infix_t oper)
        -> std::string
    {
        return infix_str[
            std::underlying_type_t<infix_t>(oper)
        ];
    }

    auto to_string(prefix_t oper)
        -> std::string
    {
        return prefix_str[
            std::underlying_type_t<prefix_t>(oper)
        ];
    }

    auto to_string(postfix_t oper)
        -> std::string
    {
        return postfix_str[
            std::underlying_type_t<postfix_t>(oper)
        ];
    }
}}
