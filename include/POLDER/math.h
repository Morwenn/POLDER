/*
 * Copyright (C) 2011-2013 Morwenn
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
#include <POLDER/math/norm.h>


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


#endif // _POLDER_MATH_H
