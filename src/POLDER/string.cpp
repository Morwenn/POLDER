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
#include <cctype>
#include <cstring>
#include <POLDER/string.h>


namespace polder
{
namespace string
{

////////////////////////////////////////////////////////////
// Static variables used with "iterator" functions
////////////////////////////////////////////////////////////

// For read_word_first() and read_word_next()
static std::size_t read_word_index;
static std::size_t read_word_length;
static char* read_word_str;


////////////////////////////////////////////////////////////
// Deletes the spaces and tabulations at the beginning and the end of a string
////////////////////////////////////////////////////////////
void strip(char* str)
{
    std::size_t length = strlen(str) - 1;
    bool offset = (str[length] == '\n');

    // Delete the spaces at the end of the string
    int i = length - offset;
    for (; i >= 0 ; --i)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            if (offset)
            {
                str[++i] = '\n';
            }
            str[++i] = '\0';
            break;
        }
    }

    // Count the number of spaces at the beginning of the string
    int count_spaces = -1;
    while (str[++count_spaces] == ' ' || str[count_spaces] == '\t');

    // Delete the spaces at the beginning of the line
    memcpy(str, (char*) str + count_spaces, i - count_spaces + 1);
}

void strip(std::string& str)
{
    // Strip the characters at the beginning of the string
    int i = -1;
    while (std::isspace(str[++i]));
    str.erase(0, i);

    // Strip the characters at the end of the string
    i = str.size();
    while (std::isspace(str[--i]));
    str.erase(i+1, str.size()-i);
}

////////////////////////////////////////////////////////////
// Deletes the spaces and tabulations at the beginning of a string
////////////////////////////////////////////////////////////
void lstrip(char* str)
{
    // Count the number of spaces at the beginning of the string
    int count_spaces = -1;
    while (str[++count_spaces] == ' ' || str[count_spaces] == '\t');

    // Delete the spaces at the beginning of the line
    memcpy(str, (char*) str + count_spaces, strlen(str) - count_spaces + 1);
}

void lstrip(std::string& str)
{
    // Strip the characters at the beginning of the string
    int i = -1;
    while (std::isspace(str[++i]));
    str.erase(0, i);
}

////////////////////////////////////////////////////////////
// Deletes the spaces and tabulations at the end of a string
////////////////////////////////////////////////////////////
void rstrip(char* str)
{
    std::size_t length = strlen(str) - 1;
    bool offset = (str[length] == '\n');

    // Delete the spaces at the end of the string
    int i = length - offset;
    for (; i >= 0 ; --i)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            if (offset)
            {
                str[++i] = '\n';
            }
            str[++i] = '\0';
            break;
        }
    }
}

void rstrip(std::string& str)
{
    // Strip the characters at the end of the string
    int i = str.size();
    while (std::isspace(str[--i]));
    str.erase(i+1, str.size()-i);
}

char* stripped(const char* str)
{
    std::size_t length = strlen(str) - 1;
    bool offset = (str[length] == '\n');

    char* new_str = new char[length+2];
    strcpy(new_str, str);

    // Delete the spaces at the end of the string
    int i = length - offset;
    for (; i >= 0 ; --i)
    {
        if (new_str[i] != ' ' && new_str[i] != '\t')
        {
            if (offset)
            {
                new_str[++i] = '\n';
            }
            new_str[++i] = '\0';
            break;
        }
    }

    // Count the number of spaces at the beginning of the string
    int count_spaces = -1;
    while (new_str[++count_spaces] == ' ' || new_str[count_spaces] == '\t');

    // Delete the spaces at the beginning of the line
    memcpy(new_str, (char*) new_str + count_spaces, i - count_spaces + 1);
    return new_str;
}

auto stripped(std::string str)
    -> std::string
{
    strip(str);
    return str;
}

char* lstripped(const char* str)
{
    std::size_t length = strlen(str) + 1;
    char* new_str = new char[length];
    strcpy(new_str, str);

    // Count the number of spaces at the beginning of the string
    int count_spaces = -1;
    while (new_str[++count_spaces] == ' ' || new_str[count_spaces] == '\t');

    // Delete the spaces at the beginning of the line
    memcpy(new_str, (char*) new_str + count_spaces, length - count_spaces);
    return new_str;
}

auto lstripped(std::string str)
    -> std::string
{
    lstrip(str);
    return str;
}

char* rstripped(const char* str)
{
    std::size_t length = strlen(str) - 1;
    bool offset = (str[length] == '\n');

    char* new_str = new char[length+2];
    strcpy(new_str, str);

    // Delete the spaces at the end of the string
    int i = length - offset;
    for (; i >= 0 ; --i)
    {
        if (new_str[i] != ' ' && new_str[i] != '\t')
        {
            if (offset)
            {
                new_str[++i] = '\n';
            }
            new_str[++i] = '\0';
            break;
        }
    }
    return new_str;
}

auto rstripped(std::string str)
    -> std::string
{
    rstrip(str);
    return str;
}

