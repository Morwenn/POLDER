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
Direction<N, T>::Direction()
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& pt):
    super{pt}
{
    normalize();
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& pt1, const Point<N, T>& pt2):
    Direction{pt2 - pt1}
{}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Vector<N, T>& vec):
    super{vec}
{
    normalize();
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Line<N, T>& line):
    Direction{line.direction()}
{}

////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Direction<N, T>::normalize()
    -> void
{
    using std::abs;
    using std::sqrt;

    // Compute the norm
    value_type tmp{};
    for (auto coord: coordinates)
    {
        tmp += coord*coord;
    }
    tmp = sqrt(tmp);

    // Divide by the norm
    for (auto& coord: coordinates)
    {
        coord /= tmp;
        coord = abs(coord);
    }
}

////////////////////////////////////////////////////////////
// Outside class operators - Comparison
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
    -> bool
{
    return std::equal(std::begin(lhs), std::end(lhs),
                      std::begin(rhs), std::end(rhs),
                      [](T a, T b)
                      {
                          return math::is_close(a, b);
                      });
}

template<std::size_t N, typename T>
auto operator!=(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
