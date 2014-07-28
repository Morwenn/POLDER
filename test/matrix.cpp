/*
 * Copyright (C) 2011-2014 Morwenn
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
#include <POLDER/index.h>
#include <POLDER/itertools.h>
#include <POLDER/matrix.h>
#include <POLDER/rational.h>

int main()
{
    using namespace polder;

    // TEST: constructors/basic properties
    // - Default constructor
    // - std::initializer_list constructors
    // - Size constructors
    // - Copy constructor
    // - Move constructor
    // - height/width
    // - size
    // - dimensions
    // - min/max
    // - sum
    {
        // Default constructor
        Matrix<int> a;
        POLDER_ASSERT(a.height() == 0);
        POLDER_ASSERT(a.width() == 0);
        POLDER_ASSERT(a.size() == 0);

        // Initializer_list constructors
        Matrix<int> b = { 1, 2, 3, 4 };
        POLDER_ASSERT(b.height() == 1);
        POLDER_ASSERT(b.width() == 4);
        POLDER_ASSERT(b.size() == 4);

        Matrix<int> c = {
            { 2, 3, 8, 6 },
            { 8, -9, 52, 3 },
            { -9, -5555, 1, 2 },
            { 2, -87, 56, 9 }
        };
        POLDER_ASSERT(c.height() == 4);
        POLDER_ASSERT(c.width() == 4);
        POLDER_ASSERT(c.size() == 16);

        std::pair<size_t, size_t> dim = { 4, 4 };
        POLDER_ASSERT(c.dimensions() == dim);

        // Copy constructor
        Matrix<int> d = c;
        POLDER_ASSERT(d.height() == 4);
        POLDER_ASSERT(d.width() == 4);
        POLDER_ASSERT(d.size() == 16);

        // Move constructor
        Matrix<int> e = std::move(d);
        POLDER_ASSERT(e.height() == 4);
        POLDER_ASSERT(e.width() == 4);
        POLDER_ASSERT(e.size() == 16);

        // Constructors with size (uninitialized values)
        Matrix<size_t> f(5, 6);
        POLDER_ASSERT(f.height() == 5);
        POLDER_ASSERT(f.width() == 6);
        POLDER_ASSERT(f.size() == 30);
        Matrix<short> g(8);
        POLDER_ASSERT(g.height() == 1);
        POLDER_ASSERT(g.width() == 8);
        POLDER_ASSERT(g.size() == 8);

        // min/max/sum
        POLDER_ASSERT(b.min() == 1);
        POLDER_ASSERT(b.max() == 4);
        POLDER_ASSERT(b.sum() == 10);
        POLDER_ASSERT(c.min() == -5555);
        POLDER_ASSERT(c.max() == 56);
        POLDER_ASSERT(c.sum() == -5508);
    }

    // TEST: element access
    // - operator[]
    // - operator()
    // - at
    // - front/back
    {
        Matrix<int> a = {
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 }
        };

        // Assignment
        a[1][1] = 99;       // C arrays syntax
        a.at(2, 2) = 85;    // function at()
        a(0, 0) = 8;        // Matlab syntax
        a[{1, 2}] = 63;     // polder::index

        // Value tests
        POLDER_ASSERT(a.at(1, 1) == 99);
        POLDER_ASSERT(a[2][2] == 85);
        POLDER_ASSERT(a(0, 0) == 8);
        POLDER_ASSERT(a[{1,2}] == 63);

        // front/back
        POLDER_ASSERT(a.front() == 8);
        POLDER_ASSERT(a.back() == 85);

        // Full matrix indexing test
        for (std::size_t i = 0 ; i < a.height() ; ++i)
        {
            for (std::size_t j = 0 ; j < a.width() ; ++j)
            {
                int val = a[i][j];
                POLDER_ASSERT(val == a.at(i, j));
                POLDER_ASSERT(val == a[{i, j}]);
                POLDER_ASSERT(val == a(i, j));
            }
        }
    }

    // TEST: matrix equality
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 0, 2, 1 },
            { 1, -3, 5 }
        };
        auto c = b;

        POLDER_ASSERT(c == b);
        POLDER_ASSERT(a != b);
        POLDER_ASSERT(c != a);
    }

    // TEST: matrix addition
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 0, 2, 1 },
            { 1, -3, 5 }
        };
        Matrix<int> c = {
            { 1, 7, -1 },
            { 3, -3, 6 }
        };
        POLDER_ASSERT(a+b == c);
    }

    // TEST: matrix subtraction
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 0, 2, 1 },
            { 1, -3, 5 }
        };
        Matrix<int> c = {
            { 1, 3, -3 },
            { 1, 3, -4 }
        };
        POLDER_ASSERT(a-b == c);
    }

    // TEST: matrix transpose
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 1, 2 },
            { 5, 0 },
            { -2, 1 }
        };
        POLDER_ASSERT(transpose(a) == b);
    }

    // TEST: matrix/scalar multiplication
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 5, 25, -10 },
            { 10, 0, 5 }
        };
        POLDER_ASSERT(5*a == b);
        POLDER_ASSERT(a*5 == b);
        POLDER_ASSERT(5*a == a*5);
    }

    // TEST: matrix/matrix multiplication
    {
        Matrix<int> a = {
            { 1, 3, 2 },
            { 5, 7, 4 }
        };
        Matrix<int> b = {
            { 4, -2 },
            { 1, 0 },
            { -1, 4 }
        };
        Matrix<int> c = {
            { 5, 6 },
            { 23, 6 }
        };
        POLDER_ASSERT(a*b == c);

        Matrix<int> d = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> e = {
            { 0, 2 },
            { 1, -1 },
            { 2, 4 }
        };
        Matrix<int> f = {
            { 1, -11 },
            { 2, 8 }
        };
        POLDER_ASSERT(d*e == f);

        // Associativity
        POLDER_ASSERT(a*b*c == (a*b)*c);
        POLDER_ASSERT(d*e*f == (d*e)*f);

        // Distributivity
        POLDER_ASSERT(a*(b+e) == a*b + a*e);
    }

    // TEST: miscellaneous matrix operations
    // - is_square
    // - is_invertible
    // - determinant
    // - adjugate
    // - transpose
    // - inverse
    {
        using namespace polder;

        Matrix<rational<int>> a = {
            { 1_r, 2_r, -1_r },
            { -2_r, 1_r, 1_r },
            { 0_r, 3_r, -3_r }
        };
        Matrix<rational<int>> b = {
            { -6_r, -6_r, -6_r },
            { 3_r, -3_r, -3_r },
            { 3_r, 1_r, 5_r }
        };
        Matrix<rational<int>> c = {
            { -6_r, 3_r, 3_r },
            { -6_r, -3_r, 1_r },
            { -6_r, -3_r, 5_r }
        };
        Matrix<rational<int>> d = {
            { {1,2}, {-1,4}, {-1,4} },
            { {1,2}, {1,4}, {-1,12} },
            { {1,2}, {1,4}, {-5,12} }
        };

        POLDER_ASSERT(a.is_square());
        POLDER_ASSERT(a.is_invertible());
        POLDER_ASSERT(determinant(a) == -12);
        POLDER_ASSERT(adjugate(a) == b);
        POLDER_ASSERT(transpose(b) == c);
        POLDER_ASSERT(make_rational(-1, 12) * c == d);
        POLDER_ASSERT(inverse(a) == d);
    }

    // TEST: static construction and flat iterators
    {
        using polder::itertools::flat;

        auto a = Matrix<int>::zeros(5, 8);
        for (int val: flat(a))
        {
            POLDER_ASSERT(val == 0);
        }
    }
}
