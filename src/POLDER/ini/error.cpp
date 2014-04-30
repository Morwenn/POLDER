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
#include <POLDER/ini/error.h>


namespace polder
{
namespace ini
{
    Error::Error():
        _msg{"polder::ini::Error: undocumented error."}
    {}

    Error::Error(const std::string& what_arg):
        _msg{what_arg}
    {}

    Error::Error(const char* what_arg):
        _msg{what_arg}
    {}

    Error::Error(std::size_t line, const std::string& what_arg):
        _msg{"line " + std::to_string(line) + ": " + what_arg}
    {}

    Error::Error(std::size_t line, const char* what_arg):
        Error{line, std::string{what_arg}}
    {}


    Error::~Error() noexcept
        = default;

    auto Error::what() const noexcept
        -> const char*
    {
        return _msg.c_str();
    }
}}
