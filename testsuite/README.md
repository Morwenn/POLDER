POLDER test suite
=================

The POLDER test suite runs with a custom modified version of the Catch unit
testing framework, due to problems with overloaded operators. The modified
version of Catch (header-only) is embedded in catch.hpp.

Changes to Catch
----------------

Here is a list of what is different from the original Catch framework:
* Ignored GCC warning -Wzero-as-null-pointer-constant
* Symmetrical handling of operators on both sides of comparison and relational operators in REQUIRE and friends (thanks tclamb)
* Ignored GCC warning -Wparenthesis
* Define CATCH_CONFIG_CPP11_CONSTEXPR and CATCH_CONSTEXPR for GCC and Clang >= C++11
* Approx construction, comparison and custom() functions are constexpr when possible