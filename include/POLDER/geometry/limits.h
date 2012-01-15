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
#ifndef _POLDER_GEOMETRY_LIMITS_H
#define _POLDER_GEOMETRY_LIMITS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <limits>


namespace polder
{
namespace geometry
{


////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////

/**
 * Margin error for comparison
 */
static double geo_margin_error = std::numeric_limits<double>::epsilon() * 10;


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

/**
 * @brief Gets the margin error used in geometric equality
 * @return Margin error
 */
double margin_error();

/**
 * @brief Sets the margin error
 * @param error New margin error
 */
void set_margin_error(double error);

/**
 * @brief Resets the margin error
 */
void reset_margin_error();

/**
 * @brief Compares two doubles taking in account the margin error
 * @param a First double to compare
 * @param b Second double to compare
 */
bool round_equal(double a, double b);

/**
 * @brief Compares two sets of data taking in account the margin error
 *
 * @param first Iterator on the first element of the first set of data to compare
 * @param last Iterator on the last element of the first set of data to compare
 * @param first2 Iterator on the first element of the second set of data to compare
*/
template<typename InputIterator>
bool round_equal(InputIterator first, InputIterator last, InputIterator first2)
{
    auto j = first2;
    for (auto i = first ; i != last ; ++i, ++j)
    {
        if (fabs(*i-*j) > geo_margin_error * *i)
        {
            return false;
        }
    }
    return true;
}


} // namespace geo
} // namespace polder


#endif // _POLDER_GEOMETRY_LIMITS_H
