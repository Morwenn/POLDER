**************************
:mod:`gray` --- Gray codes
**************************

.. module:: gray

This module defines a class that represents `Gray code`_. The Gray code, or binary
reflected code is a binary numeral system invented by Frank Gray where every value
differs from its neighbours by only one bit. Gray codes have several applications
in computer programming and can notably be used in the field of genetic algorithms.

Note that specific operations on Gray codes are defined in this module if and only
if they are faster than converting the Gray codes to regular integers, performing
an operation on integers and converting the result back to a Gray code. Therefore,
you might notice that every bitwise operation is define while only some arithmetic
operations are defined, such as increment and decrement.

.. cpp:class:: gray_code<T>

    This class takes a built-in unsigned integer type ``T`` as a template parameter.
    If any other type is passed, the compilation ill fail with an error message.
	
.. cpp:type:: gray_code<T>::value_type

    This is an alias for the underlying unsigned integer type ``T``.
	
.. cpp:member:: gray_code<T>::value_type gray_code<T>::value

    This is the underlying unsigned integer value whose bits are in Gray code order.

Construction functions
----------------------

Gray codes can be default-constructed or constructed from an instance of the underlying
type or from a boolean. As of now, there isn't any function to create a Gray code directly
with its underlying value without a conversion.

.. cpp:member:: gray_code<T>::gray_code() noexcept

    Default constructor. It initializes the underlying value with :math:`0`. There is no
    dedicated way to construct an uninitialized ``gray_code`` instance. 

.. cpp:member:: explicit gray_code<T>::gray_code(value_type value) noexcept

    Takes an instance of the underlying type and converts it to a Gray code. Note that
    ``gray_code`` is not meant to « be an integer », therefore all the conversions to and
    from the underlying type are ``explicit`` so that none of the types is considered more
    important than the other. It may sound quite philosophical, but that's it.
    
.. cpp:member:: explicit gray_code<T>::gray_code(bool value) noexcept

    The Gray code and base :math:`2` representations for the numbers :math:`0` and :math:`1`
    are the same. Therefore, an ``explicit`` construction from a boolean type makes sense
    and is guaranteed not to perform any conversion.

Conversion functions
--------------------

Gray codes can be converted to their underlying type or to a boolean. Such a conversion is
always explicit. Contrary to regular integers, there is no conversion allowed between a
``gray_code<unsigned>`` and a ``gray_code<unsigned long>`` for example. All conversions are
``explicit`` so that there are no unexpected conversions while trying to perform a bitwise
operation between a Gray code and an instance of its underlying type for example.

.. cpp:member:: explicit gray_code<T>::operator value_type() const noexcept

    Converts the Gray code into its regular base :math:`2` representation.

.. cpp:member:: constexpr explicit gray_code<T>::operator bool() const noexcept

    Converts the Gray code into a boolean. This function will return ``false`` if the Gray
    code is equal to :math:`0` and ``true`` otherwise.

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

As stated in the introduction, arithmetic operations are only implemented if they can
be at least as fast if not even faster than converting the parameters to a base :math:`2`
representation, performing an operation and converting the result back to a Gray code. The
following arithmetic operations are defined on Gray codes:

.. cpp:member:: gray_code<T>& gray_code<T>::operator++() noexcept

.. cpp:member:: gray_code<T> gray_code<T>::operator++(int) noexcept

.. cpp:member:: gray_code<T>& gray_code<T>::operator--() noexcept

.. cpp:member:: gray_code<T> gray_code<T>::operator--(int) noexcept


.. _Gray code: https://en.wikipedia.org/wiki/Gray_code