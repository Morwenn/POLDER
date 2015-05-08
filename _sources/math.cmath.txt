:mod:`cmath` --- Common mathematical functions
==============================================

.. module:: cmath

The functions in the :mod:`cmath` module are meant to mimic the ones from
the ``<cmath>`` standard library header. The main difference is that they
all live in the subnamespace ``polder::math::meta`` and are explicitly meant
to be used at compile time.

Some of the functions in this module are less versatile than their ``<cmath>``
counterparts (*e.g.* *pow*) while some of them are more versatile (*e.g*
*min* and *max*). Since the functions are generic, the original names
have been stripped from their type-specific prefixes and suffixes.


Basic functions
---------------

.. cpp:function:: constexpr Number math::meta::abs(Number x)

    Return the absolute value of *x*.

.. cpp:function:: constexpr CommonType math::meta::min(T first, U second, Rest... rest)

    Return the smallest of two or more arguments. If the arguments have different types,
    the result type will be the common type of the different arguments,
    ``std::common_type_t<T, U, Rest...>``.

.. cpp:function:: constexpr CommonType math::meta::max(T first, U second, Rest... rest)

    Return the largest of two or more arguments. If the arguments have different types,
    the result type will be the common type of the different arguments,
    ``std::common_type_t<T, U, Rest...>``.


Number-theoretic and representation functions
---------------------------------------------

.. cpp:function:: constexpr Float math::meta::floor(Float x)

    Return the nearest integer not greater than *x*.

.. cpp:function:: constexpr Float math::meta::ceil(Float x)

    Return the nearest integer not less than *x*.

.. cpp:function:: constexpr Float math::meta::round(Float x)

    Return the nearest integer to *x*, rounding away from zero in halfway cases.

.. cpp:function:: constexpr Float math::meta::trunc(Float x)

    Return the nearest integer not greater in magnitude than *x*.


Power and logarithmic functions
-------------------------------

.. cpp:function:: constexpr CommonType math::meta::pow(T value, Integer exponent)

    Return *value* raised to the power *exponent*.

.. cpp:function:: constexpr Float math::meta::sqrt(Float x)

    Return the square root of *x*.
    
    *Precondition:* ``x >= 0``.
