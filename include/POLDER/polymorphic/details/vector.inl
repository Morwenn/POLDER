/*
 * Copyright (C) 2014-2015 Morwenn
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
// Modifying operations

template<typename Interface, template<typename> class Adapter>
template<typename T, typename... Args>
auto vector<Interface, Adapter>::emplace_back(Args&&... args)
    -> void
{
    auto ptr = std::make_unique<Adapter<T>>(std::forward<Args>(args)...);
    _entities.push_back(std::move(ptr));
}

template<typename Interface, template<typename> class Adapter>
template<typename T>
auto vector<Interface, Adapter>::push_back(T&& other)
    -> void
{
    auto ptr = new Adapter<T>{ std::forward<T>(other) };
    _entities.emplace_back(ptr);
}

////////////////////////////////////////////////////////////
// Element access operations

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::at(size_type pos)
    -> reference
{
    return *_entities.at(pos);
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::at(size_type pos) const
    -> const_reference
{
    return *_entities.at(pos);
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::operator[](size_type pos)
    -> reference
{
    return *_entities[pos];
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::operator[](size_type pos) const
    -> const_reference
{
    return *_entities[pos];
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::front()
    -> reference
{
    return *_entities.front();
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::front() const
    -> const_reference
{
    return *_entities.front();
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::back()
    -> reference
{
    return *_entities.back();
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::back() const
    -> const_reference
{
    return *_entities.back();
}

////////////////////////////////////////////////////////////
// Iterator operations

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::begin()
    -> iterator
{
    return make_indirect_iterator(_entities.begin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::begin() const
    -> const_iterator
{
    return make_indirect_iterator(_entities.begin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::cbegin() const
    -> const_iterator
{
    return make_indirect_iterator(_entities.cbegin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::end()
    -> iterator
{
    return make_indirect_iterator(_entities.end());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::end() const
    -> const_iterator
{
    return make_indirect_iterator(_entities.end());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::cend() const
    -> const_iterator
{
    return make_indirect_iterator(_entities.cend());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::rbegin()
    -> reverse_iterator
{
    return make_indirect_iterator(_entities.rbegin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::rbegin() const
    -> const_reverse_iterator
{
    return make_indirect_iterator(_entities.rbegin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::crbegin() const
    -> const_reverse_iterator
{
    return make_indirect_iterator(_entities.crbegin());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::rend()
    -> reverse_iterator
{
    return make_indirect_iterator(_entities.rend());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::rend() const
    -> const_reverse_iterator
{
    return make_indirect_iterator(_entities.rend());
}

template<typename Interface, template<typename> class Adapter>
auto vector<Interface, Adapter>::crend() const
    -> const_reverse_iterator
{
    return make_indirect_iterator(_entities.crend());
}
