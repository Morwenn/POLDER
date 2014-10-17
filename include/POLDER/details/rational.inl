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

////////////////////////////////////////////////////////////
// Constructors

template<typename T>
constexpr rational<T>::rational():
    _numer(0),
    _denom(1)
{}

template<typename T>
rational<T>::rational(value_type numerator, value_type denominator):
    _numer(numerator),
    _denom(denominator)
{
    if (_denom == 0)
    {
        throw division_by_zero();
    }
    normalize();
}

template<typename T>
constexpr rational<T>::rational(value_type numerator) noexcept:
    _numer(numerator),
    _denom(1)
{}

////////////////////////////////////////////////////////////
// Getters

template<typename T>
auto rational<T>::numer() const noexcept
    -> value_type
{
    return _numer;
}

template<typename T>
auto rational<T>::denom() const noexcept
    -> value_type
{
    return _denom;
}

////////////////////////////////////////////////////////////
// Assignment operator

template<typename T>
auto rational<T>::operator=(value_type other) &
    -> rational&
{
    _numer = other;
    _denom = 1;
    return *this;
}

////////////////////////////////////////////////////////////
// Compound assignment operators

template<typename T>
auto rational<T>::operator+=(const rational& other)
    -> rational&
{
    _numer *= other.denom();
    _numer += other.numer() * _denom;
    _denom *= other.denom();

    normalize();
    return *this;
}

template<typename T>
auto rational<T>::operator+=(value_type other)
    -> rational&
{
    _numer += other * _denom;
    // cannot denormalize the fraction
    return *this;
}

template<typename T>
auto rational<T>::operator-=(const rational& other)
    -> rational&
{
    _numer *= other.denom();
    _numer -= other.numer() * _denom;
    _denom *= other.denom();

    normalize();
    return *this;
}

template<typename T>
auto rational<T>::operator-=(value_type other)
    -> rational&
{
    _numer -= other * _denom;
    // cannot denormalize the fraction
    return *this;
}

template<typename T>
auto rational<T>::operator*=(const rational& other)
    -> rational&
{
    _numer *= other.numer();
    _denom *= other.denom();

    normalize();
    return *this;
}

template<typename T>
auto rational<T>::operator*=(value_type other)
    -> rational&
{
    using math::gcd;

    // Reduce probability of overflow
    auto divisor = gcd(_denom, other);
    other /= divisor;
    _denom /= divisor;
    _numer *= other;

    return *this;
}

template<typename T>
auto rational<T>::operator/=(const rational& other)
    -> rational&
{
    if (other.numer() == 0)
    {
        throw division_by_zero();
    }
    _numer *= other.denom();
    _denom *= other.numer();

    normalize();
    return *this;
}

template<typename T>
auto rational<T>::operator/=(value_type other)
    -> rational&
{
    if (other == 0)
    {
        throw division_by_zero();
    }

    using math::gcd;
    using math::sign;
    using math::meta::abs;

    // Reduce probability of overflow
    auto divisor = gcd(_numer, other);
    other /= divisor;
    _numer /= divisor * sign(other);
    _denom *= abs(other);

    return *this;
}

////////////////////////////////////////////////////////////
// Increment & decrement operators

template<typename T>
auto rational<T>::operator++()
    -> rational&
{
    _numer += _denom;
    // cannot denormalize the fraction
    return *this;
}

template<typename T>
auto rational<T>::operator++(int)
    -> rational
{
    auto tmp = *this;
    operator++();
    return tmp;
}

template<typename T>
auto rational<T>::operator--()
    -> rational&
{
    _numer -= _denom;
    // cannot denormalize the fraction
    return *this;
}

template<typename T>
auto rational<T>::operator--(int)
    -> rational
{
    auto tmp = *this;
    operator--();
    return tmp;
}

////////////////////////////////////////////////////////////
// Cast operators

template<typename T>
rational<T>::operator bool() const
{
    return _numer != 0;
}

template<typename T>
rational<T>::operator float() const
{
    return static_cast<float>(_numer) /
           static_cast<float>(_denom);
}

template<typename T>
rational<T>::operator double() const
{
    return static_cast<double>(_numer) /
           static_cast<double>(_denom);
}

template<typename T>
rational<T>::operator long double() const
{
    return static_cast<long double>(_numer) /
           static_cast<long double>(_denom);
}

////////////////////////////////////////////////////////////
// Modifiers

template<typename T>
auto rational<T>::swap(rational<T>& other) noexcept
    -> void
{
    using std::swap;
    swap(_numer, other._numer);
    swap(_denom, other._denom);
}

template<typename T>
auto rational<T>::invert()
    -> rational&
{
    if (_denom == 0)
    {
        throw division_by_zero();
    }

    using std::swap;
    using math::meta::abs;
    using math::meta::sign;

    swap(_numer, _denom);
    _numer *= sign(_denom);
    _denom = abs(_denom);
    return *this;
}

////////////////////////////////////////////////////////////
// Miscellaneous functions

