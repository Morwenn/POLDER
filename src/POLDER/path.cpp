/*
 * Copyright (C) 2011-2013 Morwenn
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
#include <cstring>
#include <POLDER/path.h>
#include <POLDER/string.h>


namespace polder
{
namespace path
{

////////////////////////////////////////////////////////////
// Create a path
////////////////////////////////////////////////////////////

// Create a path
std::string make_path(const std::string& base)
{
    return base + OS_SEP_STR;
}


////////////////////////////////////////////////////////////
// Split a path
////////////////////////////////////////////////////////////

// Get the extension of a file
char* get_ext(const char* path)
{
    std::size_t length = strlen(path);
    for (int i = length - 1 ; i >= 0 ; --i)
    {
        if (path[i] == '.')
        {
            return string::substr(path, i, length-1);
        }
    }
    return (char*) "";
}

// Get the name of a file without its extension
char* get_name(const char* path)
{
    for (int i = strlen(path) - 1 ; i >= 0 ; --i)
    {
        if (path[i] == '.')
        {
            return string::substr(path, 0, i-1);
        }
    }
    return (char*) "";
}

// Get the last directory of a path
char* get_dir(const char* path)
{
    for (int i = strlen(path) - 1 ; i >= 0 ; --i)
    {
        if (path[i] == OS_SEP)
        {
            return string::substr(path, 0, i);
        }
    }
    return (char*) "";
}

#if defined _WIN32 || defined _WIN64
    char* get_drive(const char* path)
    {
        if (isupper(path[0]) && path[1] == ':' && path[2] == '\\')
        {
            char* res = new char[4];
            strcpy(res, "A:\\");
            res[0] = path[0];
            return res;
        }
        return (char*) "";
    }
#endif


////////////////////////////////////////////////////////////
// Get some information about a path
////////////////////////////////////////////////////////////

// Returns true if the path is absolute
bool is_absolute(const char* path)
{
    #ifdef __linux___
        if (strlen(path) < 1)
        {
            return false;
        }
        return path[0] == '/';
    #elif defined _WIN32 || defined _WIN64
        if (strlen(path) < 3)
        {
            return false;
        }
        return (isupper(path[0]) && path[1] == ':' && path[2] == '\\');
    #endif
}


////////////////////////////////////////////////////////////
// Normalize a path
////////////////////////////////////////////////////////////
void normalize(char* path)
{
    int length = strlen(path);
    for (int i = -1 ; path[++i+2] ;)
    {
        while (path[i] == OS_SEP)
        {
            // If a directory is '.'
            if (path[i+1] == '.' && path[i+2] == OS_SEP)
            {
                memcpy((char*) path + i + 1, (char*) path + i + 3, length-i);
                length -= 2;
            }
            // If a directory is '..'
            else if (path[i+1] == '.' && path[i+2] == '.' && path[i+3] == OS_SEP)
            {
                // Find previous directory
                int index_begin = i;
                while (path[--index_begin] != OS_SEP && index_begin >= 0);

                // There may be a previous directory
                if (path[index_begin] != OS_SEP) break;

                memcpy((char*) path + index_begin + 1, (char*) path + i + 4, length);
                int offset = i - index_begin;
                length -= offset;
                i -= offset;
            }
            else break;
        }
    }
    path[length+1] = '\0';
}

char* normalized(const char* path)
{
    char* new_path = new char[strlen(path) + 1];
    strcpy(new_path, path);
    int length = strlen(path);
    for (int i = -1 ; new_path[++i+2] ;)
    {
        while (new_path[i] == OS_SEP)
        {
            // If a directory is '.'
            if (new_path[i+1] == '.' && new_path[i+2] == OS_SEP)
            {
                memcpy((char*) new_path + i + 1, (char*) new_path + i + 3, length-i);
                length -= 2;
            }
            // If a directory is '..'
            else if (new_path[i+1] == '.' && new_path[i+2] == '.' && new_path[i+3] == OS_SEP)
            {
                // Find previous directory
                int index_begin = i;
                while (new_path[--index_begin] != OS_SEP && index_begin >= 0);

                // There should be a previous directory
                if (new_path[index_begin] != OS_SEP) break;

                memcpy((char*) new_path + index_begin + 1, (char*) new_path + i + 4, length);
                int offset = i - index_begin;
                length -= offset;
                i -= offset;
            }
            else break;
        }
    }
    new_path[length+1] = '\0';
    return new_path;
}


} // namespace path
} // namespace polder
