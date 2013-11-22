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
#ifndef _POLDER_CONTRACT_H
#define _POLDER_CONTRACT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdexcept>
#include <type_traits>
#include <POLDER/config.h>


namespace polder
{
    /**
     * @brief Contract class
     *
     * A helper class to provide some generic way to implement
     * preconditions and postconditions in member functions in
     * classes.
     *
     * Any user can provide a contract class for a given class.
     * In debug mode, the contract class will use the contract
     * functions. If NDEBUG is on, the contract class will
     * behave like the normal class.
     *
     * One of the main purposes is to separate the contract from
     * the class main body in order not to pollute it.
     */
    template<typename T>
    struct make_contract;

    template<typename T>
    struct contract:
        std::conditional<
            POLDER_DEBUG,
            make_contract<T>,
            T
        >::type
    {
        template<typename... Args>
        contract(Args&&... args):
            std::conditional<
                POLDER_DEBUG,
                make_contract<T>,
                T
            >::type(std::forward<Args>(args)...)
        {}
    };

    /**
     * @def POLDER_CONTRACT(type)
     *
     * Macro to avoid boilerplate while writing
     * the preconditions and postconditions.
     */
    #define POLDER_CONTRACT(type) \
        template<> \
        struct make_contract<type>: \
            type

    #if POLDER_DEBUG == 1

        /**
         * @def POLDER_INVARIANTS(invariants)
         *
         * Macro encapsulating all the boilerplate used
         * to check invariants thanks to RAII with a
         * check structure.
         *
         * @warning Crash if a parent class hass a member called check
         */
        #define POLDER_INVARIANTS(invariants) \
            struct check \
            { \
                check() { _check(); } \
                ~check() { _check(); } \
                void _check() \
                { \
                    invariants \
                } \
            }

    #else

        #define POLDER_INVARIANTS(...) \
            struct check \
            { \
                check() { void(); } \
            }

    #endif

    /**
     * @brief Contract failure exception
     *
     * Explicit way to tell that a contract failed. This kind of
     * failure is a logic error.
     */
    struct contract_error:
        std::logic_error
    {
        /**
         * @brief Constructor
         *
         * This constructor simply forwards its argument to
         * the constructor of std::logic_error.
         *
         * @todo Could benefit from inheriting constructors (C++11)
         * @todo Could benefit from string alias (C++??)
         */
        template<typename... Args>
        contract_error(Args&&... arg):
            std::logic_error(std::forward<Args>(arg)...)
        {}
    };
}


#endif // _POLDER_CONTRACT_H
