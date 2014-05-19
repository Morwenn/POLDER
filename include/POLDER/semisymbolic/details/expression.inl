/*
 * Copyright (C) 2014 Morwenn
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
// Expression

template<typename Expr>
Expression<Expr>::operator Expr&()
{
    return static_cast<Expr&>(*this);
}

template<typename Expr>
Expression<Expr>::operator const Expr&() const
{
    return static_cast<const Expr&>(*this);
}

template<typename Expr>
Expression<Expr>::operator value_type() const
{
    return static_cast<const Expr&>(*this).operator value_type();
}

////////////////////////////////////////////////////////////
// Arithmetic expressions

template<typename Lhs, typename Rhs>
Add<Lhs, Rhs>::Add(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Add<Lhs, Rhs>::operator value_type() const
{
    return value_type(lhs) + value_type(rhs);
}

template<typename Lhs, typename Rhs>
Sub<Lhs, Rhs>::Sub(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Sub<Lhs, Rhs>::operator value_type() const
{
    return value_type(lhs) - value_type(rhs);
}

template<typename Lhs, typename Rhs>
Mul<Lhs, Rhs>::Mul(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Mul<Lhs, Rhs>::operator value_type() const
{
    return value_type(lhs) * value_type(rhs);
}

template<typename Lhs, typename Rhs>
Div<Lhs, Rhs>::Div(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Div<Lhs, Rhs>::operator value_type() const
{
    return value_type(lhs) / value_type(rhs);
}

template<typename Lhs, typename Rhs>
Mod<Lhs, Rhs>::Mod(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Mod<Lhs, Rhs>::operator value_type() const
{
    return value_type(lhs) % value_type(rhs);
}

////////////////////////////////////////////////////////////
// Equality expressions

template<typename Lhs, typename Rhs>
Eq<Lhs, Rhs>::Eq(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Eq<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) == val_t(rhs);
}

template<typename Lhs, typename Rhs>
Ne<Lhs, Rhs>::Ne(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Ne<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) != val_t(rhs);
}

////////////////////////////////////////////////////////////
// Relational expressions

template<typename Lhs, typename Rhs>
Lt<Lhs, Rhs>::Lt(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Lt<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) < val_t(rhs);
}

template<typename Lhs, typename Rhs>
Le<Lhs, Rhs>::Le(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Le<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) <= val_t(rhs);
}

template<typename Lhs, typename Rhs>
Gt<Lhs, Rhs>::Gt(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Gt<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) > val_t(rhs);
}

template<typename Lhs, typename Rhs>
Ge<Lhs, Rhs>::Ge(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs):
    lhs{lhs},
    rhs{rhs}
{}

template<typename Lhs, typename Rhs>
Ge<Lhs, Rhs>::operator value_type() const
{
    using val_t = value_type_t<Lhs>;
    return val_t(lhs) >= val_t(rhs);
}

////////////////////////////////////////////////////////////
// Arithmetic operators

template <typename Lhs, typename Rhs>
auto operator+(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Add<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator-(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Sub<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator*(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Mul<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator/(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Div<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator%(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Mod<Lhs, Rhs>
{
   return { lhs, rhs };
}

////////////////////////////////////////////////////////////
// Equality operators

template <typename Lhs, typename Rhs>
auto operator==(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Eq<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator!=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Ne<Lhs, Rhs>
{
   return { lhs, rhs };
}

////////////////////////////////////////////////////////////
// Relational operators

template <typename Lhs, typename Rhs>
auto operator<(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Lt<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator<=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Le<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator>(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Gt<Lhs, Rhs>
{
   return { lhs, rhs };
}

template <typename Lhs, typename Rhs>
auto operator>=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
    -> Ge<Lhs, Rhs>
{
   return { lhs, rhs };
}
