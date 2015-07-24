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
#include <utility>

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
        return "Circle";
    }
};

struct Rectangle
{
    Rectangle(int /* x */, int /* y */, int /* height */, int /* width */) {}

    std::string name() const
    {
        return "Rectangle";
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
