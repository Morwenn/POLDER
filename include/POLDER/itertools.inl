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

    friend constexpr auto range(int end) noexcept
        -> RangeObject;
    friend constexpr auto range(int begin, int end, unsigned int step) noexcept
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
auto rbegin(T& iter)
    -> decltype(iter.rbegin())
{
    return iter.rbegin();
}

template<typename T>
auto rbegin(const T& iter)
    -> decltype(iter.crbegin())
{
    return iter.crbegin();
}

template<typename T, std::size_t N>
auto rbegin(T (&array)[N])
    -> std::reverse_iterator<T*>
{
    return std::reverse_iterator<T*>(std::end(array));
}

template<typename T>
auto rend(T& iter)
    -> decltype(iter.rend())
{
    return iter.rend();
}

template<typename T>
auto rend(const T& iter)
    -> decltype(iter.crend())
{
    return iter.crend();
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

        BidirectionalIterable& _iter;

        ReversedObject(BidirectionalIterable&& iter):
            _iter(iter)
        {}

    public:

        using value_type                = typename std::decay<decltype(*std::begin(_iter))>::type;
        using difference_type           = std::ptrdiff_t;
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = typename std::remove_reference<decltype(itertools::rbegin(_iter))>::type;
        using const_iterator            = typename std::remove_reference<decltype(itertools::rbegin(_iter))>::type;
        using reverse_iterator          = decltype(std::begin(_iter));
        using const_reverse_iterator    = decltype(std::begin(_iter));
        using iterator_category         = typename std::iterator_traits<iterator>::iterator_category;

        // Iterator functions
        auto begin() -> iterator
            { return itertools::rbegin(_iter); }
        auto begin() const -> const_iterator
            { return itertools::rbegin(_iter); }
        auto cbegin() const -> const_iterator
            { return itertools::rbegin(_iter); }
        auto end() -> iterator
            { return itertools::rend(_iter); }
        auto end() const -> const_iterator
            { return itertools::rend(_iter); }
        auto cend() const -> const_iterator
            { return itertools::rend(_iter); }

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return std::begin(_iter); }
        auto rbegin() const -> const_reverse_iterator
            { return std::begin(_iter); }
        auto crbegin() const -> const_reverse_iterator
            { return std::begin(_iter); }
        auto rend() -> reverse_iterator
            { return std::end(_iter); }
        auto rend() const -> const_reverse_iterator
            { return std::end(_iter); }
        auto crend() const -> const_reverse_iterator
            { return std::end(_iter); }

    friend auto reversed<>(BidirectionalIterable&& iter)
        -> ReversedObject<BidirectionalIterable>;
};

template<typename BidirectionalIterable>
inline auto reversed(BidirectionalIterable&& iter)
    -> ReversedObject<BidirectionalIterable>
{
    return { std::forward<BidirectionalIterable>(iter) };
}


////////////////////////////////////////////////////////////
template<typename FlatIterable>
class FlatObject<FlatIterable, false>
{
    protected:

        FlatIterable& _iter;

        FlatObject(FlatIterable&& iter):
            _iter(iter)
        {}

    public:

        using value_type        = typename std::decay<decltype(*_iter.fbegin())>::type;
        using difference_type   = std::ptrdiff_t;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = decltype(_iter.fbegin());
        using const_iterator    = decltype(_iter.cfbegin());
        using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

        // Iterator functions
        auto begin() -> iterator
            { return _iter.fbegin(); }
        auto begin() const -> const_iterator
            { return _iter.cfbegin(); }
        auto cbegin() const -> const_iterator
            { return _iter.cfbegin(); }
        auto end() -> iterator
            { return _iter.fend(); }
        auto end() const -> const_iterator
            { return _iter.cfend(); }
        auto cend() const -> const_iterator
            { return _iter.cfend(); }

