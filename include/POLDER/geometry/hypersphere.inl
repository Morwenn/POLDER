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
inline Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, T radius):
    _center(center),
    _radius(radius)
{}

template<std::size_t N, typename T>
inline Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, const Vector<N, T>& V):
    _center(center),
    _radius(V.norm())
{}

template<std::size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, const Point<N, T>& P):
    _center(center),
    _radius(0.0)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        const T tmp = P[i] - _center[i];
        _radius += tmp * tmp;
    }
    _radius = std::sqrt(_radius);
}

template<std::size_t N, typename T>
inline Point<N, T> Hypersphere<N, T>::center() const
{
    return _center;
}

template<std::size_t N, typename T>
inline T Hypersphere<N, T>::radius() const
{
    return _radius;
}

template<std::size_t N, typename T>
Hypersphere<N, T>& Hypersphere<N, T>::operator=(const Hypersphere<N, T>& other)
{
    if (this != &other)
    {
        _center = other.Center;
        _radius = other.Radius;
    }
    return *this;
}

template<std::size_t N, typename T>
bool Hypersphere<N, T>::includes(const Point<N, T>& P) const
{
    // Hypersphere equation:
        // Two dimensions:   (x - xc)² + (y - yc)² = R²
        // Three dimensions: (x - xc)² + (y - yc)² + (z - zc)² = R²
        // Four dimensions:  (x - xc)² + (y - yc)² + (z - zc)² + (w - wc)² = R²
        // Etc...
    // A point is included in the hypersphere if its distance to the center equals the radius
    // Actually, the above equations are used to spare the square root computation

    T res{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        const T temp = P[i] - _center[i];
        res += temp * temp;
    }
    return float_equal(res, _radius*_radius);
}

template<std::size_t N, typename T>
auto operator==(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
    -> bool
{
    return lhs.center() == rhs.center()
        && float_equal(lhs.radius(), rhs.radius());
}

template<std::size_t N, typename T>
auto operator!=(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
