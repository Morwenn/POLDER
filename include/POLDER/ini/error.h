/*
 * Copyright (C) 2014 Morwenn
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
#ifndef POLDER_INI_ERROR_H_
#define POLDER_INI_ERROR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <string>
#include <POLDER/details/config.h>

namespace polder
{
namespace ini
{
    /**
     * @brief INI-related exceptions.
     */
    class POLDER_API Error:
        public std::exception
    {
        public:

            /**
             * @brief Unexpected or undocumented error.
             */
            Error();

            /**
             * @brief Constructs an error with a message.
             *
             * \param what_arg Error message.
             */
            explicit Error(const std::string& what_arg);
            explicit Error(const char* what_arg);

            /**
             * @brief Constructs an error with a message and a line.
             *
             * The parameter \a line is meant to receive the
             * number of the line in the INI file where the
             * error occurred.
             *
             * \param line Line where the error occurred.
             * \param what_arg Error message.
             */
            Error(std::size_t line, const std::string& what_arg);
            Error(std::size_t line, const char* what_arg);

            virtual ~Error() noexcept override;

            /**
             * @brief Returns the explanatory string.
             *
             * @return Error message.
             */
            virtual auto what() const noexcept
                -> const char*
                override;

        private:

            std::string _msg; /**< Error message */
    };
}}

#endif // POLDER_INI_ERROR_H_
