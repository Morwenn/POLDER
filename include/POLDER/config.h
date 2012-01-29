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
#ifndef _POLDER_CONFIG_H
#define _POLDER_CONFIG_H


/*
 * Current POLDER version
 */
#define POLDER_VERSION_MAJOR 1
#define POLDER_VERSION_MINOR 0


/*
 * Operating system
 */
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


/*
 * DLL import/export handling
 */
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
    #define POLDER_API __declspec(dllexport)

#endif



/*
 * Some global documentation
 * Mainly here because the documented namespaces
 * appear in several places ine the code
 */

/**
 * @namespace polder
 * @brief Global namespace for POLDER library
 *
 * All the functions, variables and classes defined
 * in POLDER library are placed under the polder
 * namespace.
 */

/**
 * @namespace polder::geometry
 * @brief Geometry-related objects and functions
 *
 * This namespace contains many objects and functions
 * that allow to perform geometry in N-dimensional spaces.
 * For exemple, points, vectors, lines... representations
 * and useful functions such as distances and intersections.
 */


#endif // _POLDER_CONFIG_H
