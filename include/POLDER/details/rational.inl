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
////////////////////////////////////////////////////////////

template<typename T>
constexpr rational<T>::rational():
    _numer(0),
    _denom(1)
{}

template<typename T>
constexpr rational<T>::rational(value_type numerator, value_type denominator):
    _numer(numerator * math::meta::sign(denominator)),
    _denom(math::meta::abs(denominator))
{}

template<typename T>
constexpr rational<T>::rational(value_type numerator) noexcept:
    _numer(numerator),
    _denom(1)
{}

////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////

template<typename T>
constexpr
auto rational<T>::numer() const noexcept
    -> value_type
{
    return _numer;
}

template<typename T>
constexpr
auto rational<T>::denom() const noexcept
    -> value_type
{
    return _denom;
}

////////////////////////////////////////////////////////////
// In-class operators
////////////////////////////////////////////////////////////

template<typename T>
auto rational<T>::operator=(value_type other)
    -> rational&
{
    _numer = other;
    _denom = 1;
    return *this;
}

template<typename T>
auto rational<T>::operator+=(const rational& other)
    -> rational&
{
    _numer *= other.denom();
    _numer += other.numer() * _denom;
    _denom *= other.denom();
    return *this;
}

template<typename T>
auto rational<T>::operator+=(value_type other)
    -> rational&
{
    _numer += other * _denom;
    return *this;
}

template<typename T>
auto rational<T>::operator-=(const rational& other)
    -> rational&
{
    _numer *= other.denom();
    _numer -= other.numer() * _denom;
    _denom *= other.denom();
    return *this;
}

template<typename T>
auto rational<T>::operator-=(value_type other)
    -> rational&
{
    _numer -= other * _denom;
    return *this;
}

template<typename T>
auto rational<T>::operator*=(const rational& other)
    -> rational&
{
    _numer *= other.numer();
    _denom *= other.denom();
    return *this;
}

template<typename T>
auto rational<T>::operator*=(value_type other)
    -> rational&
{
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
    return *this;
}

template<typename T>
auto rational<T>::operator/=(value_type val)
    -> rational&
{
    if (val == 0)
    {
        throw division_by_zero();
    }
    _denom *= val;
    return *this;
}

template<typename T>
constexpr rational<T>::operator float() const
{
    return static_cast<float>(_numer) /
           static_cast<float>(_denom);
}

template<typename T>
constexpr rational<T>::operator double() const
{
    return static_cast<double>(_numer) /
           static_cast<double>(_denom);
}

template<typename T>
constexpr rational<T>::operator long double() const
{
    return static_cast<long double>(_numer) /
           static_cast<long double>(_denom);
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<typename T>
auto rational<T>::simplify()
    -> void
{
    // Sign simplification
    if (denom < 0)
    {
        _numer = -_numer;
        denom = -denom;
    }
    // Value simplification
    if (_numer != 1 && denom != 1)
    {
        auto _gcd = math::gcd(_numer, denom);
        if (_gcd != 1)
        {
            _numer /= _gcd;
            denom /= _gcd;
        }
    }
}

////////////////////////////////////////////////////////////
// Unary arithmetic operators
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
    return rat *= T{-1};
}

////////////////////////////////////////////////////////////
// Binary arithmetic operators
////////////////////////////////////////////////////////////

template<typename T, typename U>
auto operator+(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) += rhs;
}

template<typename T, typename Integer>
auto operator+(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) += rhs;
}

template<typename T, typename Integer>
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

template<typename T, typename Integer>
auto operator-(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) -= rhs;
}

template<typename T, typename Integer>
auto operator-(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return {
        lhs * rhs.denom() - rhs.numer(),
        rhs.denom()
    };
}

template<typename T, typename U>
auto operator*(const rational<T>& lhs, const rational<U>& rhs)
    -> rational<std::common_type_t<T, U>>
{
    return rational<std::common_type_t<T, U>>(lhs) *= rhs;
}

template<typename T, typename Integer>
auto operator*(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) *= rhs;
}

template<typename T, typename Integer>
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

