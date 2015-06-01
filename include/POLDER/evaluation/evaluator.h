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
#ifndef POLDER_EVALUATION_EVALUATOR_H_
#define POLDER_EVALUATION_EVALUATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/evaluation/callback.h>
#include <POLDER/evaluation/error.h>
#include <POLDER/evaluation/functions.h>
#include <POLDER/evaluation/token.h>

namespace polder
{
namespace evaluation
{
    /**
     * @brief Mathematical expressions evaluator.
     *
     * This class can be used as a functor which will evaluate
     * the given string as if it was a mathematical expression
     * and return the result. See the documentation for a full
     * showcase of its abilities.
     */
    template<typename Number>
    class evaluator
    {
        public:

            /**
             * @brief Evaluate a mathematical expression.
             */
            auto evaluate(const std::string& expression) const
                -> Number;

            /**
             * @brief Calls evaluate.
             */
            auto operator()(const std::string& expression) const
                -> Number;

            /**
             * @brief Register a function.
             *
             * Register a function that will be called when the given
             * name is used in the mathematical expression.
             */
            template<typename Func>
            auto connect(const std::string& name, Func&& function)
                -> void;

            /**
             * @brief Unregister a connected function.
             */
            auto disconnect(const std::string& name)
                -> void;

        private:

            auto eval_postfix(std::stack<token<Number>>&& tokens) const
                -> Number;

            std::unordered_map<std::string, callback<Number>> callbacks;
    };

    #include "details/evaluator.inl"
}}

#endif // POLDER_EVALUATION_EVALUATOR_H_
