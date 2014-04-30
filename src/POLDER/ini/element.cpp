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
#include <ostream>
#include <POLDER/ini/element.h>

namespace polder
{
namespace ini
{
    Element::Element() = default;
    Element::Element(const Element&) = default;
    Element::Element(Element&&) = default;
    Element::~Element() = default;

    auto Element::operator=(const Element&)
        -> Element&
        = default;
    auto Element::operator=(Element&&)
        -> Element&
        = default;

    Element::Element(const std::string& str):
        type_id(typeid(std::string)),
        _data(str)
    {}

    Element::Element(const char* str):
        Element(std::string(str))
    {}

    Element::operator std::string() const
    {
        return _data;
    }

    // Generate the constructors
    // from standard types
    #define X(type, func)                   \
        Element::Element(type value):       \
            type_id(typeid(type)),          \
            _data(std::to_string(value))    \
        {}
    #include <POLDER/ini/details/ini.def>
    #undef X

    // Generate the conversion operators
    // to standard types
    #define X(type, func)               \
        Element::operator type() const  \
        {                               \
            return std::func(_data);    \
        }
    #include <POLDER/ini/details/ini.def>
    #undef X

    auto operator<<(std::ostream& stream, const Element& elem)
        -> std::ostream&
    {
        stream << elem._data;
        return stream;
    }
}}
