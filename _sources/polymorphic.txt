**********************************************
:mod:`polymorphic` --- Polymorphic collections
**********************************************

.. module:: polymorphic

This module contains collection classes based on the standard library collections
which are meant to store instances of polymorphic types. Through the ``Adapter``
template template parameter, they allow to use regular polymorphism but also to
automagically adapt the stored types and implement concept-based polymorphism.

Every class in this module lives in the namespace ``polder::polymorphism``. The
collection classes all follow the same general design:

.. code-block:: cpp

    template<
        typename Interface,
        template<typename> class Adapter = default_adapter
    >
    class collection
    {
        // ...
    };

In this class, the template parameter ``Interface`` corresponds to the class
describing the concept or interface that the stored types must satisfy. With the
default adapter, it means that every type whose instances are stored in the
collection must derive from ``Interface``. It becomes a bit more subtle when we
use custom adapters, so we will come back to this in the part about concept-based
polymorphism.

The collection classes are design to be as close as possible from the standard
library collection classes, so learning how to use them should be straightforward
for anyone already using the standard library. There are however a few differences
that you should know about:

* There is no ``value_type`` member in the polymorphic collections. That is because
  it would be impossible to sanely alias any type. We don't want to alias ``Interface``
  because it is generally an abstract class but it wouldn't mean anything to alias
  ``Interface&`` or ``Interface*`` either. We decided to avoid any surprise due to
  one assumption or another and to simply remove ``value_type``.

* The ``emplace_*`` family of functions takes an additional template parameter so
  it knows which type it has to construct and add to the collection. We generally
  want to construct an instance of a derived type and this additional type parameter
  is there for that.

* The collections currently don't handle custom allocators but that could be a future
  direction for the module.

Regular polymorphism
--------------------

At first, we will ignore the ``Adapter`` template template parameter and focus on
the first use case of polymorphic collections: store instances of polymorphic types.
So, let's write a simple hierarchy of shapes:

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
            return "Circle";
        }
    };

    struct Rectangle:
        Shape
    {
        Rectangle(int /* x */, int /* y */, int /* height */, int /* width */) {}

        virtual std::string name() const override
        {
            return "Rectangle";
        }
    };

Nothing new here: we have a very simple hierarchy with a base class ``Shape``
and two subclasses that reimplement the method ``name``. Here is an example
using a ``polymorphic::vector<Shape>`` to demonstrate how simple it is to
add anything derived from ``Shape`` into it:

.. code-block:: cpp

    int main()
    {
        // Create a collection, feed it the base class used by every
        // type whose instances will be stored
        polder::polymorphic::vector<Shape> shapes;

        // Add elements at the end of the collection
        shapes.emplace_back<Circle>(1, 2, 3);
        shapes.push_back(Rectangle(4, 5, 6, 7));

        // Insert elements wherever we want to
        shapes.emplace<Rectangle>(shapes.begin(), 8, 9, 10, 11);
        shapes.insert(shapes.end(), Circle(12, 13, 14));

        // Print the name of the class of the stored instances, effectively
        // calling Circle::name and Rectangle::name when needed
        for (const Shape& shape: shapes)
        {
            std::cout << shape.name() << '\n';
        }
    }

As you can see, using such a class is merely as easy as using a standard library
collection. Be careful however that you always use reference or pointer semantics.
Raw value semantics don't well with polymorphism so you could be up to get unlucky.
        
Concept-based polymorphism
--------------------------

Concept-based polymorphism is a powerful mechanism that allows to store instances
of several types in our polymorphic collections as long as they satisfy the concept
of the ``Interface`` class. In other words, you can store them as long as you know
how to adapt them so that they are compatible with the ``virtual`` methods of the
``Interface`` class without even having them actually derive from ``Interface``.
To make it easier to understand, let's take our shapes from before and strip them
from their base class:

.. code-block:: cpp

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

The ``polymorphic`` module will still allow you to store instances of these classes into
its collections as long as you know how to write the corresponding adapter. Fortunately,
it's quite easy to write for such a simple ``Interface`` class. Here is a ``ShapeAdapter``:

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

This ``ShapeAdapter`` does three things:

* It stores an instance of ``T``, which would be an instance of ``Rectangle`` or ``Circle``
  in our case.

* It forwards everything it is constructed with to the constructor of the wrapped type so
  that the ``emplace_*`` family of functions work like a charm.

* It It reimplements the ``virtual`` functions from ``Shape`` so that every reimplemented
  function calls the function with the same name in the wrapped class.

Now, we can rewrite the first examples with our new ``Circle`` and ``Rectangle`` classes
and let the ``ShapeAdapter`` do its job to call the appropriate functions:

.. code-block:: cpp

    int main()
    {
        // Create a collection, feed it the class to be used as
        // an interface and the class to adapt other classes to
        // this interface
        polder::polymorphic::vector<Shape, ShapeAdapter> shapes;

        // Add elements at the end of the collection
        shapes.emplace_back<Circle>(1, 2, 3);
        shapes.push_back(Rectangle(4, 5, 6, 7));

        // Insert elements wherever we want to
        shapes.emplace<Rectangle>(shapes.begin(), 8, 9, 10, 11);
        shapes.insert(shapes.end(), Circle(12, 13, 14));

        // Print the name of the class of the stored instances, effectively
        // calling Circle::name and Rectangle::name when needed
        for (const Shape& shape: shapes)
        {
            std::cout << shape.name() << '\n';
        }
    }

With a single adapter, we managed to transform a non-polymorphic but consistent family
of classes so that they can be stored and used *as if* they all derived from a same
given base class. While adapters were originally design to implement concept-based
polymorphism, they are actually a much more powerful mechanism and allow to add some
common features to a consistent family of classes.
