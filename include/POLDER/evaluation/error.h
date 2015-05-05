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
#include <exception>
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
    enum struct error_code:
        std::uint_fast8_t
    {
        unknown_operator,
        unexpected_character,
        not_enough_operands
    };

    /**
     * Exceptions raised when a syntax error is
     * found in the expression to evaluate.
     */
    class POLDER_API error:
        public std::exception
    {
        public:

            explicit error();
            explicit error(const std::string& arg);
            error(error_code err, char c);
            error(error_code err, infix_t oper);
            error(error_code err, prefix_t oper);
            error(error_code err, postfix_t oper);
            error(error_code err, const std::string& arg);

            virtual ~error() override;

            virtual auto what() const noexcept
                -> const char*
                override;

        private:

            std::string msg; /**< Error message */
    };
}}

#endif // POLDER_EVALUATION_ERROR_H_
