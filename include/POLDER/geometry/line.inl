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

template<std::size_t N, typename T>
inline Line<N, T>::Line(const Point<N, T>& P1, const Point<N, T>& P2):
    P(P1),
    D(Direction<N, T>(P1, P2))
{
    POLDER_ASSERT(P1 != P2);
}

template<std::size_t N, typename T>
inline Line<N, T>::Line(const Point<N, T>& P, const Vector<N, T>& V):
    P(P),
    D(Direction<N, T>(V))
{}

template<std::size_t N, typename T>
inline Line<N, T>::Line(const Point<N, T>& P, const Direction<N, T>& D):
    P(P),
    D(D)
{}

template<std::size_t N, typename T>
inline Direction<N, T> Line<N, T>::direction() const
{
    return D;
}

template<std::size_t N, typename T>
inline Line<N, T>& Line<N, T>::operator=(const Line<N, T>& other)
{
    if (this != &other)
    {
        P = other.P;
        D = other.D;
    }
    return *this;
}

template<std::size_t N, typename T>
inline bool Line<N, T>::operator==(const Line<N, T>& other) const
{
    return D == other.D && other.includes(P);
}

template<std::size_t N, typename T>
inline bool Line<N, T>::operator!=(const Line<N, T>& other) const
{
    return !(*this == other);
}

template<std::size_t N, typename T>
bool Line<N, T>::includes(const Point<N, T>& P) const
{
    // Line equation:
        // X = px + t * dx
        // Y = py + t * dy
        // Z = pz + t * dz
        // Etc...
    // And so:
        // t = X - px (dx always equals 1)
        // t = (Y - py) / dy
        // t = (Z - pz) / dz
        // etc...
    // A point is included in the line if it satisfies the parametric
    // equation for all the coordinates

    const T t1 = P.x() - this->P.x();
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        const T t = (P[i] - this->P[i]) / D[i-1];
        if (not float_equal(t, t1))
        {
            return false;
        }
    }
    return true;
}

template<std::size_t N, typename T>
inline Point<N, T> Line<N, T>::point() const
{
    return P;
}