    friend auto flat<>(FlatIterable&& iter)
        -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
class FlatObject<FlatIterable, true>:
    public FlatObject<FlatIterable, false>
{
    private:

        using FlatObject<FlatIterable, false>::_iter;

        FlatObject(FlatIterable&& iter):
            FlatObject<FlatIterable, false>(iter)
        {}

    public:

        using value_type                = typename std::decay<decltype(*_iter.fbegin())>::type;
        using difference_type           = std::ptrdiff_t;
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = decltype(_iter.fbegin());
        using const_iterator            = decltype(_iter.cfbegin());
        using reverse_iterator          = decltype(_iter.rfbegin());
        using const_reverse_iterator    = decltype(_iter.crfbegin());
        using iterator_category         = typename std::iterator_traits<iterator>::iterator_category;

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return _iter.rfbegin(); }
        auto rbegin() const -> const_reverse_iterator
            { return _iter.crfbegin(); }
        auto crbegin() const -> const_reverse_iterator
            { return _iter.crfbegin(); }
        auto rend() -> reverse_iterator
            { return _iter.rfend(); }
        auto rend() const -> const_reverse_iterator
            { return _iter.crfend(); }
        auto crend() const -> const_reverse_iterator
            { return _iter.crfend(); }

    friend auto flat<>(FlatIterable&& iter)
        -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
inline auto flat(FlatIterable&& iter)
    -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>
{
    return { std::forward<FlatIterable>(iter) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class MapObject<T, Iterable, false>
{
    protected:

        const Iterable& _iter;
        T (*_func)(const T&);
        decltype(std::begin(_iter)) _begin;
        const decltype(std::end(_iter)) _end;

        MapObject(T (*function)(const T&), Iterable&& iter):
            _iter(iter),
            _func(function),
            _begin(std::begin(_iter)),
            _end(std::end(_iter))
        {}

    public:

        using value_type        = typename std::decay<decltype(*std::begin(_iter))>::type;
        using difference_type   = std::ptrdiff_t;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = decltype(std::begin(_iter));
        using const_iterator    = decltype(std::begin(_iter));
        using iterator_category = std::forward_iterator_tag;

        const MapObject& begin() const
        {
            return *this;
        }

        const MapObject& end() const
        {
            return *this;
        }

        bool operator!=(const MapObject&) const
        {
            return _begin != _end;
        }

        void operator++()
        {
            ++_begin;
        }

        value_type operator*() const
        {
            return _func(*_begin);
        }

    friend auto map<>(T (*function)(const T&) , Iterable&& iter)
        -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
class MapObject<T, Iterable, true>:
    public MapObject<T, Iterable, false>
{
    private:

        using super = MapObject<T, Iterable, false>;
        using super::_iter;
        using super::_func;
        using super::_begin;
        using super::_end;

        mutable bool _forward = true;
        decltype(itertools::rbegin(_iter)) _rbegin;
        const decltype(itertools::rend(_iter)) _rend;

        MapObject(T (*function)(const T&), Iterable&& iter):
            super(function, iter),
            _rbegin(itertools::rbegin(_iter)),
            _rend(itertools::rend(_iter))
        {}

    public:

        using value_type                = typename super::value_type;
        using difference_type           = std::ptrdiff_t;
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = typename super::iterator;
        using const_iterator            = typename super::const_iterator;
        using reverse_iterator          = decltype(itertools::rbegin(_iter));
        using const_reverse_iterator    = decltype(itertools::rbegin(_iter));
        using iterator_category         = std::bidirectional_iterator_tag;

        const MapObject& rbegin() const
        {
            _forward = false;
            return *this;
        }

        const MapObject& rend() const
        {
            return *this;
        }

        bool operator!=(const MapObject&) const
        {
            return _forward ? (_begin != _end) : (_rbegin != _rend);
        }

        void operator++()
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

        value_type operator*() const
        {
            return _forward ? _func(*_begin) : _func(*_rbegin);
        }

    friend auto map<>(T (*function)(const T&) , Iterable&& iter)
        -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
inline auto map(T (*function)(const T&) , Iterable&& iter)
    -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>
{
    return { function, std::forward<Iterable>(iter) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class FilterObject
{
    private:

        const Iterable& _iter;
        bool (*_func)(const T&);
        decltype(std::begin(_iter)) _begin;
        const decltype(std::end(_iter)) _end;

        FilterObject(bool (*function)(const T&), Iterable&& iter):
            _iter(iter),
            _func(function),
            _begin(std::begin(_iter)),
            _end(std::end(_iter))
        {}

    public:

        using value_type        = typename std::decay<decltype(*std::begin(_iter))>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = decltype(std::begin(_iter));
        using const_iterator    = decltype(std::begin(_iter));
        using iterator_category = std::forward_iterator_tag;

        const FilterObject& begin() const
        {
            return *this;
        }

        const FilterObject& end() const
        {
            return *this;
        }

        bool operator!=(const FilterObject&) const
        {
            return _begin != _end;
        }

        void operator++()
        {
            do
            {
                ++_begin;
            }
            while (_func(*_begin) == false && _begin != _end);
        }

        T operator*()
        {
            return *_begin;
        }

    friend auto filter<>(bool (*function)(const T&) , Iterable&& iter)
        -> FilterObject<T, Iterable>;
};

template<typename T, typename Iterable>
inline auto filter(bool (*function)(const T&) , Iterable&& iter)
    -> FilterObject<T, Iterable>
{
    return { function, std::forward<Iterable>(iter) };
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

        using value_type        = typename std::decay<decltype(*_iter)>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = ChainObject&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        ChainObject(First&& first, Iterables&&... iters):
            super(std::forward<Iterables>(iters)...),
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

        bool operator!=(const ChainObject&) const
        {
            return super::operator!=(*this);
        }

        void operator++()
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

        auto operator*()
            -> decltype(*_iter)
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

        bool operator!=(const ChainObject&) const
        {
            return _iter != std::end(_first);
        }

        void operator++()
        {
            ++_iter;
        }

        auto operator*()
            -> decltype(*_iter)
        {
            return *_iter;
        }
};

template<typename... Iterables>
inline auto chain(Iterables&&... iters)
    -> ChainObject<Iterables...>
{
    static_assert(is_same<typename std::decay<Iterables>::type::value_type...>::value,
                  "different value_type for arguments passed to chain");

    return { std::forward<Iterables>(iters)... };
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ZipObject:
    public ZipObject<typename std::decay<Iterables>::type...>
{
    private:

        First& _first;
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

        ZipObject():
            super(std::forward<typename std::decay<Iterables>::type>(Iterables())...),
            _first(First())
        {}

        ZipObject(First&& first, Iterables&&... iters):
            super(std::forward<typename std::decay<Iterables>::type>(iters)...),
            _first(first),
            _iter(std::begin(first))
        {}

        const ZipObject& begin() const
        {
            return *this;
        }

        const ZipObject& end() const
        {
            return *this;
        }

        bool operator!=(const ZipObject&) const
        {
            return _iter != std::end(_first);
        }

        void operator++()
        {
            ++_iter;
            super::operator++();
        }

        auto operator*()
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

        First& _first;
        decltype(std::begin(_first)) _iter;

    public:

        using value_type    = decltype(std::make_tuple(*_iter));
        using reference     = value_type&;
        using pointer       = value_type*;

        ZipObject():
            _first(First())
        {}

        ZipObject(First&& first):
            _first(first),
            _iter(std::begin(_first))
        {}

        const ZipObject& begin() const
        {
            return *this;
        }

        const ZipObject& end() const
        {
            return *this;
        }

        bool operator!=(const ZipObject&) const
        {
            return _iter != std::end(_first);
        }

        void operator++()
        {
            ++_iter;
        }

        auto operator*()
            -> value_type
        {
            return std::make_tuple(*_iter);
        }
};

template<typename... Iterables>
inline auto zip(Iterables&&... iters)
    -> ZipObject<Iterables...>
{
    return { std::forward<Iterables>(iters)... };
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
