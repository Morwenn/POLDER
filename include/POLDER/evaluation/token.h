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
#ifndef POLDER_EVALUATION_TOKEN_H_
#define POLDER_EVALUATION_TOKEN_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdint>
#include <ostream>
#include <string>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/evaluation/operator.h>

namespace polder
{
namespace evaluation
{
    /**
     * Token types that can be used by the evaluator.
     */
    enum struct token_t:
        std::uint_fast8_t
    {
        operand,
        name,
        infix,
        prefix,
        postfix,
        left_brace,
        right_brace,
        comma
    };

    /**
     * Token used by the evaluator. It can either represent
     * a parenthesis, an operator or a number. Number types
     * are restricted to built-in types.
     */
    template<typename Number>
    struct token
    {
        ////////////////////////////////////////////////////////////
        // Construction and destruction

        token(const token& other);

        explicit token(token_t type);

        explicit token(Number num);
        explicit token(std::string name);
        explicit token(infix_t oper);
        explicit token(prefix_t oper);
        explicit token(postfix_t oper);

        ~token();

        ////////////////////////////////////////////////////////////
        // Helper functions

        auto is_operand() const
            -> bool;
        auto is_name() const
            -> bool;
        auto is_infix() const
            -> bool;
        auto is_prefix() const
            -> bool;
        auto is_postfix() const
            -> bool;
        auto is_left_brace() const
            -> bool;
        auto is_right_brace() const
            -> bool;
        auto is_comma() const
            -> bool;

        ////////////////////////////////////////////////////////////
        // Member data

        const token_t type;

        union
        {
            Number data;
            std::string name;
            infix_t infix;
            prefix_t prefix;
            postfix_t postfix;
        };
    };

    ////////////////////////////////////////////////////////////
    // Display functions

    template<typename Number>
    auto to_string(const token<Number>& tok)
        -> std::string;

    template<typename Number>
    auto operator<<(std::ostream& stream, const token<Number>& tok)
        -> std::ostream&;

    #include "details/token.inl"
}}

#endif // POLDER_EVALUATION_TOKEN_H_
