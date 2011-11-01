////////////////////////////////////////////////////////////
///
/// POLDER Types - POLDER math type definitions
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_TYPES_H
#define _POLDER_TYPES_H


////////////////////////////////////////////////////////////
// 2D Objects definitions
////////////////////////////////////////////////////////////

// Point definition
typedef struct p2d
{
    float x;
    float y;
} p2d;
typedef p2d* Point2d;

// Vector definition
typedef struct v2d
{
    float x;
    float y;
} v2d;
typedef v2d* Vector2d;

// Line definition
typedef struct l2d
{
    Point2d P1;
    Point2d P2;
} l2d;
typedef l2d* Line2d;

// Line segment definition
typedef struct ls2d
{
    Point2d P1;
    Point2d P2;
} ls2d;
typedef ls2d* LineSegment2d;

// Circle definition
typedef struct c2d
{
    Point2d Center;
    float Radius;
} c2d;
typedef c2d* Circle2d;

// Disk definition
typedef struct d2d
{
    Point2d Center;
    float Radius;
} d2d;
typedef d2d* Disk2d;


////////////////////////////////////////////////////////////
// 3D Objects definitions
////////////////////////////////////////////////////////////

// Point definition
typedef struct p3d
{
    float x;
    float y;
    float z;
} p3d;
typedef p3d* Point3d;

// Vector definition
typedef struct v3d
{
    float x;
    float y;
    float z;
} v3d;
typedef v3d* Vector3d;

// Line definition
typedef struct l3d
{
    Point3d P1;
    Point3d P2;
} l3d;
typedef l3d* Line3d;

// Plane definition
typedef struct pl3d
{
    Point3d P1;
    Point3d P2;
    Point3d P3;
} pl3d;
typedef struct pl3d* Plane3d;

// Circle definition
typedef struct c3d
{
    Point3d Center;
    float Radius;
    Plane3d PL;
} c3d;
typedef c3d* Circle3d;

// Disk definition
typedef struct d3d
{
    Point3d Center;
    float Radius;
    Plane3d PL;
} d3d;
typedef d3d* Disk3d;

// Sphere definition
typedef struct s3d
{
    Point3d Center;
    float Radius;
} s3d;
typedef s3d* Sphere3d;

// Tube definition
typedef struct t3d
{
    Line3d Axis;
    float Radius;
} t3d;
typedef t3d* Tube3d;

// Cone definition
typedef struct co3d
{
    Point3d Center;
    Line3d Axis;
    float teta;
} co3d;
typedef co3d* Cone3d;
// z² = cot²teta * (x² + y²)


////////////////////////////////////////////////////////////
// 4D Objects definitions
////////////////////////////////////////////////////////////

// Point definition
typedef struct p4d
{
    float x;
    float y;
    float z;
    float w;
} p4d;
typedef struct p4d* Point4d;

// Vector definition
typedef struct v4d
{
    float x;
    float y;
    float z;
    float w;
} v4d;
typedef struct v4d* Vector4d;

// Line definition
typedef struct l4d
{
    Point4d P1;
    Point4d P2;
} l4d;
typedef struct l4d* Line4d;

// Hyperplane definition
typedef struct hpl4d
{
    Point4d P1;
    Point4d P2;
    Point4d P3;
    Point4d P4;
} hpl4d;
typedef struct hpl4d* Hyperplane4d;

// Hypersphere definition
typedef struct hs4d
{
    Point4d Center;
    float Radius;
} hs4d;
typedef struct hs4d* Hypersphere4d;


#endif
