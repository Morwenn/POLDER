:mod:`factorial` --- Factorial-related mathematical formula
===========================================================

.. module:: factorial

Factorial-related mathematical functions.


.. cpp:function:: Unsigned math::factorial(Unsigned n)

    Return the factorial of *n*: :math:`n!`. This function also have an equivalent in
    ``math::meta`` that is intended to run at compile time.

.. cpp:function:: Unsigned math::double_factorial(Unsigned n)

    Return the double factorial of *n*: :math:`n!! = \prod_{i=1}^{(n+1)/2} (2i-1)`.

.. cpp:function:: Unsigned math::stirling(Unsigned n)

    Uses the Stirling formula to approach :math:`n!`: :math:`\sqrt{2\pi n}\,\left({n \over {\rm e}}\right)^n`.