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
#include <POLDER/exceptions.h>


namespace polder
{


/**
 * @brief Creates a new exception
 * @param msg Error message to be displayed
 */
division_by_zero::division_by_zero(const std::string& msg):
    _msg(msg)
{}


/**
 * @brief Destructor
 */
division_by_zero::~division_by_zero() noexcept {}


/**
 * @brief Returns the error message
 * @return Error message
 */
const char* division_by_zero::what() const noexcept
{
    return _msg.c_str();
}


} // namespace polder
