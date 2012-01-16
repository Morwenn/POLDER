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
// Headers
////////////////////////////////////////////////////////////
#include <cstdlib>


namespace polder
{


/**
 * @brief Class whose references to can be counted
 */
class ReferenceCounted
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        ReferenceCounted();

        /**
         * Copy constructor
         */
        ReferenceCounted(const ReferenceCounted&);

        /**
         * Destructor
         */
        virtual ~ReferenceCounted();


        ////////////////////////////////////////////////////////////
        // Setters
        ////////////////////////////////////////////////////////////

        /**
         * @brief Adds a reference to the object
         */
        void add_reference();

        /**
         * @brief Removes a reference to the object
         */
        void remove_reference();


        ////////////////////////////////////////////////////////////
        // Getters
        ////////////////////////////////////////////////////////////

        /**
         * @brief Returns whether the object is pointed
         * @return true if there is at least one reference to the object
         */
        bool is_referenced() const;

        /**
         * @brief Returns whether the object is pointed more than once
         * @return true if there are a least two references to the object
         */
        bool is_shared() const;

        /**
         * @brief Provides a pointer to the object
         * @return Pointer to the pointed object
         */
        virtual const void* get_pointer() const;


    protected:

        // Member data
        size_t count;   /**< Number of references to the objects */
};


} // namespace polder


#endif // _POLDER_REFERENCE_COUNTED_H
