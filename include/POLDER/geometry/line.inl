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

template<size_t N>
inline Line<N>::Line(const Point<N>& P1, const Point<N>& P2):
    P(P1),
    D(Direction<N>(P1, P2))
{
    assert(P1 != P2);
}

template<size_t N>
inline Line<N>::Line(const Point<N>& P, const Vector<N>& V):
    P(P),
    D(Direction<N>(V))
{}

template<size_t N>
inline Line<N>::Line(const Point<N>& P, const Direction<N>& D):
    P(P),
    D(D)
{}

template<size_t N>
inline Direction<N> Line<N>::direction() const
{
    return D;
}

template<size_t N>
inline Line<N>& Line<N>::operator=(const Line<N>& other)
{
    if (this != &other)
    {
        P = other.P;
        D = other.D;
    }
    return *this;
}

template<size_t N>
inline bool Line<N>::operator==(const Line<N>& other) const
{
    return D == other.D && other.includes(P);
}

template<size_t N>
inline bool Line<N>::operator!=(const Line<N>& other) const
{
    return !(*this == other);
}

template<size_t N>
bool Line<N>::includes(const Point<N>& P) const
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

    const double t1 = P.x() - this->P.x();
    for (size_t i = 1 ; i < N ; ++i)
    {
        const double t = (P[i] - this->P[i]) / D[i-1];
        if (!round_equal(t, t1))
        {
            return false;
        }
    }
    return true;
}

template<size_t N>
inline Point<N> Line<N>::point() const
{
    return P;
}
