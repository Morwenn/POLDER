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
#ifndef _POLDER_EXCEPTIONS_H
#define _POLDER_EXCEPTIONS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <string>
#include <POLDER/config.h>


namespace polder
{


/**
 * @brief Division by zero
 *
 * This exception is returned by some classes when
 * an operation is somehow asked to perform a
 * division by 0.
 */
class POLDER_API division_by_zero:
    public std::exception
{
    public:

        /**
         * @brief Creates a new exception
         * @param msg Error message to be displayed
         */
        explicit division_by_zero(const std::string& msg="Division by zero.");

        /**
         * @brief Destructor
         */
        virtual ~division_by_zero() noexcept;

        /**
         * @brief Returns the error message
         * @return Error message
         */
        virtual const char* what() const noexcept;

    protected:

        std::string _msg;   /**< Error message */
};


/**
 * @brief
 */
class POLDER_API not_implemented:
    public std::exception
{
    public:

        /**
         * @brief Creates a new exception
         * @param msg Error message to be displayed
         */
        explicit not_implemented(const std::string& msg="Not implemented.");

        /**
         * @brief Destructor
         */
        virtual ~not_implemented() noexcept;

        /**
         * @brief Returns the error message
         * @return Error message
         */
        virtual const char* what() const noexcept;

    protected:

        std::string _msg;   /**< Error message */
};


} // namespace polder


#endif // _POLDER_EXCEPTIONS_H
