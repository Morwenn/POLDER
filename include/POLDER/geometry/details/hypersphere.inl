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
Hypersphere<N, T>::Hypersphere()
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& centre, T radius):
    centre{centre},
    radius{radius}
{}

template<std::size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& centre, const Vector<N, T>& vec):
    centre{centre},
    radius{vec.norm()}
{}

template<std::size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& centre, const Point<N, T>& pt):
    centre{centre},
    radius{(pt-centre).norm()}
{}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Hypersphere<N, T>::includes(const Point<N, T>& pt) const
    -> bool
{
    // Hypersphere equation:
        // Two dimensions:   (x - xc)² + (y - yc)² = R²
        // Three dimensions: (x - xc)² + (y - yc)² + (z - zc)² = R²
        // Four dimensions:  (x - xc)² + (y - yc)² + (z - zc)² + (w - wc)² = R²
        // Etc...
    // A point is included in the hypersphere if its distance to the centre equals the radius
    // Actually, the above equations are used to spare the square root computation

    value_type res{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        value_type tmp = pt[i] - centre[i];
        res += tmp * tmp;
    }
    return math::is_close(res, radius*radius);
}

////////////////////////////////////////////////////////////
// Outside class operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
    -> bool
{
    return lhs.centre == rhs.centre
        && math::is_close(lhs.radius, rhs.radius);
}

template<std::size_t N, typename T>
auto operator!=(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
