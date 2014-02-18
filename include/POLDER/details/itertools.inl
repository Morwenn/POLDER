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
class RangeObject
{
    private:

        constexpr RangeObject(int end) noexcept:
            _i(0),
            _end(end),
            _step(1),
            _sup(end >= 0)
        {}

        constexpr RangeObject(int begin, int end, unsigned int step) noexcept:
            _i(begin),
            _end(end),
            _step(step),
            _sup(end >= begin)
        {}

    public:

        constexpr auto begin() noexcept
            -> const RangeObject&
        {
            return *this;
        }

        constexpr auto end() const noexcept
            -> const RangeObject&
        {
            return *this;
        }

        constexpr auto operator!=(const RangeObject&) const noexcept
            -> bool
        {
            return _sup ? (_i < _end) : (_i > _end);
        }

        inline auto operator++() noexcept
            -> void
        {
            if (_sup)
            {
                _i += _step;
            }
            else
            {
                _i -= _step;
            }
        }

        constexpr auto operator*() const noexcept
            -> const int&
        {
            return _i;
        }

    private:

        int _i;
        const int _end;
        const unsigned int _step;
        const bool _sup;

    friend constexpr auto range(int) noexcept
        -> RangeObject;
    friend constexpr auto range(int, int, unsigned int) noexcept
        -> RangeObject;
};

constexpr auto range(int end) noexcept
    -> RangeObject
{
    return { end };
}

constexpr auto range(int begin, int end, unsigned int step) noexcept
    -> RangeObject
{
    return { begin, end, step };
}


////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////
template<typename BidirectionalIterable>
class ReversedObject
{
    private:

        BidirectionalIterable& _iterable;

        ReversedObject(BidirectionalIterable&& iterable):
            _iterable(iterable)
        {}

    public:

        using value_type                = typename std::decay<decltype(*std::begin(_iterable))>::type;
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = typename std::remove_reference<decltype(itertools::rbegin(_iterable))>::type;
        using const_iterator            = typename std::remove_reference<decltype(itertools::rbegin(_iterable))>::type;
        using reverse_iterator          = decltype(std::begin(_iterable));
        using const_reverse_iterator    = decltype(std::begin(_iterable));
        using iterator_category         = typename std::iterator_traits<iterator>::iterator_category;

        // Iterator functions
        auto begin() -> iterator
            { return itertools::rbegin(_iterable); }
        auto begin() const -> const_iterator
            { return itertools::rbegin(_iterable); }
        auto cbegin() const -> const_iterator
            { return itertools::rbegin(_iterable); }
        auto end() -> iterator
            { return itertools::rend(_iterable); }
        auto end() const -> const_iterator
            { return itertools::rend(_iterable); }
        auto cend() const -> const_iterator
            { return itertools::rend(_iterable); }

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return std::begin(_iterable); }
        auto rbegin() const -> const_reverse_iterator
            { return std::begin(_iterable); }
        auto crbegin() const -> const_reverse_iterator
            { return std::begin(_iterable); }
        auto rend() -> reverse_iterator
            { return std::end(_iterable); }
        auto rend() const -> const_reverse_iterator
            { return std::end(_iterable); }
        auto crend() const -> const_reverse_iterator
            { return std::end(_iterable); }

    friend auto reversed<>(BidirectionalIterable&&)
        -> ReversedObject;
};

