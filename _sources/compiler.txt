**********************************************
:mod:`compiler` --- Implementation information
**********************************************

.. module:: compiler

This module contains functions to query properties of the compiler or of the
standard library implementation. It is mainly used by the test files to check
whether compiler-specific optimizations work.


Compiler-related functions
--------------------------

.. cpp:function:: constexpr bool compiler::has_ebco()

    Returns whether the compiler is able to perform `empty base class optimization`_.

Standard library-related functions
----------------------------------

.. cpp:function:: constexpr bool compiler::has_ebco_for()

    Returns whether the given template from the standard library is optimized to take
    advantage of the empty base class optimization. This function has specializations
    for some of the standard library templates and always return ``false`` otherwise.
    
    It has specializations for the following standard library templates:
    
    * ``std::unique_ptr``
    * ``std::tuple``

    .. code-block:: cpp

        // Example usage
        if (compiler::has_ebco_for<std::unique_ptr>())
        {
            assert(
                sizeof(std::unique_ptr<int>) <
                sizeof(std::unique_ptr<int, int(*)(int*)>)
            );
        }

.. _empty base class optimization: http://en.cppreference.com/w/cpp/language/ebo