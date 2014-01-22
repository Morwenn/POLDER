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
// Constructors/destructor
////////////////////////////////////////////////////////////

template<typename Unsigned>
constexpr GrayCode<Unsigned>::GrayCode()
    = default;

template<typename Unsigned>
constexpr GrayCode<Unsigned>::GrayCode(const GrayCode&)
    = default;

template<typename Unsigned>
constexpr GrayCode<Unsigned>::GrayCode(GrayCode&&)
    = default;

template<typename Unsigned>
constexpr GrayCode<Unsigned>::GrayCode(value_type value):
    value( (value >> 1) ^ value )
{}

////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////

template<typename Unsigned>
auto GrayCode<Unsigned>::operator=(const GrayCode<Unsigned>&)
    -> GrayCode&
    = default;

template<typename Unsigned>
auto GrayCode<Unsigned>::operator=(GrayCode<Unsigned>&&)
    -> GrayCode&
    = default;

template<typename Unsigned>
auto GrayCode<Unsigned>::operator=(value_type other)
    -> GrayCode&
{
    value = (other >> 1) ^ other;
    return *this;
}

template<typename Unsigned>
GrayCode<Unsigned>::operator value_type() const
{
    value_type res = value;
    for (value_type mask = sizeof(value_type)*4 ; mask ; mask >>= 1)
    {
        res ^= res >> mask;
    }
    return res;
}

////////////////////////////////////////////////////////////
// Arithmetic operations
////////////////////////////////////////////////////////////

template<typename Unsigned>
auto GrayCode<Unsigned>::operator++()
    -> GrayCode&
{
    if (math::is_odd(*this))
    {
        auto y = value & -value;
        value ^= (y << 1);
    }
    else
    {
        // Flip rightmost bit
        value ^= 1;
    }
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator++(int)
    -> GrayCode&
{
    auto res = *this;
    operator++();
    return res;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator--()
    -> GrayCode&
{
    if (math::is_odd(*this))
    {
        // Flip rightmost bit
        value ^= 1;
    }
    else
    {
        auto y = value & -value;
        value ^= (y << 1);
    }
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator--(int)
    -> GrayCode&
{
    auto res = *this;
    operator--();
    return res;
}

////////////////////////////////////////////////////////////
// Bitwise operations
////////////////////////////////////////////////////////////

template<typename Unsigned>
auto GrayCode<Unsigned>::operator&=(const GrayCode<Unsigned>& other)
    -> GrayCode&
{
    value &= other.value;
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator|=(const GrayCode<Unsigned>& other)
    -> GrayCode&
{
    value |= other.value;
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator^=(const GrayCode<Unsigned>& other)
    -> GrayCode&
{
    value ^= other.value;
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator>>=(const GrayCode<Unsigned>& other)
    -> GrayCode&
{
    value >>= other.value;
    return *this;
}

template<typename Unsigned>
auto GrayCode<Unsigned>::operator<<=(const GrayCode<Unsigned>& other)
    -> GrayCode&
{
    value <<= other.value;
    return *this;
}

////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////

template<typename Unsigned>
constexpr auto gray(Unsigned value)
    -> GrayCode<Unsigned>
{
    return GrayCode<Unsigned>(value);
}

////////////////////////////////////////////////////////////
// Comparison operators
////////////////////////////////////////////////////////////

template<typename Unsigned>
constexpr auto operator==(const GrayCode<Unsigned>& lhs, const GrayCode<Unsigned>& rhs)
    -> bool
{
    return lhs.value == rhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(const GrayCode<Unsigned>& lhs, const GrayCode<Unsigned>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename Unsigned>
constexpr auto operator==(const GrayCode<Unsigned>& lhs, Unsigned rhs)
    -> bool
{
    return (rhs ^ (rhs >> 1)) == lhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(const GrayCode<Unsigned>& lhs, Unsigned rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<typename Unsigned>
constexpr auto operator==(Unsigned lhs, const GrayCode<Unsigned>& rhs)
    -> bool
{
    return (lhs ^ (lhs >> 1)) == rhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(Unsigned lhs, const GrayCode<Unsigned>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Bitwise operations
////////////////////////////////////////////////////////////

template<typename Unsigned>
auto operator&(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
    -> GrayCode<Unsigned>
{
    return lhs &= rhs;
}

template<typename Unsigned>
auto operator|(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
    -> GrayCode<Unsigned>
{
    return lhs |= rhs;
}

template<typename Unsigned>
auto operator^(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
    -> GrayCode<Unsigned>
{
    return lhs ^= rhs;
}

template<typename Unsigned>
auto operator>>(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
    -> GrayCode<Unsigned>
{
    return lhs >>= rhs;
}

template<typename Unsigned>
auto operator<<(GrayCode<Unsigned> lhs, const GrayCode<Unsigned>& rhs)
    -> GrayCode<Unsigned>
{
    return lhs <<= rhs;
}

////////////////////////////////////////////////////////////
// Overloaded math functions
////////////////////////////////////////////////////////////

namespace math
{
    template<typename Unsigned>
    auto is_even(const GrayCode<Unsigned>& code)
        -> bool
    {
        return not is_odd(code);
    }

    template<typename Unsigned>
    auto is_odd(const GrayCode<Unsigned>& code)
        -> bool
    {
        // A gray code is odd when the number
        // of bits set in its representation
        // is odd

        auto val = code.value;
        unsigned nb_bits{};
        for (; val ; ++nb_bits)
        {
            // clear the least significant bit set
            val &= val - 1;
        }
        return bool(nb_bits % 2);
    }
}
