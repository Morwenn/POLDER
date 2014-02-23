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
#include <POLDER/exceptions.h>


namespace polder
{


division_by_zero::division_by_zero(const std::string& msg):
    _msg(msg)
{}

division_by_zero::~division_by_zero() noexcept
    = default;

auto division_by_zero::what() const noexcept
    -> const char*
{
    return _msg.c_str();
}


not_implemented::not_implemented(const std::string& msg):
    _msg(msg)
{}

not_implemented::~not_implemented() noexcept
    = default;

auto not_implemented::what() const noexcept
    -> const char*
{
    return _msg.c_str();
}


} // namespace polder
