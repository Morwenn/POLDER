////////////////////////////////////////////////////////////
///
/// POLDER ptype - POLDER library meant to recognize "types"
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_PTYPE_H
#define _POLDER_PTYPE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cctype>
#include <cstring>


namespace polder
{
namespace ptype
{


bool is_bool(const char* str);
bool is_uint(const char* str);
bool is_int(const char* str);
bool is_ufloat(const char* str);
bool is_float(const char* str);
bool is_unumber(const char* str);
bool is_number(const char* str);


} // namespace ptype
} // namespace polder


#endif
