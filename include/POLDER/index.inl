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

template<std::size_t N>
index<N>::index()
    = default;

template<std::size_t N>
index<N>::index(const index<N>& other)
    = default;

template<std::size_t N>
index<N>::index(index<N>&& other)
    = default;

template<std::size_t N>
template<typename... Indices>
index<N>::index(Indices... indices)
{
    static_assert(sizeof...(Indices) == N,
                  "Wrong number of arguments to construct the index.");
    construct(indices...);
}

template<std::size_t N>
auto index<N>::operator=(const index<N>& other)
    -> index&
    = default;

template<std::size_t N>
auto index<N>::operator=(index<N>&& other)
    -> index&
    = default;

template<std::size_t N>
auto index<N>::operator[](std::size_t ind) const
    -> std::size_t
{
    return _indices[ind];
}

template<std::size_t N>
template<typename... Args>
auto index<N>::construct(std::size_t head, Args... tail)
    -> void
{
    _indices[N-sizeof...(Args)-1] = head;
    construct(tail...);
}

template<std::size_t N>
auto index<N>::construct(std::size_t head)
    -> void
{
    _indices[N-1] = head;
}

template<std::size_t N>
auto operator==(const index<N>& lhs, const index<N>& rhs)
    -> bool
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
template<std::size_t N>
auto operator!=(const index<N>& lhs, const index<N>& rhs)
    -> bool
{
    return !(lhs == rhs);
}
