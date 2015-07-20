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
#include <string>
#include <POLDER/polymorphic/vector.h>
#include "catch.hpp"

using namespace std::string_literals;
using namespace polder;

////////////////////////////////////////////////////////////
// Non-polymorphic shapes

struct Shape
{
    virtual std::string name() const = 0;

    virtual ~Shape() {};
};

struct Circle
{
    Circle(int /* x */, int /* y */, int /* radius */) {}

    std::string name() const
    {
        return "Circle"s;
    }
};

struct Rectangle
{
    Rectangle(int /* x */, int /* y */, int /* height */, int /* width */) {}

    std::string name() const
    {
        return "Rectangle"s;
    }
};

////////////////////////////////////////////////////////////
// Polymorphic shape adapter

template<typename T>
struct ShapeAdapter:
    Shape
{
    template<typename... Args>
    ShapeAdapter(Args&&... args):
        data(std::forward<Args>(args)...)
    {}

    virtual std::string name() const override
    {
        return data.name();
    }

    T data;
};

////////////////////////////////////////////////////////////
// Actual tests

SCENARIO( "vector of shapes", "[polymorphic][vector]" )
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
