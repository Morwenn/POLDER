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
#ifndef POLDER_SEMISYMBOLIC_EXPRESSION_H_
#define POLDER_SEMISYMBOLIC_EXPRESSION_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/utility.h>

namespace polder
{
namespace semisymbolic
{
    ////////////////////////////////////////////////////////////
    // Expression

    template<typename Expr>
    struct Expression
    {
        using value_type = value_type_t<Expr>;

        operator Expr&();
        operator const Expr&() const;

        operator value_type() const;
    };

    ////////////////////////////////////////////////////////////
    // Arithmetic expressions

    template<typename Lhs, typename Rhs>
    struct Add:
        Expression<Add<Lhs, Rhs>>
    {
        using typename Expression<Add<Lhs, Rhs>>::value_type;

        Lhs lhs;
        Rhs rhs;

        Add(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Sub:
        Expression<Sub<Lhs, Rhs>>
    {
        using typename Expression<Sub<Lhs, Rhs>>::value_type;

        Lhs lhs;
        Rhs rhs;

        Sub(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Mul:
        Expression<Mul<Lhs, Rhs>>
    {
        using typename Expression<Mul<Lhs, Rhs>>::value_type;

        Lhs lhs;
        Rhs rhs;

        Mul(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Div:
        Expression<Div<Lhs, Rhs>>
    {
        using typename Expression<Div<Lhs, Rhs>>::value_type;

        Lhs lhs;
        Rhs rhs;

        Div(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Mod:
        Expression<Mod<Lhs, Rhs>>
    {
        using typename Expression<Mod<Lhs, Rhs>>::value_type;

        Lhs lhs;
        Rhs rhs;

        Mod(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    ////////////////////////////////////////////////////////////
    // Equality expressions

    template<typename Lhs, typename Rhs>
    struct Eq:
        Expression<Eq<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Eq(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Ne:
        Expression<Ne<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Ne(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    ////////////////////////////////////////////////////////////
    // Relational expressions

    template<typename Lhs, typename Rhs>
    struct Lt:
        Expression<Lt<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Lt(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Le:
        Expression<Le<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Le(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Gt:
        Expression<Gt<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Gt(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    template<typename Lhs, typename Rhs>
    struct Ge:
        Expression<Ge<Lhs, Rhs>>
    {
        using value_type = bool;

        Lhs lhs;
        Rhs rhs;

        Ge(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs);

        operator value_type() const;
    };

    ////////////////////////////////////////////////////////////
    // Arithmetic operators

    template <typename Lhs, typename Rhs>
    auto operator+(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Add<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator-(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Sub<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator*(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Mul<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator/(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Div<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator%(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Mod<Lhs, Rhs>;

    ////////////////////////////////////////////////////////////
    // Equality operators

    template <typename Lhs, typename Rhs>
    auto operator==(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Eq<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator!=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Ne<Lhs, Rhs>;

    ////////////////////////////////////////////////////////////
    // Relational operators

    template <typename Lhs, typename Rhs>
    auto operator<(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Lt<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator<=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Le<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator>(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Gt<Lhs, Rhs>;

    template <typename Lhs, typename Rhs>
    auto operator>=(const Expression<Lhs>& lhs, const Expression<Rhs>& rhs)
        -> Ge<Lhs, Rhs>;

    #include "details/expression.inl"
}}

namespace polder
{
    ////////////////////////////////////////////////////////////
    // CRTP value_type propagation

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Add<Lhs, Rhs>>
    {
        using value_type = value_type_t<Lhs>;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Sub<Lhs, Rhs>>
    {
        using value_type = value_type_t<Lhs>;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Mul<Lhs, Rhs>>
    {
        using value_type = value_type_t<Lhs>;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Div<Lhs, Rhs>>
    {
        using value_type = value_type_t<Lhs>;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Mod<Lhs, Rhs>>
    {
        using value_type = value_type_t<Lhs>;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Eq<Lhs, Rhs>>
    {
        using value_type = bool;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Ne<Lhs, Rhs>>
    {
        using value_type = bool;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Lt<Lhs, Rhs>>
    {
        using value_type = bool;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Le<Lhs, Rhs>>
    {
        using value_type = bool;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Gt<Lhs, Rhs>>
    {
        using value_type = bool;
    };

    template<typename Lhs, typename Rhs>
    struct types_t<semisymbolic::Ge<Lhs, Rhs>>
    {
        using value_type = bool;
    };
}

#endif // POLDER_SEMISYMBOLIC_EXPRESSION_H_
