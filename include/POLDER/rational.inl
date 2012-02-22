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

template<typename T>
inline rational<T>::rational(const T& numerator, const T& denominator):
    _numerator(numerator),
    _denominator(denominator)
{
    if (denominator == 0)
    {
        throw division_by_zero();
    }
}

template<typename T>
inline rational<T>::rational(const T& numerator):
    _numerator(numerator),
    _denominator(1)
{}

template<typename T>
inline T rational<T>::numerator() const
{
    return _numerator;
}

template<typename T>
inline T rational<T>::denominator() const
{
    return _denominator;
}


template<typename T>
inline rational<T>& rational<T>::operator=(const T& other)
{
    _numerator = other;
    _denominator = 1;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator+=(const rational<T>& other)
{
    _numerator *= other._denominator;
    _numerator += other._numerator * _denominator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator+=(const T& other)
{
    _numerator += other * _denominator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator-=(const rational<T>& other)
{
    _numerator *= other._denominator;
    _numerator -= other._numerator * _denominator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator-=(const T& other)
{
    _numerator -= other * _denominator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator*=(const rational<T>& other)
{
    _numerator *= other._numerator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator*=(const T& other)
{
    _numerator *= other;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator/=(const rational<T>& other)
{
    if (other._numerator == 0)
    {
        throw division_by_zero();
    }
    _numerator *= other._denominator;
    _denominator *= other._numerator;
    return *this;
}

template<typename T>
inline rational<T>& rational<T>::operator/=(const T& val)
{
    if (val == 0)
    {
        throw division_by_zero();
    }
    _denominator *= val;
    return *this;
}

template<typename T>
inline rational<T> rational<T>::operator+()
{
    return *this;
}

template<typename T>
inline rational<T> rational<T>::operator-()
{
    return rational<T>(*this) *= -1;
}

template<typename T>
inline rational<T>::operator float() const
{
    return (float) _numerator / (float) _denominator;
}

template<typename T>
inline rational<T>::operator double() const
{
    return (double) _numerator / (double) _denominator;
}

template<typename T>
inline rational<T>::operator long double() const
{
    return (long double) _numerator / (long double) _denominator;
}

template<typename T>
void rational<T>::simplify()
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

template<typename T>
inline const rational<T> operator+(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) += r2;
}

template<typename T>
inline const rational<T> operator+(const rational<T>& r, const T& val)
{
    return rational<T>(r) += val;
}

template<typename T>
inline const rational<T> operator+(const T& val, const rational<T>& r)
{
    return rational<T>(r) += val;
}

template<typename T>
inline const rational<T> operator-(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) -= r2;
}

template<typename T>
inline const rational<T> operator-(const rational<T>& r, const T& val)
{
    return rational<T>(r) -= val;
}

template<typename T>
inline const rational<T> operator-(const T& val, const rational<T>& r)
{
    return rational<T>(r) -= val;
}

template<typename T>
inline const rational<T> operator*(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) *= r2;
}

template<typename T>
inline const rational<T> operator*(const rational<T>& r, const T& val)
{
    return rational<T>(r) *= val;
}

template<typename T>
inline const rational<T> operator*(const T& val, const rational<T>& r)
{
    return rational<T>(r) *= val;
}

template<typename T>
inline const rational<T> operator/(const rational<T>& r1, const rational<T>& r2)
{
    return rational<T>(r1) /= r2;
}

template<typename T>
inline const rational<T> operator/(const rational<T>& r, const T& val)
{
    return rational<T>(r) /= val;
}

template<typename T>
inline const rational<T> operator/(const T& val, const rational<T>& r)
{
    return rational<T>(r) /= val;
}

template<typename T>
inline bool operator==(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() == r1.denominator() * r2.numerator();
}

template<typename T>
inline bool operator==(const rational<T>& r, const T& val)
{
    return r.numerator() == r.denominator() * val;
}

template<typename T>
inline bool operator==(const T& val, const rational<T>& r)
{
    return r.numerator() == r.denominator() * val;
}

template<typename T>
inline bool operator!=(const rational<T>& r1, const rational<T>& r2)
{
    return !(r1 == r2);
}

template<typename T>
inline bool operator!=(const rational<T>& r, const T& val)
{
    return !(r == val);
}

template<typename T>
inline bool operator!=(const T& val, const rational<T>& r)
{
    return !(r == val);
}

template<typename T>
inline bool operator<(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() < r1.denominator() * r2.numerator();
}

template<typename T>
inline bool operator<(const rational<T>& r, const T& val)
{
    return r.numerator() < r.denominator() * val;
}

template<typename T>
inline bool operator<(const T& val, const rational<T>& r)
{
    return r.numerator() >= r.denominator() * val;
}

template<typename T>
inline bool operator>(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() > r1.denominator() * r2.numerator();
}

template<typename T>
inline bool operator>(const rational<T>& r, const T& val)
{
    return r.numerator() > r.denominator() * val;
}

template<typename T>
inline bool operator>(const T& val, const rational<T>& r)
{
    return r.numerator() <= r.denominator() * val;
}

template<typename T>
inline bool operator<=(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() <= r1.denominator() * r2.numerator();
}

template<typename T>
inline bool operator<=(const rational<T>& r, const T& val)
{
    return r.numerator() <= r.denominator() * val;
}

template<typename T>
inline bool operator<=(const T& val, const rational<T>& r)
{
    return r.numerator() > r.denominator() * val;
}

template<typename T>
inline bool operator>=(const rational<T>& r1, const rational<T>& r2)
{
    return r1.numerator() * r2.denominator() >= r1.denominator() * r2.numerator();
}

template<typename T>
inline bool operator>=(const rational<T>& r, const T& val)
{
    return r.numerator() >= r.denominator() * val;
}

template<typename T>
inline bool operator>=(const T& val, const rational<T>& r)
{
    return r.numerator() < r.denominator() * val;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const rational<T>& r)
{
    stream << r.numerator() << "/" << r.denominator();
    return stream;
}

template<typename T>
inline rational<T> make_rational(T numerator, T denominator)
{
    return rational<T>(numerator, denominator);
}
