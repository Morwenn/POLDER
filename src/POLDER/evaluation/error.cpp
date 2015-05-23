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
#include <sstream>
#include <POLDER/evaluation/error.h>

namespace polder
{
namespace evaluation
{
    using namespace std::string_literals;

    error::error():
        msg("polder::evaluation::error: undocumented error")
    {}

    error::error(const std::string& arg):
        msg("polder::evaluation::error: "s += arg)
    {}

    error::error(error_code err, char c)
    {
        std::ostringstream oss;
        oss << "polder::evaluation::error: ";

        switch (err)
        {
            case error_code::unknown_operator:
                oss << "unknown operator '" << c << "' in the expression";
                break;
            case error_code::unexpected_character:
                oss << "unexpected character '" << c <<"' in the expression";
                break;
            default:
                oss << "unknown error in the expression";
                break;
        }

        msg = oss.str();
    }

    error::error(error_code err, infix_t oper)
    {
        std::ostringstream oss;
        oss << "polder::evaluation::error: ";

        switch (err)
        {
            case error_code::unknown_operator:
                oss << "unknown operator '" << to_string(oper) << "' in the expression";
                break;
            default:
                oss << "unknown error in the expression";
                break;
        }

        msg = oss.str();
    }

    error::error(error_code err, prefix_t oper)
    {
        std::ostringstream oss;
        oss << "polder::evaluation::error: ";

        switch (err)
        {
            case error_code::unknown_operator:
                oss << "unknown operator '" << to_string(oper) << "' in the expression";
                break;
            default:
                oss << "unknown error in the expression";
                break;
        }

        msg = oss.str();
    }

    error::error(error_code err, postfix_t oper)
    {
        std::ostringstream oss;
        oss << "polder::evaluation::error: ";

        switch (err)
        {
            case error_code::unknown_operator:
                oss << "unknown operator '" << to_string(oper) << "' in the expression";
                break;
            default:
                oss << "unknown error in the expression";
                break;
        }

        msg = oss.str();
    }

    error::error(error_code err, const std::string& arg)
    {
        std::ostringstream oss;
        oss << "polder::evaluation::error: ";

        switch (err)
        {
            case error_code::unknown_operator:
                oss << "unknown operator '" << arg << "' in the expression";
                break;
            case error_code::not_enough_operands:
                oss << "not enough operands for operator '" << arg << "'.";
                break;
            default:
                oss << "unknown error in the expression";
                break;
        }

        msg = oss.str();
    }

    error::~error()
        = default;

    auto error::what() const noexcept
        -> const char*
    {
        return msg.c_str();
    }
}}
