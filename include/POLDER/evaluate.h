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
#ifndef _POLDER_EVALUATION_H
#define _POLDER_EVALUATION_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cctype>
#include <cmath>
#include <cstring>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "math.h"
#include "ptype.h"
#include "string.h"


namespace polder
{

////////////////////////////////////////////////////////////
/// Errors/Exceptions handling
////////////////////////////////////////////////////////////

// Error types (internal, not to be used)
enum class _eval_error
{
    UNKNOWN_OPERATOR,
    UNEXPECTED_CHARACTER,
    EXPECTED_CHARACTER,
    LAST_CHARACTER,
    INVALID_NUMBER
};

// An evaluation_error exception is raised (or should be) whenever
// there is a syntax error in the expression to evaluate
class evaluation_error:
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
        std::string msg;
};


////////////////////////////////////////////////////////////
/// Functions
////////////////////////////////////////////////////////////

// Evaluation function
double evaluate(const char* expr);


} // namespace polder


#endif // _POLDER_EVALUATE_H
