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

////////////////////////////////////////////////////////////
/// Read a line from a text file
///
/// \param line: Variable where to put the line
/// \param f: File where to read the line
///
////////////////////////////////////////////////////////////
bool fgetl(char** line, FILE* f);

////////////////////////////////////////////////////////////
/// Returns the nth word of the given string
/// Returns an empty string if there is not N words in the string
///
/// \param str: Tested string
/// \param N: Number of the word to search
///
////////////////////////////////////////////////////////////
char* read_word(const char* str, size_t N);

////////////////////////////////////////////////////////////
/// Initializes the reading of a string
///
/// \param str: String to read
///
////////////////////////////////////////////////////////////
char* read_word_first(const char* str);

////////////////////////////////////////////////////////////
/// Returns the "next" word in a string
///
/// \param str: String to read
///
////////////////////////////////////////////////////////////
char* read_word_next();

////////////////////////////////////////////////////////////
/// Returns a sub-string of the given string
///
/// \param str: Tested string
/// \param index_begin: Index of the first character of the sub-string in the string
/// \param index_end: Index of the last character of the sub-string in the string
///
////////////////////////////////////////////////////////////
char* substr(const char* str, size_t index_begin, size_t index_end);

////////////////////////////////////////////////////////////
/// Delete all the occurences of the given character in the given string
///
/// \param str: String to modify
/// \param c: character to delete
///
////////////////////////////////////////////////////////////
void delchr(char* str, const char c);

////////////////////////////////////////////////////////////
/// Deletes the spaces at the beginning and the end of a string
///
/// \param str: String to modify
///
////////////////////////////////////////////////////////////
void strip(char* str);
void lstrip(char* str);
void rstrip(char* str);
char* stripped(const char* str);
char* lstripped(const char* str);
char* rstripped(const char* str);

////////////////////////////////////////////////////////////
/// If the given character has more than one successive occurence, successive occurences are deleted until one remain
///
/// \param str: String to modify
/// \param c: Character to test
///
////////////////////////////////////////////////////////////
void reduce_char(char* str, char c);

////////////////////////////////////////////////////////////
/// Reduce all the successive occurences of a character to one
///
/// \param str: String to modify
/// \param c: Character to test
///
////////////////////////////////////////////////////////////
void reduce_all(char* str);

////////////////////////////////////////////////////////////
/// Return a given string with all the letters as majuscules
///
/// \param str: Tested string
///
////////////////////////////////////////////////////////////
char* upper(const char* str);
void touppercase(char* str);

////////////////////////////////////////////////////////////
/// Return a given string with all the letters as minuscules
///
/// \param str: Tested string
///
////////////////////////////////////////////////////////////
char* lower(const char* str);
void tolowercase(char* str);


} // namespace string
} // namespace polder


#endif
