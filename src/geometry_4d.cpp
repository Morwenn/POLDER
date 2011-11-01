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
#include "geometry_4d.h"

namespace polder
{
namespace geo
{
namespace _4d
{

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

// Point creation
Point4d Point(float x, float y, float z, float w)
{
    Point4d P = new p4d;
    P->x = x;
    P->y = y;
    P->z = z;
    P->w = w;
    return P;
}

// Vector creation
Vector4d Vector(float x, float y, float z, float w)
{
    Vector4d V = new v4d;
    V->x = x;
    V->y = y;
    V->z = z;
    V->w = w;
    return V;
}

Vector4d Vector(Point4d P1, Point4d P2)
{
    Vector4d V = new v4d;
    V->x = P2->x - P1->x;
    V->y = P2->y - P1->y;
    V->z = P2->z - P1->z;
    V->w = P2->w - P1->w;
    return V;
}

Line4d Line(Point4d P1, Point4d P2)
{
    if (P1->x == P2->x
     && P1->y == P2->y
     && P1->z == P2->z
     && P1->w == P2->w)
    {
        // The points must be distinct
        return NULL;
    }

    Line4d L = new l4d;
    L->P1 = P1;
    L->P2 = P2;
    return L;
}

Hyperplane4d Hyperplane(Point4d P1, Point4d P2, Point4d P3, Point4d P4)
{
    // TODO: belonging test

    Hyperplane4d HPL = new hpl4d;
    HPL->P1 = P1;
    HPL->P2 = P2;
    HPL->P3 = P3;
    HPL->P4 = P4;
    return HPL;
}

Hypersphere4d Hypersphere(Point4d Center, float Radius)
{
    Hypersphere4d HS = new hs4d;
    HS->Center = Center;
    // A radius can not be lesser than 0
    HS->Radius = fabs(Radius);
    return HS;
}


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////

// Distance between two points
float Distance(Point4d P1, Point4d P2)
{
    float X = P2->x - P1->x;
    float Y = P2->y - P1->y;
    float Z = P2->z - P1->z;
    float W = P2->w - P1->w;
    return sqrt(X*X + Y*Y + Z*Z + W*W);
}


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////

// Line-Hypersphere intersection
std::pair<Point4d, Point4d> Intersection(Line4d L, Hypersphere4d HS)
{
    // Aliases : more understandable code
    float x1 = L->P1->x; float x2 = L->P2->x;
    float y1 = L->P1->y; float y2 = L->P2->y;
    float z1 = L->P1->z; float z2 = L->P2->z;
    float w1 = L->P1->w; float w2 = L->P2->w;
    float xc = HS->Center->x;
    float yc = HS->Center->y;
    float zc = HS->Center->z;
    float wc = HS->Center->w;

    // Aliases : optimization
    float _X = x2 - x1;
    float _Y = y2 - y1;
    float _Z = z2 - z1;
    float _W = w2 - w1;

    // Equation of the line : x = t(xb-xa) + xa ; y = t(yb-ya) + ya ; z = t(zb-za) + za ; w = t(wb-wa) + wa
    float A = _X*_X + _Y*_Y + _Z*_Z + _W*_W;
    float B = 2 * (_X*(x1-xc) + _Y*(y1-yc) + _Z*(z1-zc) + _W*(w1-wc));
    float C = x1*x1 + y1*y1 + z1*z1 + w1*w1 + xc*xc + yc*yc + zc*zc + wc*wc - 2 * (xc*x1 + yc*y1 + zc*z1 + wc*w1) - HS->Radius*HS->Radius;

    auto C2F = math::quadratic(A, B, C);

    float t1 = C2F.first.real();
    float t2 = C2F.second.real();

    Point4d res1 = Point(t1*_X+x1, t1*_Y+y1, t1*_Z+z1, t1*_W+w1);
    Point4d res2 = Point(t2*_X+x1, t2*_Y+y1, t2*_Z+z1, t2*_W+w1);
    return std::make_pair(res1, res2);
}


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

// Norm of a vector
float Norm(Vector4d V)
{
    float x = V->x;
    float y = V->y;
    float z = V->z;
    float w = V->w;
    return sqrt(x*x + y*y + z*z + w*w);
}

// Dot product
float Dot(Vector4d V1, Vector4d V2)
{
    return V1->x*V2->x + V1->y*V2->y + V1->z*V2->z + V1->w*V2->w;
}


////////////////////////////////////////////////////////////
// Vector operations
////////////////////////////////////////////////////////////

// Vector-Vector addition
Vector4d add(Vector4d V1, Vector4d V2)
{
    Vector4d V = new v4d;
    V->x = V1->x + V2->x;
    V->y = V1->y + V2->y;
    V->z = V1->z + V2->z;
    V->w = V1->w + V2->w;
    return V;
}

// Vector-Vector substraction
Vector4d sub(Vector4d V1, Vector4d V2)
{
    Vector4d V = new v4d;
    V->x = V1->x - V2->x;
    V->y = V1->y - V2->y;
    V->z = V1->z - V2->z;
    V->w = V1->w - V2->w;
    return V;
}

// Float-Vector addition
Vector4d add(float f, Vector4d V)
{
    Vector4d W = new v4d;
    V->x = f + V->x;
    V->y = f + V->y;
    V->z = f + V->z;
    V->w = f + V->w;
    return W;
}

// Float-Vector multiplication
Vector4d mul(float f, Vector4d V)
{
    Vector4d W = new v4d;
    V->x = f * V->x;
    V->y = f * V->y;
    V->z = f * V->z;
    V->w = f * V->w;
    return W;
}


} // namespace _4d
} // namespace geo
} // namespace polder
