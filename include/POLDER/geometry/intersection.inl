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

template<size_t N, typename T>
Object intersection(const Line<N, T>& L, const Hypersphere<N, T>& HS)
{
    // Take an arbitrary point from the Line and its direction
    const Point<N, T>& P = L.point();
    const Direction<N, T>& D = L.direction();
    // Take the center of the Hypersphere
    const Point<N, T>& C = HS.center();

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
    T a = 1.0;
    T b = P[0] - C[0];
    T c = std::fma(P[0], P[0] - 2*C[0], C[0]*C[0]);

    // Use the other coordinates
    for (size_t i = 1 ; i < N ; ++i)
    {
        a += D[i-1] * D[i-1];
        b += D[i-1] * (P[i] - C[i]);
        c += std::fma(P[i], P[i] - 2*C[i], C[i]*C[i]);
    }
    b *= 2;
    c -= HS.radius() * HS.radius();

    // Compute the results of the equation to find t
    auto t = math::quadratic(a, b, c);

    if (t.first.imag() != 0 || t.second.imag() != 0)
    {
        // There is no intersection
        // Return an empty object
        return Object();
    }

    T t1 = t.first.real();
    T t2 = t.second.real();

    if (float_equal(t1, t2))
    {
        // The solution is a unique point
        Point<N, T> res;

        res.x() = P.x() + t1;
        for (size_t i = 1 ; i < N ; ++i)
        {
            // res[i] = P[i] + t1 * C[i-1]
            res[i] = std::fma(t1, C[i-1], P[i]);
        }

        return Object(res);
    }

    // In the other cases, the result is two points
    Point<N, T> res1, res2;

    res1.x() = P.x() + t1;
    res2.x() = P.x() + t2;
    for (size_t i = 1 ; i < N ; ++i)
    {
        res1[i] = std::fma(t1, C[i-1], P[i]);
        res2[i] = std::fma(t2, C[i-1], P[i]);
    }

    return Object(std::make_pair(res1, res2));
}

template<size_t N, typename T>
inline Object intersection(const Hypersphere<N, T>& HS, const Line<N, T>& L)
{
    return intersection(L, HS);
}

template<size_t N, typename T>
Object intersection(const Line<N, T>& L1, const Line<N, T>& L2)
{
    // Take the directions of the lines
    const Direction<N, T>& D1 = L1.direction();
    const Direction<N, T>& D2 = L2.direction();
    // Take arbitrary points in the lines
    const Point<N, T>& P1 = L1.point();
    const Point<N, T>& P2 = L2.point();

    // Line equation:
        // X = px + t * dx
        // Y = py + t * dy
        // Z = pz + t * dz
        // Etc...


    /// TODO

    return Object();
}
