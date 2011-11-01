////////////////////////////////////////////////////////////
///
/// POLDER Geometry 3d - POLDER library dealing with 3D geometry
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_GEOMETRY_3D_H
#define _POLDER_GEOMETRY_3D_H

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
namespace _3d
{

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

// Basic ojects creation
Point3d Point(float x, float y, float z);
Vector3d Vector(float x, float y, float z);
Vector3d Vector(Point3d P1, Point3d P2);
Line3d Line(Point3d P1, Point3d P2);
Plane3d Plane(Point3d P1, Point3d P2, Point3d P3);
Plane3d Plane(Point3d P, Line3d L);
Circle3d Circle(Point3d Center, float Radius, Plane3d PL);
Circle3d Circle(Disk3d D);
Disk3d Disk(Point3d Center, float Radius, Plane3d PL);
Disk3d Disk(Circle3d C);
Sphere3d Sphere(Point3d Center, float Radius);
Tube3d Tube(Line3d Axis, float Radius);
Cone3d Cone(Point3d Center, Line3d Axis, float teta);


////////////////////////////////////////////////////////////
// Operators overloading
////////////////////////////////////////////////////////////

// Basic operations
Vector3d operator+(v3d V1, v3d V2);
Vector3d operator-(v3d V1, v3d V2);
Vector3d operator*(float f, v3d P);
Point3d operator+(p3d P1, p3d P2);
Point3d operator-(p3d P1, p3d P2);
Point3d operator*(float f, p3d P);

// Other operations
float operator*(v3d V1, v3d V2);
Vector3d operator^(v3d V1, v3d V2);


////////////////////////////////////////////////////////////
// Objects conversion
////////////////////////////////////////////////////////////
Point3d _P_(Vector3d V);
Vector3d _V_(Point3d P);


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////
float Distance(Point3d P1, Point3d P2);
float Distance(Point3d P, Line3d L);
float Distance(Point3d P, Plane3d PL);
float Distance(Point3d, Sphere3d);


////////////////////////////////////////////////////////////
// Projection
////////////////////////////////////////////////////////////
Point3d Projection(Point3d P, Line3d L);
Point3d Projection(Point3d P, Plane3d PL);
Disk3d Projection(Sphere3d S, Plane3d PL);


////////////////////////////////////////////////////////////
// Belonging tests
////////////////////////////////////////////////////////////

// Point belonging to something
bool BelongsTo(Point3d P, Line3d L);
bool BelongsTo(Point3d P, Plane3d PL);
bool BelongsTo(Point3d P, Circle3d C);
bool BelongsTo(Point3d P, Sphere3d S);
bool BelongsTo(Point3d P, Tube3d T);
bool BelongsTo(Point3d P, Cone3d CO);

// Line belonging to something
bool BelongsTo(Line3d L, Plane3d PL);

// Circle belonging to something
bool BelongsTo(Circle3d C, Plane3d P);


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////
Point3d Intersection(Line3d L, Plane3d PL);
std::pair<Point3d, Point3d> Intersection(Line3d L, Sphere3d S);
std::pair<Point3d, Point3d> Intersection(Line3d L, Tube3d T);
Line3d Intersection(Plane3d PL1, Plane3d PL2);
Circle3d Intersection(Plane3d PL, Sphere3d S);
Circle3d Intersection(Sphere3d S1, Sphere3d S2);


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////
float Norm(Vector3d V);
Vector3d Normal(Plane3d PL);
Vector3d Direction(Line3d L);


} // namespace _2d
} // namespace geo
} // namespace polder


#endif
