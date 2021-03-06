:mod:`formula` --- Miscellaneous mathematical formula
=====================================================

.. module:: formula

This module contains miscellaneous mathematical formula is various
areas of mathematics. Most of them exist because they are needed in
the implementations of other POLDER modules.


Basic functions
---------------

.. cpp:function:: int math::sign(Number x)

    Signum function: :math:`\mathrm{sign}(x) = \begin{cases} -1 & \text{if } x < 0, \\ 0 & \text{if } x = 0, \\ 1 & \text{if } x > 0. \end{cases}`.

.. cpp:function:: CommonType math::sum(T first, U second, Rest... rest)

    Return the sum of two or more arguments. If the arguments have different
    types, the result type will be the common type of the different arguments,
    ``std::common_type_t<T, U, Rest...>``.

.. cpp:function:: CommonType math::mean(Numbers... args)

    Return the mean of two or more arguments. If the arguments have different
    types, the result type will be the common type of the different arguments,
    ``std::common_type_t<Numbers...>``.

.. cpp:function:: Number math::sqr(Number x)

    Return the square of *x*: :math:`x*x`.

.. cpp:function:: Number math::clamp(Number x, Number min, Number max)

    Return *x*, `clamped`_ between *min* and *max*.

    
Integer-related functions
-------------------------
    
.. cpp:function:: bool math::is_even(Integer n)

    Return whether *n* is an even number.

.. cpp:function:: bool math::is_odd(Integer n)

    Return whether *n* is an odd number.

.. cpp:function:: bool math::is_prime(Unsigned n)

    Return whether *n* is a prime number.

.. cpp:function:: Unsigned math::prime(Unsigned n)

    Return the nth prime number.

.. cpp:function:: Unsigned math::fibonacci(Unsigned n)

    Return the nth Fibonacci number: :math:`F_n = F_{n-1} + F_{n-2}`.

.. cpp:function:: Unsigned math::gcd(Unsigned a, Unsigned b)

    Return the `greatest common divisor`_ of *a* and *b*.

.. cpp:function:: Unsigned math::lcm(Unsigned a, Unsigned b)

    Return the `least common multiple`_ of *a* and *b*.

.. cpp:function:: Unsigned math::modpow(Unsigned a, Unsigned b, Unsigned c)

    `Modular exponentiation`_ function. Computes :math:`a^b \pmod{c}` and may prevent overflows. 

Angle conversions
-----------------
    
.. cpp:function:: Float math::degrees(Float x)

    Converts angle *x* from radians to degrees.

.. cpp:function:: Float math::radians(Float x)

    Converts angle *x* from degrees to radians.

Trigonometric functions
-----------------------
        
.. cpp:function:: Float math::sinc(Float x)

    Unnormalized cardinal since of *x*: :math:`\mathrm{sinc}(x) = \frac{\sin(x)}{x}`.

.. cpp:function:: Float math::normalized_sinc(Float x)

    Normalized cardinal since of *x*: :math:`\mathrm{sinc}(x) = \frac{\sin(\pi x)}{\pi x}`.


Miscellaneous functions
-----------------------

.. cpp:function:: std::array<std::complex<Float, 2u>> math::quadratic(Float a, Float b, Float c)

    Return the results *x* solutions of the quadratic equation :math:`ax^2 + bx +c`.
    
    :math:`x = \frac{-b\pm\sqrt{b^2-4ac\ }}{2a}`.

.. cpp:function:: constexpr bool is_close(T lhs, T rhs)

    This function uses a mathematical formula to check whether two values are
    close from each other. It returns whether the following relation holds:

    :math:`|lhs-rhs| \le \epsilon * max(|lhs|, |rhs|)`

    Where :math:`\epsilon` is ``std::numeric_limits<T>::epsilon()``.

Compile-time functions
----------------------

Some of the functions also have equivalents in the namespace ``math::meta``
that can be executed at compile time:

* ``math::meta::sign``
* ``math::meta::sum``
* ``math::meta::mean``
* ``math::meta::sqr``
* ``math::meta::clamp``
* ``math::meta::is_even``
* ``math::meta::is_odd``
* ``math::meta::is_prime``
* ``math::meta::fibonacci``
* ``math::meta::gcd``
* ``math::meta::lcm``
* ``math::meta::modpow``
* ``math::meta::degrees``
* ``math::meta::radians``
* ``math::meta::is_close``


.. _clamped: http://en.wikipedia.org/wiki/Clamping_%28graphics%29

.. _greatest common divisor: http://en.wikipedia.org/wiki/Greatest_common_divisor

.. _least common multiple: http://en.wikipedia.org/wiki/Least_common_multiple

.. _Modular exponentiation: http://en.wikipedia.org/wiki/Modular_exponentiation
