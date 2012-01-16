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
#include <POLDER/reference_counted.h>


namespace polder
{


// Default constructor
ReferenceCounted::ReferenceCounted():
    count(1)
{}

// Copy constructor
ReferenceCounted::ReferenceCounted(const ReferenceCounted&):
    count(1)
{}

// Add a reference to the object
void ReferenceCounted::add_reference()
{
    ++count;
}

// Remove a reference to the object
void ReferenceCounted::remove_reference()
{
    --count;
}

bool ReferenceCounted::is_referenced() const
{
    return count != 0;
}

bool ReferenceCounted::is_shared() const
{
    return count > 1;
}

const void* ReferenceCounted::get_pointer() const
{
    return nullptr;
}

ReferenceCounted::~ReferenceCounted() {}


} // namespace polder
