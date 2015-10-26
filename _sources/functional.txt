**************************************
:mod:`functional` --- Function objects
**************************************

.. module:: functional

This module contains generic function objects. Some of them are inspired by the
ones found in the standard library header ``<functional`` while others are slightly
different in the way they work.

Function objects
----------------

Just like the standard library, POLDER provides function objects that represent
common operators. However, these classes are not templated, only their function
call operators are. When possible, they are defined as alias for the equivalent
``void`` specialization in the standard library. For example, ``plus`` is defined
as follows:

.. code-block:: cpp

    using plus = std::plus<>;

POLDER completes this set of function objects with the ones used to represent the
missing shift and assignement operators. Here is the full list of function objects
provided by POLDER:

.. cpp:class:: plus

.. cpp:class:: minus

.. cpp:class:: multiplies

.. cpp:class:: divides

.. cpp:class:: modulus

.. cpp:class:: negate

.. cpp:class:: equal_to

.. cpp:class:: not_equal_to

.. cpp:class:: greater

.. cpp:class:: less

.. cpp:class:: greater_equal

.. cpp:class:: less_equal

.. cpp:class:: logical_and

.. cpp:class:: logical_or

.. cpp:class:: logical_not

.. cpp:class:: bit_and

.. cpp:class:: bit_or

.. cpp:class:: bit_xor

.. cpp:class:: bit_not

.. cpp:class:: left_shift

.. cpp:class:: right_shift

.. cpp:class:: assign

.. cpp:class:: plus_assign

.. cpp:class:: minus_assign

.. cpp:class:: multiplies_assign

.. cpp:class:: divides_assign

.. cpp:class:: modulus_assign

.. cpp:class:: bit_and_assign

.. cpp:class:: bit_or_assign

.. cpp:class:: bit_xor_assign

.. cpp:class:: left_shift_assign

.. cpp:class:: right_shift_assign
