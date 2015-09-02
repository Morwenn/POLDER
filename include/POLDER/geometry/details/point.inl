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
// Defaulted functions
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Point<N, T>::Point()
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
template<typename... Args>
Point<N, T>::Point(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Point constructed with wrong number of coordinates.");
    this->construct(args...);
}

////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Point<N, T>::operator+=(const Vector<N, T>& vec)
    -> Point&
{
    for_each(
        std::begin(coordinates),
        std::end(coordinates),
        std::begin(vec),
        plus_assign()
    );
    return *this;
}

template<std::size_t N, typename T>
auto Point<N, T>::operator-=(const Vector<N, T>& vec)
    -> Point&
{
    for_each(
        std::begin(coordinates),
        std::end(coordinates),
        std::begin(vec),
        minus_assign()
    );
    return *this;
}

////////////////////////////////////////////////////////////
// Outside class operators - Comparison
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs),
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<std::size_t N, typename T>
auto operator!=(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Outside class operators - Relational operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator<(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return std::lexicographical_compare(
        std::begin(lhs), std::end(lhs),
        std::begin(rhs), std::end(rhs)
    );
}

template<std::size_t N, typename T>
auto operator<=(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<std::size_t N, typename T>
auto operator>(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return rhs < lhs;
}

template<std::size_t N, typename T>
auto operator>=(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return !(lhs < rhs);
}

////////////////////////////////////////////////////////////
// Outside class operators - Point-Vector arithmetic
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto operator+(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>
{
    return pt += vec;
}

template<std::size_t N, typename T>
inline auto operator+(const Vector<N, T>& vec, Point<N, T> pt)
    -> Point<N, T>
{
    return pt += vec;
}

template<std::size_t N, typename T>
inline auto operator-(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>
{
    return pt -= vec;
}

template<std::size_t N, typename T>
auto operator-(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> Vector<N, T>
{
    Vector<N, T> res;
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        res[i] = lhs[i] - rhs[i];
    }
    return res;
}
