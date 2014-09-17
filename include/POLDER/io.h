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
#ifndef POLDER_IO_H_
#define POLDER_IO_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <utility>
#include <POLDER/details/config.h>


namespace polder
{
    ////////////////////////////////////////////////////////////
    // Print function

    /**
     * @brief Print an arbitrary number of arguments to the standard output
     * @param first First argument to be printed
     * @param others Other arguments to be printed
     */
    template<typename... Args>
    auto print(Args&&... args)
        -> void;

    template<typename... Args>
    auto print(std::ostream& stream, Args&&... args)
        -> void;

    #include "details/io.inl"
}

#endif // POLDER_IO_H_
