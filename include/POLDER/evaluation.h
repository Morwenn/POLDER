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

/**
 * @file POLDER/math.h
 * @brief This header includes the whole evaluation module.
 */

#ifndef POLDER_EVALUATION_H_
#define POLDER_EVALUATION_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/evaluation/callback.h>
#include <POLDER/evaluation/error.h>
#include <POLDER/evaluation/evaluator.h>
#include <POLDER/evaluation/functions.h>
#include <POLDER/evaluation/operation.h>
#include <POLDER/evaluation/operator.h>
#include <POLDER/evaluation/token.h>

////////////////////////////////////////////////////////////
// Documentation
////////////////////////////////////////////////////////////

/**
 * @namespace polder::evaluation
 * @brief Evaluator and related functions.
 *
 * This namespace regroups a the features related to the
 * evaluation of mathematical expressions, such as operator
 * precedence parsing and utility classes. Eventually, the
 * class evaluator is imported in the polder:: namespace
 * since every other feature of the module is meant to
 * implement that one.
 */

////////////////////////////////////////////////////////////
// Main module class
////////////////////////////////////////////////////////////

namespace polder
{
    template<typename Number>
    using evaluator = evaluation::evaluator<Number>;
}

#endif // POLDER_EVALUATION_H_
