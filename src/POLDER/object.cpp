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
#include <POLDER/object.h>


namespace polder
{


/*
 * Default constructor
 */
Object::Object() noexcept:
    ptr(nullptr)
{}


/*
 * "Copy" constructor
 */
Object::Object(const Object& other) noexcept:
    ptr(other.ptr)
{
    if (ptr != nullptr)
    {
        ptr->add_reference();
    }
}


/*
 * Destructor
 */
Object::~Object()
{
    if (ptr != nullptr && ptr->is_referenced())
    {
        ptr->remove_reference();
        if (!ptr->is_referenced())
        {
            delete ptr;
        }
    }
}


/*
 * Operators
 */

// Assignement
Object& Object::operator=(const Object& other) noexcept
{
    if (ptr != nullptr && ptr->is_referenced())
    {
        ptr->remove_reference();
        if (!ptr->is_referenced())
        {
            delete ptr;
        }
    }
    ptr = other.ptr;
    if (other.ptr != nullptr)
    {
        ptr->add_reference();
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
