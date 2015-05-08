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
// Construction operations

template<typename Unsigned>
constexpr gray_code<Unsigned>::gray_code() noexcept:
    value(0u)
{}

template<typename Unsigned>
constexpr gray_code<Unsigned>::gray_code(value_type value) noexcept:
    value( (value >> 1) ^ value )
{}

template<typename Unsigned>
constexpr gray_code<Unsigned>::gray_code(bool value) noexcept:
    value(value)
{}

////////////////////////////////////////////////////////////
// Assignment operations

template<typename Unsigned>
auto gray_code<Unsigned>::operator=(value_type other) & noexcept
    -> gray_code&
{
    value = (other >> 1) ^ other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator=(bool other) & noexcept
    -> gray_code&
{
    value = other;
    return *this;
}

////////////////////////////////////////////////////////////
// Conversion operations

template<typename Unsigned>
gray_code<Unsigned>::operator value_type() const noexcept
{
    value_type res = value;
    for (value_type mask = std::numeric_limits<value_type>::digits / 2
         ; mask ; mask >>= 1)
    {
        res ^= res >> mask;
    }
    return res;
}

template<typename Unsigned>
constexpr gray_code<Unsigned>::operator bool() const noexcept
{
    return bool(value);
}

////////////////////////////////////////////////////////////
// Increment/decrement operations

template<typename Unsigned>
auto gray_code<Unsigned>::operator++() noexcept
    -> gray_code&
{
    static constexpr value_type msb
        = 1 << (std::numeric_limits<value_type>::digits - 1);

    if (is_odd(*this))
    {
        if (value == msb)
        {
            value = 0;
        }
        else
        {
            auto y = value & -value;
            value ^= (y << 1);
        }
    }
    else
    {
        // Flip rightmost bit
        value ^= 1;
    }
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator++(int) noexcept
    -> gray_code
{
    auto res = *this;
    operator++();
    return res;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator--() noexcept
    -> gray_code&
{
    static constexpr value_type msb
        = 1 << (std::numeric_limits<value_type>::digits - 1);

    if (is_odd(*this))
    {
        // Flip rightmost bit
        value ^= 1;
    }
    else
    {
        if (value == 0)
        {
            value = msb;
        }
        else
        {
            auto y = value & -value;
            value ^= (y << 1);
        }
    }
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator--(int) noexcept
    -> gray_code
{
    auto res = *this;
    operator--();
    return res;
}

////////////////////////////////////////////////////////////
// Bitwise assignment operations

template<typename Unsigned>
auto gray_code<Unsigned>::operator&=(gray_code other) noexcept
    -> gray_code&
{
    value &= other.value;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator&=(value_type other) noexcept
    -> gray_code&
{
    value &= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator&=(bool other) noexcept
    -> gray_code&
{
    value &= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator|=(gray_code other) noexcept
    -> gray_code&
{
    value |= other.value;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator|=(value_type other) noexcept
    -> gray_code&
{
    value |= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator|=(bool other) noexcept
    -> gray_code&
{
    value |= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator^=(gray_code other) noexcept
    -> gray_code&
{
    value ^= other.value;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator^=(value_type other) noexcept
    -> gray_code&
{
    value ^= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator^=(bool other) noexcept
    -> gray_code&
{
    value ^= other;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator>>=(std::size_t pos) noexcept
    -> gray_code&
{
    value >>= pos;
    return *this;
}

template<typename Unsigned>
auto gray_code<Unsigned>::operator<<=(std::size_t pos) noexcept
    -> gray_code&
{
    value <<= pos;
    return *this;
}

////////////////////////////////////////////////////////////
// Construction function

template<typename Unsigned>
constexpr auto gray(Unsigned value) noexcept
    -> gray_code<Unsigned>
{
    return gray_code<Unsigned>(value);
}

////////////////////////////////////////////////////////////
// Comparison operations

template<typename Unsigned>
constexpr auto operator==(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
    -> bool
{
    return lhs.value == rhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
    -> bool
{
    return lhs.value != rhs.value;
}

template<typename Unsigned>
constexpr auto operator==(gray_code<Unsigned> lhs, Unsigned rhs) noexcept
    -> bool
{
    return (rhs ^ (rhs >> 1)) == lhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(gray_code<Unsigned> lhs, Unsigned rhs) noexcept
    -> bool
{
    return (rhs ^ (rhs >> 1)) != lhs.value;
}

template<typename Unsigned>
constexpr auto operator==(Unsigned lhs, gray_code<Unsigned> rhs) noexcept
    -> bool
{
    return (lhs ^ (lhs >> 1)) == rhs.value;
}

template<typename Unsigned>
constexpr auto operator!=(Unsigned lhs, gray_code<Unsigned> rhs) noexcept
    -> bool
{
    return (lhs ^ (lhs >> 1)) != rhs.value;
}

////////////////////////////////////////////////////////////
// Bitwise operations

template<typename Unsigned>
auto operator&(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs &= rhs;
}

template<typename Unsigned>
auto operator|(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs |= rhs;
}

template<typename Unsigned>
auto operator^(gray_code<Unsigned> lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs ^= rhs;
}

template<typename Unsigned>
auto operator~(gray_code<Unsigned> val) noexcept
    -> gray_code<Unsigned>
{
    val.value = ~val.value;
    return val;
}

template<typename Unsigned>
auto operator>>(gray_code<Unsigned> val, std::size_t pos) noexcept
    -> gray_code<Unsigned>
{
    return val >>= pos;
}

template<typename Unsigned>
auto operator<<(gray_code<Unsigned> val, std::size_t pos) noexcept
    -> gray_code<Unsigned>
{
    return val <<= pos;
}

////////////////////////////////////////////////////////////
// Bitwise operations with bool

template<typename Unsigned>
auto operator&(gray_code<Unsigned> lhs, bool rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs &= rhs;
}

template<typename Unsigned>
auto operator&(bool lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return rhs &= lhs;
}

template<typename Unsigned>
auto operator|(gray_code<Unsigned> lhs, bool rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs |= rhs;
}

template<typename Unsigned>
auto operator|(bool lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return rhs |= lhs;
}

template<typename Unsigned>
auto operator^(gray_code<Unsigned> lhs, bool rhs) noexcept
    -> gray_code<Unsigned>
{
    return lhs ^= rhs;
}

template<typename Unsigned>
auto operator^(bool lhs, gray_code<Unsigned> rhs) noexcept
    -> gray_code<Unsigned>
{
    return rhs ^= lhs;
}

////////////////////////////////////////////////////////////
// Bitwise assignment operations

template<typename Unsigned>
auto operator&=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
    -> Unsigned&
{
    return lhs &= rhs.value;
}

template<typename Unsigned>
auto operator|=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
    -> Unsigned&
{
    return lhs |= rhs.value;
}

template<typename Unsigned>
auto operator^=(Unsigned& lhs, gray_code<Unsigned> rhs) noexcept
    -> Unsigned&
{
    return lhs ^= rhs.value;
}

////////////////////////////////////////////////////////////
// Utility functions

template<typename Unsigned>
auto swap(gray_code<Unsigned>& lhs, gray_code<Unsigned>& rhs) noexcept
    -> void
{
    std::swap(lhs, rhs);
}

////////////////////////////////////////////////////////////
// Mathematical functions

template<typename Unsigned>
auto is_even(gray_code<Unsigned> code) noexcept
    -> bool
{
    return not is_odd(code);
}

template<typename Unsigned>
auto is_odd(gray_code<Unsigned> code) noexcept
    -> bool
{
    // A gray code is odd when the number
    // of bits set in its representation
    // is odd

    #if defined(__GNUC__) || defined(__clang__)

        // Compiler intrinsics can be
        // insanely faster
        return bool(__builtin_parity(code.value));

    #else

        unsigned nb_bits{};
        for (auto val = code.value ; val ; ++nb_bits)
        {
            // clear the least significant bit set
            val &= val - 1;
        }
        return bool(nb_bits % 2);

    #endif
}
