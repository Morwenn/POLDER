************************************************************
:mod:`evaluation` --- Evaluation of mathematical expressions
************************************************************

.. module:: evaluation

This module defines a class template ``evaluator`` which can be used
to evaluate mathematical expressions, and exposes as well many of the
details of the implementation, which may be reused for other purposes,
even though ``evaluator`` is the main component of the module. Every
feature of this module lives in the namespace ``polder::evaluation``,
but the class template ``evaluator`` is also available directly from
the ``polder`` namespace.

Since there are many things to be said about this simple class, let's
start with a simple example:

.. code-block:: cpp

    #include <cstdlib>
    #include <iostream>
    #include <POLDER/evaluation.h>
    
    int main()
    {
        polder::evaluator<int> eval;
        
        std::cout << eval("2 + 5 * 3") << '\n'; // 17
        std::cout << eval("(4 + 2) * (2 ** 3)") << '\n'; // 48
        std::cout << eval("5!") << '\n'; // 120
        
        // Connect the absolute value function
        eval.connect("abs", [](int n) {
            return std::abs(n);
        });
        
        std::cout << eval("2 * abs(2 - 8) + 4") << '\n'; // 16
    }

The class template ``evaluator``
--------------------------------

As said above, the most important class in the module is ``evaluator``
and it is the only one most people should care about.

.. cpp:class:: evaluator<Number>

    Engine for evaluating mathematical expressions. It handles by default
    a set of built-in operators and can be extended by connecting functions
    to it. The template parameter corresponds to the type of the operations
    performed by the engine and to the return type of an evaluation.

.. cpp:function:: Number evaluator<Number>::evaluate(const std::string& expression) const

    Evaluates the expression string with the current rules of evaluation and
    returns the result of the evaluation.
   
.. cpp:function:: Number evaluator<Number>::operator()(const std::string& expression) const

    Alias for the method ``evaluate``. The aim is to give a function object
    feeling to the ``evaluator`` class.
    
.. cpp:function:: void evaluator<Number>::connect(const std::string& name, Func&& function)

    Connects the given ``function`` to the evaluator. When evaluating an expression,
    if ``name`` is found in the expression string, it is considered as a function
    and the evaluator will try to call ``function`` on the arguments. In order for
    things to work properly, ``function`` has to be callable which takes any number
    of ``Number`` parameters and returns an instance of ``Number``.

    In its current form, the evaluator does not handle functions that have more than
    16 parameters and does not handle functions with a variable number of parameters
    either. Overloaded functions are not supported either, a name represents one and
    only one function, not an overload set.
    
.. cpp:function:: void evaluator<Number>::disconnect(const std::string& name)

    Disconnects the function corresponding to ``name`` from the the evaluator if such
    a function exists.

Built-in operators
------------------

The evaluation module supports a wide range of infix operators out of the box as well
as some prefix and postfix operators. The following infix operators are supported:

================ ======================================
Infix operator                Meaning
================ ======================================
a + b            :math:`a + b`
a - b            :math:`a - b`
a * b            :math:`a * b`
a / b            :math:`\frac{a}{b}`
a // b           :math:`\frac{a}{b}` (integer division)
a % b            :math:`a \bmod b`
a ** b           :math:`a^b`
a = b            :math:`a = b`
a != b           :math:`a \neq b`
a <=> b          :math:`sign(a - b)`
a < b            :math:`a < b`
a > b            :math:`a > b`
a <= b           :math:`a \le b`
a >= b           :math:`a \ge b`
a && b           :math:`a \wedge b`
a || b           :math:`a \vee b`
a ^^ b           :math:`a \oplus b`
a & b            Bitwise AND
a | b            Bitwise OR
a ^ b            Bitwise XOR
a << b           Left shift
a >> b           Right shift
================ ======================================

The following prefix operators are supported:

================ ======================================
Prefix operator                Meaning
================ ======================================
-n               :math:`-n`
!n               :math:`\neg n`
~n               Bitwise NOT
================ ======================================

The following postfix operators are supported:

================ ======================================
Postfix operator                Meaning
================ ======================================
n!               :math:`n!`
================ ======================================
