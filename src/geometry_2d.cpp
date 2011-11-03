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
#include "geometry_2d.h"


namespace polder
{
namespace geo
{
namespace _2d
{

using namespace std;

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

Point2d Point(float x, float y)
{
    Point2d P = new p2d;
    P->x = x;
    P->y = y;
    return P;
}

Vector2d Vector(float x, float y)
{
    Vector2d V = new v2d;
    V->x = x;
    V->y = y;
    return V;
}

Vector2d Vector(Point2d P1, Point2d P2)
{
    Vector2d V = new v2d;
    V->x = P2->x - P1->x;
    V->y = P2->y - P1->y;
    return V;
}

Line2d Line(Point2d P1, Point2d P2)
{
    // The points must be distinct
    assert(P1->x != P2->x || P1->y != P2->y);

    Line2d L = new l2d;
    L->P1 = P1;
    L->P2 = P2;
    return L;
}

Line2d Line(LineSegment2d LS)
{
    Line2d L = new l2d;
    L->P1 = LS->P1;
    L->P2 = LS->P2;
    return L;
}

LineSegment2d LineSegment(Point2d P1, Point2d P2)
{
    // The points must be distinct
    assert(P1->x != P2->x || P1->y != P2->y);

    LineSegment2d LS = new ls2d;
    LS->P1 = P1;
    LS->P2 = P2;
    return LS;
}

Circle2d Circle(Point2d Center, float Radius)
{
    Circle2d C = new c2d;
    C->Center = Center;
    C->Radius = fabs(Radius); // A radius can not be lesser than 0
    return C;
}

// Circle creation
Circle2d Circle(Point2d Center, Point2d P)
{
    Circle2d C = new c2d;
    float Radius = Distance(Center, P);
    C->Center = Center;
    C->Radius = Radius;
    return C;
}

Circle2d Circle(Disk2d D)
{
    Circle2d C = new c2d;
    C->Center = D->Center;
    C->Radius = D->Radius;
    return C;
}

// Disk creation
Disk2d Disk(Point2d Center, float Radius)
{
    Disk2d D = new d2d;
    D->Center = Center;
    D->Radius = Radius;
    return D;
}

Disk2d Disk(Point2d Center, Point2d P)
{
    Disk2d D = new d2d;
    float Radius = Distance(Center, P);
    D->Center = Center;
    D->Radius = Radius;
    return D;
}

Disk2d Disk(Circle2d C)
{
    Disk2d D = new d2d;
    D->Center = C->Center;
    D->Radius = C->Radius;
    return D;
}


////////////////////////////////////////////////////////////
// Operators overloading
////////////////////////////////////////////////////////////

// Vector addition
Vector2d operator+(v2d V1, v2d V2)
{
    return Vector(V1.x + V2.x, V1.y + V2.y);
}

// Vector substraction
Vector2d operator-(v2d V1, v2d V2)
{
    return Vector(V1.x - V2.x, V1.y - V2.y);
}

// Point addition
Point2d operator+(p2d P1, p2d P2)
{
    return Point(P1.x + P2.x, P1.y + P2.y);
}

// Point substraction
Point2d operator-(p2d P1, p2d P2)
{
    return Point(P1.x - P2.x, P1.y - P2.y);
}

// float - Point multiplication
Point2d operator*(float f, p2d P)
{
    return Point(P.x * f, P.y * f);
}

// Scalar product
float operator*(v2d V1, v2d V2)
{
    return V1.x*V2.x + V1.y*V2.y;
}

// Cross product
float operator^(v2d V1, v2d V2)
{
    return V1.x*V2.y - V1.y*V2.x;
}


////////////////////////////////////////////////////////////
// Objects conversion
////////////////////////////////////////////////////////////

// From Vector to Point
Point2d _P_(Vector2d V)
{
    return Point(V->x, V->y);
}

// From Point to Vector
Vector2d _V_(Point2d P)
{
    return Vector(P->x, P->y);
}


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////

// Distance between two points
float Distance(Point2d P1, Point2d P2)
{
    float X = P2->x - P1->x;
    float Y = P2->y - P1->y;
    return hypot(X, Y);
}

// Distance between a point and a line
float Distance(Point2d P, Line2d L)
{
    float x = P->x;
    float y = P->y;

    Vector2d N = Normal(L);

    float a = N->x;
    float b = N->y;
    float c = - a*x - b*y;

    return abs(a*x + b*y + c) / sqrt(a*a + b*b);
}

// Distance between a point and a circle
float Distance(Point2d P, Circle2d C)
{
    return abs(Distance(P, C->Center) - C->Radius);
}


////////////////////////////////////////////////////////////
// Projection
////////////////////////////////////////////////////////////

// Projection of a point on a line
Point2d Projection(Point2d P, Line2d L)
{
    // Aliases : more understandable code
    float xp = P->x; float yp = P->y;
    float x1 = L->P1->x; float y1 = L->P1->y;
    float x2 = L->P2->x; float y2 = L->P2->y;

    // Aliases : optimization
    float _X = x2 - x1;
    float _Y = y2 - y1;

    // Line equation : X = t*(x2-x1) + x1 ; etc...
    float t = (_X*(x1-xp) + _Y*(y2-yp)) / (_X*_X + _Y*_Y);
    return Point(t*_X+x1, t*_Y+y1);
}

// Projection of circle on a line
LineSegment2d Projection(Circle2d C, Line2d L)
{
    Point2d middle = Projection(C->Center, L);
    auto C2P = Intersection(L, Circle(middle, C->Radius));
    return LineSegment(C2P.first, C2P.second);
}

// Projection of a disk on a line
LineSegment2d Projection(Disk2d D, Line2d L)
{
    Point2d middle = Projection(D->Center, L);
    auto C2P = Intersection(L, Circle(middle, D->Radius));
    return LineSegment(C2P.first, C2P.second);
}


////////////////////////////////////////////////////////////
// Belonging tests
////////////////////////////////////////////////////////////

// Point belonging to a line
bool BelongsTo(Point2d P, Line2d L)
{
    // If it is a vertical line
    if (L->P1->x == L->P2->x)
    {
        // We just have to test the egality of x values
        return P->x == L->P1->x;
    }

    // Line equation : y = m*x + p
    float m = Slope(L);
    float p = L->P1->y - m * L->P1->x;
    return (P->y == m * P->x + p);
}

// Point belonging to a line segment
bool BelongsTo(Point2d P, LineSegment2d LS)
{
    if (BelongsTo(P, Line(LS)))
    {
        return P->x >= fmin(LS->P1->x, LS->P2->x) && P->x <= fmax(LS->P1->x, LS->P2->x)
                && P->y >= fmin(LS->P1->y, LS->P2->y) && P->y <= fmax(LS->P1->y, LS->P2->y);
    }
    return false;
}

// Point belonging to a circle
bool BelongsTo(Point2d P, Circle2d C)
{
    return Distance(P, C->Center) == C->Radius;
}

// Point belonging to a disk
bool BelongsTo(Point2d P, Disk2d D)
{
    return Distance(P, D->Center) <= D->Radius;
}


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////

// Line-Line intersection
Point2d Intersection(Line2d L1, Line2d L2)
{
    // Aliases ; the variables are then easier to use
    float x1 = L1->P1->x; float y1 = L1->P1->y;
    float x2 = L1->P2->x; float y2 = L1->P2->y;
    float x3 = L2->P1->x; float y3 = L2->P1->y;
    float x4 = L2->P2->x; float y4 = L2->P2->y;

    // Aliases ; so that we won't have to do the same operation multiple times
    float X1 = x1 - x2;
    float X2 = x3 - x4;
    float Y1 = y1 - y2;
    float Y2 = y3 - y4;

    float d = X1 * Y2 - Y1 * X2;
    if (d == 0) // The lines are parallel
    {
        return NULL;
    }

    float pre = (x1*y2 - y1*x2);
    float post = (x3*y4 - y3*x4);
    float x = (pre * (X2) - (X1) * post) / d;
    float y = (pre * (Y2) - (Y1) * post) / d;

    // Returns the point of intersection
    return Point(x, y);
}

// LineSegment-LineSegment intersection
Point2d Intersection(LineSegment2d LS1, LineSegment2d LS2)
{
    // Try the intersection with the corresponding lines
    Point2d res = Intersection(Line(LS1), Line(LS2));
    if (res == NULL)
    {
        return NULL;
    }

    // Checks if the x and y coordinates are within both segments
    if (res->x < fmin(LS1->P1->x, LS1->P2->x) || res->x > fmax(LS1->P1->x, LS1->P2->x) ||
        res->x < fmin(LS2->P1->x, LS2->P2->x) || res->x > fmax(LS2->P1->x, LS2->P2->x))
        return NULL;
    if (res->y < fmin(LS1->P1->y, LS1->P2->y) || res->y > fmax(LS1->P1->y, LS1->P2->y) ||
        res->y < fmin(LS2->P1->y, LS2->P2->y) || res->y > fmax(LS2->P1->y, LS2->P2->y))
        return NULL;

    return res;
}

// Line-LineSegment intersection
Point2d Intersection(Line2d L, LineSegment2d LS)
{
    Point2d res = Intersection(L, Line(LS));
    if (res == NULL)
    {
        return NULL;
    }

    // Checks if the x and y coordinates are within the segment
    if (res->x < fmin(LS->P1->x, LS->P2->x) || res->x > fmax(LS->P1->x, LS->P2->x))
        return NULL;
    if (res->y < fmin(LS->P1->y, LS->P2->y) || res->y > fmax(LS->P1->y, LS->P2->y))
        return NULL;

    return res;
}

// Line-Circle intersection
pair<Point2d, Point2d> Intersection(Line2d L, Circle2d C)
{
    assert(Distance(C->Center, L) <= C->Radius);

    // Aliases : more understandable code
    float x1 = L->P1->x; float x2 = L->P2->x;
    float y1 = L->P1->y; float y2 = L->P2->y;
    float xc = C->Center->x;
    float yc = C->Center->y;

    // Aliases : optimization
    float _X = x2 - x1;
    float _Y = y2 - y1;

    // Equation of the line : x = t(xb-xa) - xa ; y = t(yb-ya) - ya
    float a = _X*_X + _Y*_Y;
    float b = 2 * (_X*(x1-xc) + _Y*(y1-yc));
    float c = x1*x1 + y1*y1 + xc*xc + yc*yc - 2 * (xc*x1 + yc*y1) - C->Radius*C->Radius;

    auto C2F = math::quadratic(a, b, c);
    assert(C2F.first.imag() == 0 && C2F.second.imag() == 0);

    float t1 = C2F.first.real();
    float t2 = C2F.second.real();

    Point2d res1 = Point(t1*_X+x1, t1*_Y+y1);
    Point2d res2 = Point(t2*_X+x1, t2*_Y+y1);
    return make_pair(res1, res2);
}

// Circle-Circle intersection
pair<Point2d, Point2d> Intersection(Circle2d C1, Circle2d C2)
{
    // Equations : R1� = (X - x1)� + (Y - y1)� & R2� = (X - x2)� + (Y - y2)�
    float R1 = C1->Radius; float R1_2 = R1*R1;
    float R2 = C2->Radius;
    float x1 = C1->Center->x; float x1_2 = x1*x1;
    float y1 = C1->Center->y; float y1_2 = y1*y1;
    float x2 = C2->Center->x;
    float y2 = C2->Center->y;

    float D = Distance(C1->Center, C2->Center);
    assert(D <= R1 + R2); // The circles may not be distant
    assert(fabs(R1 - R2) >= D); // There may not be a cirecle in another one

    // To avoid a division by 0
    if (y1 == y2)
    {
        float X = (R2*R2 - R1_2 - x2*x2 + x1_2) / (2 * (x1-x2));
        float C = x1_2 + X*X - 2*x1*X + y1_2 - R1_2;
        auto C2F = math::quadratic(1, -2*y1, C);
        return make_pair(Point(X, C2F.first.real()), Point(X, C2F.second.real()));
    }

    float E = (R1_2 - R2*R2 - x1_2 + y2*y2 + x2*x2 - y1_2) / (2 * (y2-y1));
    float F = (x1-x2) / (y2-y1);

    float A = 1 + F*F;
    float B = 2 * (-x1 + E*F - y1*F);
    float C = x1_2 + E*(E - 2*y1) + y1_2 - R1_2;

    // Pair of complex numbers
    auto C2X = math::quadratic(A, B, C);
    assert(imag(C2X.first) == 0 && imag(C2X.second) == 0);

    // Final results
    float X1 = real(C2X.first);
    float X2 = real(C2X.second);
    float Y1 = X1 * F + E;
    float Y2 = X2 * F + E;

    return make_pair(Point(X1, Y1), Point(X2, Y2));
}

// Line-Disk intersection
LineSegment2d Intersection(Line2d L, Disk2d D)
{
    auto C2P = Intersection(L, Circle(D));
    return LineSegment(C2P.first, C2P.second);
}


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

// Normal of a line
Vector2d Normal(Line2d L)
{
    if (L->P1->x != L->P2->x)
    {
        return Vector(-Slope(L), 1);
    }
    // Horizontal line, arbitrary values
    return Vector(L->P1, Point(L->P1->x+5, L->P1->y));
}

// Direction vector of a line
Vector2d Direction(Line2d L)
{
    return Vector(L->P1, L->P2);
}

// Slope of a line
float Slope(Line2d L)
{
    float _temp = L->P2->x - L->P1->x;
    assert(_temp);
    return (L->P2->y - L->P1->y) / _temp;
}

// Perpendicular bisector of a line segment
Line2d Bisector(LineSegment2d LS)
{
    // Aliases : more understandable code
    float x1 = LS->P1->x;
    float y1 = LS->P1->y;
    float x2 = LS->P2->x;
    float y2 = LS->P2->y;

    // Find the mid-point
    Point2d MP = Point((x1+x2)/2, (y1+y2)/2);

    // We return a line made with arbitrary points corresponding to its equation
    if (x1 != x2)
    {
        // Slope of the bisector
        float m = - (1 / Slope(Line(LS)));
        float p = MP->y - m * MP->x;

        // Equation : y = mx + p
        return Line(MP, Point(0, p));
    }
    return Line(MP, Point(MP->x+5, MP->y));
}

// Circle creation with three points of the circle perimeter
Circle2d Circumscribed(Point2d P1, Point2d P2, Point2d P3)
{
    if (BelongsTo(P1, Line(P2, P3)))
    {
        // The three points must not be colinear
        return NULL;
    }

    Line2d L1 = Bisector(LineSegment(P1, P2));
    Line2d L2 = Bisector(LineSegment(P2, P3));

    Circle2d C = new c2d;
    C->Center = Intersection(L1, L2);
    C->Radius = Distance(C->Center, P1);
    return C;
}

// Norm of a vector
float Norm(Vector2d V)
{
    float x = V->x;
    float y = V->y;
    return hypot(x, y);
}


} // namespace _2d
} // namespace geo
} // namespace polder
