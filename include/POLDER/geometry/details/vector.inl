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
// Implementation details
////////////////////////////////////////////////////////////

namespace details
{
    template<std::size_t N, typename T>
    auto norm(math::norm::manhattan, const Vector<N, T>& vec)
        -> T
    {
        using std::abs;

        T res{};
        for (auto coord: vec)
        {
            res += abs(coord);
        }
        return res;
    }

    template<std::size_t N, typename T>
    auto norm(math::norm::euclidean, const Vector<N, T>& vec)
        -> T
    {
        using std::sqrt;

        T res{};
        for (auto coord: vec)
        {
            res += coord * coord;
        }
        return sqrt(res);
    }

    template<std::size_t N, typename T>
    auto norm(math::norm::uniform, const Vector<N, T>& vec)
        -> T
    {
        using std::abs;

        T res = abs(vec[0]);
        for (std::size_t i = 1 ; i < N ; ++i)
        {
            T tmp = abs(vec[i]);
            if (tmp > res)
            {
                res = tmp;
            }
        }
        return res;
    }

    template<std::size_t N, typename T>
    auto norm(math::norm::p, const Vector<N, T>& vec, unsigned p)
        -> T
    {
        using std::abs;
        using std::pow;

        T res{};
        for (auto coord: vec)
        {
            auto tmp = abs(coord);
            res += pow(tmp, p);
        }
        return pow(res, 1.0/p);
    }
}

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Vector<N, T>::Vector()
    = default;

template<std::size_t N, typename T>
template<typename... Args>
Vector<N, T>::Vector(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Vector constructed with wrong number of coordinates.");
    this->construct(args...);
}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Point<N, T>& pt):
    super{pt}
{}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Direction<N, T>& dir):
    super{dir}
{}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Point<N, T>& origin, const Point<N, T>& target):
    Vector{target - origin}
{}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Line<N, T>& line):
    Vector{line.direction()}
{}

////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto Vector<N, T>::operator+=(const Vector& other)
    -> Vector&
{
    for_each(
        std::begin(coordinates),
        std::end(coordinates),
        std::begin(other.coordinates),
        plus_assign()
    );
    return *this;
}

template<std::size_t N, typename T>
auto Vector<N, T>::operator-=(const Vector& other)
    -> Vector&
{
    for_each(
        std::begin(coordinates),
        std::end(coordinates),
        std::begin(other.coordinates),
        minus_assign()
    );
    return *this;
}

template<std::size_t N, typename T>
auto Vector<N, T>::operator*=(value_type val)
    -> Vector&
{
    for (auto& coord: coordinates)
    {
        coord *= val;
    }
    return *this;
}

template<std::size_t N, typename T>
auto Vector<N, T>::operator/=(value_type val)
    -> Vector&
{
    for (auto& coord: coordinates)
    {
        coord /= val;
    }
    return *this;
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto Vector<N, T>::direction() const
    -> Direction<N, T>
{
    return Direction<N, T>(*this);
}

template<std::size_t N, typename T>
template<typename Norm>
auto Vector<N, T>::norm() const
    -> value_type
{
    return details::norm(Norm{}, *this);
}

template<std::size_t N, typename T>
template<typename Norm>
auto Vector<N, T>::norm(unsigned p) const
    -> value_type
{
    return details::norm(Norm{}, *this, p);
}

////////////////////////////////////////////////////////////
// Outside class operators - Comparison
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> bool
{
    return std::equal(std::begin(lhs), std::end(lhs),
                      std::begin(rhs), std::end(rhs),
                      [](T a, T b)
                      {
                          return math::is_close(a, b);
                      });
}

template<std::size_t N, typename T>
auto operator!=(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Outside class operators - Vector arithmetic
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto operator+(Vector<N, T> lhs, const Vector<N, T>& rhs)
    -> Vector<N, T>
{
    return lhs += rhs;
}

template<std::size_t N, typename T>
inline auto operator-(Vector<N, T> lhs, const Vector<N, T>& rhs)
    -> Vector<N, T>
{
    return lhs -= rhs;
}

template<std::size_t N, typename T>
auto operator*(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> T
{
    T res{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        res += lhs[i] * rhs[i];
    }
    return res;
}

template<std::size_t N, typename T>
auto operator-(Vector<N, T> vec)
    -> Vector<N, T>
{
    return vec *= -1;
}

////////////////////////////////////////////////////////////
// Outside class operators - Vector-scalar arithmetic
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto operator*(Vector<N, T> vec, T val)
    -> Vector<N, T>
{
    return vec *= val;
}

template<std::size_t N, typename T>
inline auto operator*(T val, Vector<N, T> vec)
    -> Vector<N, T>
{
    return vec *= val;
}

template<std::size_t N, typename T>
inline auto operator/(Vector<N, T> vec, T val)
    -> Vector<N, T>
{
    return vec /= val;
}
