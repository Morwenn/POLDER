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
#include <POLDER/ini/dialect.h>

namespace polder
{
namespace ini
{
    auto to_dialect(const std::string& str, Dialect dialect)
        -> std::string
    {
        std::string res;
        for (char c: str)
        {
            if (c == dialect.quotechar)
            {
                if (dialect.doublequote)
                {
                    res += dialect.quotechar;
                }
                else
                {
                    res += dialect.escapechar;
                }
            }
            else if (c == dialect.escapechar
                     && not dialect.doublequote)
            {
                res += dialect.escapechar;
            }
            res += c;
        }
        return dialect.quotechar
             + res
             + dialect.quotechar;
    }
}}
