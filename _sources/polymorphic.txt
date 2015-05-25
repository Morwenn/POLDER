************************************************************
:mod:`polymorphic` --- Concept-based polymorphic collections
************************************************************

.. module:: polymorphic

This module contains collection classes based on the standard library collections
which implement concept-based polymorphism, a powerful mechanism that allows to
call functions in unrelated classes in a polymorphic way even though they don't
inherit frm a common base.


Concept-based polymorphism example
----------------------------------

There's nothing better than a simple example to introduce a new topic. Let's say
you have a basic class ``Shape`` and two derived classes ``Circle`` and ``Rectangle``
that have some ``virtual`` functions for the sake of the example:

    .. code-block:: cpp
    
        struct Shape
        {
            virtual std::string name() const = 0;

            virtual ~Shape() {};
        };

        struct Circle:
            Shape
        {
            Circle(int /* x */, int /* y */, int /* radius */) {}

            virtual std::string name() const override
            {
                return "Circle"s;
            }
        };

        struct Rectangle:
            Shape
        {
            Rectangle(int /* x */, int /* y */, int /* height */, int /* width */) {}

            virtual std::string name() const override
            {
                return "Rectangle"s;
            }
        };

Now if you want to store these classes in a sequence and call the right functions,
you would have to store pointers in the first place or use a class such as ``boost::ptr_vector``.
The collections proposed in this module allow not only to have reference semantics
instead of pointer semantics but they don't even require that ``Circle`` and ``Rectangle``
inherit from ``Shape``. They only require that these classes have consistent names
and that you write a small adapter class so that everything works fine. Let's keep our
``Shape`` class and reimplement ``Circle`` and ``Rectangle``:

    .. code-block:: cpp

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

Now let's write a ``ShapeAdapter`` which will tell how to adapt any class satisfying
the ``Shape`` concept or interface into a real ``Shape``:

    .. code-block:: cpp
        
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

As you can see, this very basic adapter simply wraps any class and calls the method
``name`` from this class whenever its own method ``name`` is called. While this is
the most simple behaviour, it might be changed to do more complicated things if needed.
Now, we can use a polymorphic collection which will actually store instances of this
``ShapeAdapter`` and make it look like ``Circle`` and ``Rectangle`` actually inherit
from ``Shape``:

    .. code-block:: cpp

        int main()
        {
            // Create a collection, feed it the class to be used as
            // an interface and the class to adapt ther classes to
            // this interface
            polymorphic::vector<Shape, ShapeAdapter> shapes;

            // Add elements at the end
            shapes.emplace_back<Circle>(1, 2, 3);
            shapes.push_back(Rectangle(4, 5, 6, 7));

            // Add elements wherever we want to
            shapes.emplace<Rectangle>(shapes.begin(), 8, 9, 10, 11);
            shapes.insert(shapes.end(), Circle(12, 13, 14));

            // Print the name of the wrapped classes, effectively
            // calling Circle::name and Rectangle::name when needed
            for (const Shape& shape: shapes)
            {
                std::cout << shape.name() << '\n';
            }
        }

While the underlying class actually uses and ``std::vector<std::unique_ptr<Shape>>``,
it is totally hidden to users of the class which can use it with nice reference
semantics. One thing to remember though is that these collections do not have a
``value_type`` type since there would be no sane way to pick such a type without
creating confusion. 
