/*
 * Copyright (C) 2011-2015 Morwenn
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
#ifndef POLDER_EVALUATION_ERROR_H_
#define POLDER_EVALUATION_ERROR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdint>
#include <stdexcept>
#include <string>
#include <POLDER/details/config.h>
#include <POLDER/evaluation/operator.h>

namespace polder
{
namespace evaluation
{
    /**
     * Error codes fed to the exceptions to specify
     * which kind of error has been thrown.
     */
    enum struct error_type:
        std::uint_fast8_t
    {
        unknown_operator,
        unexpected_character,
        unexpected_token,
        not_enough_operands,
        several_dots,
        stray_comma,
        closed_parenthesis,
        mismatched_parenthesis
    };

    /**
     * Exceptions raised when a syntax error is
     * found in the expression to evaluate.
     */
    class POLDER_API error:
        public std::runtime_error
    {
        public:

            /**
             * Constructs a default error message for the exception
             * thanks to its error code.
             */
            explicit error(error_type ecode);

            /**
             * Constructs an exception with an error code and a custom
             * error message.
             */
            error(error_type ecode, const std::string& arg);

            /**
             * Returns the exception's error code.
             */
            auto code() const noexcept
                -> error_type;

        private:

            error_type ecode;   /**< Error code */
    };
}}

#endif // POLDER_EVALUATION_ERROR_H_
