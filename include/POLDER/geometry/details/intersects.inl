/*
 * Copyright (C) 2015 Morwenn
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
auto intersects(const Line<N, T>& line, const Hypersphere<N, T>& hs)
    -> bool
{
    using std::fma;
    using math::sqr;

    // Take an arbitrary point from the Line and its direction
    const auto& pt  = line.point();
    const auto& dir = line.direction();
    // Take the centre of the Hypersphere
    const auto& ctr = hs.centre;

    // Line equation:
        // X = px + t * dx
        // Y = py + t * dy
        // Z = pz + t * dz
        // Etc...

    // Hypersphere equations:
        // Two dimensions:   (X - xc)² + (Y - yc)² = R²
        // Three dimensions: (X - xc)² + (Y - yc)² + (Z - zc)² = R²
        // Four dimensions:  (X - xc)² + (Y - yc)² + (Z - zc)² + (W - wc)² = R²
        // Etc...

    // So we have:
        // a = dx² + dy² + ...
        // b = 2 * (dx(px-xc) + dy(py-yc) + ...)
        // c = (px² - 2xc*px + xc²) + (py² - 2yc*py + yc²) + ... - R²

    T a{}, b{}, c{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        a += sqr(dir[i]);
        b += dir[i] * (pt[i] - ctr[i]);
        c += fma(pt[i], pt[i] - 2*ctr[i], sqr(ctr[i]));
    }
    b *= 2;
    c -= sqr(hs.radius);

    // Compute the results of the equation to find t
    auto t = math::quadratic(a, b, c);
    return t[0].imag() == 0 && t[1].imag() == 0;
}

template<std::size_t N, typename T>
auto intersects(const Hypersphere<N, T>& hs, const Line<N, T>& line)
    -> bool
{
    return intersects(line, hs);
}

template<std::size_t N, typename T>
auto intersects(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
    -> bool
{
    using std::abs;

    auto dist = distance(lhs.centre, rhs.centre);
    if (dist > lhs.radius + rhs.radius)
    {
        // The hyperspheres are distant
        return false;
    }
    if (abs(lhs.radius - rhs.radius) > dist)
    {
        // One of the hyperspheres is in the other
        return false;
    }
    return true;
}
