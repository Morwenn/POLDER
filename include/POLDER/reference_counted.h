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
#ifndef _POLDER_REFERENCE_COUNTED_H
#define _POLDER_REFERENCE_COUNTED_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cstdlib>


namespace polder
{


class ReferenceCounted
{
    public:

        ////////////////////////////////////////////////////////////
        /// Constructors
        ////////////////////////////////////////////////////////////

        // Default constructor
        ReferenceCounted();

        // Copy constructor
        ReferenceCounted(const ReferenceCounted&);

        // Destructor
        virtual ~ReferenceCounted();


        ////////////////////////////////////////////////////////////
        /// Setters
        ////////////////////////////////////////////////////////////

        // Adds a reference to the object
        void add_reference();

        // Removes a reference to the object
        void remove_reference();


        ////////////////////////////////////////////////////////////
        /// Getters
        ////////////////////////////////////////////////////////////

        // Returns whether the object is pointed
        bool is_referenced() const;

        // Returns whether the object is pointed more than once
        bool is_shared() const;

        // Returns a pointer to the object
        virtual const void* get_pointer() const;


    protected:

        // Number of references to the objects
        size_t count;
};


} // namespace polder


#endif // _POLDER_REFERENCE_COUNTED_H
