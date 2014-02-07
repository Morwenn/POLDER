/*
 * Copyright (C) 2011-2013 Morwenn
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
// Defaulted members
////////////////////////////////////////////////////////////

template<typename T>
constexpr rational<T>::rational(const rational&)
    = default;

template<typename T>
auto rational<T>::operator=(const rational<T>&)
    -> rational<T>&
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<typename T>
constexpr rational<T>::rational():
    _numerator(0),
    _denominator(1)
{}

template<typename T>
constexpr rational<T>::rational(const T& numerator, const T& denominator):
    _numerator(numerator * math::meta::sign(denominator)),
    _denominator(denominator >= 0 ? denominator : -denominator)
{}

template<typename T>
constexpr rational<T>::rational(const T& numerator) noexcept:
    _numerator(numerator),
    _denominator(1)
{}

////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////

template<typename T>
constexpr
auto rational<T>::numerator() const noexcept
    -> value_type
{
    return _numerator;
}

template<typename T>
constexpr
auto rational<T>::denominator() const noexcept
    -> value_type
{
    return _denominator;
}

////////////////////////////////////////////////////////////
// In-class operators
////////////////////////////////////////////////////////////

template<typename T>
auto rational<T>::operator=(const T& other)
    -> rational<T>&
{
    _numerator = other;
    _denominator = 1;
    return *this;
}

template<typename T>
auto rational<T>::operator+=(const rational<T>& other)
    -> rational<T>&
{
    _numerator *= other._denominator;
    _numerator += other._numerator * _denominator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
auto rational<T>::operator+=(const value_type& other)
    -> rational<T>&
{
    _numerator += other * _denominator;
    return *this;
}

template<typename T>
auto rational<T>::operator-=(const rational<T>& other)
    -> rational<T>&
{
    _numerator *= other._denominator;
    _numerator -= other._numerator * _denominator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
auto rational<T>::operator-=(const value_type& other)
    -> rational<T>&
{
    _numerator -= other * _denominator;
    return *this;
}

template<typename T>
auto rational<T>::operator*=(const rational<T>& other)
    -> rational<T>&
{
    _numerator *= other._numerator;
    _denominator *= other._denominator;
    return *this;
}

template<typename T>
auto rational<T>::operator*=(const value_type& other)
    -> rational<T>&
{
    _numerator *= other;
    return *this;
}

template<typename T>
auto rational<T>::operator/=(const rational<T>& other)
    -> rational<T>&
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
auto rational<T>::operator/=(const value_type& val)
    -> rational<T>&
{
    if (val == 0)
    {
        throw division_by_zero();
    }
    _denominator *= val;
    return *this;
}

template<typename T>
constexpr
rational<T>::operator float() const
{
    return float(_numerator) / float(_denominator);
}

template<typename T>
constexpr
rational<T>::operator double() const
{
    return double(_numerator) / double(_denominator);
}

template<typename T>
constexpr
rational<T>::operator long double() const
{
    return (long double) _numerator / (long double) _denominator;
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<typename T>
auto rational<T>::simplify()
    -> void
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
        auto _gcd = math::gcd(_numerator, _denominator);
        if (_gcd != 1)
        {
            _numerator /= _gcd;
            _denominator /= _gcd;
        }
    }
}

////////////////////////////////////////////////////////////
// Outside-class operators
////////////////////////////////////////////////////////////

template<typename T>
constexpr auto operator+(rational<T> rat)
    -> rational<T>
{
    return rat;
}

template<typename T>
auto operator-(rational<T> rat)
    -> rational<T>
{
    return rat *= -1;
}

template<typename T, typename U>
auto operator+(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) += rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator+(const rational<T>& lhs, const U& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) += rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator+(const U& lhs, const rational<T>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(rhs) += lhs;
}

template<typename T, typename U>
auto operator-(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) -= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator-(const rational<T>& lhs, const U& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) -= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator-(const U& lhs, const rational<T>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(
        lhs * rhs.denominator() - rhs.numerator(),
        rhs.denominator()
    );
}

template<typename T, typename U>
auto operator*(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) *= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator*(const rational<T>& lhs, const U& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) *= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator*(const U& lhs, const rational<T>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(rhs) *= lhs;
}

template<typename T, typename U>
auto operator/(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) /= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator/(const rational<T>& lhs, const U& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(lhs) /= rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator/(const U& lhs, const rational<T>& rhs)
    -> rational<typename std::common_type<T, U>::type>
{
    return rational<typename std::common_type<T, U>::type>(
        lhs * rhs.denominator(),
        rhs.numerator()
    );
}

template<typename T, typename U>
constexpr
auto operator==(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numerator() * rhs.denominator()
        == lhs.denominator() * rhs.numerator();
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
constexpr
auto operator==(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return lhs.numerator() == lhs.denominator() * rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
constexpr
auto operator==(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numerator() == rhs.denominator() * lhs;
}

template<typename T, typename U>
constexpr
auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
constexpr
auto operator!=(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
constexpr
auto operator!=(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename U>
auto operator<(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numerator() * rhs.denominator()
        < lhs.denominator() * rhs.numerator();
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator<(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return lhs.numerator() < lhs.denominator() * rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator<(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numerator() >= rhs.denominator() * lhs;
}

template<typename T, typename U>
auto operator>(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numerator() * rhs.denominator()
        > lhs.denominator() * rhs.numerator();
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator>(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return lhs.numerator() > lhs.denominator() * rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator>(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numerator() <= rhs.denominator() * lhs;
}

template<typename T, typename U>
auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numerator() * rhs.denominator()
        <= lhs.denominator() * rhs.numerator();
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator<=(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return lhs.numerator() <= lhs.denominator() * rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator<=(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return lhs * rhs.denominator() <= rhs.numerator();
}

template<typename T, typename U>
auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numerator() * rhs.denominator()
        >= lhs.denominator() * rhs.numerator();
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator>=(const rational<T>& lhs, const U& rhs)
    -> bool
{
    return lhs.numerator() >= lhs.denominator() * rhs;
}

template<typename T, typename U, typename = typename std::enable_if<std::is_integral<U>::value, void>::type>
auto operator>=(const U& lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numerator() < rhs.denominator() * lhs;
}

template<typename T>
auto operator<<(std::ostream& stream, const rational<T>& rat)
    -> std::ostream&
{
    stream << rat.numerator() << "/" << rat.denominator();
    return stream;
}

////////////////////////////////////////////////////////////
// Construction helper
////////////////////////////////////////////////////////////

template<typename T>
constexpr auto make_rational(T numerator, T denominator)
    -> rational<T>
{
    return rational<T>(numerator, denominator);
}
