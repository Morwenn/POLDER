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
#ifndef _POLDER_PATH_H
#define _POLDER_PATH_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <cstdarg>
#include "string.h"


namespace polder
{
namespace path
{

////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////
#ifdef __linux__
    #define OS_SEP ('/')
    #define OS_SEP_STR ("/")
#elif defined _WIN32 || defined _WIN64
    #define OS_SEP ('\\')
    #define OS_SEP_STR ("\\")
#endif


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

// Create a path
char* make_path(const char* base, ...);

// Split a path
char* get_ext(const char* path);
char* get_name(const char* path);
char* get_dir(const char* path);
#if defined _WIN32 || defined _WIN64
    char* get_drive(const char* path);
#endif

// Get some information about a path
bool is_absolute(const char* path);

// Normalize a path
void normalize(char* path);
char* normalized(char* path);


} // namespace path
} // namespace polder


#endif
