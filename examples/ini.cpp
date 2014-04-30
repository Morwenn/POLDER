/*
 * Headers
 */
#include <fstream>
#include <iostream>
#include <string>
#include <POLDER/ini.h>

using namespace polder;
using namespace ini;


/**
 * @brief Entry point of application
 *
 * @return Application exit code
*/
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
                config.write(fout);
            }
        }

        ////////////////////////////////////////////////////////////
        // Read, modify & write a file
        {
            char fname[] = "test2.ini";
            Parser config;
            {
                std::ifstream fin(fname);
                config.read(fin);
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
                config.write(fout);
            }
        }
    }
    catch (const ini::Error& err)
    {
        std::cout << err.what() << std::endl;
    }
}
