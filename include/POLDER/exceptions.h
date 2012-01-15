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
#ifndef _POLDER_EXCEPTIONS_H
#define _POLDER_EXCEPTIONS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <string>


namespace polder
{


/**
 * @brief Division by zero
 *
 * This exception is returned by some classes when
 * an operation is somehow asked to perform a
 * division by 0.
 */
class division_by_zero:
    public std::exception
{
    public:

        explicit division_by_zero(const std::string& msg="Division by zero.");
        virtual ~division_by_zero() throw();
        virtual const char* what() const throw();

    protected:

        std::string _msg;   /**< Error message */
};


} // namespace polder


#endif // _POLDER_EXCEPTIONS_H
