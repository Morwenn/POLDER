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

/**
 * Headers
 */
#include <cmath>
#include <POLDER/exceptions.h>
#include <POLDER/math.h>


namespace polder
{


/**
 * @brief Rational numbers
 *
 * Only integral types should be used as a template parameter
 */
template<typename T>
struct rational
{
    public:

        /**
         * Constructors & destructor
         */

        // Default constructor
        rational() = default;

        // Copy constructor
        rational(const rational<T>&) = default;

        // Initilization constructor
        rational(T numerator, T denominator):
            _numerator(numerator),
            _denominator(denominator)
        {
            if (denominator == 0)
            {
                throw division_by_zero();
            }
        }

        // Numerator-only constructor (optimization)
        rational(T numerator):
            _numerator(numerator),
            _denominator(1)
        {}

        // Destructor
        ~rational() = default;


        /**
         * Getters
         */

        inline T numerator() const
        {
            return _numerator;
        }

        inline T denominator() const
        {
            return _denominator;
        }


        /**
         * Operators
         */

        // Assignement
        rational<T>& operator=(const rational<T>&) = default;
        rational<T>& operator=(const T& other)
        {
            _numerator = other;
            _denominator = 1;
            return *this;
        }

        rational<T>& operator+=(const rational<T>& other)
        {
            _numerator *= other._denominator;
            _numerator += other._numerator * _denominator;
            _denominator *= other._denominator;
            return *this;
        }
        rational<T>& operator+=(const T& other)
        {
            _numerator += other * _denominator;
            return *this;
        }

        rational<T>& operator-=(const rational<T>& other)
        {
            _numerator *= other._denominator;
            _numerator -= other._numerator * _denominator;
            _denominator *= other._denominator;
            return *this;
        }
        rational<T>& operator-=(const T& other)
        {
            _numerator -= other * _denominator;
            return *this;
        }

        rational<T>& operator*=(const rational<T>& other)
        {
            _numerator *= other._numerator;
            _denominator *= other._denominator;
            return *this;
        }
        rational<T>& operator*=(const T& other)
        {
            _numerator *= other;
            return *this;
        }

        rational<T>& operator/=(const rational<T>& other)
        {
            if (other._numerator == 0)
            {
                throw division_by_zero();
            }
            _numerator *= other._denominator;
            _denominator *= other._numerator;
            return *this;
        }
        rational<T>& operator/=(const T& val)
        {
            if (val == 0)
            {
                throw division_by_zero();
            }
            _denominator *= val;
            return *this;
        }

        rational<T> operator+()
        {
            return *this;
        }

        rational<T> operator-()
        {
            return rational<T>(*this) *= -1;
        }

        operator float() const
        {
            return (float) _numerator / (float) _denominator;
        }

        operator double() const
        {
            return (double) _numerator / (double) _denominator;
        }

        operator long double() const
        {
            return (long double) _numerator / (long double) _denominator;
        }


        /**
         * @brief Simplify the fraction
         *
         * Divides _numerator and _denominator by their
         * greatest common divisor if needed. Also does a
         * sign simplification if necessary.
         */
        void simplify()
        {
            // Sign simplification
            if (_denominator < 0)
            {
                _numerator = -_numerator;
                _denominator = -_denominator;
            }
            // Value simplification
            if (_numerator != 1 && _denominator != 1)
            {
                const T& _gcd = math::gcd(_numerator, _denominator);
                if (_gcd != 1)
                {
                    _numerator /= _gcd;
                    _denominator /= _gcd;
                }
            }
        }


    private:

        // Member data
        T _numerator;
        T _denominator;
};


/**
 * Global operators
 */

template<typename T>
const rational<T> operator+(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) += r2;
}
template<typename T>
const rational<T> operator+(const rational<T>& r, const T& val)
{
    return rational<T>(r) += val;
}
template<typename T>
const rational<T> operator+(const T& val, const rational<T>& r)
{
    return rational<T>(r) += val;
}

