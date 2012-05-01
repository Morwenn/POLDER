/*
 * Copyright (C) 2011-2012 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_PTYPE_H
#define _POLDER_PTYPE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cctype>
#include <cstring>
#include <POLDER/config.h>


namespace polder
{

/**
 * @namespace polder::ptype
 * @brief String representations of numbers analysis
 *
 * All the functions in this namespace are used to analyse
 * strings. They all return whether the given string
 * represents a given kind of number such as an integer or
 * a real number.
 */
namespace ptype
{


POLDER_API bool is_bool(const char* str);
POLDER_API bool is_uint(const char* str);
POLDER_API bool is_int(const char* str);
POLDER_API bool is_ufloat(const char* str);
POLDER_API bool is_float(const char* str);
POLDER_API bool is_unumber(const char* str);
POLDER_API bool is_number(const char* str);


} // namespace ptype
} // namespace polder


#endif // _POLDER_PTYPE_H