template<typename BidirectionalIterable>
inline auto reversed(BidirectionalIterable&& iterable)
    -> ReversedObject<BidirectionalIterable>
{
    return { std::forward<BidirectionalIterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename FlatIterable>
class FlatObject<FlatIterable, false>
{
    protected:

        FlatIterable& _iterable;

        FlatObject(FlatIterable&& iterable):
            _iterable(iterable)
        {}

    public:

        using value_type        = typename std::decay<decltype(*_iterable.fbegin())>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = decltype(_iterable.fbegin());
        using const_iterator    = decltype(_iterable.cfbegin());
        using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

        // Iterator functions
        auto begin() -> iterator
            { return _iterable.fbegin(); }
        auto begin() const -> const_iterator
            { return _iterable.cfbegin(); }
        auto cbegin() const -> const_iterator
            { return _iterable.cfbegin(); }
        auto end() -> iterator
            { return _iterable.fend(); }
        auto end() const -> const_iterator
            { return _iterable.cfend(); }
        auto cend() const -> const_iterator
            { return _iterable.cfend(); }

    friend auto flat<>(FlatIterable&&)
        -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
class FlatObject<FlatIterable, true>:
    public FlatObject<FlatIterable, false>
{
    private:

        using super = FlatObject<FlatIterable, false>;
        using super::_iterable;

        FlatObject(FlatIterable&& iterable):
            FlatObject<FlatIterable, false>(iterable)
        {}

    public:

        using typename super::value_type;
        using typename super::reference;
        using typename super::pointer;
        using typename super::iterator;
        using typename super::const_iterator;
        using reverse_iterator          = decltype(_iterable.rfbegin());
        using const_reverse_iterator    = decltype(_iterable.crfbegin());
        using typename super::iterator_category;

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return _iterable.rfbegin(); }
        auto rbegin() const -> const_reverse_iterator
            { return _iterable.crfbegin(); }
        auto crbegin() const -> const_reverse_iterator
            { return _iterable.crfbegin(); }
        auto rend() -> reverse_iterator
            { return _iterable.rfend(); }
        auto rend() const -> const_reverse_iterator
            { return _iterable.crfend(); }
        auto crend() const -> const_reverse_iterator
            { return _iterable.crfend(); }

    friend auto flat<>(FlatIterable&&)
        -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
inline auto flat(FlatIterable&& iterable)
    -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>
{
    return { std::forward<FlatIterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class MapObject<T, Iterable, false>
{
    protected:

        const Iterable& _iterable;
        T (*_func)(const T&);
        decltype(std::begin(_iterable)) _begin;
        const decltype(std::end(_iterable)) _end;

        MapObject(T (*function)(const T&), Iterable&& iterable):
            _iterable(iterable),
            _func(function),
            _begin(std::begin(_iterable)),
            _end(std::end(_iterable))
        {}

    public:

        using value_type        = typename std::decay<decltype(*std::begin(_iterable))>::type;
        using difference_type   = std::ptrdiff_t;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = MapObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        // Iterator functions
        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const MapObject&) const
            -> bool
        {
            return _begin != _end;
        }

        auto operator++()
            -> void
        {
            ++_begin;
        }

        auto operator*() const
            -> value_type
        {
            return _func(*_begin);
        }

    friend auto map<>(T (*)(const T&), Iterable&&)
        -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
class MapObject<T, Iterable, true>:
    public MapObject<T, Iterable, false>
{
    private:

        using super = MapObject<T, Iterable, false>;
        using super::_iterable;
        using super::_func;
        using super::_begin;
        using super::_end;

        mutable bool _forward = true;
        decltype(itertools::rbegin(_iterable)) _rbegin;
        const decltype(itertools::rend(_iterable)) _rend;

        MapObject(T (*function)(const T&), Iterable&& iterable):
            super(function, iterable),
            _rbegin(itertools::rbegin(_iterable)),
            _rend(itertools::rend(_iterable))
        {}

    public:

        using typename super::value_type;
        using typename super::difference_type;
        using typename super::reference;
        using typename super::pointer;
        using iterator                  = MapObject&;
        using const_iterator            = const iterator;
        using reverse_iterator          = iterator;
        using const_reverse_iterator    = const_iterator;
        using iterator_category         = std::bidirectional_iterator_tag;

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return *this; }
        auto rbegin() const -> const_reverse_iterator
            { return *this; }
        auto crbegin() const -> const_reverse_iterator
            { return *this; }
        auto rend() -> reverse_iterator
            { return *this; }
        auto rend() const -> const_reverse_iterator
            { return *this; }
        auto crend() const -> const_reverse_iterator
            { return *this; }

        auto operator!=(const MapObject&) const
            -> bool
        {
            return _forward ? (_begin != _end) : (_rbegin != _rend);
        }

        auto operator++()
            -> void
        {
            if (_forward)
            {
                ++_begin;
            }
            else
            {
                ++_rbegin;
            }
        }

        auto operator*() const
            -> value_type
        {
            return _forward ? _func(*_begin) : _func(*_rbegin);
        }

    friend auto map<>(T (*)(const T&), Iterable&&)
        -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
inline auto map(T (*function)(const T&) , Iterable&& iterable)
    -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>
{
    return { function, std::forward<Iterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class FilterObject
{
    private:

        const Iterable& _iterable;
        bool (*_func)(const T&);
        decltype(std::begin(_iterable)) _begin;
        const decltype(std::end(_iterable)) _end;

        FilterObject(bool (*function)(const T&), Iterable&& iterable):
            _iterable(iterable),
            _func(function),
            _begin(std::begin(_iterable)),
            _end(std::end(_iterable))
        {}

    public:

        using value_type        = typename std::decay<decltype(*std::begin(_iterable))>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = FilterObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const FilterObject&) const
            -> bool
        {
            return _begin != _end;
        }

        auto operator++()
            -> void
        {
            do
            {
                ++_begin;
            }
            while (_func(*_begin) == false && _begin != _end);
        }

        auto operator*() const
            -> value_type
        {
            return *_begin;
        }

    friend auto filter<>(bool (*)(const T&), Iterable&&)
        -> FilterObject;
};

template<typename T, typename Iterable>
inline auto filter(bool (*function)(const T&) , Iterable&& iterable)
    -> FilterObject<T, Iterable>
{
    return { function, std::forward<Iterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ChainObject:
    private ChainObject<Iterables...>
{
    private:

        First& _first;
        decltype(std::begin(_first)) _iter;

        using super = ChainObject<Iterables...>;

    public:

        using typename super::value_type;
        using typename super::reference;
        using typename super::pointer;
        using iterator          = ChainObject&;
        using const_iterator    = const iterator;
        using typename super::iterator_category;

        ChainObject(First&& first, Iterables&&... iterables):
            super(std::forward<Iterables>(iterables)...),
            _first(first),
            _iter(std::begin(first))
        {}

        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const ChainObject&) const
            -> bool
        {
            return super::operator!=(*this);
        }

        auto operator++()
            -> void
        {
            if (_iter != std::end(_first))
            {
                ++_iter;
            }
            else
            {
                super::operator++();
            }
        }

        auto operator*() const
            -> reference
        {
            if (_iter != std::end(_first))
            {
                return *_iter;
            }
            return super::operator*();
        }
};

template<typename First>
class ChainObject<First>
{
    private:

        First& _first;
        decltype(std::begin(_first)) _iter;

    public:

        using value_type        = typename std::decay<decltype(*_iter)>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = ChainObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        ChainObject(First&& first):
            _first(first),
            _iter(std::begin(first))
        {}

        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const ChainObject&) const
            -> bool
        {
            return _iter != std::end(_first);
        }

        auto operator++()
            -> void
        {
            ++_iter;
        }

        auto operator*() const
            -> reference
        {
            return *_iter;
        }
};

template<typename... Iterables>
inline auto chain(Iterables&&... iterables)
    -> ChainObject<Iterables...>
{
    static_assert(is_same<typename std::decay<Iterables>::type::value_type...>::value,
                  "different value_type for arguments passed to chain");

    return { std::forward<Iterables>(iterables)... };
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ZipObject:
    public ZipObject<typename std::decay<Iterables>::type...>
{
    private:

        const First& _first;
        decltype(std::begin(_first)) _iter;

        using super = ZipObject<typename std::decay<Iterables>::type...>;

    public:

        using value_type = decltype(
            std::tuple_cat(
                std::make_tuple(*_iter),
                super().operator*()
            )
        );
        using reference = value_type&;
        using pointer   = value_type*;
        using iterator          = ZipObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        ZipObject():
            super(std::forward<typename std::decay<Iterables>::type>(Iterables())...),
            _first(First())
        {}

        ZipObject(First&& first, Iterables&&... iterables):
            super(std::forward<typename std::decay<Iterables>::type>(iterables)...),
            _first(first),
            _iter(std::begin(first))
        {}

        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const ZipObject&) const
            -> bool
        {
            return _iter != std::end(_first);
        }

        auto operator++()
            -> void
        {
            ++_iter;
            super::operator++();
        }

        auto operator*() const
            -> value_type
        {
            return std::tuple_cat(
                    std::make_tuple(*_iter),
                    super::operator*()
                );
        }
};

template<typename First>
class ZipObject<First>
{
    private:

        const First& _first;
        decltype(std::begin(_first)) _iter;

    public:

        using value_type    = decltype(std::make_tuple(*_iter));
        using reference     = value_type&;
        using pointer       = value_type*;
        using iterator          = ZipObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        ZipObject():
            _first(First())
        {}

        ZipObject(First&& first):
            _first(first),
            _iter(std::begin(_first))
        {}

        auto begin() -> iterator
            { return *this; }
        auto begin() const -> const_iterator
            { return *this; }
        auto cbegin() const -> const_iterator
            { return *this; }
        auto end() -> iterator
            { return *this; }
        auto end() const -> const_iterator
            { return *this; }
        auto cend() const -> const_iterator
            { return *this; }

        auto operator!=(const ZipObject&) const
            -> bool
        {
            return _iter != std::end(_first);
        }

        auto operator++()
            -> void
        {
            ++_iter;
        }

        auto operator*() const
            -> value_type
        {
            return std::make_tuple(*_iter);
        }
};

template<typename... Iterables>
inline auto zip(Iterables&&... iterables)
    -> ZipObject<Iterables...>
{
    return { std::forward<Iterables>(iterables)... };
}

////////////////////////////////////////////////////////////
template<std::size_t N, typename Iterator>
get_iterator<N, Iterator>::get_iterator()
    = default;

template<std::size_t N, typename Iterator>
get_iterator<N, Iterator>::get_iterator(Iterator it):
    _current(it)
{}

template<std::size_t N, typename Iterator>
template<typename U>
get_iterator<N, Iterator>::get_iterator(const get_iterator<N, U>& other):
    _current(other.base())
{}

template<std::size_t N, typename Iterator>
template<typename U>
auto get_iterator<N, Iterator>::operator=(const get_iterator<N, U>& other)
    -> get_iterator&
{
    if (&other != this)
    {
        _current = other.base();
    }
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::base() const
    -> Iterator
{
    return _current;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator*() const
    -> reference
{
    return std::get<N>(*_current);
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator->() const
    -> pointer
{
    return &(operator*());
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator++()
    -> get_iterator&
{
    ++_current;
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator++(int)
    -> get_iterator&
{
    auto tmp = *this;
    ++_current;
    return tmp;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator--()
    -> get_iterator&
{
    --_current;
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator--(int)
    -> get_iterator&
{
    auto tmp = *this;
    --_current;
    return tmp;
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator==(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return lhs.base() == rhs.base();
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator!=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator<(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return lhs.base() < rhs.base();
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator<=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator>(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return rhs < lhs;
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator>=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(lhs < rhs);
}
