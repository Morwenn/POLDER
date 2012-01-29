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
#include <POLDER/config.h>
#include <POLDER/string.h>


namespace polder
{


/**
 * @namespace polder::path
 * @brief Path manipulation functions
 *
 * The paths are strings whose syntax can change
 * from an operating system to another. This namespace
 * contains path-related functions that adapt themselves
 * to the operating system.
 */
namespace path
{


////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////

#ifdef POLDER_OS_WINDOWS

    /**
     * Standard separator character
     */
    constexpr char OS_SEP = '\\';

    /**
     * Standard separator character as string
     */
    constexpr char OS_SEP_STR[2] = "\\";

#else

    /**
     * Standard separator character
     */
    constexpr char OS_SEP = '/';

    /**
     * Standard separator character as string
     */
    constexpr char OS_SEP_STR[2] = "/";

#endif


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

/**
 * @brief Create a path
 *
 * This function creates a path by separating the different
 * given elements by a correct separator.
 * It stops when finding an empty string argument
 *
 * @param base First element of the path
 * @return Complete portable path
 */
POLDER_API char* make_path(const char* base, ...);

/**
 * @brief Get the extension of a path
 *
 * The extension of a given path is returned,
 * including its dot.
 *
 * @param path Path to "split"
 * @return Extension of the path
 */
POLDER_API char* get_ext(const char* path);

/**
 * @brief Get the name of a path
 *
 * The name returned includes the repertory
 * and not the extension nor the dot.
 *
 * @param path Path to "split"
 * @return Name of the path
 */
POLDER_API char* get_name(const char* path);

/**
 * @brief Get the directory of a path
 *
 * @param path Path to "split"
 * @return Directory of the path
 */
POLDER_API char* get_dir(const char* path);

#ifdef POLDER_OS_WINDOWS

    /**
     * @brief Drive letter of a path
     *
     * @param path Path to "split"
     * @return Drive of the path
     */
    POLDER_API char* get_drive(const char* path);

#endif

/**
 * @brief Check whether a path is obsolute
 *
 * @param path Path to analyze
 * @return True if the path is absolute
 */
POLDER_API bool is_absolute(const char* path);

/**
 * @brief Normalize a path
 *
 * This functions tries to get rid of the . and ..
 * directories in the given path to make an absolute
 * path out of it
 *
 * @param path Path to normalize
 */
POLDER_API void normalize(char* path);

/**
 * @brief Normalize a path
 * @see is_absolute()
 *
 * @param path Path to normalize
 * @return Normalized path
 */
POLDER_API char* normalized(const char* path);


} // namespace path
} // namespace polder


#endif // _POLDER_PATH_H
