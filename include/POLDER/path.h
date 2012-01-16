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
#include <POLDER/string.h>


namespace polder
{
namespace path
{


////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////

#ifdef __linux__

    /**
     * Standard separator character
     */
    constexpr char OS_SEP = '/';

    /**
     * Standard separator character as string
     */
    constexpr char OS_SEP_STR[2] = "/";

#elif defined _WIN32 || defined _WIN64

    /**
     * Standard separator character
     */
    constexpr char OS_SEP = '\\';

    /**
     * Standard separator character as string
     */
    constexpr char OS_SEP_STR[2] = "\\";

#endif


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

/**
 * @brief Create a path
 *
 * This function creates a path by separating the different
 * given elements by a correct separator.
 * It stops when finding a nullptr or NULL argument.
 *
 * @param base First element of the path
 * @return Complete portable path
 */
char* make_path(const char* base, ...);

/**
 * @brief Get the extension of a path
 *
 * The extension of a given path is returned,
 * including its dot.
 *
 * @param path Path to "split"
 * @return Extension of the path
 */
char* get_ext(const char* path);

/**
 * @brief Get the name of a path
 *
 * The name returned includes the repertory
 * and not the extension nor the dot.
 *
 * @param path Path to "split"
 * @return Name of the path
 */
char* get_name(const char* path);

/**
 * @brief Get the directory of a path
 *
 * @param path Path to "split"
 * @return Directory of the path
 */
char* get_dir(const char* path);

#if defined _WIN32 || defined _WIN64

    /**
     * @brief Drive letter of a path
     *
     * @param path Path to "split"
     * @return Drive of the path
     */
    char* get_drive(const char* path);

#endif

/**
 * @brief Check whether a path is obsolute
 *
 * @param path Path to analyze
 * @return True if the path is absolute
 */
bool is_absolute(const char* path);

/**
 * @brief Normalize a path
 *
 * This functions tries to get rid of the . and ..
 * directories in the given path to make an absolute
 * path out of it
 *
 * @param path Path to normalize
 */
void normalize(char* path);

/**
 * @brief Normalize a path
 * @see is_absolute()
 *
 * @param path Path to normalize
 * @return Normalized path
 */
char* normalized(const char* path);


} // namespace path
} // namespace polder


#endif // _POLDER_PATH_H
