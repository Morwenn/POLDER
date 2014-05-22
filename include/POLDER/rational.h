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
#include <type_traits>
#include <POLDER/exceptions.h>
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
            ////////////////////////////////////////////////////////////

            // Default constructor
            constexpr rational();

            /**
             * @brief Initialization constructor
             *
             * Constructs a new rational number with their numerator
             * and denominator. Throws a division_by_zero exception if
             * denominator == 0.
             *
             * @param numerator Numerator of the fraction
             * @param denominator Denominator of the fraction
             */
            constexpr rational(value_type numerator, value_type denominator);

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
            constexpr rational(value_type numerator) noexcept;

            ////////////////////////////////////////////////////////////
            // Getters
            ////////////////////////////////////////////////////////////

            /**
             * @brief Returns the numerator of a rational number
             * @return Numerator
             */
            constexpr
            auto numer() const noexcept
                -> value_type;

            /**
             * @brief Returns the denominator of a rational number
             * @return Denominator
             */
            constexpr
            auto denom() const noexcept
                -> value_type;

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Assignment
            auto operator=(value_type other)
                -> rational&;

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

            auto operator/=(const rational& other)
                -> rational&;
            auto operator/=(value_type val)
                -> rational&;

            explicit constexpr operator float() const;
            explicit constexpr operator double() const;
            explicit constexpr operator long double() const;

            /**
             * @brief Simplify the fraction
             *
             * Divides _numerator and _denominator by their
             * greatest common divisor if needed. Also does a
             * sign simplification if necessary.
             */
            auto simplify()
                -> void;

        private:

            // Member data
            value_type _numer;      /**< Numerator */
            value_type _denom;    /**< Denominator */
    };


    ////////////////////////////////////////////////////////////
    // Unary arithmetic operators

    template<typename T>
    constexpr auto operator+(rational<T> rat)
        -> rational<T>;
    template<typename T>
    auto operator-(rational<T> rat)
        -> rational<T>;

    ////////////////////////////////////////////////////////////
    // Binary arithmetic operators

    template<typename T, typename U>
    auto operator+(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator+(const rational<T>& lhs, U rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator+(U lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator-(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator-(const rational<T>& lhs, U rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator-(U lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator*(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator*(const rational<T>& lhs, U rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator*(U lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator/(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator/(const rational<T>& lhs, U rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator/(U lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    ////////////////////////////////////////////////////////////
    // Equality operators

    template<typename T, typename U>
    constexpr
    auto operator==(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator==(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator==(U lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator!=(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator!=(U lhs, const rational<T>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Relational operators

    template<typename T, typename U>
    constexpr
    auto operator<(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<(U lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator>(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>(U lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<=(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<=(U lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>=(const rational<T>& lhs, U rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>=(U lhs, const rational<T>& rhs)
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
    template<typename T>
    constexpr auto make_rational(T numerator, T denominator=1)
        -> rational<T>;

    ////////////////////////////////////////////////////////////
    // Mathematical functions

    template<typename T>
    constexpr auto abs(const rational<T>& rat)
        -> rational<T>;

    template<typename T, typename Integer>
    constexpr auto pow(const rational<T>& rat, Integer exponent)
        -> rational<std::common_type_t<T, Integer>>;

    template<typename T>
    constexpr auto sign(const rational<T>& rat)
        -> int;

    #include "details/rational.inl"
}

#endif // POLDER_RATIONAL_H_
