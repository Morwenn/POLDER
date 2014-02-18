/*
 * Copyright (C) 2011-2014 Morwenn
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
#include <cctype>
#include <cstring>
#include <POLDER/stype.h>


namespace polder
{
namespace stype
{

// Return true is str is a boolean
bool is_bool(const char* str)
{
    if (strcmp(str, "true"))
    {
        if (strcmp(str, "false"))
        {
            return false;
        }
    }
    return true;
}

// Return true if str is an unsigned integer
bool is_uint(const char* str)
{
    if (!str[0])
    {
        // The string can not be empty
        return false;
    }
    for (int i = -1 ; str[++i] ;)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Return true is str is an integer
bool is_int(const char* str)
{
    if (!str[0])
    {
        // The string can not be empty
        return false;
    }
    if (!str[1]) // If the size of the string is 1
    {
        return isdigit(str[0]); // The first char can not be anything else than a digit
    }
    if (!isdigit(str[0]) && str[0] != '-')
    {
        return false;
    }
    for (unsigned int i = 0 ; str[++i] ;)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Return true if str is an unsigned floating point number
bool is_ufloat(const char* str)
{
    bool dot_found = false;
    for (unsigned int i = 0 ; str[i] ; ++i)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] != '.' || dot_found)
            {
                return false;
            }
            dot_found = true;
        }
    }
    return dot_found;
}

// Return true if str is a floating point number
bool is_float(const char* str)
{
    if (!str[0] || !str[1])
    {
        // The string length is 2 at least (ex: .5 or 1.)
        return false;
    }
    bool dotfound = false;
    if (!isdigit(str[0]) && str[0] != '-')
    {
        if (str[0] != '.')
        {
            // The first character must be a dot, a minus or a digit
            return false;
        }
        dotfound = true;
    }
    for (unsigned int i = 0 ; str[++i] ;)
    {
        if (!isdigit(str[i]))
        {
            if (dotfound || str[i] != '.' ||
                (str[i] == '.' && str[i-1] == '-' && str[i+1] == '\0')) // If the string is "-."
            {
                // There can not be more than one dot in a floating point number
                // There can not be anything else than digits and dots in the body of floating point number
                return false;
            }
            dotfound = true;
        }
    }
    return dotfound; // A floating point number is identified by his dot
}

// Returns whether a string corresponds to a unsigned number or not
bool is_unumber(const char* str)
{
    bool dot_found = false;
    for (unsigned int i = 0 ; str[i] ; ++i)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] != '.' || dot_found)
            {
                return false;
            }
            dot_found = true;
        }
    }
    return true;
}

// Returns whether a string corresponds to a number or not
bool is_number(const char* str)
{
    if (!isdigit(str[0]) && str[0] != '.' && str[0] != '-')
    {
        return false;
    }
    if (str[0] == '-' && str[1] == '\0')
    {
        return false;
    }
    bool dot_found = false;
    if (str[0] == '.')
    {
        dot_found = true;
    }
    for (unsigned int i = 1 ; str[i] ; ++i)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] != '.' || dot_found)
            {
                return false;
            }
            dot_found = true;
        }
    }
    return true;
}


} // namespace stype
} // namespace polder
