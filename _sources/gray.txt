**************************
:mod:`gray` --- Gray codes
**************************

.. module:: gray

This module defines a class that represents `Gray code`_. The Gray code, or binary
reflected code is a binary numeral system invented by Frank Gray where every value
differs from its neighbours by only one bit. Gray codes have several applications
in computer programming and can notably be used in the field of genetic algorithms.

.. cpp:class:: gray_code<T>

    This class takes a built-in unsigned integer type ``T`` as a template parameter.
    If any other type is passed, the compilation ill fail with an error message.
	
.. cpp:type:: gray_code<T>::value_type

    This is an alias for the underlying unsigned integer type ``T``.
	
.. cpp:member:: gray_code<T>::value_type gray_code<T>::value

    This is the underlying unsigned integer value whose bits are in Gray code order.

Conversion between ``gray_code`` and built-in integers
------------------------------------------------------

Gray codes are only interesting if it is possible to perform conversion to and from
the underlying built-in unsigned integer type ``T``. Therefore, a couple of functions
exists in order to these conversions. Here are the main ones:

.. cpp:member:: gray_code<T>::gray_code()

.. cpp:member:: gray_code<T>::gray_code(value_type value)

.. cpp:member:: gray_code<T>::operator value_type() const

.. cpp:function:: gray_code<T> gray(T value)

Bitwise operations
------------------

One of the main interests of Gray codes is their binary representation. Therefore,
the class ``gray_code`` overloads the basic bitwise operators so that they work as
expected in the most simple cases. First of all, these operators are overloaded to
work between instances of the same ``gray_code`` specialization:

.. cpp:function:: gray_code<T> operator&(gray_code<T> lhs, gray_code<T> rhs)

.. cpp:function:: gray_code<T> operator|(gray_code<T> lhs, gray_code<T> rhs)

.. cpp:function:: gray_code<T> operator^(gray_code<T> lhs, gray_code<T> rhs)

.. cpp:function:: gray_code<T> operator~(gray_code<T> rhs)

Arithmetic operations
---------------------


.. _Gray code: https://en.wikipedia.org/wiki/Gray_code