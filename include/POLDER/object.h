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
#ifndef _POLDER_OBJECT_H
#define _POLDER_OBJECT_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <typeinfo>
#include "wrapper.h"
#include "reference_counted.h"


namespace polder
{


/*
    Object is a generic object that can represent any
    object of the POLDER/geo module. It is useful when some
    methods (intersections for example...) can return different objects.
    Then the "assign" method can be used to check the returned object.
*/
class Object
{
    public:

        ////////////////////////////////////////////////////////////
        /// Constructors
        ///
        ////////////////////////////////////////////////////////////

        // Default constructor
        Object();

        // Copy constructor
        Object(const Object& other);


        // "Encapsulation" constructor
        template<class T>
        explicit Object(const T& other):
            ptr(new Wrapper<T>(other))
        {}

        // Destructor
        ~Object();


        ////////////////////////////////////////////////////////////
        /// Operators
        ///
        ////////////////////////////////////////////////////////////

        // Assignement
        Object& operator=(const Object& other);

        // Equality
        bool operator==(const Object& other);

        // Inequality
        bool operator!=(const Object& other);


        ////////////////////////////////////////////////////////////
        /// Miscellaneous functions
        ///
        ////////////////////////////////////////////////////////////

        // Assign function
        template<class T>
        bool assign(T& other) const
        {
            const Wrapper<T>* tmp = dynamic_cast<Wrapper<T>*>(ptr);
            if (tmp == nullptr)
            {
                return false;
            }
            other = tmp->get();
            return true;
        }


    private:

        // Pointer to a wrapper
        ReferenceCounted* ptr;
};


// Outside-class assign function
template<class T>
bool assign(T& sometype, const Object& object)
{
    return object.assign(sometype);
}


} // namespace polder


#endif // _POLDER_OBJECT_H
