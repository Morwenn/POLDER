/*
 * Copyright (C) 2015 Morwenn
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
#include "catch.hpp"

using namespace polder;

TEST_CASE( "matrix", "[matrix]" )
{
    SECTION( "basic properties" )
    {
        // Default constructor
        Matrix<int> a;
        CHECK( a.height() == 0 );
        CHECK( a.width() == 0 );
        CHECK( a.size() == 0 );

        // Initializer_list constructors
        Matrix<int> b = { 1, 2, 3, 4 };
        CHECK( b.height() == 1 );
        CHECK( b.width() == 4 );
        CHECK( b.size() == 4 );

        Matrix<int> c = {
            { 2, 3, 8, 6 },
            { 8, -9, 52, 3 },
            { -9, -5555, 1, 2 },
            { 2, -87, 56, 9 }
        };
        CHECK( c.height() == 4 );
        CHECK( c.width() == 4 );
        CHECK( c.size() == 16 );

        std::pair<size_t, size_t> dim = { 4, 4 };
        CHECK( c.dimensions() == dim );

        // Copy constructor
        Matrix<int> d = c;
        CHECK( d.height() == 4 );
        CHECK( d.width() == 4 );
        CHECK( d.size() == 16 );

        // Move constructor
        Matrix<int> e = std::move(d);
        CHECK( e.height() == 4 );
        CHECK( e.width() == 4 );
        CHECK( e.size() == 16 );

        // Constructors with size (uninitialized values)
        Matrix<size_t> f(5, 6 );
        CHECK( f.height() == 5 );
        CHECK( f.width() == 6 );
        CHECK( f.size() == 30 );
        Matrix<short> g(8);
        CHECK( g.height() == 1 );
        CHECK( g.width() == 8 );
        CHECK( g.size() == 8 );

        // min/max/sum
        CHECK( b.min() == 1 );
        CHECK( b.max() == 4 );
        CHECK( b.sum() == 10 );
        CHECK( c.min() == -5555 );
        CHECK( c.max() == 56 );
        CHECK( c.sum() == -5508 );
    }

    SECTION( "elements access" )
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
        CHECK( a.at(1, 1) == 99 );
        CHECK( a[2][2] == 85 );
        CHECK( a(0, 0) == 8 );
        CHECK( (a[{1,2}]) == 63 );

        // front/back
        CHECK( a.front() == 8 );
        CHECK( a.back() == 85 );

        // Full matrix indexing test
        for (std::size_t i = 0 ; i < a.height() ; ++i)
        {
            for (std::size_t j = 0 ; j < a.width() ; ++j)
            {
                int val = a[i][j];
                CHECK( val == a.at(i, j) );
                CHECK( val == (a[{i, j}]) );
                CHECK( val == a(i, j) );
            }
        }
    }

    SECTION( "comparison operators" )
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

        CHECK( c == b );
        CHECK( a != b );
        CHECK( c != a );
    }

    SECTION( "addition" )
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
        CHECK( a + b == c );
    }

    SECTION( "subtraction" )
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
        CHECK( a - b == c );
    }

    SECTION( "transpose" )
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
        CHECK( transpose(a) == b );
        CHECK( transpose(b) == a );
    }

    SECTION( "matrix/scalar multiplication" )
    {
        Matrix<int> a = {
            { 1, 5, -2 },
            { 2, 0, 1 }
        };
        Matrix<int> b = {
            { 5, 25, -10 },
            { 10, 0, 5 }
        };
        CHECK( 5 * a == b );
        CHECK( a * 5 == b );
        CHECK( 5 * a == a * 5 );
    }

    SECTION( "matrix/matrix multiplication" )
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
        CHECK( a * b == c );

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
        CHECK( d * e == f );

        // Associativity
        CHECK( a * b * c == (a * b) * c );
        CHECK( d * e * f == (d * e) * f );

        // Distributivity
        CHECK( a * (b + e) == a*b + a*e );
    }

    SECTION( "miscellaneous operations" )
    {
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

        CHECK( a.is_square() );
        CHECK( a.is_invertible() );
        CHECK( determinant(a) == -12 );
        CHECK( adjugate(a) == b );
        CHECK( transpose(b) == c );
        CHECK( make_rational(-1, 12) * c == d );
        CHECK( inverse(a) == d );
    }

    SECTION( "flat iterators" )
    {
        using polder::itertools::flat;

        auto a = Matrix<int>::zeros(5, 8);
        for (int val: flat(a))
        {
            CHECK( val == 0 );
        }
    }
}

