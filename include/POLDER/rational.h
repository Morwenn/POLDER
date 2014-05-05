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
#include <cmath>
#include <type_traits>
#include <POLDER/exceptions.h>
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
                      "A rational can only be made of integral values.");

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
            constexpr rational(const value_type& numerator, const value_type& denominator);

            /**
             * @brief Initialization constructor
             *
             * Same as the complete initialization constructor
             * except that this one does not need to check the
             * denominator since it is always 1.
             *
             * @param numerator Numerator of the fraction
             * @see rational(const value_type& numerator, const value_type& denominator)
             */
            constexpr rational(const value_type& numerator) noexcept;

            ////////////////////////////////////////////////////////////
            // Getters
            ////////////////////////////////////////////////////////////

            /**
             * @brief Returns the numerator of a rational number
             * @return Numerator
             */
            constexpr
            auto numerator() const noexcept
                -> value_type;

            /**
             * @brief Returns the denominator of a rational number
             * @return Denominator
             */
            constexpr
            auto denominator() const noexcept
                -> value_type;

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Assignment
            auto operator=(const value_type& other)
                -> rational&;

            auto operator+=(const rational& other)
                -> rational&;
            auto operator+=(const value_type& other)
                -> rational&;

            auto operator-=(const rational& other)
                -> rational&;
            auto operator-=(const value_type& other)
                -> rational&;

            auto operator*=(const rational& other)
                -> rational&;
            auto operator*=(const value_type& other)
                -> rational&;

            auto operator/=(const rational& other)
                -> rational&;
            auto operator/=(const value_type& val)
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
            value_type _numerator;      /**< Numerator */
            value_type _denominator;    /**< Denominator */
    };


    ////////////////////////////////////////////////////////////
    // Global operators
    ////////////////////////////////////////////////////////////

    template<typename T>
    constexpr auto operator+(rational<T> rat)
        -> rational<T>;
    template<typename T>
    auto operator-(rational<T> rat)
        -> rational<T>;

    template<typename T, typename U>
    auto operator+(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator+(const rational<T>& lhs, const U& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator+(const U& lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator-(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator-(const rational<T>& lhs, const U& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator-(const U& lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator*(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator*(const rational<T>& lhs, const U& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator*(const U& lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    auto operator/(const rational<T>& lhs, const rational<U>& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator/(const rational<T>& lhs, const U& rhs)
        -> rational<std::common_type_t<T, U>>;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    auto operator/(const U& lhs, const rational<T>& rhs)
        -> rational<std::common_type_t<T, U>>;

    template<typename T, typename U>
    constexpr
    auto operator==(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator==(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator==(const U& lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator!=(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator!=(const U& lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator<(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<(const U& lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator>(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>(const U& lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<=(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator<=(const U& lhs, const rational<T>& rhs)
        -> bool;

    template<typename T, typename U>
    constexpr
    auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>=(const rational<T>& lhs, const U& rhs)
        -> bool;
    template<typename T, typename U, typename = std::enable_if_t<std::is_integral<U>::value, void>>
    constexpr
    auto operator>=(const U& lhs, const rational<T>& rhs)
        -> bool;

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

    /**
     * @brief Rational numbers creation handler
     *
     * Function helping to construct rational numbers without
     * having to fill the template parameters since they will
     * be deduced from the parameters.
     *
     * @param numerator Numerator of a fraction
     * @param denominator Denominator of the fraction
     * @return New rational number
     */
    template<typename T>
    constexpr auto make_rational(T numerator, T denominator=1)
        -> rational<T>;

    #include "details/rational.inl"
}

#endif // POLDER_RATIONAL_H_
