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
#include "limits.h"


namespace polder
{
namespace geometry
{


// Get the margin error
double margin_error()
{
    return geo_margin_error;
}

// Set the margin error
void set_margin_error(double error)
{
    geo_margin_error = error;
}

// Reset the margin error
void reset_margin_error()
{
    geo_margin_error = std::numeric_limits<double>::epsilon() * 10;
}

// Compare two doubles taking in account the marging error
bool round_equal(double a, double b)
{
    return fabs(a-b) < geo_margin_error * a;
}


} // namespace geo
} // namespace polder
