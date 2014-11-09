/*
 * Copyright (C) 2011-2014 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef POLDER_RATIONAL_H_
#define POLDER_RATIONAL_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <ostream>
#include <type_traits>
#include <utility>
#include <POLDER/math/cmath.h>
#include <POLDER/math/formula.h>

namespace polder
{
    /**
     * @brief Rational numbers
     *
     * Ensembles: B < N < Z < Q < R < C.
     *
     * All of those ensembles already exist in the C++ standard
     * library or in the language itself except the rational
     * numbers (Q), represented by "fractions": an integer
     * numerator and denominator.
     *
     * @warning Only integral types should be used as a template parameter
     * @warning The denominator should not be 0
     */
    template<typename T>
    struct rational
    {
        static_assert(std::is_integral<T>::value,
                      "a rational can only be made of integral values");

        public:

            using value_type = T;

            ////////////////////////////////////////////////////////////
            // Constructors

            // Default constructor
            constexpr rational();

            /**
             * @brief Initialization constructor
             *
             * Same as the complete initialization constructor
             * except that this one does not need to check the
             * denominator since it is always 1.
             *
             * @param numerator Numerator of the fraction
             * @see rational(value_type numerator, value_type denominator)
             */
            explicit constexpr rational(value_type numerator) noexcept;

            /**
             * @brief Initialization constructor
             *
             * Constructs a new rational number with their numerator
             * and denominator.
             *
             * Precondition: denominator != 0.
             *
             * @param numerator Numerator of the fraction
             * @param denominator Denominator of the fraction
             */
            rational(value_type numerator, value_type denominator);

            ////////////////////////////////////////////////////////////
            // Getters

            /**
             * @brief Returns the numerator of a rational number
             * @return Numerator
             */
            auto numer() const noexcept
                -> value_type;

            /**
             * @brief Returns the denominator of a rational number
             * @return Denominator
             */
            auto denom() const noexcept
                -> value_type;

            ////////////////////////////////////////////////////////////
            // Assignment operator

            auto operator=(value_type other) &
                -> rational&;

            ////////////////////////////////////////////////////////////
            // Compound assignment operators

            auto operator+=(const rational& other)
                -> rational&;
            auto operator+=(value_type other)
                -> rational&;

            auto operator-=(const rational& other)
                -> rational&;
            auto operator-=(value_type other)
                -> rational&;

            auto operator*=(const rational& other)
                -> rational&;
            auto operator*=(value_type other)
                -> rational&;

            /**
             * @brief rational-rational division.
             *
             * Precondition: other.numer() != 0.
             */
            auto operator/=(const rational& other)
                -> rational&;

            /**
             * @brief rational-integer division.
             *
             * Precondition: other != 0.
             */
            auto operator/=(value_type other)
                -> rational&;

            ////////////////////////////////////////////////////////////
            // Increment & decrement operators

            auto operator++()
                -> rational&;
            auto operator++(int)
                -> rational;

            auto operator--()
                -> rational&;
            auto operator--(int)
                -> rational;

            ////////////////////////////////////////////////////////////
            // Cast operators

            explicit operator bool() const;

            explicit operator float() const;
            explicit operator double() const;
            explicit operator long double() const;

            ////////////////////////////////////////////////////////////
            // Modifiers

            auto swap(rational& other) noexcept
                -> void;

            /**
             * @brief Inverts the numerator and the denominator.
             *
             * The numerator and the denominator are swapped, then
             * the numerator acquires the sign information while
             * abs is applied to the denominator.
             *
             * Precondition: numer() != 0.
             */
            auto invert()
                -> rational&;

        private:

            ////////////////////////////////////////////////////////////
            // Miscellaneous functions

            /*
             * Normalize the fraction.
             *
             * Divides _numer and _denom by their greatest
             * common divisor if needed. Also does a
             * sign simplification if necessary.
             */
            auto normalize()
                -> void;

            ////////////////////////////////////////////////////////////
            // Member data

            value_type _numer;  /**< Numerator */
            value_type _denom;  /**< Denominator */
    };


    ////////////////////////////////////////////////////////////
    // Unary arithmetic operators

    template<typename T>
    auto operator+(rational<T> rat)
        -> rational<T>;
    template<typename T>
    auto operator-(rational<T> rat)
        -> rational<T>;

    ////////////////////////////////////////////////////////////
    // Binary arithmetic operators

    template<typename T, typename U>
    auto operator+(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator+(const rational<T>& lhs, Integer rhs)
        -> rational<std::common_type_t<T, Integer>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator+(Integer lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, Integer>>;

    template<typename T, typename U>
    auto operator-(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator-(const rational<T>& lhs, Integer rhs)
        -> rational<std::common_type_t<T, Integer>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator-(Integer lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, Integer>>;

    template<typename T, typename U>
    auto operator*(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator*(const rational<T>& lhs, Integer rhs)
        -> rational<std::common_type_t<T, Integer>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator*(Integer lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, Integer>>;

    template<typename T, typename U>
    auto operator/(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator/(const rational<T>& lhs, Integer rhs)
        -> rational<std::common_type_t<T, Integer>>;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator/(Integer lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, Integer>>;

    ////////////////////////////////////////////////////////////
    // Equality operators

    template<typename T, typename U>
    auto operator==(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator==(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator==(Integer lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator!=(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator!=(Integer lhs, const rational<T>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Relational operators

    template<typename T, typename U>
    auto operator<(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator<(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator<(Integer lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    auto operator>(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator>(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator>(Integer lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator<=(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator<=(Integer lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator>=(const rational<T>& lhs, Integer rhs)
        -> bool;
    template<typename T, typename Integer,
             typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
    auto operator>=(Integer lhs, const rational<T>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Stream operators

    /**
     * @brief Output stream operator overload
     *
     * @param stream Output stream
     * @param r Rational number to display
     * @return Modified \a stream
     */
    template<typename T>
    auto operator<<(std::ostream& stream, const rational<T>& rat)
        -> std::ostream&;

    ////////////////////////////////////////////////////////////
    // Helper functions

    /**
     * @brief Rational numbers creation helper
     *
     * Function helping to construct rational numbers without
     * having to specify the template parameters since they
     * will be deduced from the parameters.
     *
     * @param numerator Numerator of a fraction
     * @param denominator Denominator of the fraction
     * @return New rational number
     */
    template<typename T, typename U>
    auto make_rational(T numerator, U denominator)
        -> rational<std::common_type_t<T, U>>;

    template<typename T>
    auto make_rational(T numerator)
        -> rational<T>;

    template<typename T>
    auto swap(rational<T>& lhs, rational<T>& rhs) noexcept
        -> void;

    ////////////////////////////////////////////////////////////
    // Mathematical functions

    template<typename T>
    auto reciprocal(rational<T> rat)
        -> rational<T>;

    template<typename T>
    auto abs(const rational<T>& rat)
        -> rational<T>;

    template<typename T, typename Integer>
    auto pow(const rational<T>& rat, Integer exponent)
        -> rational<std::common_type_t<T, Integer>>;

    template<typename T>
    auto sign(const rational<T>& rat)
        -> int;

    ////////////////////////////////////////////////////////////
    // User-defined literals

    inline namespace literals
    {
    inline namespace rational_literals
    {
        auto operator "" _r(unsigned long long n)
            -> rational<int>;

        auto operator "" _rl(unsigned long long n)
            -> rational<long>;

        auto operator "" _rll(unsigned long long n)
            -> rational<long long>;

        auto operator "" _ru(unsigned long long n)
            -> rational<unsigned>;

        auto operator "" _rul(unsigned long long n)
            -> rational<unsigned long>;

        auto operator "" _rull(unsigned long long n)
            -> rational<unsigned long long>;
    }}

    #include "details/rational.inl"
}

#endif // POLDER_RATIONAL_H_
