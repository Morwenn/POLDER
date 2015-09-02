.. POLDER documentation master file, created by
   sphinx-quickstart on Mon May 12 21:12:16 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to POLDER's documentation!
==================================

POLDER is a random modern C++ library. It is based on C++14, but just in case this
very is outdated, know that it may use any feature from the most recent C++ standard
and from any approved TS. This is not a production library, it's an experimental
library where are thrown together a wide range of things without a proper cohesion.

You can use and reuse any part of the library you want, but be sure that any feature
may be redesigned at any time and introduce breaking changes everywhere without
worrying about who might actually use the feature. Now you're warned. If you still
find some feature interesting, don't hesitate to take and use it though.

Also, note that this library is kind of template-heavy, but Sphinx doesn't have the
nicest formatting for templates (yet?). Therefore, I use a « light » or « folded »
syntax where the ``template<typename T>`` is dropped from the declarations. Generally
speaking, if a type starts with a capital letter somewhere in this documentation, it
tends to denote a template parameter.

Contents:

.. toctree::
   :maxdepth: 2
   :numbered:
   
   algorithm
   compiler
   evaluation
   gray
   math
   polymorphic


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

