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
#ifndef POLDER_EVALUATE_H_
#define POLDER_EVALUATE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <string>
#include <POLDER/details/config.h>

namespace polder
{
    ////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////

    /**
     * @brief Evaluates a mathematical/logical expression
     *
     * @param expr Expression to evaluate
     * @return Result of the expression
     */
    POLDER_API
    auto evaluate(const std::string& expr)
        -> double;

    ////////////////////////////////////////////////////////////
    // Errors/Exceptions handling
    ////////////////////////////////////////////////////////////

    // Evaluation error codes
    enum struct eval_error_code;

    /**
     * Exceptions raised when a syntax error is
     * found in the expression to evaluate.
     */
    class POLDER_API evaluation_error:
        public std::exception
    {
        public:
            explicit evaluation_error();
            explicit evaluation_error(const std::string& arg);
            explicit evaluation_error(eval_error_code e, char c);
            explicit evaluation_error(eval_error_code e, const std::string& arg);
            virtual ~evaluation_error() noexcept override;
            virtual auto what() const noexcept
                -> const char*
                override;

        private:
            std::string msg; /**< Error message */
    };
}

#endif // POLDER_EVALUATE_H_
