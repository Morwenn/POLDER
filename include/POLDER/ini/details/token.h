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
#ifndef POLDER_INI_TOKEN_H_
#define POLDER_INI_TOKEN_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include <POLDER/details/config.h>
#include <POLDER/ini/dialect.h>

namespace polder
{
namespace ini
{
    /**
     * Types of tokens that can be read.
     */
    enum struct token_t
    {
        BRACE_CLOSE,
        BRACE_OPEN,
        DELIMITER,
        FLOATING_POINT,
        IDENTIFIER,
        INTEGER,
        STRING
    };

    /**
     * @brief Token used in ini parsing.
     */
    struct POLDER_API Token
    {
        Token(token_t type, std::string data="");

        token_t type;
        std::string data;
    };

    /**
     * @brief Tokenizes a string.
     *
     * \param str String to tokenize.
     * \param dialect Dialect used to parse \a str.
     */
    POLDER_API
    auto tokenize(std::string str, Dialect dialect)
        -> std::vector<Token>;
}}

#endif // POLDER_INI_TOKEN_H_
