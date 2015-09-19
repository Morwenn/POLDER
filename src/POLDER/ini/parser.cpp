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
#include <cstddef>
#include <istream>
#include <iterator>
#include <ostream>
#include <typeindex>
#include <utility>
#include <vector>
#include <POLDER/ini/details/token.h>
#include <POLDER/ini/error.h>
#include <POLDER/ini/parser.h>

namespace polder
{
namespace ini
{
    ////////////////////////////////////////////////////////////
    // Construction
    ////////////////////////////////////////////////////////////

    Parser::Parser()
        = default;

    Parser::Parser(std::istream& input, Dialect dialect):
        dialect{dialect}
    {
        read(input);
    }

    Parser::Parser(std::initializer_list<
                    std::pair<
                        std::string,
                        std::initializer_list<
                            std::pair<std::string, Element>
                        >
                    >
                > values)
    {
        for (const auto& value: values)
        {
            Section& sec = add(std::get<0>(value));
            for (const auto& item: std::get<1>(value))
            {
                sec[std::get<0>(item)] = std::get<1>(item);
            }
        }
    }

    ////////////////////////////////////////////////////////////
    // read & write
    ////////////////////////////////////////////////////////////

    auto Parser::read(std::istream& input)
        -> void
    {
        if (not input)
        {
            throw Error("polder::ini::Parser::read: invalid input");
        }

        // Keeping track of the line number
        // to report the errors
        std::size_t line_number = 0u;
        // Current section
        std::string section = "";

        std::string line;
        while (std::getline(input, line, dialect.lineterminator))
        {
            ++line_number;

            std::vector<Token> tokens;
            try
            {
                tokens = tokenize(line, dialect);
            }
            catch (const Error& error)
            {
                // Rethrow the error with the line
                // number information
                throw Error(line_number, error.what());
            }

            if (tokens.empty())
            {
                continue;
            }

            ////////////////////////////////////////////////////////////
            // parse the tokens

            for (auto it = tokens.cbegin() ; it != tokens.cend() ; ++it)
            {
                switch (it->type)
                {
                    case token_t::BRACE_CLOSE:
                    {
                        throw Error(line_number, "closing brace does not match anything");
                        break;
                    }

                    case token_t::BRACE_OPEN:
                    {
                        // Check the section name
                        ++it;
                        if (it->type != token_t::IDENTIFIER)
                        {
                            throw Error(line_number, "invalid token after opening brace");
                        }
                        section = it->data;

                        // Check the closing brace
                        ++it;
                        if (it->type != token_t::BRACE_CLOSE)
                        {
                            throw Error(line_number, "mismatched square braces");
                        }

                        // Check whether there are other tokens
                        if (it+1 != tokens.end())
                        {
                            throw Error(line_number, "stray tokens after section header");
                        }

                        add(section);
                        break;
                    }

                    case token_t::DELIMITER:
                    {
                        throw Error(line_number, "stray delimiter in the code");
                        break;
                    }

                    case token_t::FLOATING_POINT:
                    {
                        throw Error("stray floating point literal in the code");
                        break;
                    }

                    case token_t::IDENTIFIER:
                    {
                        auto key = it->data;

                        // Check for the delimiter
                        ++it;
                        if (it->type != token_t::DELIMITER)
                        {
                            throw Error(line_number, "missing delimiter after identifier");
                        }

                        ++it;
                        if (it->type != token_t::INTEGER
                            && it->type != token_t::FLOATING_POINT
                            && it->type != token_t::STRING)
                        {
                            throw Error(line_number, "non-literal token after delimiter");
                        }

                        // Check whether there are other tokens
                        if (it+1 != tokens.end())
                        {
                            throw Error(line_number, "stray tokens after value assignment");
                        }

                        Element& elem = (*this)[section][key];
                        elem = it->data;
                        if (it->type == token_t::INTEGER)
                        {
                            elem.type_id = typeid(unsigned long long);
                        }
                        else if (it->type == token_t::FLOATING_POINT)
                        {
                            elem.type_id = typeid(long double);
                        }

                        break;
                    }

                    case token_t::INTEGER:
                    {
                        throw Error("stray integer literal in the code");
                        break;
                    }

                    case token_t::STRING:
                    {
                        throw Error("stray string literal in the code");
                        break;
                    }
                }
            }
        }
    }

