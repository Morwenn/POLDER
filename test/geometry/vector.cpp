/*
 * Copyright (C) 2014 Morwenn
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
#include <POLDER/algorithm.h>
#include <POLDER/geometry/vector.h>

int main()
{
    using namespace polder;

    // TEST: Vector basic operations
    // - construction
    // - indexing
    // relational operators
    {
        using Vector = geometry::Vector<2u, int>;

        Vector a(48, 23);
        POLDER_ASSERT(a[0] == 48);
        POLDER_ASSERT(a[1] == 23);
        POLDER_ASSERT(a.x() == 48);
        POLDER_ASSERT(a.y() == 23);
        POLDER_ASSERT(*(a.begin()) == 48);

        Vector b = { 48, 23 };
        POLDER_ASSERT(b[0] == 48);
        POLDER_ASSERT(b[1] == 23);
        POLDER_ASSERT(b.x() == 48);
        POLDER_ASSERT(b.y() == 23);
        POLDER_ASSERT(*(b.begin()) == 48);

        POLDER_ASSERT(a == b);
        POLDER_ASSERT(not (a != b));
        POLDER_ASSERT(Vector(2, 3) != a);

        Vector foo;
        POLDER_ASSERT(foo.x() == 0);
        POLDER_ASSERT(foo.y() == 0);
    }

    // TEST: Vector-scalar multiplication
    {
        using Vector = geometry::Vector<2u, int>;

        Vector a = { 3, 5 };

        POLDER_ASSERT(2*a == Vector(6, 10));
        POLDER_ASSERT(a*3 == Vector(9, 15));
        POLDER_ASSERT(a*15 == 15*a);
    }

    // TEST: Vector-scalar division
    {
        using Vector = geometry::Vector<2u, int>;

        Vector a = { 12, 6 };

        POLDER_ASSERT(a/2 == Vector(6, 3));
        POLDER_ASSERT(a/3 == Vector(4, 2));
        POLDER_ASSERT(a/2*2 == a);
        POLDER_ASSERT(a == 3*a/3);
    }

    // TEST: dot product
    {
        using Vector2 = geometry::Vector<2u, int>;
        using Vector3 = geometry::Vector<3u, int>;

        Vector3 a = { 1, 3, -5 };
        Vector3 b = { 4, -2, -1 };
        POLDER_ASSERT(a*b == 3);
        POLDER_ASSERT(a*b == b*a);

        Vector3 c = { 1, 2, 3 };
        Vector3 d = { 4, -5, 6 };
        POLDER_ASSERT(c*d == 12);

        Vector2 e = { -4, -9 };
        Vector2 f = { -1, 2 };
        POLDER_ASSERT(e*f == -14);
    }

    // TEST: Vector arithmetic
    // - addition
    // - subtraction
    // - opposite
    {
        using Vector = geometry::Vector<2u, int>;

        Vector a = { 2, 3 };
        Vector b = { 6, 8 };

        POLDER_ASSERT(-a == Vector(-2, -3));
        POLDER_ASSERT(-b == Vector(-6, -8));
        POLDER_ASSERT(a+b == Vector(8, 11));
        POLDER_ASSERT(a+b == b+a);
        POLDER_ASSERT(b-a == Vector(4, 5));
        POLDER_ASSERT(a-b == Vector(-4, -5));
        POLDER_ASSERT(b-a == -(a-b));
        POLDER_ASSERT(a-b == a+(-b));
    }

    // TEST: Vector norms
    {
        using polder::float_equal;
        using namespace polder::geometry;
        using namespace polder::math::norm;

        Vector<3u> test = { 4.0, -2.0, 6.0 };

        POLDER_ASSERT(float_equal(
            test.norm(), test.norm<euclidean>()
        ));
        POLDER_ASSERT(float_equal(
            test.norm<manhattan>(), 12.0
        ));
        POLDER_ASSERT(float_equal(
            test.norm<euclidean>(), 7.483314773547883
        ));
        POLDER_ASSERT(float_equal(
            test.norm<maximum>(), 6.0
        ));

        POLDER_ASSERT(test.norm(3u) == test.norm<p>(3u));
        POLDER_ASSERT(float_equal(
            test.norm<p>(3u), 6.603854497789253
        ));
        POLDER_ASSERT(float_equal(
            test.norm<p>(5u), 6.154769770788126
        ));
    }
}
