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

template<typename Derived>
inline auto recursion_array<Derived>::operator()(std::size_t n)
    -> value_type
{
    return self(n);
}

template<typename Derived>
constexpr recursion_array<Derived>::recursion_array(std::initializer_list<value_type> vals):
    _values(std::begin(vals), std::end(vals))
{}

template<typename Derived>
auto recursion_array<Derived>::self(std::size_t n)
    -> value_type
{
    while (size() <= n)
    {
        // Compute and add the values to the vector
        _values.emplace_back(function(size()));
    }
    return _values[n];
}

template<typename Derived>
constexpr auto recursion_array<Derived>::size() const
    -> std::size_t
{
    return _values.size();
}

template<typename Derived>
auto recursion_array<Derived>::function(std::size_t n)
    -> value_type
{
    return static_cast<Derived&>(*this).function(n);
}