    auto Parser::write(std::ostream& output) const
        -> void
    {
        if (not output)
        {
            throw Error("polder::ini::Parser::write: invalid output stream");
        }

        for (auto& section_item: items)
        {
            auto& section_name  = std::get<0>(section_item);
            auto& section       = std::get<1>(section_item);

            output << "[" << section_name << "]";
            output << dialect.lineterminator;
            for (auto& key_item: section.items)
            {
                auto& key_name  = std::get<0>(key_item);
                auto& key       = std::get<1>(key_item);

                // Convert the element to the dialect
                // if the element is a string
                std::string val;
                if (key.type_id == typeid(std::string))
                {
                    val = to_dialect(key, dialect);
                }
                else
                {
                    val = std::string(key);
                }

                output << key_name
                       << dialect.delimiter
                       << val
                       << dialect.lineterminator;
            }
            output << dialect.lineterminator;
        }
    }

    ////////////////////////////////////////////////////////////
    // Miscellaneous functions
    ////////////////////////////////////////////////////////////

    auto Parser::has(const std::string& section)
        -> bool
    {
        return bool(items.count(section));
    }

    auto Parser::add(const std::string& section)
        -> Section&
    {
        // std::map::operator[] creates a node if
        // it does not exist. Simply trying to
        // access such a node creates it.
        return items[section];
    }

    auto Parser::operator[](const std::string& section)
        -> Section&
    {
        return items[section];
    }

    ////////////////////////////////////////////////////////////
    // Iteration
    ////////////////////////////////////////////////////////////

    auto Parser::begin()
        -> iterator
    {
        return iterator(std::begin(items));
    }

    auto Parser::begin() const
        -> const_iterator
    {
        return const_iterator(std::begin(items));
    }

    auto Parser::cbegin() const
        -> const_iterator
    {
        return const_iterator(std::begin(items));
    }

    auto Parser::end()
        -> iterator
    {
        return iterator(std::end(items));
    }

    auto Parser::end() const
        -> const_iterator
    {
        return const_iterator(std::end(items));
    }

    auto Parser::cend() const
        -> const_iterator
    {
        return const_iterator(std::end(items));
    }

    ////////////////////////////////////////////////////////////
    // ini::Parser::Section
    ////////////////////////////////////////////////////////////

    auto Parser::Section::has(const std::string& key)
        -> bool
    {
        return bool(items.count(key));
    }

    auto Parser::Section::operator[](const std::string& key)
        -> Element&
    {
        return items[key];
    }

    auto Parser::Section::begin()
        -> iterator
    {
        return iterator(std::begin(items));
    }

    auto Parser::Section::begin() const
        -> const_iterator
    {
        return const_iterator(std::begin(items));
    }

    auto Parser::Section::cbegin() const
        -> const_iterator
    {
        return const_iterator(std::begin(items));
    }

    auto Parser::Section::end()
        -> iterator
    {
        return iterator(std::end(items));
    }

    auto Parser::Section::end() const
        -> const_iterator
    {
        return const_iterator(std::end(items));
    }

    auto Parser::Section::cend() const
        -> const_iterator
    {
        return const_iterator(std::end(items));
    }

    ////////////////////////////////////////////////////////////
    // Stream operators
    ////////////////////////////////////////////////////////////

    auto operator<<(std::ostream& stream, const Parser& config)
        -> std::ostream&
    {
        config.write(stream);
        return stream;
    }

    auto operator>>(std::istream& stream, Parser& config)
        -> std::istream&
    {
        config.read(stream);
        return stream;
    }
}}
