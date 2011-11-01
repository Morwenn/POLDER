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
#include "ini.h"


namespace polder
{
namespace ini
{

using namespace string;

////////////////////////////////////////////////////////////
/// Return a string without comments
////////////////////////////////////////////////////////////
static char* strnorm(const char* str)
{
    char* new_str = (char*) malloc(strlen(str));
    int count = -1, i = -1;
    while (str[++i])
    {
        if (i == '\n' || i == ';' || i == '#')
        {
            count -= 2;
            break;
        }
        new_str[++count] = str[i];
    }
    new_str[count] = '\0';
    return stripped(new_str);
}

////////////////////////////////////////////////////////////
/// Return whether the given section exists or not
////////////////////////////////////////////////////////////
size_t section_exists(const char* fname, const char* section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return 0;
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines and search the section number
    size_t n_line = 1;
    char* line = NULL;
    while (fgetl(&line, f))
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


////////////////////////////////////////////////////////////
/// Return whether the given key exists or not
////////////////////////////////////////////////////////////
size_t key_exists(const char* fname, const char* section, const char* key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return 0;
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    size_t n_line = 1;
    char* line = NULL;
    while (fgetl(&line, f))
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
                while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                if (line[i] == '=' || line[i] == ':')
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


////////////////////////////////////////////////////////////
/// Read the string value corresponding to the given key
////////////////////////////////////////////////////////////
char* read_string(const char* fname, const char* section, const char* key, char* default_value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return default_value;
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    char* line = NULL;
    while (fgetl(&line, f))
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
                while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                if (line[i] == '=' || line[i] == ':')
                {
                    if (!strcmp(key, stripped(substr(line, 0, i-1))))
                    {
                        // The key has been found
                        int j = i;
                        while (line[++j] != '\n' && line[j] != '\0' && line[j] != ';' && line[j] != '#');
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


////////////////////////////////////////////////////////////
/// Read the real value corresponding to the given key
////////////////////////////////////////////////////////////
double read_real(const char* fname, const char* section, const char* key, double default_value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return default_value;
    }

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool section_found = false;
    char* line = NULL;
    while (fgetl(&line, f))
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
                while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                if (line[i] == '=' || line[i] == ':')
                {
                    if (!strcmp(key, stripped(substr(line, 0, i-1))))
                    {
                        // The key has been found
                        int j = i;
                        while (line[++j] != '\n' && line[j] != '\0' && line[j] != ';' && line[j] != '#');
                        fclose(f);
                        return atof(substr(line, i+1, j-1));
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


////////////////////////////////////////////////////////////
/// Deletes the given section of an INI file
////////////////////////////////////////////////////////////
ini_error section_delete(const char* fname, const char* section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool in_section = false;
    bool section_found = false;
    char* line = NULL;
    while (fgetl(&line, f))
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
    remove(fname);
    rename(temp_name, fname);

    if (section_found)
    {
        return ini_error::NONE;
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}


////////////////////////////////////////////////////////////
/// Deletes the given key of an INI file
////////////////////////////////////////////////////////////
ini_error key_delete(const char* fname, const char* section, const char* key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Read the lines
    bool in_section = false;
    bool in_key = false;
    bool section_found = false;
    bool key_found = false;
    char* line = NULL;
    while (fgetl(&line, f))
    {
        strip(line);
        if (!key_found)
        {
            if (in_section)
            {
                if (line[0] == '[')
                {
                    in_section = false;
                }
                else if (line[0] != ';' && line[0] != '#' && line[0] != '\0') // We check whether the key is the good one
                {
                    register int i = -1;
                    while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                    if (line[i] == '=' || line[i] == ':')
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
    remove(fname);
    rename(temp_name, fname);

    // Finish
    if (section_found)
    {
        if (key_found)
        {
            return ini_error::NONE;
        }
        else
        {
            return ini_error::KEY_DOES_NOT_EXIST;
        }
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}


////////////////////////////////////////////////////////////
/// Write a string in an INI file
////////////////////////////////////////////////////////////
ini_error write_string(const char* fname, const char* section, const char* key, const char* value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        // Create a new file
        f = fopen(fname, "w");
        fprintf(f, "[%s]\n", section);
        fprintf(f, "%s%c%s\n", key, '=', value);
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    size_t empty_lines = 0;

    char* line = NULL;
    while (fgetl(&line, f))
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
                        while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                        if (line[i] == '=' || line[i] == ':')
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

    // Finish, check errors
    fclose(f);
    fclose(temp);
    remove(fname);
    rename(temp_name, fname);

    if (section_found)
    {
        if (key_found)
        {
            return ini_error::NONE;
        }
        else
        {
            return ini_error::KEY_DOES_NOT_EXIST;
        }
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}


////////////////////////////////////////////////////////////
/// Write a real in an INI file
////////////////////////////////////////////////////////////
ini_error write_real(const char* fname, const char* section, const char* key, double value)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        // Create a new file
        f = fopen(fname, "w");
        fprintf(f, "[%s]\n", section);
        fprintf(f, "%s%c%f\n", key, '=', value);
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    size_t empty_lines = 0;

    char* line = NULL;
    while (fgetl(&line, f))
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
                        while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
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

    // Finish, check errors
    fclose(f);
    fclose(temp);
    remove(fname);
    rename(temp_name, fname);

    if (section_found)
    {
        if (key_found)
        {
            return ini_error::NONE;
        }
        else
        {
            return ini_error::KEY_DOES_NOT_EXIST;
        }
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}

////////////////////////////////////////////////////////////
/// Renames the given section of an INI file
////////////////////////////////////////////////////////////
ini_error section_rename(const char* fname, const char* section, const char* new_section)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    // Create the searched word : [new_section]
    size_t new_length = strlen(new_section) + 2;
    char new_searched_word[new_length+1];
    strcpy(new_searched_word, "[");
    strcat(new_searched_word, new_section);
    strcat(new_searched_word, "]");

    bool section_found = false;
    bool write_line = true;
    char* line = NULL;
    while (fgetl(&line, f))
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
            return ini_error::SECTION_ALREADY_EXISTS;
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

    if (section_found)
    {
        return ini_error::NONE;
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}

////////////////////////////////////////////////////////////
/// Renames the given key of an INI file
////////////////////////////////////////////////////////////
ini_error key_rename(const char* fname, const char* section, const char* key, const char* new_key)
{
    // Open the file
    FILE* f = fopen(fname, "r");
    if (f == NULL)
    {
        return ini_error::CAN_NOT_OPEN_FILE;
    }

    // Creation of a temporary file
    char temp_name[L_tmpnam];
    tmpnam(temp_name);
    FILE* temp = fopen(temp_name, "w");

    // Create the searched word : [section]
    size_t length = strlen(section) + 2;
    char searched_word[length+1];
    strcpy(searched_word, "[");
    strcat(searched_word, section);
    strcat(searched_word, "]");

    bool section_found = false;
    bool key_found = false;
    bool in_section = false;
    bool write_line = true;
    char* line = NULL;
    while (fgetl(&line, f))
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
                    in_section = false;
                }
                // We check whether the key is the good one
                else if (line[0] != ';' && line[0] != '#' && line[0] != '\0')
                {
                    strnorm(line);
                    int i = -1;
                    while (line[++i] != '=' && line[i] != ':' && line[i] != '\n' && line[i] != '\0');
                    if (line[i] == '=' || line[i] == ':')
                    {
                        if (!strcmp(key, stripped(substr(line, 0, i-1))))
                        {
                            // The key has been found
                            key_found = true;
                            write_line = false;
                            int j = i;
                            while (line[++j] != '\n' && line[j] != '\0' && line[j] != ';' && line[j] != '#');
                            fprintf(temp, "%s%c%s\n", new_key, '=', substr(line, i+1, j-1));
                        }
                        else if (!strcmp(new_key, stripped(substr(line, 0, i-1))))
                        {
                            return ini_error::KEY_ALREADY_EXISTS;
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
    remove(fname);
    rename(temp_name, fname);

    if (section_found)
    {
        if (key_found)
        {
            return ini_error::NONE;
        }
        else
        {
            return ini_error::KEY_DOES_NOT_EXIST;
        }
    }
    else
    {
        return ini_error::SECTION_DOES_NOT_EXIST;
    }
}


} // namespace ini
} // namespace polder
