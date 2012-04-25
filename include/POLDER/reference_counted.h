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
#include <POLDER/config.h>


namespace polder
{


/**
 * @brief Class whose references to can be counted
 */
class POLDER_API ReferenceCounted
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        ReferenceCounted() noexcept;

        /**
         * Copy constructor
         */
        ReferenceCounted(const ReferenceCounted&) noexcept;

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
        void add_reference() noexcept;

        /**
         * @brief Removes a reference to the object
         */
        void remove_reference() noexcept;


        ////////////////////////////////////////////////////////////
        // Getters
        ////////////////////////////////////////////////////////////

        /**
         * @brief Returns whether the object is pointed
         * @return true if there is at least one reference to the object
         */
        bool is_referenced() const noexcept;

        /**
         * @brief Returns whether the object is pointed more than once
         * @return true if there are a least two references to the object
         */
        bool is_shared() const noexcept;

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
