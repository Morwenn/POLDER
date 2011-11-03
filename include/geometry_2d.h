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
#ifndef _POLDER_GEOMETRY_2D_H
#define _POLDER_GEOMETRY_2D_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include "math.h"
#include "types.h"


namespace polder
{
namespace geo
{
namespace _2d
{

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

// Basic ojects creation
Point2d Point(float x, float y);
Vector2d Vector(float x, float y);
Vector2d Vector(Point2d P1, Point2d P2);
Line2d Line(Point2d P1, Point2d P2);
Line2d Line(LineSegment2d LS);
LineSegment2d LineSegment(Point2d P1, Point2d P2);
Circle2d Circle(Point2d Center, float Radius);
Circle2d Circle(Point2d Center, Point2d P);
Circle2d Circle(Disk2d D);
Disk2d Disk(Point2d Center, float Radius);
Disk2d Disk(Point2d Center, Point2d P);
Disk2d Disk(Circle2d C);


////////////////////////////////////////////////////////////
// Operators overloading
////////////////////////////////////////////////////////////

// Basic operations
Vector2d operator+(v2d V1, v2d V2);
Vector2d operator-(v2d V1, v2d V2);
Point2d operator+(p2d P1, p2d P2);
Point2d operator-(p2d P1, p2d P2);
Point2d operator*(float f, p2d P);

// Other operations
float operator*(v2d V1, v2d V2);
float operator^(v2d V1, v2d V2);


////////////////////////////////////////////////////////////
// Objects conversion
////////////////////////////////////////////////////////////
Point2d _P_(Vector2d V);
Vector2d _V_(Point2d P);


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////
float Distance(Point2d P1, Point2d P2);
float Distance(Point2d P, Line2d L);
float Distance(Point2d P, Circle2d C);


////////////////////////////////////////////////////////////
// Projection
////////////////////////////////////////////////////////////
Point2d Projection(Point2d P, Line2d L);
LineSegment2d Projection(Circle2d C, Line2d L);
LineSegment2d Projection(Disk2d D, Line2d L);


////////////////////////////////////////////////////////////
// Belonging tests
////////////////////////////////////////////////////////////
bool BelongsTo(Point2d P, Line2d L);
bool BelongsTo(Point2d P, LineSegment2d LS);
bool BelongsTo(Point2d P, Circle2d C);
bool BelongsTo(Point2d P, Disk2d D);


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////
Point2d Intersection(Line2d L1, Line2d L2);
Point2d Intersection(LineSegment2d LS1, LineSegment2d LS2);
Point2d Intersection(Line2d L, LineSegment2d LS);
std::pair<Point2d, Point2d> Intersection(Line2d L, Circle2d C);
std::pair<Point2d, Point2d> Intersection(Circle2d C1, Circle2d C2);
LineSegment2d Intersection(Line2d, Disk2d);


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////
float Slope(Line2d L);
float Norm(Vector2d V);
Vector2d Normal(Line2d L);
Vector2d Direction(Line2d L);
Line2d Bisector(LineSegment2d LS);
Circle2d Circumscribed(Point2d P1, Point2d P2, Point2d P3);


} // namespace _2d
} // namespace geo
} // namespace polder


#endif
