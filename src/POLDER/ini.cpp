/*
 * Copyright (C) 2011-2012 Morwenn
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <POLDER/ini.h>
#include <POLDER/io.h>
#include <POLDER/string.h>
#include <POLDER/stype.h>


namespace polder
{
namespace ini
{

using namespace string;


// INI-specific elements
namespace
{
    // # and ;
    constexpr bool _comment[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    // : and =
    constexpr bool _equal[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    // :, =, \0 and \n
    constexpr bool _not_break1[256] = {
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    // #, ;, \0 and \n
    constexpr bool _not_break2[256] = {
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    constexpr bool is_comment_s(const char c)
    {
        return _comment[(unsigned)c];
    }

    constexpr bool is_equal_s(const char c)
    {
        return _equal[(unsigned)c];
    }

    constexpr bool is_not_break1(const char c)
    {
        return _not_break1[(unsigned)c];
    }

    constexpr bool is_not_break2(const char c)
    {
        return _not_break2[(unsigned)c];
    }

    /**
     * Return a string without comments
     */
    char* strnorm(const char* str)
    {
        char* new_str = (char*) malloc(strlen(str));
        int count = -1, i = -1;
        while (str[++i])
        {
            if (str[i] == '\n' || is_comment_s(str[i]))
            {
                count -= 2;
                break;
            }
            new_str[++count] = str[i];
        }
        new_str[count] = '\0';
        return stripped(new_str);
    }
}

/**
 * Return whether the given section exists or not
 */
size_t section_exists(const char* fname, const char* section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines and search the section number
    size_t n_line = 1;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        lstrip(line);
        if (!strncmp(line, searched_word, length))
        {
            fclose(f);
            return n_line;
        }
        ++n_line;
    }

    // Finish, the section has not been found
    fclose(f);
    return 0;
}


/**
 * Return whether the given key exists or not
 */
size_t key_exists(const char* fname, const char* section, const char* key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    size_t n_line = 1;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (section_found == false)
        {
            // Search the section number
            if (!strncmp(line, searched_word, length))
            {
                section_found = true;
            }
        }
        else // If the given section exists
        {
            if (line[0] == '[')
            {
                // We reached another section
                fclose(f);
                return 0;
            }
            else if (line[0] != ';' && line[0] != '#' && line[0] != '\0') // We check whether the key is the good one
            {
                int i = -1;
                while (is_not_break1(line[++i]));
                if (is_equal_s(line[i]))
                {
                    if (!strcmp(key, stripped(substr(line, 0, i-1))))
                    {
                        // The key has been found
                        fclose(f);
                        return n_line;
                    }
                }
                // Else, there is no key, strange...
            }
        }
        ++n_line;
    }

    // Finish, an error occured
    fclose(f);
    return 0;
}


/**
 * Read the string value corresponding to the given key
 */
char* read_string(const char* fname, const char* section, const char* key, char* default_value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (section_found == false)
        {
            // Search the section number
            if (!strncmp(line, searched_word, length))
            {
                section_found = true;
            }
        }
        else // If the given section exists
        {
            if (line[0] == '[')
            {
                // We reached another section
                fclose(f);
                return default_value;
            }
            else if (line[0] != ';' && line[0] != '#' && line[0] != '\0') // We check whether the key is the good one
            {
                int i = -1;
                while (is_not_break1(line[++i]));
                if (is_equal_s(line[i]))
                {
                    if (!strcmp(key, stripped(substr(line, 0, i-1))))
                    {
                        // The key has been found
                        int j = i;
                        while (is_not_break2(line[++j]));
                        fclose(f);
                        return stripped(substr(line, i+1, j-1));
                    }
                }
                // Else, there is no key, strange...
            }
        }
    }
    // Finish, an error occured
    fclose(f);
    return default_value;
}


/**
 * Read the real value corresponding to the given key
 */
double read_real(const char* fname, const char* section, const char* key, double default_value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (section_found == false)
        {
            // Search the section number
            if (!strncmp(line, searched_word, length))
            {
                section_found = true;
            }
        }
        else // If the given section exists
        {
            if (line[0] == '[')
            {
                // We reached another section
                fclose(f);
                return default_value;
            }
            else if (line[0] != ';' && line[0] != '#' && line[0] != '\0') // We check whether the key is the good one
            {
                int i = -1;
                while (is_not_break1(line[++i]));
                if (is_equal_s(line[i]))
                {
                    if (!strcmp(key, stripped(substr(line, 0, i-1))))
                    {
                        // The key has been found
                        int j = i;
                        while (is_not_break2(line[++j]));
                        fclose(f);
                        if (stype::is_number(substr(line, i+1, j-1)))
                        {
                            return atof(substr(line, i+1, j-1));
                        }
                        else
                        {
                            return default_value;
                        }
                    }
                }
                // Else, there is no key, strange...
            }
        }
    }

    // Finish, an error occured
    fclose(f);
    return default_value;
}


/**
 * Deletes the given section of an INI file
 */
