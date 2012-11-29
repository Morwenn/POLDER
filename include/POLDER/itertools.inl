/*
 * Copyright (C) 2011-2012 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
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

        constexpr const RangeObject& begin() noexcept
        {
            return *this;
        }

        constexpr const RangeObject& end() const noexcept
        {
            return *this;
        }

        constexpr bool operator!=(const RangeObject&) const noexcept
        {
            return _sup ? (_i < _end) : (_i > _end);
        }

        inline void operator++() noexcept
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

        constexpr const int& operator*() const noexcept
        {
            return _i;
        }

    private:

        int _i;
        const int _end;
        const unsigned int _step;
        const bool _sup;

    friend constexpr RangeObject range(int end) noexcept;
    friend constexpr RangeObject range(int begin, int end, unsigned int step) noexcept;
};

constexpr RangeObject range(int end) noexcept
{
    return RangeObject(end);
}

constexpr RangeObject range(int begin, int end, unsigned int step) noexcept
{
    return RangeObject(begin, end, step);
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
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = decltype(itertools::rbegin(_iter));
        using const_iterator            = decltype(itertools::rbegin(_iter));
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
    return ReversedObject<BidirectionalIterable>(std::forward<BidirectionalIterable>(iter));
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
    return FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>(std::forward<FlatIterable>(iter));
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class MapObject
{
    private:

        const Iterable& _iter;
        T (*_func)(const T&);
        decltype(_iter.begin()) _begin;
        const decltype(_iter.end()) _end;

        MapObject(T (*function)(const T&), Iterable&& iter):
            _iter(iter),
            _func(function),
            _begin(_iter.begin()),
            _end(_iter.end())
        {}

    public:

        using value_type        = typename std::decay<decltype(*std::begin(_iter))>::type;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = decltype(std::begin(_iter));
        using const_iterator    = decltype(std::begin(_iter));
        using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

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

        T operator*()
        {
            return _func(*_begin);
        }

    friend auto map<>(T (*function)(const T&) , Iterable&& iter)
        -> MapObject<T, Iterable>;
};

template<typename T, typename Iterable>
inline auto map(T (*function)(const T&) , Iterable&& iter)
    -> MapObject<T, Iterable>
{
    return MapObject<T, Iterable>(function, std::forward<Iterable>(iter));
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ChainObject:
    private ChainObject<Iterables...>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

        using parent_type = ChainObject<Iterables...>;

    public:

        using value_type = decltype(*_iter);

        ChainObject(First&& first, Iterables&&... iters):
            parent_type(std::forward<Iterables>(iters)...),
            _first(first),
            _iter(first.begin())
        {}

        const ChainObject& begin() const
        {
            return *this;
        }

        const ChainObject& end() const
        {
            return *this;
        }

        bool operator!=(const ChainObject&) const
        {
            return parent_type::operator!=(*this);
        }

        void operator++()
        {
            if (_iter != _first.end())
            {
                ++_iter;
            }
            else
            {
                parent_type::operator++();
            }
        }

        auto operator*()
            -> value_type
        {
            if (_iter != _first.end())
            {
                return *_iter;
            }
            return parent_type::operator*();
        }
};

template<typename First>
class ChainObject<First>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

    public:

        using value_type = decltype(*_iter);

        ChainObject(First&& first):
            _first(first),
            _iter(first.begin())
        {}

        const ChainObject& begin() const
        {
            return *this;
        }

        const ChainObject& end() const
        {
            return *this;
        }

        bool operator!=(const ChainObject&) const
        {
            return _iter != _first.end();
        }

        void operator++()
        {
            ++_iter;
        }

        auto operator*()
            -> value_type
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
    return ChainObject<Iterables...>(std::forward<Iterables>(iters)...);
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ZipObject:
    public ZipObject<typename std::decay<Iterables>::type...>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

        using parent_type = ZipObject<typename std::decay<Iterables>::type...>;

    public:

        using value_type = decltype(
            std::tuple_cat(
                std::make_tuple(*_iter),
                parent_type().operator*()
            )
        );

        ZipObject():
            parent_type(std::forward<typename std::decay<Iterables>::type>(Iterables())...),
            _first(First())
        {}

        ZipObject(First&& first, Iterables&&... iters):
            parent_type(std::forward<typename std::decay<Iterables>::type>(iters)...),
            _first(first),
            _iter(first.begin())
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
            return _iter != _first.end();
        }

        void operator++()
        {
            ++_iter;
            parent_type::operator++();
        }

        auto operator*()
            -> value_type
        {
            return std::tuple_cat(
                    std::make_tuple(*_iter),
                    parent_type::operator*()
                );
        }
};

template<typename First>
class ZipObject<First>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

    public:

        using value_type = decltype(std::make_tuple(*_iter));

        ZipObject():
            _first(First())
        {}

        ZipObject(First&& first):
            _first(first),
            _iter(first.begin())
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
            return _iter != _first.end();
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
    return ZipObject<Iterables...>(std::forward<Iterables>(iters)...);
}
