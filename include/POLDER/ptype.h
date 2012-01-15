/*
 * Copyright (C) 2011 Morwenn
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


namespace polder
{
namespace ptype
{


bool is_bool(const char* str);
bool is_uint(const char* str);
bool is_int(const char* str);
bool is_ufloat(const char* str);
bool is_float(const char* str);
bool is_unumber(const char* str);
bool is_number(const char* str);


} // namespace ptype
} // namespace polder


#endif // _POLDER_PTYPE_H
