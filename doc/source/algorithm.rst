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

    This function is a mere wrapper around ``std::for_each`` which works
    exactly the same way. It is provided for consistency with its binary
    version.

.. cpp:function:: BinaryOperation for_each(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)

    This function is a binary equivalent to ``std::for_each``. It applies a
    given operation to the elements obtained by dereferencing the iterators
    in the ranges ``[first1, last1)`` and ``[first2, first2 + last1 - first1)``.

.. cpp:function:: auto min_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp)

    This function is a fused algorithm which computes the smallest element in
    a range of elements and returns the corresponding iterator as well as a
    boolean value corresponding to whether the range is sorted or not. The
    return type is an unnamed ``struct`` with the following structure:

    .. code-block:: cpp

        struct
        {
            ForwardIt min;
            bool is_sorted;
        };

    The algorithm should perform exactly ``last - first`` comparisons. If the
    comparator ``comp`` is omitted, the algorithm uses a default-constructed
    instance of ``std::less<>``.

.. cpp:function:: auto max_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp)

    This function is a fused algorithm which computes the greatest element in
    a range of elements and returns the corresponding iterator as well as a
    boolean value corresponding to whether the range is sorted or not.  The
    return type is an unnamed ``struct`` with the following structure:

    .. code-block:: cpp

        struct
        {
            ForwardIt max;
            bool is_sorted;
        };

    The algorithm should perform exactly ``last - first`` comparisons. If the
    comparator ``comp`` is omitted, the algorithm uses a default-constructed
    instance of ``std::less<>``.

.. cpp:function:: auto min_element_and_is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)

    This function is a fused algorithm which computes the smallest element in
    a range of elements and returns the corresponding iterator as well as another
    one corresponding to one past the last sorted element. The return type is an
    unnamed ``struct`` with the following structure:

    .. code-block:: cpp

        struct
        {
            ForwardIt min;
            ForwardIt until;
        };

    The algorithm should perform exactly ``last - first`` comparisons. If ``comp``
    is omitted, the algorithm uses a default-constructed instance of ``std::less<>``.

.. cpp:function:: auto max_element_and_is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)

    This function is a fused algorithm which computes the greatest element in
    a range of elements and returns the corresponding iterator as well as another
    one corresponding to one past the last sorted element. The return type is an
    unnamed ``struct`` with the following structure:

    .. code-block:: cpp

        struct
        {
            ForwardIt max;
            ForwardIt until;
        };

    The algorithm should perform exactly ``last - first`` comparisons. If ``comp``
    is omitted, the algorithm uses a default-constructed instance of ``std::less<>``.

Other algorithms
----------------

Miscellaneous algorithms, not range-based:

.. cpp:function:: int compare(const T& lhs, const U& rhs)

    This functions compares the values ``lhs`` and ``rhs`` and returns either
    0, 1 or -1 when the values are respectively in order, equal or in reverse
    order. It has efficient specializations for some standard types.
