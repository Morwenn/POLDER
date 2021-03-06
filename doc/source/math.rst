***********************************
:mod:`math` --- Mathematical module
***********************************

.. module:: math

This module contains math-related constants and formula. It is separated in several
submodules that can be included separately. It is still possible to include the
whole module at once with the following line of code:

.. code-block:: cpp

    #include <POLDER/math.h>

This module contains math-related constants and formula. All the functions in this
module live in the namespace ``polder::math``. Some of the functions also have some
kinds of "overloads" that can be executed at compile time. These compile time
functions live in the subnamespace ``polder::math::meta``; the limitations of the
compile time implementations make the compile time functions unsuitable for runtime
use. If you need to execute a function at runtime, use the ones that live directly
in ``polder::math``.


.. toctree::

    math.cmath.rst
    math.formula.rst
    math.constants.rst
    math.distnorm.rst
    math.factorial.rst
