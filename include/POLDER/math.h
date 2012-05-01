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

/**
 * @file POLDER/math.h
 * @brief This header includes the whole mathematics module.
 */

#ifndef _POLDER_MATH_H
#define _POLDER_MATH_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/math/constants.h>
#include <POLDER/math/formula.h>
#include <POLDER/math/factorial.h>


////////////////////////////////////////////////////////////
// Documentation
////////////////////////////////////////////////////////////
/**
 * @namespace polder::math
 * @brief Mathematical functions and constants
 *
 * Under this namespace are grouped several mathematical
 * constants and functions usable for different purpose.
 * It is often used as a low-level library for other
 * headers of POLDER library.
 */

/**
 * @namespace polder::math::standard
 * @brief Default versions of mathematical functions
 *
 * Functions that have numerous versions have their most
 * intuitive implementation under this namespace.
 */

/**
 * @namespace polder::math::meta
 * @brief Functions evaluated at compile time
 *
 * Some simple functions can be evaluated at compile time
 * in some cases. However, at runtime, they are not as fast
 * as the standard ones. That's why we separate the
 * versions.
 */

/**
 * @namespace polder::math::memoized
 * @brief Functions with memoized results
 *
 * Sometimes, we can use some more memory to gain some speed.
 * Memoized functions store their results in memory and them
 * after instead of computing them again. It can be useful
 * when we have to compute many times the same results.
 */


#endif // _POLDER_MATH_H