////////////////////////////////////////////////////////////
// If the given character has more than one successive
// occurrence, successive occurrences are deleted until
// only one remains
////////////////////////////////////////////////////////////
void reduce_char(char* str, char c)
{
    std::size_t index = 0;
    for (int i = -1 ; str[++i] ;)
    {
        if (str[i] != c || str[i+1] != c)
        {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}


////////////////////////////////////////////////////////////
// If the given character has more than one successive occurence, successive occurences are deleted until one remain
////////////////////////////////////////////////////////////
void reduce_all(char* str)
{
    std::size_t index = 0;
    for (int i = -1 ; str[++i] ;)
    {
        if (str[i] != str[i+1])
        {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}


////////////////////////////////////////////////////////////
// Returns a sub-string of the given string
////////////////////////////////////////////////////////////
char* read_word(const char* str, std::size_t searched_word_number)
{
    unsigned int word_number = 0;
    unsigned int word_begin;

    // For each character in the string
    int i = -1;
    while (str[++i])
    {
        if (!isspace(str[i]) && (isspace(str[i-1]) || i == 0))
        {
            // This is the beginning of a new word
            if (++word_number == searched_word_number)
            {
                // If the word is the researched word,
                // we save its beginning index
                word_begin = i;
            }
        }
        else if (!isspace(str[i-1]) && isspace(str[i]) && word_number == searched_word_number)
        {
            // If we have reached the end of the wanted word, we return it
            return substr(str, word_begin, i-1);
        }
    }
    if (word_begin)
    {
        return substr(str, word_begin, i-1);
    }
    // If the word is not found, an empty string is returned
    return (char*) "";
}

////////////////////////////////////////////////////////////
// Initializes the reading of a string
////////////////////////////////////////////////////////////
char* read_word_first(const char* str)
{
    read_word_index = 0;
    read_word_length = strlen(str);
    read_word_str = new char[read_word_length+1];
    strcpy(read_word_str, str);
    return read_word_next();
}

////////////////////////////////////////////////////////////
// Returns the "next" word in a string
////////////////////////////////////////////////////////////
char* read_word_next()
{
    std::size_t word_begin;
    if (read_word_index == 0 && !isspace(read_word_str[0]))
    {
        word_begin = 0;
        ++read_word_index;
    }

    // For each character in the string
    for (; read_word_index <= read_word_length ; ++read_word_index)
    {
        if (!isspace(read_word_str[read_word_index])
            && read_word_str[read_word_index]
            && isspace(read_word_str[read_word_index-1]))
        {
            // we save its beginning index
            word_begin = read_word_index;
        }
        else if ((!isspace(read_word_str[read_word_index-1]) && isspace(read_word_str[read_word_index]))
                 || read_word_index == read_word_length)
        {
            // If we have reached the end of the wanted word, we return it
            return substr(read_word_str, word_begin, read_word_index++ - 1);
        }
    }

    // If the word is not found, an empty string is returned
    return (char*) "";
}

////////////////////////////////////////////////////////////
// Returns a sub-string of the given string
////////////////////////////////////////////////////////////
char* substr(const char* str, std::size_t index_begin, size_t index_end)
{
    if (index_end <= strlen(str) && index_begin <= index_end)
    {
        int temp = index_end - index_begin + 1;
        char* res_str = new char[temp+1];
        memcpy(res_str, (char*) str + index_begin, temp);
        res_str[temp] = '\0';
        return res_str;
    }
    // If the sub-string is not found, an empty string is returned
    return (char*) "";
}


////////////////////////////////////////////////////////////
// Delete all the occurences of the given character in the given string
////////////////////////////////////////////////////////////
void delchr(char* str, const char c)
{
    std::size_t index = 0;
    for (int i = -1 ; str[++i] ;)
    {
        if (str[i] != c)
        {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}


////////////////////////////////////////////////////////////
// Return a given string with all the letters as minuscules
////////////////////////////////////////////////////////////
char* lower(const char* str)
{
    std::size_t length = strlen(str);
    char* res_str = new char[length+1];
    strcpy(res_str, str);
    for (int i = -1 ; res_str[++i] ;)
    {
        res_str[i] = tolower(res_str[i]);
    }
    return res_str;
}
void to_lower(char* str)
{
    for (int i = -1 ; str[++i] ;)
    {
        str[i] = tolower(str[i]);
    }
}


////////////////////////////////////////////////////////////
// Return a given string with all the letters as majuscules
////////////////////////////////////////////////////////////
char* upper(const char* str)
{
    std::size_t length = strlen(str);
    char* res_str = new char[length+1];
    strcpy(res_str, str);
    for (int i = -1 ; res_str[++i] ;)
    {
        res_str[i] = toupper(res_str[i]);
    }
    return res_str;
}
void to_upper(char* str)
{
    for (int i = -1 ; str[++i] ;)
    {
        str[i] = toupper(str[i]);
    }
}


} // namespace string
} // namespace polder
