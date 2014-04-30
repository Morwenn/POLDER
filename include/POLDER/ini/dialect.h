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
#ifndef POLDER_INI_DIALECT_H_
#define POLDER_INI_DIALECT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <POLDER/details/config.h>

namespace polder
{
namespace ini
{
    /**
     * @brief Dialect used to parse an INI file.
     */
    struct Dialect
    {
        char delimiter      = '=';
        char commentchar    = ';';
        char escapechar     = '\\';
        char lineterminator = '\n';
        char quotechar      = '"';
        bool doublequote    = false;
    };

    /**
     * @brief Converts a dialect-free string to the given dialect.
     *
     * @param str Dialect-free string.
     * @param dialect Dialect of conversion.
     * @return \a str converted to \a dialect.
     */
    POLDER_API
    auto to_dialect(const std::string& str, Dialect dialect)
        -> std::string;
}}

#endif // POLDER_INI_DIALECT_H_
