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
#ifndef _POLDER_INI_H
#define _POLDER_INI_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <POLDER/config.h>
#include <POLDER/string.h>
#include <POLDER/ptype.h>


namespace polder
{

/**
 * @namespace polder::ini
 * @brief INI-related functions
 *
 * All the functions placed under this namespace are
 * meant to use simply some regular INI files. You can
 * find some more information on Morwenn wiki about the
 * INI syntax understood by these functions (since there
 * is not any norm to define it).
 */
namespace ini
{


////////////////////////////////////////////////////////////
// Exceptions handling
////////////////////////////////////////////////////////////

/**
 * Exceptions that can be raised during the manipulation
 * of an INI file.
 */
class POLDER_API ini_error:
    public std::exception
{
    public:
        explicit ini_error();
        explicit ini_error(const std::string& arg);
        virtual ~ini_error() noexcept;
        virtual const char* what() const noexcept;

    private:
        std::string msg; /**< Error message */
};


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

/**
 * @brief Return whether the given section exists or not
 *
 * @param fname INI file to read
 * @param section Section whose existence is checked
 *
 * @return True is the section exists
 */
POLDER_API size_t section_exists(const char* fname, const char* section);

/**
 * @brief Return whether the given key exists or not
 *
 * @param fname INI file to read
 * @param section Section whose existence is checked
 * @param key Key whose existence is checked
 *
 * @return True if the key exists
*/
POLDER_API size_t key_exists(const char* fname, const char* section, const char* key);

/**
 * @brief Read the string value corresponding to the given key
 *
 * @param fname INI file to read
 * @param section Section to read
 * @param key Key to read
 * @param default_value Value to return if the key does not exist
 *
 * @return Read value or default value
*/
POLDER_API char* read_string(const char* fname, const char* section, const char* key, char* default_value);

/**
 * @brief Read the real value corresponding to the given key
 *
 * @param fname INI file to read
 * @param section Section to read
 * @param key Key to read
 * @param default_value Value to return if the key does not exist
 *
 * @return Read value or default value
*/
POLDER_API double read_real(const char* fname, const char* section, const char* key, double default_value);

/**
 * @brief Deletes the given section of an INI file
 *
 * @param fname INI file to read
 * @param section Section to delete
*/
POLDER_API void section_delete(const char* fname, const char* section);

/**
 * @brief Deletes the given key of an INI file
 *
 * @param fname INI file to read
 * @param section Section where is located the key to delete
 * @param key Key to delete
*/
POLDER_API void key_delete(const char* fname, const char* section, const char* key);

/**
 * @brief Write a string in an INI file
 *
 * @param fname INI file to read
 * @param section Section where to write the string
 * @param key Key where to write the string
 * @param value String to write
*/
POLDER_API void write_string(const char* fname, const char* section, const char* key, const char* value);

/**
 * @brief Write a real in an INI file
 *
 * @param fname INI file to read
 * @param section Section where to write the real
 * @param key Key where to write the real
 * @param value Real to write
*/
POLDER_API void write_real(const char* fname, const char* section, const char* key, double value);

/**
 * @brief Renames the given section of an INI file
 *
 * @param fname INI file to read
 * @param section Section to rename
 * @param new_section New name of the section
*/
POLDER_API void section_rename(const char* fname, const char* section, const char* new_section);

/**
 * @brief Renames the given key of an INI file
 *
 * @param fname INI file to read
 * @param section Section where is located the key to delete
 * @param key Key to rename
 * @param new_key New name of the key
*/
POLDER_API void key_rename(const char* fname, const char* section, const char* key, const char* new_key);


} // namespace ini
} // namespace polder


#endif // _POLDER_INI_H