template<typename T>
auto rational<T>::normalize()
    -> void
{
    using math::gcd;
    using math::meta::abs;
    using math::meta::sign;

    // Sign simplification
    _numer *= sign(_denom);
    _denom = abs(_denom);

    // Value simplification
    if (_numer != 1 && _denom != 1)
    {
        auto _gcd = gcd(abs(_numer), _denom);
        _numer /= _gcd;
        _denom /= _gcd;
    }
}

////////////////////////////////////////////////////////////
// Unary arithmetic operators

template<typename T>
auto operator+(rational<T> rat)
    -> rational<T>
{
    return rat;
}

template<typename T>
auto operator-(rational<T> rat)
    -> rational<T>
{
    return rat *= T{-1};
}

////////////////////////////////////////////////////////////
// Binary arithmetic operators

template<typename T, typename U>
auto operator+(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) += rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator+(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) += rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator+(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(rhs) += lhs;
}

template<typename T, typename U>
auto operator-(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) -= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator-(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) -= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator-(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) -= rhs;
}

template<typename T, typename U>
auto operator*(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) *= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator*(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) *= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator*(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(rhs) *= lhs;
}

template<typename T, typename U>
auto operator/(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) /= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator/(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) /= rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator/(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) /= rhs;
}

////////////////////////////////////////////////////////////
// Comparison operators

template<typename T, typename U>
auto operator==(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() == rhs.numer()
        && lhs.denom() == rhs.denom();
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator==(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() == rhs
        && lhs.denom() == 1;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator==(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs == lhs;
}

template<typename T, typename U>
auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator!=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator!=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Relational operators

template<typename T, typename U>
auto operator<(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
         < lhs.denom() * rhs.numer();
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator<(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() < lhs.denom() * rhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator<(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return lhs * rhs.denom() < rhs.numer();
}

template<typename T, typename U>
auto operator>(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return rhs < lhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator>(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return rhs < lhs;
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator>(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs < lhs;
}

template<typename T, typename U>
auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator<=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator<=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<typename T, typename U>
auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return !(lhs < rhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator>=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return !(lhs < rhs);
}

template<typename T, typename Integer,
         typename = std::enable_if_t<std::is_convertible<Integer, T>::value>>
auto operator>=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return !(lhs < rhs);
}

////////////////////////////////////////////////////////////
// Stream operators

template<typename T>
auto operator<<(std::ostream& stream, const rational<T>& rat)
    -> std::ostream&
{
    stream << rat.numer() << "/" << rat.denom();
    return stream;
}

////////////////////////////////////////////////////////////
// Helper functions

template<typename T, typename U>
auto make_rational(T numerator, U denominator)
    -> rational<std::common_type_t<T, U>>
{
    return { numerator, denominator };
}

template<typename T>
auto make_rational(T numerator)
    -> rational<T>
{
    return rational<T>{ numerator };
}

template<typename T>
auto swap(rational<T>& lhs, rational<T>& rhs) noexcept
    -> void
{
    lhs.swap(rhs);
}

////////////////////////////////////////////////////////////
// Mathematical functions

template<typename T>
auto reciprocal(rational<T> rat)
    -> rational<T>
{
    return rat.invert();
}

template<typename T>
auto abs(const rational<T>& rat)
    -> rational<T>
{
    using math::meta::abs;

    return {
        abs(rat.numer()),
        rat.denom()
    };
}

template<typename T, typename Integer>
auto pow(const rational<T>& rat, Integer exponent)
    -> rational<std::common_type_t<T, Integer>>
{
    using math::meta::pow;

    if (exponent > 0)
    {
        return {
            pow(rat.numer(), exponent),
            pow(rat.denom(), exponent)
        };
    }
    else if (exponent < 0)
    {
        return {
            pow(rat.denom(), -exponent),
            pow(rat.numer(), -exponent)
        };
    }
    return rational<std::common_type_t<T, Integer>>{ 1 };
}

template<typename T>
auto sign(const rational<T>& rat)
    -> int
{
    using math::sign;
    return sign(rat.numer());
}

////////////////////////////////////////////////////////////
// User-defined literals

inline namespace literals
{
inline namespace rational_literals
{
    auto operator "" _r(unsigned long long n)
        -> rational<int>
    {
        return rational<int>{ static_cast<int>(n) };
    }

    auto operator "" _rl(unsigned long long n)
        -> rational<long>
    {
        return rational<long>{ static_cast<long>(n) };
    }

    auto operator "" _rll(unsigned long long n)
        -> rational<long long>
    {
        return rational<long long>{ static_cast<long long>(n) };
    }

    auto operator "" _ru(unsigned long long n)
        -> rational<unsigned>
    {
        return rational<unsigned>{ static_cast<unsigned>(n) };
    }

    auto operator "" _rul(unsigned long long n)
        -> rational<unsigned long>
    {
        return rational<unsigned long>{ static_cast<unsigned long>(n) };
    }

    auto operator "" _rull(unsigned long long n)
        -> rational<unsigned long long>
    {
        return rational<unsigned long long>{ n };
    }
}}
