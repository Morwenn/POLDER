POLDER - Open Source C++ Library
================================

POLDER is some personal library where I just throw whatever reusable
bit of code I write. POLDER has no specific purpose nor has it any
proper cohesion between its modules (I am somehow working on that).

Most of the library is template-only and compiling the rest should not
be a problem. There are some CMake files to build either a static or a
dynamic library and some tools to automate the build. That said, these
CMake files and tools have been left unmaintained for a while and I
doubt that they still work.

Some examples are provided along with the library. The examples are
regularly recompiled, so they should work.

Compilation
-----------

POLDER uses some of the most recent C++ features, even some that
are not already standardized but that ought to work with some of
the most recent compilers. POLDER should compile with:
* g++ 5.1
* clang++ 3.5

Documentation
-------------

There is no complete documentation for POLDER. You can find some work
in progress documentation at http://morwenn.github.io/POLDER/ using
Sphinx. You can also use Doxygen to generate some partial documentation
from the comments embedded in the code but templates being kind of hard
to document properly, you should really use the Sphinx documentation
when possible.

Test suite
----------

A partial test suite is provided along with the library. It is written
with a custom version of the Catch framework. You can find some additional
documentation about this test suite in the dedicated folder.
