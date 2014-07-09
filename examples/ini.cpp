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
#include <fstream>
#include <iostream>
#include <string>
#include <POLDER/ini.h>

using namespace polder;
using namespace ini;

int main()
{
    try
    {
        ////////////////////////////////////////////////////////////
        // Create a new configuration
        {
            // Note that you can store values of
            // any type accepted by std::to_string

            Parser config = {
                { "section1", {
                    { "key1", "value1" },
                    { "key2", 3 },
                    { "key3", 4.5 },
                }},
                { "section2", {
                    { "key1", "value1" },
                    { "key2", "value2" },
                    { "key3", 89ull },
                }},
                { "section3", {
                    { "key1", "value1" },
                    { "key2", "value2" },
                    { "key3", "value3" },
                }}
            };

            // Write config to a file
            {
                std::ofstream fout("test1.ini");
                fout << config;
            }

            // Write config to standard output
            std::cout << config;
        }

        ////////////////////////////////////////////////////////////
        // Read, modify & write a file
        {
            char fname[] = "test2.ini";
            Parser config;
            {
                std::ifstream fin(fname);
                fin >> config;
            }

            if (config.has("section"))
            {
                Parser::Section& section = config["section"];
                for (const Element& key: section)
                {
                    std::cout << key << " ";
                }
            }

            // Create & edit section 1
            config["section1"]["key1"] = 1;
            config["section1"]["key2"] = 2;
            // Create & edit section 2
            auto& sec2 = config.add("section2");
            sec2["key"] = std::string("del\"rkghj");
            sec2["keyyy"] = 5.9;
            // Create section 3
            config.add("section3");

            // Write config back to a file
            {
                std::ofstream fout(fname);
                fout << config;
            }
        }
    }
    catch (const ini::Error& err)
    {
        std::cout << err.what() << std::endl;
    }
}
