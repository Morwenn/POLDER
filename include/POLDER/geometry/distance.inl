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

namespace details
{
    template<std::size_t N, typename T, typename Norm>
    struct distance_helper_t;

    template<std::size_t N, typename T>
    struct distance_helper_t<N, T, math::norm::manhattan>
    {
        static auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
            -> T
        {
            T res = T(0);
            for (std::size_t i = 0 ; i < N ; ++i)
            {
                res += std::abs(p1[i] - p2[i]);
            }
            return res;
        }
    };

    template<std::size_t N, typename T>
    struct distance_helper_t<N, T, math::norm::euclidean>
    {
        static auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
            -> T
        {
            T res = T(0);
            for (std::size_t i = 0 ; i < N ; ++i)
            {
                auto tmp = std::abs(p1[i] - p2[i]);
                res += tmp * tmp;
            }
            return std::sqrt(res);
        }

        static auto distance(const Point<N, T>& p, const Hypersphere<N, T>& h)
            -> T
        {
            return std::abs(distance(p, h.center()) - h.radius());
        }
    };

    template<std::size_t N, typename T>
    struct distance_helper_t<N, T, math::norm::maximum>
    {
        static auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
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
    };

    template<std::size_t N, typename T>
    struct distance_helper_t<N, T, math::norm::canberra>
    {
        static auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
            -> T
        {
            T res = T(0);
            for (std::size_t i = 0 ; i < N ; ++i)
            {
                auto tmp = std::abs(p1[i] - p2[i]);
                tmp /= std::abs(p1[i]) + std::abs(p2[i]);
                res += tmp;
            }
            return res;
        }
    };

    template<std::size_t N, typename T>
    struct distance_helper_t<N, T, math::norm::p>
    {
        static auto distance(const Point<N, T>& p1, const Point<N, T>& p2, unsigned p)
            -> T
        {
            T res = T(0);
            for (std::size_t i = 0 ; i < N ; ++i)
            {
                auto tmp = std::abs(p1[i] - p2[i]);
                res += std::pow(tmp, p);
            }
            return std::pow(res, 1.0/p);
        }
    };
}

template<typename Norm, std::size_t N, typename T>
auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
    -> T
{
   return details::distance_helper_t<N, T, Norm>::distance(p1, p2);
}

template<typename Norm, std::size_t N, typename T>
auto distance(const Point<N, T>& p1, const Point<N, T>& p2, unsigned p)
    -> T
{
    return details::distance_helper_t<N, T, Norm>::distance(p1, p2, p);
}

template<typename Norm, std::size_t N, typename T>
auto distance(const Point<N, T>& p, const Hypersphere<N, T>& h)
    -> T
{
    return details::distance_helper_t<N, T, Norm>::distance(p, h);
}

template<typename Norm, std::size_t N, typename T>
auto distance(const Hypersphere<N, T>& h, const Point<N, T>& p)
    -> T
{
    return details::distance_helper_t<N, T, Norm>::distance(p, h);
}
