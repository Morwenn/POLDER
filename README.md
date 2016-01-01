POLDER - Open Source C++ Library
================================

POLDER is some personal library where I just throw whatever reusable
bit of code I write. POLDER has no specific purpose nor has it any
proper cohesion between its modules (I am somehow working on that).
If you ever feel like using some code, don't hesitate to do so: go
ahead and pick whatever you want to.

Most of the library is template-only and compiling the rest should not
be a problem. There are some CMake files to build either a static or a
dynamic library and some tools to automate the build. That said, these
CMake files and tools have been left unmaintained for a while and I
doubt that they still work.

Some examples are provided along with the library. The examples are
regularly recompiled, so they should work.

Compilation
-----------

POLDER uses some of the most recent C++ features, even some from the
approved technica specifications and should therefore compile only
with the most recent compilers. I expect it to compile with the
following ones:
* g++ 5.2
* clang++ 3.5

Documentation
-------------

There is no complete documentation for POLDER. You can find some work
in progress documentation at http://morwenn.github.io/POLDER/ generated
with Sphinx. You can also use Doxygen to generate some anemic and mostly
redudant documentation from the comments embedded in the code. However,
templates being kind of hard to document properly with Doxygen, it is
really advised that you use the Sphinx documentation when possible.

Test suite
----------

A partial test suite is provided along with the library, written with
Catch. It is far from being complete, but it should give a good idea
about which parts of the library are more recent or mature.
