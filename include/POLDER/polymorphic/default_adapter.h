/*
 * Copyright (C) 2015 Morwenn
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
#ifndef POLDER_POLYMORPHIC_DEFAULT_ADAPTER_H_
#define POLDER_POLYMORPHIC_DEFAULT_ADAPTER_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <POLDER/details/config.h>

namespace polder
{
namespace polymorphic
{
    /**
     * @brief Default adapter for polymorphic collections.
     *
     * While polymorphic collections have been design to implement
     * concept-based polymorphism, this adapter still allows them
     * to store regular polymorphic classes without having to
     * redefine every virtual method in the adapter.
     */
    template<typename Base>
    struct default_adapter:
        Base
    {
        // Forward everything to the base class constructors
        template<typename... Args>
        default_adapter(Args&&... args):
            Base(std::forward<Args>(args)...)
        {}
    };
}}

#endif // POLDER_POLYMORPHIC_DEFAULT_ADAPTER_H_
