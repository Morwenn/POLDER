/*
 * Copyright (C) 2011 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_RATIONAL_H
#define _POLDER_RATIONAL_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
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
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        rational() = default;

        /**
         * Copy constructor
         */
        rational(const rational<T>&) = default;

        /**
         * @brief Initilization constructor
         *
         * Constructs a new rational number with their numerator
         * and denominator. Throws a division_by_zero exception if
         * denominator == 0.
         *
         * @param numerator Numerator of the fraction
         * @param denominator Denominator of the fraction
         */
        rational(const T& numerator, const T& denominator);

        /**
         * @brief Initilization constructor
         *
         * Same as the complete initialization constructor
         * except that this one does not need to check the
         * denominator since it is always 1.
         *
         * @param numerator Numerator of the fraction
         * @see rational(const T& numerator, const T& denominator)
         */
        rational(const T& numerator);

        /**
         * Destructor
         */
        ~rational() = default;


        ////////////////////////////////////////////////////////////
        // Getters
        ////////////////////////////////////////////////////////////

        /**
         * @brief Returns the numerator of a rational number
         * @return Numerator
         */
        T numerator() const;

        /**
         * @brief Returns the denominator of a rational number
         * @return Denominator
         */
        T denominator() const;


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Assignement
        rational<T>& operator=(const rational<T>&) = default;
        rational<T>& operator=(const T& other);

        rational<T>& operator+=(const rational<T>& other);
        rational<T>& operator+=(const T& other);

        rational<T>& operator-=(const rational<T>& other);
        rational<T>& operator-=(const T& other);

        rational<T>& operator*=(const rational<T>& other);
        rational<T>& operator*=(const T& other);
        rational<T>& operator/=(const rational<T>& other);
        rational<T>& operator/=(const T& val);

        rational<T> operator+();

        rational<T> operator-();

        operator float() const;

        operator double() const;

        operator long double() const;


        /**
         * @brief Simplify the fraction
         *
         * Divides _numerator and _denominator by their
         * greatest common divisor if needed. Also does a
         * sign simplification if necessary.
         */
        void simplify();


    private:

        // Member data
        T _numerator;   /**< Numerator */
        T _denominator; /**< Denominator */
};


////////////////////////////////////////////////////////////
// Global operators
////////////////////////////////////////////////////////////

template<typename T>
const rational<T> operator+(const rational<T>& r1, const rational<T>& r2);
template<typename T>
const rational<T> operator+(const rational<T>& r, const T& val);
template<typename T>
const rational<T> operator+(const T& val, const rational<T>& r);

template<typename T>
const rational<T> operator-(const rational<T>& r1, const rational<T>& r2);
template<typename T>
const rational<T> operator-(const rational<T>& r, const T& val);
template<typename T>
const rational<T> operator-(const T& val, const rational<T>& r);

template<typename T>
const rational<T> operator*(const rational<T>& r1, const rational<T>& r2);
template<typename T>
const rational<T> operator*(const rational<T>& r, const T& val);
template<typename T>
const rational<T> operator*(const T& val, const rational<T>& r);

template<typename T>
const rational<T> operator/(const rational<T>& r1, const rational<T>& r2);
template<typename T>
const rational<T> operator/(const rational<T>& r, const T& val);
template<typename T>
const rational<T> operator/(const T& val, const rational<T>& r);

template<typename T>
bool operator==(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator==(const rational<T>& r, const T& val);
template<typename T>
bool operator==(const T& val, const rational<T>& r);

template<typename T>
bool operator!=(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator!=(const rational<T>& r, const T& val);
template<typename T>
bool operator!=(const T& val, const rational<T>& r);

template<typename T>
bool operator<(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator<(const rational<T>& r, const T& val);
template<typename T>
bool operator<(const T& val, const rational<T>& r);

template<typename T>
bool operator>(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator>(const rational<T>& r, const T& val);
template<typename T>
bool operator>(const T& val, const rational<T>& r);

template<typename T>
bool operator<=(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator<=(const rational<T>& r, const T& val);
template<typename T>
bool operator<=(const T& val, const rational<T>& r);

template<typename T>
bool operator>=(const rational<T>& r1, const rational<T>& r2);
template<typename T>
bool operator>=(const rational<T>& r, const T& val);
template<typename T>
bool operator>=(const T& val, const rational<T>& r);


/**
 * @brief Output stream operator overload
 *
 * @param stream Output stream
 * @param r Rational number to display
 * @return Modified \a stream
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const rational<T>& r);


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
rational<T> make_rational(const T& numerator, const T& denominator);

#include <POLDER/rational.inl>


} // namespace polder



////////////////////////////////////////////////////////////
// Global operators
////////////////////////////////////////////////////////////
#if 0
// So that the functions can be called with or without std::
inline namespace std
{
    /**
     * @brief Absolute value of a number
     * @see std::abs(double)
     */
    template<typename T>
    polder::rational<T> abs(const polder::rational<T>& r)
    {
        return polder::rational<T>(abs(r.numerator()), abs(r.denominator()));
    }

    /**
     * @brief Power of a number
     * @see std::pow(double, double)
     */
    template<typename T>
    polder::rational<T> pow(const polder::rational<T>& r, int n)
    {
        if (n >= 0)
        {
            return polder::rational<T>(pow(r.denominator(), n), pow(r.numerator(), n));
        }
        else
        {
            n = -n;
            return polder::rational<T>(pow(r.denominator(), n), pow(r.numerator(), n));
        }
    }
}
#endif


#endif // _POLDER_RATIONAL_H
