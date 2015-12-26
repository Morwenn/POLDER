***********************************
:mod:`iterator` --- Fancy iterators
***********************************

.. module:: iterator

This module contains additional iterators modeled after the ones found in the standard
library. New kinds of iterators are added to the library when there is a need for them
in the library itself. While they are not fully documented here, every new iterator has
a corresponding ``make_*`` factory function to hide away the template parameters.

Transforming iterator
---------------------

This iterator is close to its equivalent in Boost: it takes an iterator and a function,
and applies the function to the dereferenced original iterators whenever it is itself
dereferenced. It allows to apply a small transformation on-the-fly whenever it comes in
handy.

.. cpp:class:: transform_iterator<Iterator, UnaryFunction>

The interface is almost exactly the same, so if you need additional documentation for
this iterator, you can refer to the `Boost documentation`_, but be careful: POLDER's
implementation contains a bit less tricks and the order of the template parameters is
not the same (it is iterator first). Unlike Boost, we perform the empty base class
optimization when the function is an empty object.

``transform_iterator`` has two sepcializations in the same module: ``indirect_iterator``
to iterator over a collection of pointers, and ``get_iterator`` to iterator over
collections of tuple-like objects while we only care about one of the returned values.
Here are the corresponding implementations (the structures ``indirection`` and ``getter``
are not available):

.. code-block:: cpp

    struct indirection
    {
        template<typename T>
        auto operator()(T&& arg) const
            -> decltype(*std::forward<T>(arg))
        {
            return *std::forward<T>(arg);
        }
    };

    template<typename Iterator>
    using indirect_iterator = transform_iterator<Iterator, indirection>;

    template<std::size_t N>
    struct getter
    {
        template<typename T>
        auto operator()(T&& arg) const
            -> decltype(std::get<N>(std::forward<T>(arg)))
        {
            return std::get<N>(std::forward<T>(arg));
        }
    };

    template<std::size_t N, typename Iterator>
    using get_iterator = transform_iterator<Iterator, getter<N>>;

Strided iterator
----------------

``stride_iterator`` takes an iterator and a stride which will be used so that incrementing
or decrementing the iterator by 1 will actually increment or decrement it by the stride.
It is the user's responsability to make sure that the stride won't ever pass the ``end``
iterator.

.. cpp:class:: stride_iterator<Iterator, Distance>


.. _Boost documentation: http://www.boost.org/doc/libs/1_60_0/libs/iterator/doc/transform_iterator.html
