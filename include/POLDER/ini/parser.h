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
#ifndef POLDER_INI_PARSER_H_
#define POLDER_INI_PARSER_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <initializer_list>
#include <iosfwd>
#include <map>
#include <string>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/ini/dialect.h>
#include <POLDER/ini/element.h>
#include <POLDER/itertools.h>

namespace polder
{
namespace ini
{
    /**
     * @brief Ini file class.
     *
     * An ini file works like a file but can also
     * be used as a map of sections.
     */
    struct POLDER_API Parser
    {
        // Forward reference
        struct Section;

        // Types
        using iterator = itertools::get_iterator<1, std::map<std::string, Section>::iterator>;
        using const_iterator = itertools::get_iterator<1, std::map<std::string, Section>::const_iterator>;

        Parser();

        /**
         * @brief Stream constructor.
         *
         * Constructs the parser with an optional
         * dialect and have it read the given
         * stream.
         *
         * @param input Input stream.
         * @param dialect Dialect used to parse the data.
         */
        Parser(std::istream& input, Dialect dialect={});

        /**
         * @brief Initialization constructor.
         *
         * Allows to initialize the parser data with
         * sections and key/value pairs in those
         * sections.
         *
         * @brief values Initialization values.
         */
        Parser(std::initializer_list<
                std::pair<
                    std::string,
                    std::initializer_list<
                        std::pair<std::string, Element>
                    >
                >
            > values);

        /**
         * @brief Reads data from a stream.
         *
         * Reads the config data from a given stream.
         * The data is parsed according the the parser's
         * current dialect.
         *
         * @param input Input stream.
         */
        auto read(std::istream& input)
            -> void;

        /**
         * @brief Writes data to a stream.
         *
         * Writes the config data to a given stream.
         * The data is formatted according to the
         * parser's current dialect.
         *
         * @param output Output stream.
         */
        auto write(std::ostream& output)
            -> void;

        /**
         * @brief Checks whether a section exists.
         *
         * This function checks whether a section with
         * the given name already exists in the file.
         *
         * @param section Section name.
         * @return Whether \a section exists.
         */
        auto has(const std::string& section)
            -> bool;

        /**
         * @brief Adds an empty section.
         *
         * This functions add an empty section with the
         * given name to the file, provided that the
         * section does not already exist.
         *
         * @param section Name of the section to create.
         */
        auto add(const std::string& section)
            -> Section&;

        auto operator[](const std::string& section)
            -> Section&;

        auto begin()
            -> iterator;
        auto begin() const
            -> const_iterator;
        auto cbegin() const
            -> const_iterator;

        auto end()
            -> iterator;
        auto end() const
            -> const_iterator;
        auto cend() const
            -> const_iterator;

        // Member data
        Dialect dialect;    /**< Dialect used to parse the data */
        std::map<std::string, Section> items; /**< Sections */
    };

    /**
     * @brief Parser section.
     *
     * Basically, a parser section is just a
     * collection of key/value pairs.
     */
    struct Parser::Section
    {
        using iterator = itertools::get_iterator<1, std::map<std::string, Element>::iterator>;
        using const_iterator = itertools::get_iterator<1, std::map<std::string, Element>::const_iterator>;

        auto has(const std::string& key)
            -> bool;

        auto operator[](const std::string& key)
            -> Element&;

        auto begin()
            -> iterator;
        auto begin() const
            -> const_iterator;
        auto cbegin() const
            -> const_iterator;

        auto end()
            -> iterator;
        auto end() const
            -> const_iterator;
        auto cend() const
            -> const_iterator;

        std::map<std::string, Element> items;
    };
}}

#endif // POLDER_INI_PARSER_H_
