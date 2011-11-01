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
#include "geometry_3d.h"


namespace polder
{
namespace geo
{
namespace _3d
{

using namespace std;

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

// Point creation
Point3d Point(float x, float y, float z)
{
    Point3d P = new p3d;
    P->x = x;
    P->y = y;
    P->z = z;
    return P;
}

// Vector creation
Vector3d Vector(float x, float y, float z)
{
    Vector3d V = new v3d;
    V->x = x;
    V->y = y;
    V->z = z;
    return V;
}

Vector3d Vector(Point3d P1, Point3d P2)
{
    Vector3d V = new v3d;
    V->x = P2->x - P1->x;
    V->y = P2->y - P1->y;
    V->z = P2->z - P1->z;
    return V;
}

Line3d Line(Point3d P1, Point3d P2)
{
    if (P1->x == P2->x && P1->y == P2->y && P1->z == P2->z)
    {
        // The points must be distinct
        return NULL;
    }

    Line3d L = new l3d;
    L->P1 = P1;
    L->P2 = P2;
    return L;
}

Plane3d Plane(Point3d P1, Point3d P2, Point3d P3)
{
    if (BelongsTo(P1, Line(P2, P3)))
    {
        // The three points must not be colinear
        return NULL;
    }

    Plane3d PL = new pl3d;
    PL->P1 = P1;
    PL->P2 = P2;
    PL->P3 = P3;
    return PL;
}

Plane3d Plane(Point3d P, Line3d L)
{
    if (BelongsTo(P, L))
    {
        // The three points must not be colinear
        return NULL;
    }

    Plane3d PL = new pl3d;
    PL->P1 = P;
    PL->P2 = L->P1;
    PL->P3 = L->P2;
    return PL;
}

Circle3d Circle(Point3d Center, float Radius, Plane3d PL)
{
    Circle3d C = new c3d;
    C->Center = Center;
    C->Radius = Radius;
    C->PL = PL;
    return C;
}

Circle3d Circle(Disk3d D)
{
    Circle3d C = new c3d;
    C->Center = D->Center;
    C->Radius = D->Radius;
    C->PL = D->PL;
    return C;
}

Disk3d Disk(Point3d Center, float Radius, Plane3d PL)
{
    Disk3d D = new d3d;
    D->Center = Center;
    D->Radius = Radius;
    D->PL = PL;
    return D;
}

Disk3d Disk(Circle3d C)
{
    Disk3d D = new d3d;
    D->Center = C->Center;
    D->Radius = C->Radius;
    D->PL = C->PL;
    return D;
}

Sphere3d Sphere(Point3d Center, float Radius)
{
    assert(Radius != 0);
    Sphere3d S = new s3d;
    S->Center = Center;
    S->Radius = abs(Radius);
    return S;
}

// Tube creation
Tube3d Tube(Line3d Axis, float Radius)
{
    assert(Radius != 0);
    Tube3d T = new t3d;
    T->Axis = Axis;
    T->Radius = abs(Radius);
    return T;
}

// Cone creation
Cone3d Cone(Point3d Center, Line3d Axis, float teta)
{
    Cone3d CO = new co3d;
    CO->Center = Center;
    CO->Axis = Axis;
    CO->teta = teta;
    return CO;
}


////////////////////////////////////////////////////////////
// Operators overloading
////////////////////////////////////////////////////////////

// Vector addition
Vector3d operator+(v3d V1, v3d V2)
{
    return Vector(V1.x + V2.x, V1.y + V2.y, V1.z + V2.z);
}

// Vector substraction
Vector3d operator-(v3d V1, v3d V2)
{
    return Vector(V1.x - V2.x, V1.y - V2.y, V1.z - V2.z);
}

// float - Vector multiplication
Vector3d operator*(float f, v3d V)
{
    return Vector(V.x * f, V.y * f, V.z * f);
}

// Point addition
Point3d operator+(p3d P1, p3d P2)
{
    return Point(P1.x + P2.x, P1.y + P2.y, P1.z + P2.z);
}

// Point substraction
Point3d operator-(p3d P1, p3d P2)
{
    return Point(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z);
}

// float - Point multiplication
Point3d operator*(float f, p3d P)
{
    return Point(P.x * f, P.y * f, P.z * f);
}

// Scalar product
float operator*(v3d V1, v3d V2)
{
    return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
}

// Cross product
Vector3d operator^(v3d V1, v3d V2)
{
    float X = V1.y * V2.z - V1.z * V2.y;
    float Y = V1.z * V2.x - V1.x * V2.z;
    float Z = V1.x * V2.y - V1.y * V2.x;
    return Vector(X, Y, Z);
}


////////////////////////////////////////////////////////////
// Objects conversion
////////////////////////////////////////////////////////////

Point3d _P_(Vector3d V)
{
    return Point(V->x, V->y, V->z);
}

// Avoid to do: Vector3d V = Vector(P, Point(0, 0, 0));
Vector3d _V_(Point3d P)
{
    return Vector(P->x, P->y, P->z);
}


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////

// Distance between two points
float Distance(Point3d P1, Point3d P2)
{
    float X = P2->x - P1->x;
    float Y = P2->y - P1->y;
    float Z = P2->z - P1->z;
    return sqrt(X*X + Y*Y + Z*Z);
}

// Distance between a point and a line
float Distance(Point3d P, Line3d L)
{
    Vector3d LP = Vector(L->P1, P);
    Vector3d u = Direction(L);
    return Norm(*LP ^ *u) / Norm(u);
}

// Distance between a point and a plane
float Distance(Point3d P, Plane3d PL)
{
    // Plane equation : ax + by + cz + d
    Vector3d N = Normal(PL);
    float a = N->x;
    float b = N->y;
    float c = N->z;
    float d = - (PL->P1->x * a) - (PL->P1->y * b) - (PL->P1->z * c);

    float x = P->x;
    float y = P->y;
    float z = P->z;

    return fabs(a*x + b*y + c*z + d) / sqrt(a*a + b*b + c*c);
}

// Distance between a point and a sphere
float Distance(Point3d P, Sphere3d S)
{
    return abs(Distance(P, S->Center) - S->Radius);
}


////////////////////////////////////////////////////////////
// Projection
////////////////////////////////////////////////////////////

// Projection of a point on a line
Point3d Projection(Point3d P, Line3d L)
{
    // Aliases : more understandable code
    float xp = P->x; float yp = P->y; float zp = P->z;
    float x1 = L->P1->x; float y1 = L->P1->y; float z1 = L->P1->z;
    float x2 = L->P2->x; float y2 = L->P2->y; float z2 = L->P2->z;

    // Aliases : optimization
    float _X = x2 - x1;
    float _Y = y2 - y1;
    float _Z = z2 - z1;

    // Line equation : X = t*(x2-x1) + x1 ; etc...
    float t = (_X*(x1-xp) + _Y*(y2-yp) + _Z*(z2-zp)) / (_X*_X + _Y*_Y + _Z*_Z);
    return Point(t*_X-x1, t*_Y-y1, t*_Z-z1);
}

// Projection of a plane on a line
Point3d Projection(Point3d P, Plane3d PL)
{
    float x1 = PL->P1->x;
    float y1 = PL->P1->y;
    float z1 = PL->P1->z;

    Vector3d N = Normal(PL);
    float a = N->x;
    float b = N->y;
    float c = N->z;
    float d = *(-1 * *N) * *_V_(PL->P1);

    float t = (-a*x1 - b*y1 - c*z1 - d) / (a*a + b*b + c*c);
    return Point(t*a+P->x, t*b+P->y, t*c+P->z);
}

// Projection of a sphere on a plane
Disk3d Projection(Sphere3d S, Plane3d PL)
{
    Point3d Center = Projection(S->Center, PL);
    return Disk(Center, S->Radius, PL);
}


////////////////////////////////////////////////////////////
// Belonging tests
////////////////////////////////////////////////////////////

// Point belonging to a line
bool BelongsTo(Point3d P, Line3d L)
{
    // Line equation :
        // X = t(x2-x1) - x1
        // Y = t(y2-y1) - y1
        // Z = t(z2-z1) - z1

    float x1 = L->P1->x; float x2 = L->P2->x;
    float y1 = L->P1->y; float y2 = L->P2->y;
    float z1 = L->P1->z; float z2 = L->P2->z;

    float t1 = (P->x + x1) / (x2 - x1);
    float t2 = (P->y + y1) / (y2 - y1);
    if (t1 != t2)
    {
        return false;
    }
    else
    {
        float t3 = (P->z + z1) / (z2 - z1);
        return t1 == t3;
    }
}

// Point belonging to a plane
bool BelongsTo(Point3d P, Plane3d PL)
{
    Vector3d N = Normal(PL);

    // Plane equation : ax + by + cx + d = 0
    // Or : N.x*x + N.y*y + N.z*z + dot(-N, OA) = 0

    Vector3d A = _V_(PL->P1);
    Vector3d B = Vector(-N->x, -N->y, -N->z);

    return (N->x*P->x) + (N->y*P->y) + (N->z*P->z) + (*A * *B) == 0;
}

// Point belonging to a circle
bool BelongsTo(Point3d P, Circle3d C)
{
    return (BelongsTo(P, C->PL)) && (Distance(P, C->Center) == C->Radius);
}

// Point belonging to a sphere
bool BelongsTo(Point3d P, Sphere3d S)
{
    return Distance(P, S->Center) == S->Radius;
}

// Point belonging to a tube
bool BelongsTo(Point3d P, Tube3d T)
{
    return Distance(P, T->Axis) == T->Radius;
}

// Point belonging to a cone
bool BelongsTo(Point3d P, Cone3d CO)
{
    Point3d P2 = Projection(P, CO->Axis);
    float d1 = Distance(P, P2);
    float d2 = Distance(P2, CO->Center);
    float d3 = Distance(P, CO->Center);
    return d3*d3 == d2*d2 + d1*d1;
}

// Line belonging to a plane
bool BelongsTo(Line3d L, Plane3d PL)
{
    Vector3d N = Normal(PL);
    Vector3d V = Direction(L);
    return *N * *V == 0;
}

// Circle belonging to a plane
bool BelongsTo(Circle3d C, Plane3d PL)
{
    Vector3d N1 = Normal(C->PL);
    Vector3d N2 = Normal(PL);

    return (N1->x + N1->y + N1->z) == (N2->x + N2->y + N2->z);
}


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////

// Line-Plane intersection
Point3d Intersection(Line3d L, Plane3d PL)
{
    Vector3d N = Normal(PL);

    Point3d Pt1 = *PL->P1 - *L->P1;
    Point3d Pt2 = *PL->P2 - *L->P1;

    // Plane equation : ax + by + cx + d = 0
    float d = *N * *_V_(Pt2); // d = N * Vector(Pt2)
    if (d == 0)
    {
        // PL and L are parallel
        return NULL;
    }

    // Line equation : x = t(x2-x1) - x1
    float t = *N * *_V_(Pt1) / d;
    Point3d P = *(t * *Pt2) + *L->P2; // P = t * Pt2 + L->P2
    return P;
}

// Plane-Plane intersection
Line3d Intersection(Plane3d PL1, Plane3d PL2)
{
    // We create two lines with the three points of a plan
    Line3d L1 = Line(PL1->P1, PL1->P2);
    Line3d L2 = Line(PL1->P1, PL1->P3);

    // We get the intersection points between the two lines and the second plane
    Point3d P1 = Intersection(L1, PL2);
    Point3d P2 = Intersection(L2, PL2);

    if (P1 == NULL && P2 == NULL)
    {
        // (PL1) and (PL2) are parallel
        return NULL;
    }

    if ((P1 == NULL) xor (P2 == NULL))
    {
        // One of the lines of (PL1) is parallel to (PL2),
        // we need another line to find another point
        Line3d L3 = Line(PL1->P2, PL1->P3);
        P2 = Intersection(L3, PL2);
    }

    // The intersection line is the line determined by the two intersection points
    return Line(P1, P2);
}

// Line-Sphere intersection
pair<Point3d, Point3d> Intersection(Line3d L, Sphere3d S)
{
    assert(Distance(S->Center, L) <= S->Radius);

    // Aliases : more understandable code
    float x1 = L->P1->x; float x2 = L->P2->x;
    float y1 = L->P1->y; float y2 = L->P2->y;
    float z1 = L->P1->z; float z2 = L->P2->z;
    float xc = S->Center->x;
    float yc = S->Center->y;
    float zc = S->Center->z;

    // Aliases : optimization
    float _X = x2 - x1;
    float _Y = y2 - y1;
    float _Z = z2 - z1;

    // Equation of the line : x = t(xb-xa) - xa ; y = t(yb-ya) - ya ; z = t(zb-za) - za
    float A = _X*_X + _Y*_Y + _Z*_Z;
    float B = 2 * (_X*(x1-xc) + _Y*(y1-yc) + _Z*(z1-zc));
    float C = x1*x1 + y1*y1 + z1*z1 + xc*xc + yc*yc + zc*zc - 2 * (xc*x1 + yc*y1 + zc*z1) - S->Radius*S->Radius;

    auto C2F = math::quadratic(A, B, C);
    assert(C2F.first.imag() == 0 && C2F.second.imag() == 0);

    float t1 = C2F.first.real();
    float t2 = C2F.second.real();

    Point3d res1 = Point(t1*_X+x1, t1*_Y+y1, t1*_Z+z1);
    Point3d res2 = Point(t2*_X+x1, t2*_Y+y1, t2*_Z+z1);
    return make_pair(res1, res2);
}

// Plane-Sphere intersection
Circle3d Intersection(Plane3d PL, Sphere3d S)
{
    float D = Distance(S->Center, PL);
    if (D > S->Radius)
    {
        // The plane and the sphere do not cross
        return NULL;
    }

    Point3d Center = Projection(S->Center, PL);
    float Radius = S->Radius - D;

    return Circle(Center, Radius, PL);
}

// Sphere-Sphere intersection
Circle3d Intersection(Sphere3d S1, Sphere3d S2)
{
    // Equations : R1² = (X - x1)² + (Y - y1)² & R2² = (X - x2)² + (Y - y2)²
    float R1 = S1->Radius;
    float R2 = S2->Radius;
    float x1 = S1->Center->x;
    float y1 = S1->Center->y;
    float z1 = S1->Center->z;
    float x2 = S2->Center->x;
    float y2 = S2->Center->y;
    float z2 = S2->Center->z;

    float D = Distance(S1->Center, S2->Center);
    if (D > R1 + R2)
    {
        // The spheres are distant
        return NULL;
    }
    if (fabs(R1 - R2) >= D)
    {
        // One of the spheres is in the other
        return NULL;
    }

    float coeff = R2 / R1 + 1;
    float A = D / coeff;

    // Radius of the intersection
    float Radius = D - A;

    float u = x2 - x1;
    float v = y2 - y1;
    float w = z2 - z1;

    float dx = u / coeff;
    float dy = v / coeff;
    float dz = w / coeff;

    // Center of the intersection
    Point3d Center = Point(dx, dy, dz);

    // Plane equation : uX + vY + wZ + d = 0
    float d = -u*dx - v*dy - w*dz;

    // Plane of the intersection
    // Made with three arbitrary values
    Plane3d PL = Plane(Center, Point(-d/u, 0, 0), Point((-d-v-w)/u, 1, 1));

    return Circle(Center, Radius, PL);
}


// Line-Tube intersection
pair<Point3d, Point3d> Intersection(Line3d L, Tube3d T)
{
    // Tube equation: x² + y² + z² - (ax + by + cz) / (a² + b² + c²) = R²
    // Line equation: x = t * (x2-x1) + x1 (same for y and z)
    float x1 = L->P1->x; float x2 = L->P2->x;
    float y1 = L->P1->y; float y2 = L->P2->y;
    float z1 = L->P1->z; float z2 = L->P2->z;

    float a = T->Axis->P2->x - T->Axis->P1->x; float a2 = a*a;
    float b = T->Axis->P2->y - T->Axis->P1->y; float b2 = b*b;
    float c = T->Axis->P2->z - T->Axis->P1->z; float c2 = c*c;
    float abc2 = 2*a*b*c;
    assert(abc2 != 0);

    float _X = x2 - x1; float _X2 = _X*_X;
    float _Y = y2 - y1; float _Y2 = _Y*_Y;
    float _Z = z2 - z1; float _Z2 = _Z*_Z;

    float A1 = _X2 + _Y2 + _Z2;
    float B1 = 2 * (_X*x1 + _Y*y1 + _Z*z1);
    float C1 = x1*x1 + y1*y1 + z1*z1;

    float lambda1 = a2*_X2 + b2*_Y2 + c2*_Z2;
    float lambda2 = 2 * (a*_X*x1 + b*_Y*y1 + c*_Z*z1);
    float lambda3 = C1; // = x1² + y1² + z1²

    float A2 = lambda1 - abc2 * _X*_Y*_Z;
    float B2 = lambda2 - abc2 * (_X*y1*z1 + _Y*x1*z1 + _Z*x1*y1);
    float C2 = lambda3 - abc2 * x1*y1*z1;


    float normu = a2 + b2 + c2;

    float A = A1 + A2 / normu;
    float B = B1 + B2 / normu;
    float C = C1 + C2 / normu - T->Radius*T->Radius;

    auto res = math::quadratic(A, B, C);
    assert(res.first.imag() == 0 && res.second.imag() == 0);

    float t1 = res.first.real();
    float t2 = res.second.real();

    float X1 = t1*a+x1; float X2 = t2*a+x2;
    float Y1 = t1*b+y1; float Y2 = t2*b+y2;
    float Z1 = t1*c+z1; float Z2 = t2*c+z2;
    return make_pair(Point(X1, Y1, Z1), Point(X2, Y2, Z2));
}


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

// Norm of a vector
float Norm(Vector3d V)
{
    float x = V->x;
    float y = V->y;
    float z = V->z;
    return sqrt(x*x + y*y + z*z);
}

// Normal of a plane
Vector3d Normal(Plane3d PL)
{
    // "Distances" between points
    float X1 = (PL->P2->x - PL->P1->x);
    float Y1 = (PL->P2->y - PL->P1->y);
    float Z1 = (PL->P2->z - PL->P1->z);
    float X2 = (PL->P3->x - PL->P1->x);
    float Y2 = (PL->P3->y - PL->P1->y);
    float Z2 = (PL->P3->z - PL->P1->z);

    float D = -(X1*Y2) / X2 + Y1;
    float E = (X1*Z2) / X2;

    float B = (E - Z1) / D;

    float F = ((E*X1) + (Z1*X1)) / D;

    float A = (-F - Z2*X1) / X2;

    Vector3d res = Vector(A, B, 1);
    return res;
}

// Direction vector of a line
Vector3d Direction(Line3d L)
{
    return Vector(L->P1, L->P2);
}


} // namespace _3d
} // namespace geo
} // namespace polder
