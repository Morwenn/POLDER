:mod:`distnorm` --- Mathematical distances and norms
====================================================

.. module:: distnorm

This module defines tag types that represent mathematical distances and norms.
These tags can be used to specify which distance or norm should be used when
computing functions such as a vector norm, a matrix norm or the distance between
two geometric entities. The module is divided in two namespaces: ``math::dist``
and ``math::norm``.

Distance tag types
------------------

All of the following tag types live in the namespace ``math::dist``:

.. cpp:type:: math::dist::manhattan

    Tag for the `Manhattan distance`_: :math:`d(\mathbf{p}, \mathbf{q}) = \sum\limits_{i=1}^n |p_i - q_i|`.

.. cpp:type:: math::dist::euclidean

    Tag for the `Euclidean distance`_: :math:`d(\mathbf{p}, \mathbf{q}) = \sqrt{\sum\limits_{i=1}^n (p_i - q_i)^2}`.

.. cpp:type:: math::dist::chebyshev

    Tag for the `Chebyshev distance`_: :math:`d(\mathbf{p}, \mathbf{q}) = \max_i(|p_i - q_i|)`.

.. cpp:type:: math::dist::minkowski

    Tag for the `Minkowski distance`_: :math:`d(\mathbf{p}, \mathbf{q}) = \left(\sum\limits_{i=1}^n |p_i - q_i|^p\right)^{1/p}`.

.. cpp:type:: math::dist::canberra

    Tag for the `Canberra distance`_: :math:`d(\mathbf{p}, \mathbf{q}) = \sum_{i=1}^n \frac{|p_i-q_i|}{|p_i|+|q_i|}`.
    
Norm tag types
--------------
    
All of the following tag types live in the namespace ``math::norm``:

.. cpp:type:: math::norm::manhattan

    Tag for the `Manhattan norm`_: :math:`\|x\|_1 = \sum\limits_{i=1}^n |x_i|`.

.. cpp:type:: math::norm::euclidean

    Tag for the `Euclidean norm`_: :math:`\|x\|_2 = \sqrt{\sum\limits_{i=1}^n x_i^2}`.

.. cpp:type:: math::norm::uniform

    Tag for the `uniform norm`_: :math:`\|x\|_\infty  = \max \left(|x_1|, \ldots ,|x_n| \right)`.

.. cpp:type:: math::norm::p

    Tag for the `p norm`_: :math:`\|x\|_p = \left(\sum\limits_{i=1}^n |x_i|^p\right)^{1/p}`.

Equivalence of tags
-------------------

For every existing norm, there is an equivalent distance. Therefore, the tag types in ``math::norm``
are implemented as type aliases of the tag types in ``math::dist``. Therefore, it is possible to use
the ``math::dist`` and ``math::norm`` tag types can be used interchangeably. Here is a table of the
equivalent tag types:

================================= =================================
Norm                              Distance
================================= =================================
:cpp:type:`math::norm::manhattan` :cpp:type:`math::dist::manhattan`
:cpp:type:`math::norm::euclidean` :cpp:type:`math::dist::euclidean`
:cpp:type:`math::norm::uniform`   :cpp:type:`math::dist::chebyshev`
:cpp:type:`math::norm::p`         :cpp:type:`math::dist::minkowski`
================================= =================================


.. _Manhattan distance: http://en.wikipedia.org/wiki/Taxicab_geometry#Formal_definition

.. _Euclidean distance: http://en.wikipedia.org/wiki/Euclidean_distance

.. _Chebyshev distance: http://en.wikipedia.org/wiki/Chebyshev_distance

.. _Minkowski distance: http://en.wikipedia.org/wiki/Minkowski_distance

.. _Canberra distance: http://en.wikipedia.org/wiki/Canberra_distance

.. _Manhattan norm: http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Taxicab_norm_or_Manhattan_norm

.. _Euclidean norm: http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Euclidean_norm

.. _uniform norm: http://en.wikipedia.org/wiki/Uniform_norm

.. _p norm: http://de.wikipedia.org/wiki/P-Norm