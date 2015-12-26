/*
 * Copyright (C) 2014-2015 Morwenn
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
#include <utility>
#include <catch.hpp>
#include <POLDER/polymorphic/vector.h>
#include "shapes.h"

using namespace polder;

////////////////////////////////////////////////////////////
// Insertion tests

SCENARIO( "insertion in a vector of shapes", "[polymorphic][vector]" )
{
    GIVEN( "an empty vector of shapes" )
    {
        polymorphic::vector<Shape, ShapeAdapter> shapes;

        WHEN( "we add a Circle" )
        {
            shapes.emplace_back<Circle>(2, 2, 8);

            THEN( "the first shape is a Circle" )
            {
                CHECK( shapes.at(0).name() == "Circle" );
                CHECK( shapes[0].name() == "Circle" );
                CHECK( shapes.front().name() == "Circle" );
                CHECK( shapes.back().name() == "Circle" );
                CHECK( shapes.begin()->name() == "Circle" );
                CHECK( shapes.cbegin()->name() == "Circle" );
            }
        }

        WHEN( "we add a Circle and a Rectangle" )
        {
            shapes.emplace_back<Circle>(2, 2, 8);
            shapes.emplace_back<Rectangle>(1, 2, 3, 4);

            THEN( "the first shape is a Circle" )
            {
                CHECK( shapes.begin()->name() == "Circle" );
                CHECK( shapes.cbegin()->name() == "Circle" );
            }

            THEN( "the second shape is a Rectangle" )
            {
                CHECK( shapes.at(1).name() == "Rectangle" );
                CHECK( shapes[1].name() == "Rectangle" );
                CHECK( shapes.back().name() == "Rectangle" );
                CHECK( (++shapes.begin())->name() == "Rectangle" );
                CHECK( (++shapes.cbegin())->name() == "Rectangle" );
            }
        }

        WHEN( "we push a Rectangle" )
        {
            auto rec = Rectangle(7, 8, 9, 10);
            shapes.push_back(rec);

            THEN( "the first shape is a Rectangle" )
            {
                CHECK( shapes.begin()->name() == "Rectangle" );
                CHECK( shapes.cbegin()->name() == "Rectangle" );
            }
        }
    }
}

////////////////////////////////////////////////////////////
// Deletion tests

SCENARIO( "deletion from a vector of shapes", "[polymorphic][vector]" )
{
    GIVEN( "a non-empty vector of shapes" )
    {
        polymorphic::vector<Shape, ShapeAdapter> shapes;
        shapes.emplace_back<Circle>(2, 2, 8);
        shapes.emplace_back<Rectangle>(2, 2, 8, 5);
        shapes.emplace_back<Circle>(2, 2, 8);

        WHEN( "we remove the first element" )
        {
            shapes.erase(shapes.begin());

            THEN( "there are less elements" )
            {
                CHECK( shapes.size() == 2 );
                CHECK( shapes[0].name() == "Rectangle" );
                CHECK( shapes[1].name() == "Circle" );
            }
        }

        WHEN( "we remove the last element" )
        {
            shapes.pop_back();

            THEN( "there are less elements" )
            {
                CHECK( shapes.size() == 2 );
                CHECK( shapes[0].name() == "Circle" );
                CHECK( shapes[1].name() == "Rectangle" );
            }
        }

        WHEN( "we remove every element" )
        {
            shapes.erase(shapes.begin(), shapes.end());

            THEN( "the vector becomes empty" )
            {
                CHECK( shapes.is_empty() );
                CHECK( shapes.size() == 0 );
            }
        }
    }
}

////////////////////////////////////////////////////////////
// Moving tests

SCENARIO( "moving a vector of shapes", "[polymorphic][vector]" )
{
    GIVEN( "a non-empty vector of shapes" )
    {
        polymorphic::vector<Shape, ShapeAdapter> shapes;
        shapes.emplace_back<Circle>(2, 2, 8);
        shapes.emplace_back<Rectangle>(2, 2, 8, 5);
        shapes.emplace_back<Circle>(2, 2, 8);

        WHEN( "we move-construct another vector from it" )
        {
            polymorphic::vector<Shape, ShapeAdapter> new_shapes = std::move(shapes);

            THEN( "the elements are moved into the new vector" )
            {
                CHECK( new_shapes[0].name() == "Circle" );
                CHECK( new_shapes[1].name() == "Rectangle" );
                CHECK( new_shapes[2].name() == "Circle" );

                CHECK( new_shapes.size() == 3 );
                CHECK( shapes.is_empty() );
            }
        }

        WHEN( "we move-assign it to another vector" )
        {
            polymorphic::vector<Shape, ShapeAdapter> new_shapes;
            new_shapes = std::move(shapes);

            THEN( "the elements are moved into the new vector" )
            {
                CHECK( new_shapes[0].name() == "Circle" );
                CHECK( new_shapes[1].name() == "Rectangle" );
                CHECK( new_shapes[2].name() == "Circle" );

                CHECK( new_shapes.size() == 3 );
                CHECK( shapes.is_empty() );
            }
        }
    }
}

////////////////////////////////////////////////////////////
// Swapping tests

SCENARIO( "swapping two vectors of shapes", "[polymorphic][vector]" )
{
    GIVEN( "two vectors of shapes" )
    {
        polymorphic::vector<Shape, ShapeAdapter> shapes1;
        shapes1.emplace_back<Circle>(2, 2, 8);
        shapes1.emplace_back<Rectangle>(2, 2, 8, 5);
        shapes1.emplace_back<Circle>(2, 2, 8);

        polymorphic::vector<Shape, ShapeAdapter> shapes2;
        shapes2.emplace_back<Rectangle>(2, 2, 8, 1);
        shapes2.emplace_back<Circle>(2, 2, 8);
        shapes2.emplace_back<Rectangle>(2, 2, 8, 48);

        WHEN( "we swap the vectors" )
        {
            using polymorphic::swap;
            swap(shapes1, shapes2);

            THEN( "the elements are swapped" )
            {
                CHECK( shapes1[0].name() == "Rectangle" );
                CHECK( shapes1[1].name() == "Circle" );
                CHECK( shapes1[2].name() == "Rectangle" );

                CHECK( shapes2[0].name() == "Circle" );
                CHECK( shapes2[1].name() == "Rectangle" );
                CHECK( shapes2[2].name() == "Circle" );
            }
        }
    }
}
