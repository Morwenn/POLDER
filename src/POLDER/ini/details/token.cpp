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
#include <algorithm>
#include <POLDER/ini/details/token.h>
#include <POLDER/ini/error.h>
#include <POLDER/string.h>
#include <POLDER/stype.h>

namespace polder
{
namespace ini
{
    Token::Token(token_t type, std::string data):
        type{type},
        data{std::move(data)}
    {}

    auto tokenize(std::string line, Dialect dialect)
        -> std::vector<Token>
    {
        if (not line.front())
        {
            // If the line is empty,
            // skip to the next one
            return {};
        }

        // Collection to be returned
        std::vector<Token> res;

        auto it = line.cbegin();
        while (it != line.cend())
        {
            ////////////////////////////////////////////////////////////
            // Identifier

            if (std::isalpha(*it) || *it == '_')
            {
                auto start = it;
                while (std::isalnum(*it) || *it == '_')
                {
                    ++it;
                }
                res.emplace_back(token_t::IDENTIFIER,
                                 std::string(start, it));
                continue;
            }

            ////////////////////////////////////////////////////////////
            // Number (integer or floating point)

            else if (std::isdigit(*it) || *it == '.')
            {
                auto start = it;
                bool found_dot = false;
                while (std::isdigit(*it) || *it == '.')
                {
                    if (*it == '.')
                    {
                        if (found_dot)
                        {
                            throw Error("too many dots in floating point literal");
                        }
                        found_dot = true;
                    }
                    ++it;
                }

                token_t type = found_dot ?
                    token_t::FLOATING_POINT :
                    token_t::INTEGER;

                res.emplace_back(type, std::string(start, it));
                continue;
            }

            ////////////////////////////////////////////////////////////
            // String

            else if (*it == dialect.quotechar)
            {
                auto start = ++it;
                while (it != line.cend())
                {
                    if (dialect.doublequote
                        && *it == dialect.quotechar)
                    {
                        if (*++it != dialect.quotechar)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (*it == dialect.escapechar)
                        {
                            ++it;
                        }
                        else if (*it == dialect.quotechar)
                        {
                            break;
                        }
                    }
                    ++it;
                }

                std::string str = { start, it };
                if (dialect.doublequote)
                {
                    auto last = std::unique(std::begin(str), std::end(str),
                                            [dialect](char a, char b)
                    {
                        return a == dialect.quotechar
                            && a == b;
                    });
                    str.erase(last, std::end(str));
                }
                else
                {
                    auto result = std::begin(str);
                    for (auto first = result ; first != std::end(str) ; ++first)
                    {
                        if (*result != *first
                            || *result != dialect.escapechar)
                        {
                            *result = *first;
                            ++result;
                        }
                    }
                    str.erase(result, std::end(str));
                }
                res.emplace_back(token_t::STRING, str);
            }

            ////////////////////////////////////////////////////////////
            // Delimiter

            else if (*it == dialect.delimiter)
            {
                res.emplace_back(token_t::DELIMITER);
            }

            ////////////////////////////////////////////////////////////
            // Braces

            else if (*it == '[')
            {
                res.emplace_back(token_t::BRACE_OPEN);
            }
            else if (*it == ']')
            {
                res.emplace_back(token_t::BRACE_CLOSE);
            }

            ////////////////////////////////////////////////////////////
            // Comments

            else if (*it == dialect.commentchar)
            {
                // There cannot be anything after
                // end-of-line comments
                return res;
            }

            ////////////////////////////////////////////////////////////
            // Stray characters

            else if (not std::isspace(*it))
            {
                throw Error("unknown character");
            }

            ++it;
        }

        return res;
    }
}}
