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

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Direction<N, T>&)
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& pt)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] = pt[i];
    }
    normalize();
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& pt1, const Point<N, T>& pt2):
    Direction<N, T>(pt2-pt1)
{}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Vector<N, T>& vec)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] = vec[i];
    }
    normalize();
}

template<std::size_t N, typename T>
inline Direction<N, T>::Direction(const Line<N, T>& line)
{
    *this = line.direction();
}

////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Direction<N, T>::normalize()
    -> void
{
    value_type tmp{};
    for (auto coord: coordinates)
    {
        tmp += coord*coord;
    }
    tmp = std::sqrt(tmp);
    for (auto& coord:coordinates)
    {
        coord /= tmp;
        coord = std::abs(coord);
    }
}

////////////////////////////////////////////////////////////
// Outside class operators - Comparison
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
    -> bool
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(),
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<std::size_t N, typename T>
auto operator!=(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
