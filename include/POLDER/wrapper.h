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
#ifndef _POLDER_WRAPPER_H
#define _POLDER_WRAPPER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "reference_counted.h"


namespace polder
{


template<class T>
class Wrapper:
    public ReferenceCounted
{
    // We explicitly delete the default functions
    // to ensure there will not be useless copies
    Wrapper(const Wrapper&) = delete;
    Wrapper& operator=(const Wrapper&) = delete;

    public:

        Wrapper(const T& other):
            _object(other)
        {}

        // Return the object
        const T& get() const
        {
            return _object;
        }

        // Return a pointer to the object
        virtual const void* get_pointer() const
        {
            return &_object;
        }

    private:

        T _object;
};


} // namespace polder


#endif // _POLDER_WRAPPER_H
