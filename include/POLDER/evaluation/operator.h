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
#ifndef POLDER_EVALUATION_OPERATOR_H_
#define POLDER_EVALUATION_OPERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdint>
#include <string>
#include <POLDER/details/config.h>

namespace polder
{
namespace evaluation
{
    ////////////////////////////////////////////////////////////
    // Available operators

    /**
     * Available infix operators.
     */
    enum struct infix_t:
        std::uint_fast8_t
    {
        EQ,         // =
        NE,         // !=, <>
        GE,         // >=
        LE,         // <=
        AND,        // &&
        OR,         // ||
        XOR,        // ^^
        POW,        // **
        SPACE,      // <=>
        LSHIFT,     // <<
        RSHIFT,     // >>
        ADD,        // +
        SUB,        // -
        MUL,        // *
        DIV,        // /
        MOD,        // %
        BAND,       // &
        BOR,        // |
        GT,         // >
        LT,         // <
        BXOR,       // ^
        IDIV,       // //
    };

    /**
     * Available prefix operators.
     */
    enum struct prefix_t:
        std::uint_fast8_t
    {
        USUB,       // - (Unary minus)
        NOT,        // ! (Logical NOT)
        BNOT,       // ~ (Bitwise NOT)
    };

    /**
     * Available postfix operators.
     */
    enum struct postfix_t:
        std::uint_fast8_t
    {
        FAC         // ! (Factorial)
    };

    ////////////////////////////////////////////////////////////
    // Priority of infix operators

    /**
     * Priority of infix operators.
     */
    auto priority(infix_t oper)
        -> unsigned int;

    ////////////////////////////////////////////////////////////
    // String conversion functions

    auto POLDER_API to_string(infix_t oper)
        -> std::string;

    auto POLDER_API to_string(prefix_t oper)
        -> std::string;

    auto POLDER_API to_string(postfix_t oper)
        -> std::string;
}}

#endif // POLDER_EVALUATION_OPERATOR_H_