template<typename T, typename Integer>
auto operator/(const rational<T>& lhs, Integer rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return rational<std::common_type_t<T, Integer>>(lhs) /= rhs;
}

template<typename T, typename Integer>
auto operator/(Integer lhs, const rational<T>& rhs)
    -> rational<std::common_type_t<T, Integer>>
{
    return {
        lhs * rhs.denom(),
        rhs.numer()
    };
}

////////////////////////////////////////////////////////////
// Equality operators
////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr auto operator==(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
        == lhs.denom() * rhs.numer();
}

template<typename T, typename Integer>
constexpr auto operator==(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() == lhs.denom() * rhs;
}

template<typename T, typename Integer>
constexpr auto operator==(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numer() == rhs.denom() * lhs;
}

////////////////////////////////////////////////////////////
// Relational operators
////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr auto operator!=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename Integer>
constexpr auto operator!=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename Integer>
constexpr auto operator!=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename T, typename U>
constexpr auto operator<(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
        < lhs.denom() * rhs.numer();
}

template<typename T, typename Integer>
constexpr auto operator<(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() < lhs.denom() * rhs;
}

template<typename T, typename Integer>
constexpr auto operator<(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numer() >= rhs.denom() * lhs;
}

template<typename T, typename U>
constexpr auto operator>(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
        > lhs.denom() * rhs.numer();
}

template<typename T, typename Integer>
constexpr auto operator>(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() > lhs.denom() * rhs;
}

template<typename T, typename Integer>
constexpr auto operator>(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numer() <= rhs.denom() * lhs;
}

template<typename T, typename U>
constexpr auto operator<=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
        <= lhs.denom() * rhs.numer();
}

template<typename T, typename Integer>
constexpr auto operator<=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() <= lhs.denom() * rhs;
}

template<typename T, typename Integer>
constexpr auto operator<=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return lhs * rhs.denom() <= rhs.numer();
}

template<typename T, typename U>
constexpr auto operator>=(const rational<T>& lhs, const rational<U>& rhs)
    -> bool
{
    return lhs.numer() * rhs.denom()
        >= lhs.denom() * rhs.numer();
}

template<typename T, typename Integer>
constexpr auto operator>=(const rational<T>& lhs, Integer rhs)
    -> bool
{
    return lhs.numer() >= lhs.denom() * rhs;
}

template<typename T, typename Integer>
constexpr auto operator>=(Integer lhs, const rational<T>& rhs)
    -> bool
{
    return rhs.numer() < rhs.denom() * lhs;
}

////////////////////////////////////////////////////////////
// Stream operators
////////////////////////////////////////////////////////////

template<typename T>
auto operator<<(std::ostream& stream, const rational<T>& rat)
    -> std::ostream&
{
    stream << rat.numer() << "/" << rat.denom();
    return stream;
}

////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////

template<typename T>
constexpr auto make_rational(T numerator, T denominator)
    -> rational<T>
{
    return { numerator, denominator };
}

////////////////////////////////////////////////////////////
// Mathematical functions
////////////////////////////////////////////////////////////

template<typename T>
constexpr auto abs(const rational<T>& rat)
    -> rational<T>
{
    return {
        math::meta::abs(rat.numer()),
        math::meta::abs(rat.denom())
    };
}

template<typename T, typename Integer>
constexpr auto pow(const rational<T>& rat, Integer exponent)
    -> rational<std::common_type_t<T, Integer>>
{
    using Ret = rational<std::common_type_t<T, Integer>>;

    using polder::math::meta::pow;

    return (exponent == 0) ? Ret(1) :
        (exponent > 0) ? Ret(
                        pow(rat.numer(), exponent),
                        pow(rat.denom(), exponent)
                    ) :
                    Ret(
                        pow(rat.denom(), -exponent),
                        pow(rat.numer(), -exponent)
                    );
}

template<typename T>
constexpr auto sign(const rational<T>& rat)
    -> int
{
    using polder::math::meta::sign;
    return sign(rat.numer()) * sign(rat.denom());
}
