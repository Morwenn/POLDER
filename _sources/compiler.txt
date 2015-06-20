**********************************************
:mod:`compiler` --- Implementation information
**********************************************

.. module:: compiler

This module contains features to query properties of the compiler or of the
standard library implementation. It is mainly used by the test files to check
whether compiler-specific optimizations work.


Compiler-related features
-------------------------

.. cpp:var:: constexpr bool compiler::has_ebco

    Contains ``true`` if the compiler is able to perform the `empty base class optimization`_.

Standard library-related features
---------------------------------

.. cpp:var:: constexpr bool compiler::has_ebco_for

    This variable template is specialized for some specific templates and
    will always contain ``false`` for the other ones. It will contain
    ``true`` for the specialized template if and only if the implementation
    optimizes these templates so that they can benefit from the empty base
    class optimization.
    
    It is specialized for the following standard library templates:
    
    * ``std::unique_ptr``
    * ``std::tuple``

    .. code-block:: cpp

        // Example usage
        if (compiler::has_ebco_for<std::unique_ptr>)
        {
            assert(
                sizeof(std::unique_ptr<int>) <
                sizeof(std::unique_ptr<int, int(*)(int*)>)
            );
        }

.. _empty base class optimization: http://en.cppreference.com/w/cpp/language/ebo
