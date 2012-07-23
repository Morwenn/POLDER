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
#ifndef _POLDER_EVALUATE_H
#define _POLDER_EVALUATE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <exception>
#include <string>
#include <POLDER/config.h>


namespace polder
{


////////////////////////////////////////////////////////////
// Errors/Exceptions handling
////////////////////////////////////////////////////////////

/**
 * Error types (internal, not to be used)
 */
enum struct _eval_error
{
    UNKNOWN_OPERATOR,       /**< An unknown string has been considered as an operator. */
    UNEXPECTED_CHARACTER,   /**< Character not to be used in a mathematical/logical expression. */
    EXPECTED_CHARACTER,     /**< Some open parenthesis has not been closed. */
    LAST_CHARACTER,         /**< The last character can not be the one found. */
    INVALID_NUMBER          /**< The given operand is not a number (syntax error, etc...). */
};


/**
 * Exceptions raised when a syntax error is found in the expression to evaluate.
 */
class POLDER_API evaluation_error:
    public std::exception
{
    public:
        explicit evaluation_error();
        explicit evaluation_error(const std::string& arg);
        explicit evaluation_error(_eval_error e, char c);
        explicit evaluation_error(_eval_error e, const std::string& arg);
        virtual ~evaluation_error() throw();
        virtual const char* what() const throw();

    private:
        std::string msg; /**< Error message */
};


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

/**
 * @brief Evaluates a mathematical/logical expression
 *
 * For further explanations, I recommended you to go see
 * the POLDER/evaluate.h article on Morwenn wiki.
 *
 * @param expr Expression to evaluate
 * @return Resultat of the expression
 */
POLDER_API double evaluate(const char* expr);


} // namespace polder


#endif // _POLDER_EVALUATE_H
