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
auto intersection(const Line<N, T>& line, const Hypersphere<N, T>& hs)
    -> Object
{
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

    // Use the first coordinates (considering that dx = 1.0)
    auto a = T(1.0);
    auto b = pt[0] - ctr[0];
    auto c = std::fma(pt[0], pt[0] - 2*ctr[0], sqr(ctr[0]));

    // Use the other coordinates
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        a += dir[i-1] * dir[i-1];
        b += dir[i-1] * (pt[i] - ctr[i]);
        c += std::fma(pt[i], pt[i] - 2*ctr[i], sqr(ctr[i]));
    }
    b *= 2;
    c -= sqr(hs.radius);

    // Compute the results of the equation to find t
    auto t = math::quadratic(a, b, c);

    if (t.first.imag() != 0 || t.second.imag() != 0)
    {
        // There is no intersection
        // Return an empty object
        return Object();
    }

    auto t1 = t.first.real();
    auto t2 = t.second.real();

    if (float_equal(t1, t2))
    {
        // The solution is a unique point
        Point<N, T> res;

        res.x() = pt.x() + t1;
        for (std::size_t i = 1 ; i < N ; ++i)
        {
            // res[i] = pt[i] + t1 * ctr[i-1]
            res[i] = std::fma(t1, ctr[i-1], pt[i]);
        }
        return Object(res);
    }

    // In the other cases, the result is two points
    Point<N, T> res1, res2;

    res1.x() = pt.x() + t1;
    res2.x() = pt.x() + t2;
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        res1[i] = std::fma(t1, ctr[i-1], pt[i]);
        res2[i] = std::fma(t2, ctr[i-1], pt[i]);
    }

    return Object(std::make_pair(res1, res2));
}

template<std::size_t N, typename T>
inline auto intersection(const Hypersphere<N, T>& hs, const Line<N, T>& line)
    -> Object
{
    return intersection(line, hs);
}
