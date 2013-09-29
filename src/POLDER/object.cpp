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
#include <POLDER/object.h>


namespace polder
{


Object::Object() noexcept:
    ptr(nullptr)
{}

Object::Object(const Object& other) noexcept:
    ptr(other.ptr)
{}

Object& Object::operator=(const Object& other) noexcept
{
    if (&other != this)
    {
        ptr = other.ptr;
    }
    return *this;
}

bool Object::operator==(const Object& other) noexcept
{
    return ptr == other.ptr;
}

bool Object::operator!=(const Object& other) noexcept
{
    return !(*this == other);
}


} // namespace polder
