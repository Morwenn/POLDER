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
#ifndef _POLDER_STRING_H
#define _POLDER_STRING_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>


namespace polder
{
namespace string
{

/**
 * @brief Reads a line from a text file
 *
 * @param line Variable where to put the line
 * @param f File where to read the line
 * @return true if it is not the end of file
 */
bool fgetl(char** line, FILE* f);

/**
 * @brief Returns the nth word of the given string
 *
 * @param str Tested string
 * @param searched_word_number Number of the word to search
 * @return nth word or an empty string if not found
 */
char* read_word(const char* str, size_t searched_word_number);

/**
 * @brief Initializes the reading of a string
 *
 * @param str String to read
 * @return First word of the string
 */
char* read_word_first(const char* str);

/**
 * @brief Reads the "next" word in a string
 *
 * You need to initilize the reading of the string with
 * read_word_first(), then to use this function for
 * each word in the string until there is not anything more
 * to read.
 *
 * @param str String to read
 * @return "Next" word in the string
 */
char* read_word_next();

/**
 * @brief Returns a sub-string of the given string
 *
 * @param str Tested string
 * @param index_begin Index of the first character of the sub-string in the string
 * @param index_end Index of the last character of the sub-string in the string
 * @return Substring between the two given indexes
 */
char* substr(const char* str, size_t index_begin, size_t index_end);

/**
 * @brief Delete all the occurences of the given character
 *
 * @param str String to modify
 * @param c character to delete
 */
void delchr(char* str, const char c);

/**
 * @brief Deletes the spaces at the beginning and the end of a string
 *
 * @param str String to modify
 */
void strip(char* str);
void lstrip(char* str);
void rstrip(char* str);
char* stripped(const char* str);
char* lstripped(const char* str);
char* rstripped(const char* str);

/**
 * @brief Reduce all the successive occurences of a character to one
 *
 * @param str String to modify
 * @param c Character to reduce
 */
void reduce_char(char* str, char c);

/**
 * @brief Reduce all the successive occurences of all characters to one
 *
 * @param str String to modify
 */
void reduce_all(char* str);

/**
 * @brief Converts all the lower case letters of a string to upper case
 *
 * @param str Tested string
 * @return Modified string
 */
char* upper(const char* str);
void to_upper(char* str);

/**
 * @brief Converts all the upper case letters of a string to lower case
 *
 * @param str Tested string
 * @return Modified string
 */
char* lower(const char* str);
void to_lower(char* str);


} // namespace string
} // namespace polder


#endif // _POLDER_STRING_H
