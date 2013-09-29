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
#ifndef _POLDER_MATH_NORM_H
#define _POLDER_MATH_NORM_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/config.h>


namespace polder
{
namespace math
{


/**
 * @brief Mathematical norms
 *
 * Those norms can be used by Vector or Matrix.
 */
enum class Norm
{
    Manhattan,  /**< Manhattan, Taxicab norm (norm 1) */
    Euclidean,  /**< Euclidean norm (norm 2) */
    Maximum,    /**< Maximum norm (norm infinite) */
    P           /**< P norm */
};


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_NORM_H
