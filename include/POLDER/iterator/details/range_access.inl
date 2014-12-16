/*
 * Copyright (C) 2014 Morwenn
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

template<typename T>
auto rbegin(T& iterable)
    -> decltype(iterable.rbegin())
{
    return iterable.rbegin();
}

template<typename T>
auto rbegin(const T& iterable)
    -> decltype(iterable.crbegin())
{
    return iterable.crbegin();
}

template<typename T, std::size_t N>
auto rbegin(T (&array)[N])
    -> std::reverse_iterator<T*>
{
    return std::reverse_iterator<T*>(std::end(array));
}

template<typename T>
auto rend(T& iterable)
    -> decltype(iterable.rend())
{
    return iterable.rend();
}

template<typename T>
auto rend(const T& iterable)
    -> decltype(iterable.crend())
{
    return iterable.crend();
}

template<typename T, std::size_t N>
auto rend(T (&array)[N])
    -> std::reverse_iterator<T*>
{
    return std::reverse_iterator<T*>(std::begin(array));
}
