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
#ifndef _POLDER_SINGLETON_H
#define _POLDER_SINGLETON_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>
#include <typeinfo>


namespace polder
{


/**
 * @brief Unique object class
 *
 * Any class derived from Singleton and passed as its
 * T parameter will cause the program to crash if
 * multiple instances are meant to exist at the same
 * time.
 */
template<class T>
class Singleton
{
    protected:

        /**
         * Default constructor
         */
        Singleton()
        {
            if (already_exists)
            {
                throw std::logic_error("You can't declare multiple instances of a " + std::string(typeid(T).name()) + " object.");
            }
            already_exists = true;
        }

    public:

        /*
         * Prevent the object from being copied
         */
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        /**
         * Destructor
         */
        ~Singleton()
        {
            already_exists = false;
        }

    private:

        static bool already_exists; /**< True if an instance of T already exists */
};
template<class T> bool Singleton<T>::already_exists = false;


} // namespace polder


#endif // _POLDER_SINGLETON_H