template<typename T>
const rational<T> operator-(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) -= r2;
}
template<typename T>
const rational<T> operator-(const rational<T>& r, const T& val)
{
    return rational<T>(r) -= val;
}
template<typename T>
const rational<T> operator-(const T& val, const rational<T>& r)
{
    return rational<T>(r) -= val;
}

template<typename T>
const rational<T> operator*(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) *= r2;
}
template<typename T>
const rational<T> operator*(const rational<T>& r, const T& val)
{
    return rational<T>(r) *= val;
}
template<typename T>
const rational<T> operator*(const T& val, const rational<T>& r)
{
    return rational<T>(r) *= val;
}

template<typename T>
const rational<T> operator/(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) /= r2;
}
template<typename T>
const rational<T> operator/(const rational<T>& r, const T& val)
{
    return rational<T>(r) /= val;
}
template<typename T>
const rational<T> operator/(const T& val, const rational<T>& r)
{
    return rational<T>(r) /= val;
}

template<typename T>
bool operator==(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() == r1.denominator() * r2.numerator();
}
template<typename T>
bool operator==(const rational<T>& r, const T& val)
{
    return r.numerator() == r.denominator() * val;
}
template<typename T>
bool operator==(const T& val, const rational<T>& r)
{
    return r.numerator() == r.denominator() * val;
}

template<typename T>
bool operator!=(const rational<T>& r1, const rational<T>& r2)
{
    return !(r1 == r2);
}
template<typename T>
bool operator!=(const rational<T>& r, const T& val)
{
    return !(r == val);
}
template<typename T>
bool operator!=(const T& val, const rational<T>& r)
{
    return !(r == val);
}

template<typename T>
bool operator<(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() < r1.denominator() * r2.numerator();
}
template<typename T>
bool operator<(const rational<T>& r, const T& val)
{
    return r.numerator() < r.denominator() * val;
}
template<typename T>
bool operator<(const T& val, const rational<T>& r)
{
    return r.numerator() >= r.denominator() * val;
}

template<typename T>
bool operator>(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() > r1.denominator() * r2.numerator();
}
template<typename T>
bool operator>(const rational<T>& r, const T& val)
{
    return r.numerator() > r.denominator() * val;
}
template<typename T>
bool operator>(const T& val, const rational<T>& r)
{
    return r.numerator() <= r.denominator() * val;
}

template<typename T>
bool operator<=(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() <= r1.denominator() * r2.numerator();
}
template<typename T>
bool operator<=(const rational<T>& r, const T& val)
{
    return r.numerator() <= r.denominator() * val;
}
template<typename T>
bool operator<=(const T& val, const rational<T>& r)
{
    return r.numerator() > r.denominator() * val;
}

template<typename T>
bool operator>=(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() >= r1.denominator() * r2.numerator();
}
template<typename T>
bool operator>=(const rational<T>& r, const T& val)
{
    return r.numerator() >= r.denominator() * val;
}
template<typename T>
bool operator>=(const T& val, const rational<T>& r)
{
    return r.numerator() < r.denominator() * val;
}


// Output streams gestion
template<typename T>
std::ostream& operator<<(std::ostream& stream, const rational<T>& r)
{
    stream << r.numerator() << "/" << r.denominator();
    return stream;
}


// Rational numbers creation handler
template<typename T>
rational<T> make_rational(T numerator, T denominator)
{
    return rational<T>(numerator, denominator);
}


} // namespace polder



/**
 * cmath functions overload
 */

// So that the functions can be called with or without std::
inline namespace std
{
    /**
     * @brief Absolute value of a number
     * @see std::abs(double);
     */
    template<typename T>
    polder::rational<T> abs(const polder::rational<T>& r)
    {
        return polder::rational<T>(abs(r.numerator()), abs(r.denominator()));
    }

    /**
     * @brief Power of a number
     * @see std::pow(double, double);
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


#endif // _POLDER_RATIONAL_H
