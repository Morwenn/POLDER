***************************************
:mod:`algorithm` --- Generic algorithms
***************************************

.. module:: algorithm

This module contains generic algorithms. Someof them are modeled on the
algorithms in the standard library header ``<algorithm>`` while some other
ones work on specific objects.

Range algorithms
----------------

These algorithms generally operate on pairs of iterators.

.. cpp:function:: UnaryOperation for_each(InputIt first, InputIt last, UnaryOperation unary_op)

    This function is a mere wrapper around ```std::for_each`_`` which works
    exactly the same way. It is provided for consistency with its binary
    version.

.. cpp:function:: BinaryOperation for_each(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)

    This function is a binary equivalent to ``std::for_each``. It applies a
    given operation to the elements obtained by dereferencing the iterators
    in the ranges ``[first1, last1)`` and ``[first2, first2 + last1 - first1)``.

Other algorithms
----------------

Miscellaneous algorithms, not range-based:

.. cpp:function:: int compare(const T& lhs, const U& rhs)

    This functions compares the values ``lhs`` and ``rhs`` and returns either
    0, 1 or -1 when the values are respectively in order, equal or in reverse
    order. It has efficient specializations for some standard types.

.. cpp:function:: constexpr bool float_equal(T lhs, T rhs)

    This function uses a mathematical function to check whether two values are
    close from each other. The returns whether the following relation holds:

    :math:`|lhs-rhs| \le \epsilon * max(|lhs|, |rhs|)`

    Where :math:`\epsilon` is ``std::numeric_limits<T>::epsilon()``.


.. std::for_each: http://en.cppreference.com/w/cpp/algorithm/for_each