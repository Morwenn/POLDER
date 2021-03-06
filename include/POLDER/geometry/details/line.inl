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
Line<N, T>::Line()
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Line<N, T>::Line(const Point<N, T>& pt1, const Point<N, T>& pt2):
    _point{pt1},
    _dir{pt1, pt2}
{
    POLDER_ASSERT(pt1 != pt2);
}

template<std::size_t N, typename T>
Line<N, T>::Line(const Point<N, T>& pt, const Vector<N, T>& vec):
    _point{pt},
    _dir{vec}
{}

template<std::size_t N, typename T>
Line<N, T>::Line(const Point<N, T>& pt, const Direction<N, T>& dir):
    _point{pt},
    _dir{dir}
{}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Line<N, T>::includes(const Point<N, T>& pt) const
    -> bool
{
    // Line equation:
        // X = px + t * dx
        // Y = py + t * dy
        // Z = pz + t * dz
        // Etc...
    // And so:
        // t = (X - px) / dx
        // t = (Y - py) / dy
        // t = (Z - pz) / dz
        // etc...
    // A point is included in the line if it satisfies the parametric
    // equation for all its coordinates

    auto vec = pt - _point;
    T t{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        // Handle the case where the line is
        // parallel to an axis
        if (math::is_close(_dir[i], T{0}))
        {
            if (math::is_close(vec[i], T{0}))
            {
                continue;
            }
            return false;
        }

        // Regular case
        if (math::is_close(t, T{0}))
        {
            t = vec[i] / _dir[i];
        }
        else
        {
            T tmp = vec[i] / _dir[i];
            if (not math::is_close(tmp, t))
            {
                return false;
            }
        }
    }
    return true;
}

template<std::size_t N, typename T>
inline auto Line<N, T>::direction() const
    -> Direction<N, T>
{
    return _dir;
}

template<std::size_t N, typename T>
inline auto Line<N, T>::point() const
    -> Point<N, T>
{
    return _point;
}

////////////////////////////////////////////////////////////
// Outside class operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Line<N, T>& lhs, const Line<N, T>& rhs)
    -> bool
{
    return lhs.direction() == rhs.direction()
        && lhs.includes(rhs.point());
}

template<std::size_t N, typename T>
auto operator!=(const Line<N, T>& lhs, const Line<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
