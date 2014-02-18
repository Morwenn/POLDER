/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef _POLDER_OBJECT_H
#define _POLDER_OBJECT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <POLDER/details/config.h>
#include <POLDER/details/wrapper.h>

namespace polder
{
    /**
     * @brief Generic object
     *
     * Object is a generic object that can represent any
     * object of the POLDER/geo module. It is useful when some
     * methods (intersections for example...) can return different objects.
     * Then the "assign" method can be used to check the returned object.
    */
    class POLDER_API Object
    {
        public:

            ////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////

            /**
             * Default constructor
             */
            Object() noexcept;

            /**
             * Copy constructor
             */
            Object(const Object& other) noexcept;

            /**
             * @brief "Encapsulation" constructor
             *
             * The object taken as parameter must be considered
             * as encapsulated by the current Object. And then,
             * this current Object can assign the encapsulated
             * stuff to another variable.
             *
             * @param other Object to encapsulate
             */
            template<typename T>
            explicit Object(const T& other) noexcept:
                ptr(new Wrapper<T>(other))
            {}

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            /**
             * Assignment operator
             */
            Object& operator=(const Object& other) noexcept;

            /**
             * @brief Check whether the encapsulated objects are the same
             *
             * @param other Another Object
             * @return True if the encapsulated objects are the same
             */
            bool operator==(const Object& other) noexcept;

            /**
             * @brief Check whether the encapsulated objects are not the same
             *
             * @param other Another Object
             * @return True if the encapsulated objects are not the same
             */
            bool operator!=(const Object& other) noexcept;

            ////////////////////////////////////////////////////////////
            // Miscellaneous functions
            ////////////////////////////////////////////////////////////

            /**
             * @brief Assign the encapsulated variable to another variable
             *
             * Main purpose of the Object class: we can perform some
             * downcast to the encapsulated stuff. In POLDER library
             * for example, it is useful for the intersection functions
             * of the geometry module: we can return whatever in an
             * Object and "chack" its type after.
             *
             * @param other Variable to which we want to assign the encapsulated stuff
             * @return True if the encapsulated stuff has been assigned successfully
             */
            template<typename T>
            bool assign(T& other) const noexcept
            {
                const Wrapper<T>* tmp = dynamic_cast<Wrapper<T>*>(ptr.get());
                if (tmp == nullptr)
                {
                    return false;
                }
                other = tmp->get();
                return true;
            }

        private:

            // Member data
            std::shared_ptr<WrapperBase> ptr;
    };

    /**
     * @brief Assign an Object to a variable
     * @see bool Object::assign(T& other) const
     */
    template<class T>
    bool assign(T& sometype, const Object& object) noexcept
    {
        return object.assign(sometype);
    }
}

#endif // _POLDER_OBJECT_H
