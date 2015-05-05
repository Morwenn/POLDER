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
#ifndef POLDER_EVALUATION_CALLBACK_H_
#define POLDER_EVALUATION_CALLBACK_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <functional>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/type_traits.h>

namespace polder
{
namespace evaluation
{
    /**
     * @brief Evaluation callback function.
     *
     * This class abstracts away a function that takes a given
     * number of parameters of a same type and returns a result
     * of this type.
     *
     * It is especially designed so that the number of parameters
     * of the function is kept, but is not part of the type. A
     * callback can be called with a pointer to an array of the
     * templated type and will manage to call the original function
     * with that array.
     */
    template<typename Number>
    class callback
    {
        public:

            /**
             * Convert the given function to a callback.
             */
            template<typename Func>
            callback(Func&& function);

            /**
             * Call the original function with an array of Number
             * where the elements of the array correspond to the
             * parameters to feed to the original function.
             */
            auto operator()(Number* args) const
                -> Number;

            const std::size_t arity; /**< Number of parameters that the function takes */

        private:

            template<typename Func, std::size_t... Ind>
            callback(Func&& function, std::index_sequence<Ind...>);

            std::function<Number(Number*)> _func;
    };

    #include "details/callback.inl"
}}

#endif // POLDER_EVALUATION_CALLBACK_H_
