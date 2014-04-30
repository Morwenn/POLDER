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
#ifndef POLDER_INI_ELEMENT_H_
#define POLDER_INI_ELEMENT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iosfwd>
#include <string>
#include <typeindex>
#include <POLDER/details/config.h>

namespace polder
{
namespace ini
{
    /**
     * @brief Element representing a value in an ini file.
     *
     * This class stores a std::string that represents a
     * simple string or any basic integer or floating
     * point data.
     */
    struct POLDER_API Element
    {
        Element();
        Element(const Element& other);
        Element(Element&& other);
        ~Element();

        auto operator=(const Element& other)
            -> Element&;
        auto operator=(Element&& other)
            -> Element&;

        Element(const std::string& str);
        Element(const char* str);
        operator std::string() const;

        // Generate the constructors
        // from standard types
        #define X(type, func) \
            Element(type value);
        #include "details/ini.def"
        #undef X

        // Generate the conversion operators
        // to standard types
        #define X(type, func) \
            operator type() const;
        #include "details/ini.def"
        #undef X

        // Type id of the contained data
        std::type_index type_id = typeid(std::string);

        private:

            // Contained data - dialect-free
            std::string _data;

        friend auto operator<<(std::ostream&, const Element&)
            -> std::ostream&;
    };

    auto operator<<(std::ostream& stream, const Element& elem)
        -> std::ostream&;
}}

#endif // POLDER_INI_ELEMENT_H_
