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

namespace details
{
    ////////////////////////////////////////////////////////////
    // Implementation of distance between
    // - Point
    // - Point

    template<std::size_t N, typename T>
    auto distance(math::dist::manhattan,
                  const Point<N, T>& p1, const Point<N, T>& p2)
        -> T
    {
        T res{};
        for (std::size_t i = 0 ; i < N ; ++i)
        {
            res += std::abs(p1[i] - p2[i]);
        }
        return res;
    }

    template<std::size_t N, typename T>
    auto distance(math::dist::euclidean,
                  const Point<N, T>& p1, const Point<N, T>& p2)
        -> T
    {
        T res{};
        for (std::size_t i = 0 ; i < N ; ++i)
        {
            auto tmp = p1[i] - p2[i];
            res += tmp * tmp;
        }
        return std::sqrt(res);
    }

    template<std::size_t N, typename T>
    auto distance(math::dist::chebyshev,
                  const Point<N, T>& p1, const Point<N, T>& p2)
        -> T
    {
        T res = std::abs(p1[0] - p2[0]);
        for (std::size_t i = 1 ; i < N ; ++i)
        {
            T tmp = std::abs(p1[i] - p2[i]);
            if (tmp > res)
            {
                res = tmp;
            }
        }
        return res;
    }

    template<std::size_t N, typename T>
    auto distance(math::dist::canberra,
                  const Point<N, T>& p1, const Point<N, T>& p2)
        -> T
    {
        T res{};
        for (std::size_t i = 0 ; i < N ; ++i)
        {
            auto tmp = std::abs(p1[i] - p2[i]);
            tmp /= std::abs(p1[i]) + std::abs(p2[i]);
            res += tmp;
        }
        return res;
    }

    template<std::size_t N, typename T>
    auto distance(math::dist::minkowski,
                  const Point<N, T>& p1, const Point<N, T>& p2,
                  unsigned p)
        -> T
    {
        T res{};
        for (std::size_t i = 0 ; i < N ; ++i)
        {
            auto tmp = std::abs(p1[i] - p2[i]);
            res += std::pow(tmp, p);
        }
        return std::pow(res, T{1}/p);
    }

    ////////////////////////////////////////////////////////////
    // Implementation of distance between
    // - Point
    // - Hypersphere

    template<std::size_t N, typename T>
    auto distance(math::dist::euclidean,
                  const Point<N, T>& p, const Hypersphere<N, T>& hs)
        -> T
    {
        return std::abs(distance<math::dist::euclidean>(p, hs.centre) - hs.radius);
    }
}

////////////////////////////////////////////////////////////
// Distance between
// - Point
// - Point

template<typename Dist, std::size_t N, typename T>
auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
    -> T
{
    return details::distance(Dist{}, p1, p2);
}

template<typename Dist, std::size_t N, typename T>
auto distance(const Point<N, T>& p1, const Point<N, T>& p2, unsigned p)
    -> T
{
    return details::distance(Dist{}, p1, p2, p);
}

////////////////////////////////////////////////////////////
// Distance between
// - Point
// - Hypersphere

template<typename Dist, std::size_t N, typename T>
auto distance(const Point<N, T>& p, const Hypersphere<N, T>& h)
    -> T
{
    return details::distance(Dist{}, p, h);
}

template<typename Dist, std::size_t N, typename T>
auto distance(const Hypersphere<N, T>& h, const Point<N, T>& p)
    -> T
{
    return details::distance(Dist{}, p, h);
}
