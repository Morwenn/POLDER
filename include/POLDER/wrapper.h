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
#ifndef _POLDER_WRAPPER_H
#define _POLDER_WRAPPER_H


namespace polder
{


/**
 * @brief Wrapper base class
 *
 * Dummy class, just so that Wrapper has a base
 * class accessible without the template arguments.
 * This class also has to enable polymorphism.
 */
struct WrapperBase
{
    /**
     * @brief Destructor
     *
     * The only purpose of this destructor is to make
     * the class polymorphic.
     */
    virtual ~WrapperBase()
        = default;
};


/**
 * @brief Generic wrapper for any object
 *
 * Allows to avoid using void* in many objects;
 * Moreover, the references to Wrapper may be counted.
 */
template<typename T>
class Wrapper:
    public WrapperBase
{
    public:

        /**
         * @brief Initilization constructor
         * @param other Object to wrap
         */
        Wrapper(const T& other) noexcept:
            _object(other)
        {}

        /**
         * @brief Object accessor
         * @return Reference to the enclosed object
         */
        auto get() const
            -> const T&
        {
            return _object;
        }

        /**
         * @brief Object accessor
         * @return Pointer to the enclosed object
         */
        auto get_pointer() const
            -> const T*
        {
            return &_object;
        }

        /**
         * @brief Destructor
         */
        ~Wrapper()
            = default;

    private:

        T _object;  /**< Wrapped object */
};


} // namespace polder


#endif // _POLDER_WRAPPER_H
