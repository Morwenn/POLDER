/*
 * Copyright (C) 2011-2013 Morwenn
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
#ifndef _POLDER_INI_H
#define _POLDER_INI_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <fstream>
#include <string>
#include <POLDER/config.h>


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

    /**
     * @brief Dialect for parsing an INI file.
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
 * @param dialect Dialect used to parse the file
 *
 * @return True is the section exists
 */
POLDER_API
auto section_exists(const char* fname, const char* section, Dialect dialect={})
    -> bool;

/**
 * @brief Return whether the given key exists or not
 *
 * @param fname INI file to read
 * @param section Section whose existence is checked
 * @param key Key whose existence is checked
 * @param dialect Dialect used to parse the file
 *
 * @return True if the key exists
 */
POLDER_API
auto key_exists(const char* fname, const char* section, const char* key, Dialect dialect={})
    -> bool;

/**
 * @brief Read the string value corresponding to the given key
 *
 * @param fname INI file to read
 * @param section Section to read
 * @param key Key to read
 * @param default_value Value to return if the key does not exist
 * @param dialect Dialect used to parse the file
 *
 * @return Read value or default value
 */
POLDER_API
auto read_string(const char* fname, const char* section, const char* key, char* default_value, Dialect dialect={})
    -> char*;

/**
 * @brief Read the real value corresponding to the given key
 *
 * @param fname INI file to read
 * @param section Section to read
 * @param key Key to read
 * @param default_value Value to return if the key does not exist
 * @param dialect Dialect used to parse the file
 *
 * @return Read value or default value
 */
POLDER_API
auto read_real(const char* fname, const char* section, const char* key, double default_value, Dialect dialect={})
    -> double;

/**
 * @brief Deletes the given section of an INI file
 *
 * @param fname INI file to read
 * @param section Section to delete
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto section_delete(const char* fname, const char* section, Dialect dialect={})
    -> void;

/**
 * @brief Deletes the given key of an INI file
 *
 * @param fname INI file to read
 * @param section Section where is located the key to delete
 * @param key Key to delete
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto key_delete(const char* fname, const char* section, const char* key, Dialect dialect={})
    -> void;

/**
 * @brief Write a string in an INI file
 *
 * @param fname INI file to read
 * @param section Section where to write the string
 * @param key Key where to write the string
 * @param value String to write
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto write_string(const char* fname, const char* section, const char* key, const char* value, Dialect dialect={})
    -> void;

/**
 * @brief Write a real in an INI file
 *
 * @param fname INI file to read
 * @param section Section where to write the real
 * @param key Key where to write the real
 * @param value Real to write
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto write_real(const char* fname, const char* section, const char* key, double value, Dialect dialect={})
    -> void;

/**
 * @brief Renames the given section of an INI file
 *
 * @param fname INI file to read
 * @param section Section to rename
 * @param new_section New name of the section
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto section_rename(const char* fname, const char* section, const char* new_section, Dialect dialect={})
    -> void;

/**
 * @brief Renames the given key of an INI file
 *
 * @param fname INI file to read
 * @param section Section where is located the key to delete
 * @param key Key to rename
 * @param new_key New name of the key
 * @param dialect Dialect used to parse the file
 */
POLDER_API
auto key_rename(const char* fname, const char* section, const char* key, const char* new_key, Dialect dialect={})
    -> void;


} // namespace ini
} // namespace polder


#endif // _POLDER_INI_H