void section_delete(const char* fname, const char* section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool in_section = false;
    bool section_found = false;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (in_section)
        {
            if (line[0] == '[')
            {
                in_section = false;
            }
        }
        else
        {
            if (!strncmp(line, searched_word, length))
            {
                in_section = true;
                section_found = true;
            }
        }

        // Copy the current line in the new file
        if (!in_section)
        {
            fprintf(temp, "%s", line);
        }
    }

    // Finish, check errors
    fclose(f);
    fclose(temp);

    if (!section_found)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Section '" + std::string(section) + "' not found.");
    }

    remove(fname);
    rename(temp_name, fname);
}


/**
 * Deletes the given key of an INI file
 */
void key_delete(const char* fname, const char* section, const char* key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool in_section = false;
    bool in_key = false;
    bool section_found = false;
    bool key_found = false;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (!key_found)
        {
            if (in_section)
            {
                if (line[0] == '[')
                {
                    in_section = false;
                    if (!key_found)
                    {
                        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Key '" + std::string(key) + "' not found.");
                    }
                }
                else if (line[0] != ';' && line[0] != '#' && line[0] != '\0') // We check whether the key is the good one
                {
                    register int i = -1;
                    while (is_not_break1(line[++i]));
                    if (is_equal_s(line[i]))
                    {
                        if (!strcmp(key, stripped(substr(line, 0, i-1))))
                        {
                            // The key has been found
                            key_found = true;
                            in_key = true;
                        }
                    }
                    // Else, there is no key, strange...
                }
            }
            else
            {
                if (!strncmp(line, searched_word, length))
                {
                    in_section = true;
                    section_found = true;
                }
            }
        }

        // Copy the current line in the new file
        if (!in_key)
        {
            fprintf(temp, "%s", line);
        }
        else
        {
            in_key = false;
        }
    }

    fclose(f);
    fclose(temp);

    if (!section_found)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Section '" + std::string(section) + "' not found.");
    }

    remove(fname);
    rename(temp_name, fname);
}


/**
 * Write a string in an INI file
 */
void write_string(const char* fname, const char* section, const char* key, const char* value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        // Create a new file
        f = fopen(fname, "w");
        fprintf(f, "[%s]\n", section);
        fprintf(f, "%s%c%s\n", key, '=', value);
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    size_t empty_lines = 0;

    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (!key_found)
        {
            if (section_found == false)
            {
                // Search the section
                if (!strncmp(line, searched_word, length))
                {
                    in_section = true;
                    section_found = true;
                }
            }
            else // If the given section exists
            {
                if (line[0] == '\n')
                {
                    // We "store" the empty line
                    ++empty_lines;
                    write_line = false;
                }
                else if (line[0] == '[')
                {
                    if (in_section)
                    {
                        // We reached the end of the section
                        // The key still has not be found
                        // So we add it
                        fprintf(temp, "%s%c%s\n", key, '=', value);
                        key_found = true;
                    }
                    for (size_t i = 0 ; i < empty_lines ; ++i)
                    {
                        fprintf(temp, "\n");
                    }
                    empty_lines = 0;
                }
                else
                {
                    // Add the empty lines needed
                    for (size_t i = 0 ; i < empty_lines ; ++i)
                    {
                        fprintf(temp, "\n");
                    }
                    empty_lines = 0;

                    // We check whether the key is the good one
                    if (line[0] != ';' && line[0] != '#' && line[0] != '\0')
                    {
                        strnorm(line);
                        int i = -1;
                        while (is_not_break1(line[++i]));
                        if (is_equal_s(line[i]))
                        {
                            if (!strcmp(key, stripped(substr(line, 0, i-1))))
                            {
                                // The key has been found
                                fprintf(temp, "%s%c%s\n", key, '=', value);
                                key_found = true;
                                write_line = false;
                            }
                        }
                    }
                }
            }
        }

        // Copy the current line in the new file
        if (write_line)
        {
            fprintf(temp, "%s", line);
        }
        else
        {
            write_line = true;
        }
    }

    if (!section_found)
    {
        fprintf(temp, "\n");
        fprintf(temp, "%s\n", searched_word);
        fprintf(temp, "%s%c%s\n", key, '=', value);
    }
    else if (!key_found)
    {
        fprintf(temp, "%s%c%s\n", key, '=', value);
    }

    // Finish
    fclose(f);
    fclose(temp);
    remove(fname);
    rename(temp_name, fname);
}


/**
 * Write a real in an INI file
 */
