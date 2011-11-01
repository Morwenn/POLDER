////////////////////////////////////////////////////////////
///
/// POLDER path - POLDER library dealing with paths
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_PATH_H
#define _POLDER_PATH_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <cstdarg>
#include "string.h"


namespace polder
{
namespace path
{

////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////
#ifdef __linux__
    #define OS_SEP ('/')
    #define OS_SEP_STR ("/")
#elif defined _WIN32 || defined _WIN64
    #define OS_SEP ('\\')
    #define OS_SEP_STR ("\\")
#endif


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

// Create a path
char* make_path(const char* base, ...);

// Split a path
char* get_ext(const char* path);
char* get_name(const char* path);
char* get_dir(const char* path);
#if defined _WIN32 || defined _WIN64
    char* get_drive(const char* path);
#endif

// Get some information about a path
bool is_absolute(const char* path);

// Normalize a path
void normalize(char* path);
char* normalized(char* path);


} // namespace path
} // namespace polder


#endif
