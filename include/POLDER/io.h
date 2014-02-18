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
#ifndef _POLDER_IO_H
#define _POLDER_IO_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <POLDER/details/config.h>


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
    ////////////////////////////////////////////////////////////
    // Print function

    /**
     * @brief Print an arbitrary number of arguments to the standard output
     * @param first First argument to be printed
     * @param others Other arguments to be printed
     */
    template<typename... Args>
    auto print(Args&&... args)
        -> void;

    template<typename... Args>
    auto print(std::ostream& stream, Args&&... args)
        -> void;

    ////////////////////////////////////////////////////////////
    // File reader

    /**
     * @brief Read a line from a text file
     *
     * @param line Variable where to put the line
     * @param f File where to read the line
     * @return true if it is not the end of file
     */
    POLDER_API bool fgetl(char*& line, FILE* f);

    ////////////////////////////////////////////////////////////
    // File class and related functions

    /**
     * @brief Seek positions
     *
     * Proxys for SEEK_CUR, SEEK_SET and SEEK_END.
     * Using an enum struct ensures a compile-time
     * check on the used constants.
     */
    enum struct seek_t: int
    {
        CUR = SEEK_CUR, /**< Current position */
        SET = SEEK_SET, /**< Beginning of the file */
        END = SEEK_END  /**< End of the file */
    };

    /**
     * @brief File class
     */
    class POLDER_API File
    {
        public:

            /**
             * @brief Destructor
             * Close the file if the file has not been closed yet.
             */
            ~File();

            // C functions proxy
            void close();
            int flush();
            char getc();
            void putc(char c);
            void puts(const std::string& str);
            void seek(long offset, seek_t origin);
            long tell();

            // Read file line by line in a for loop
            const File& begin() const;
            const File& end() const;
            bool operator!=(const File&) const;
            void operator++();
            std::string operator*() const;

        private:

            File(std::string&& fname, std::string&& mode);

            FILE* _file;    /**< Enclosed file */
            bool _closed;   /**< true if the file is closed */

        friend auto open(std::string&&, std::string&&)
            -> File;
    };

    /**
     * @brief Wrapper for the File constructor
     */
    POLDER_API
    auto open(std::string&& fname, std::string&& mode="r")
        -> File;

    #include "details/io.inl"
}}

#endif // _POLDER_IO_H