void write_real(const char* fname, const char* section, const char* key, double value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        // Create a new file
        f = fopen(fname, "w");
        fprintf(f, "[%s]\n", section);
        fprintf(f, "%s%c%f\n", key, '=', value);
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    size_t empty_lines = 0;

    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        strip(line);
        if (!key_found)
        {
            if (section_found == false)
            {
                // Search the section
                if (!strncmp(line, searched_word, length))
                {
                    in_section = true;
                    section_found = true;
                }
            }
            else // If the given section exists
            {
                if (line[0] == '\n')
                {
                    // We "store" the empty line
                    ++empty_lines;
                    write_line = false;
                }
                else if (line[0] == '[')
                {
                    if (in_section)
                    {
                        // We reached the end of the section
                        // The key still has not be found
                        // So we add it
                        fprintf(temp, "%s%c%f\n", key, '=', value);
                        key_found = true;
                    }
                    for (size_t i = 0 ; i < empty_lines ; ++i)
                    {
                        fprintf(temp, "\n");
                    }
                    empty_lines = 0;
                }
                else
                {
                    // Add the empty lines needed
                    for (size_t i = 0 ; i < empty_lines ; ++i)
                    {
                        fprintf(temp, "\n");
                    }
                    empty_lines = 0;


                    // We check whether the key is the good one
                    if (line[0] != ';' && line[0] != '#' && line[0] != '\0')
                    {
                        strnorm(line);
                        int i = -1;
                        while (is_not_break1(line[++i]));
                        if (line[i] == '=' || line[i] == ':')
                        {
                            if (!strcmp(key, stripped(substr(line, 0, i-1))))
                            {
                                // The key has been found
                                fprintf(temp, "%s%c%f\n", key, '=', value);
                                key_found = true;
                                write_line = false;
                            }
                        }
                    }
                }
            }
        }

        // Copy the current line in the new file
        if (write_line)
        {
            fprintf(temp, "%s", line);
        }
        else
        {
            write_line = true;
        }
    }

    if (!section_found)
    {
        fprintf(temp, "\n");
        fprintf(temp, "%s\n", searched_word);
        fprintf(temp, "%s%c%f\n", key, '=', value);
    }
    else if (!key_found)
    {
        fprintf(temp, "%s%c%f\n", key, '=', value);
    }

    // Finish
    fclose(f);
    fclose(temp);
    remove(fname);
    rename(temp_name, fname);
}

/**
 * Renames the given section of an INI file
 */
void section_rename(const char* fname, const char* section, const char* new_section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Create the searched word : [new_section]
    size_t new_length = strlen(new_section) + 2;
    char* new_searched_word = new char[new_length+1];
    strcpy(new_searched_word, "[");
    strcat(new_searched_word, new_section);
    strcat(new_searched_word, "]");

    bool section_found = false;
    bool write_line = true;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        lstrip(line);
        if (!strncmp(line, searched_word, length))
        {
            fprintf(temp, "%s\n", new_searched_word);
            write_line = false;
            section_found = true;
        }
        else if (!strncmp(line, new_searched_word, new_length))
        {
            fclose(f);
            fclose(temp);
            throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Section '" + std::string(section) + "' already exists.");
        }

        // Copy the current line in the new file
        if (write_line)
        {
            fprintf(temp, "%s", line);
        }
        else
        {
            write_line = true;
        }
    }

    // Finish, check errors
    fclose(f);
    fclose(temp);
    remove(fname);
    rename(temp_name, fname);

    if (!section_found)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Section '" + std::string(section) + "' not found.");
    }
}

/**
 * Renames the given key of an INI file
 */
void key_rename(const char* fname, const char* section, const char* key, const char* new_key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == nullptr)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Can not open file.");
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char* searched_word = new char[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    char* line = nullptr;
    while (io::fgetl(line, f))
    {
        if (!key_found)
        {
            strip(line);
            if (!section_found)
            {
                if (!strncmp(line, searched_word, length))
                {
                    section_found = true;
                    in_section = true;
                }
            }
            else if (in_section)
            {
                if (line[0] == '[')
                {
                    throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Key '" + std::string(key) + "' not found.");
                }
                // We check whether the key is the good one
                else if (line[0] != ';' && line[0] != '#' && line[0] != '\0')
                {
                    strnorm(line);
                    int i = -1;
                    while (is_not_break1(line[++i]));
                    if (is_equal_s(line[i]))
                    {
                        if (!strcmp(key, stripped(substr(line, 0, i-1))))
                        {
                            // The key has been found
                            key_found = true;
                            write_line = false;
                            int j = i;
                            while (is_not_break2(line[++j]));
                            fprintf(temp, "%s%c%s\n", new_key, '=', substr(line, i+1, j-1));
                        }
                        else if (!strcmp(new_key, stripped(substr(line, 0, i-1))))
                        {
                            throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Key '" + std::string(key) + "' already exists.");
                        }
                    }
                }
            }
        }

        // Copy the current line in the new file
        if (write_line)
        {
            fprintf(temp, "%s", line);
        }
        else
        {
            write_line = true;
        }
    }

    // Finish, check errors
    fclose(f);
    fclose(temp);

    if (!section_found)
    {
        throw ini_error(std::string(__FUNCTION__) + ": " + std::string(fname) + ": Section '" + std::string(section) + "' not found.");
    }

    remove(fname);
    rename(temp_name, fname);
}


/**
 * Exceptions handling
 */

// Create a new exception
ini_error::ini_error()
{
    std::ostringstream oss;
    oss << "polder::ini::ini_error: undocumented error.";
    msg = oss.str();
}

// Create a new exception
ini_error::ini_error(const std::string& arg)
{
    std::ostringstream oss;
    oss << arg;
    msg = oss.str();
}

// Destructor, does nothing
ini_error::~ini_error() noexcept {}

// Returns what the error is
const char* ini_error::what() const noexcept
{
    return msg.c_str();
}


} // namespace ini
} // namespace polder
