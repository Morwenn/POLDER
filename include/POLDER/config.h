/*
 * Copyright (C) 2011-2012 Morwenn
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

/**
 * @file POLDER/config.h
 * @brief This header defines some general macros.
 *
 * The defined macros include version information,
 * running operating system, dll export and import
 * macros and some basic debug tools.
 *
 */

#ifndef _POLDER_CONFIG_H
#define _POLDER_CONFIG_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdexcept>


////////////////////////////////////////////////////////////
// Current POLDER version
////////////////////////////////////////////////////////////
#define POLDER_VERSION_MAJOR 1
#define POLDER_VERSION_MINOR 0


////////////////////////////////////////////////////////////
// Operating system
////////////////////////////////////////////////////////////
#if defined _WIN32 || defined _WIN64 || defined __WIN32__ || defined __WINDOWS__

    // Windows
    #define POLDER_OS_WINDOWS

#elif defined __linux__

    // Linux
    #define POLDER_OS_LINUX

#elif defined __APPLE__

    // Mac OS X
    #define POLDER_OS_MACOSX

#elif defined __FreeBSD__

    // FreeBSD
    #define POLDER_OS_FREEBSD

#else

    // Other systems
    #error The current operating system is not supported by POLDER library

#endif


////////////////////////////////////////////////////////////
// DLL import/export handling
////////////////////////////////////////////////////////////
#ifdef POLDER_DYNAMIC

    // DLL support with Windows
    #ifdef POLDER_OS_WINDOWS

        #ifdef POLDER_EXPORTS

            // DLL side
            #define POLDER_API __declspec(dllexport)

        #else

            // Clients side
            #define POLDER_API __declspec(dllimport)

        #endif

    #else // Linux, Mac OS X, BSD...

        // Nothing to do
        #define POLDER_API

    #endif

#else

    // We do not care about the DLL stuff
    #define POLDER_API

#endif


////////////////////////////////////////////////////////////
// Debug tools
////////////////////////////////////////////////////////////

#ifndef NDEBUG

    // Define a portable debug macro
    #define POLDER_DEBUG

#endif

#ifdef POLDER_DEBUG

    /**
     * @brief Improved assert function
     *
     * This function is meant to replace the old assert function.
     * Instead of only stopping the program, it also contains an
     * error message.
     * Moreover, it throws an exception instead of just stopping
     * the program.
     *
     * The functions does not work outside of the debug mode.
     *
     * @param assertion If false, the program will crash
     * @param error_message Message to show when the program crashes
     */
    inline void polder_assert(bool assertion, const char* error_message="")
    {
        if (!assertion)
        {
            throw std::logic_error(error_message);
        }
    }

    #define POLDER_ASSERT(assertion, error_message) polder_assert(assertion, error_message)

#else

    #define POLDER_ASSERT(assertion, error_message)

#endif


////////////////////////////////////////////////////////////
// Some global documentation
////////////////////////////////////////////////////////////

/**
 * @namespace polder
 * @brief Global namespace for POLDER library
 *
 * All the functions, variables and classes defined
 * in POLDER library are placed under the polder
 * namespace.
 */


#endif // _POLDER_CONFIG_H
