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
#ifndef _POLDER_IO_H
#define _POLDER_IO_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <POLDER/config.h>


namespace polder
{

/**
 * @namespace polder::io
 * @brief Input/output functions
 *
 * Some helper functions that handle intput
 * and output in an easy way.
 */
namespace io
{


/**
 * @brief Read a line from a text file
 *
 * @param line Variable where to put the line
 * @param f File where to read the line
 * @return true if it is not the end of file
 */
POLDER_API bool fgetl(char*& line, FILE* f);

/**
 * @brief Print an arbitrary number of arguments to the standard output
 * @param first First argument to be printed
 * @param others Other arguments to be printed
 */
template<typename First, typename... Printables>
void print(const First& first, const Printables&... others);

/**
 * @brief Print a single argument to the standard output
 * @param arg Argument to be printed
 */
template<typename T>
void print(const T& arg);

/**
 * @brief File class
 */
class POLDER_API File
{
    public:

        ~File();

        void close();

        const File& begin() const;
        const File& end() const;
        bool operator!=(const File&) const;
        void operator++();
        std::string operator*() const;

    private:

        File(std::string&& fname, std::string&& mode);

        FILE* _file;    /**< Enclosed file */
        bool _closed;   /**< true if the file is closed */

    friend File open(std::string&&, std::string&&);
};

/**
 * @brief Wrapper for the File constructor
 */
POLDER_API File open(std::string&& fname, std::string&& mode="r");


#include <POLDER/io.inl>

} // namespace io
} // namespace polder


#endif // _POLDER_IO_H
