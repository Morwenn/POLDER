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
    public:

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
template<typename BidirectionalIterable>
class ReversedObject
{
    private:

        BidirectionalIterable& _iter;

    public:

        using iterator                  = decltype(_iter.rbegin());
        using const_iterator            = decltype(_iter.crbegin());
        using reverse_iterator          = decltype(_iter.begin());
        using const_reverse_iterator    = decltype(_iter.cbegin());

        ReversedObject(BidirectionalIterable&& iter):
            _iter(iter)
        {}

        // Iterator functions
        auto begin() -> iterator
            { return _iter.rbegin(); }
        auto begin() const -> const_iterator
            { return _iter.crbegin(); }
        auto cbegin() const -> const_iterator
            { return _iter.crbegin(); }
        auto end() -> iterator
            { return _iter.rend(); }
        auto end() const -> const_iterator
            { return _iter.crend(); }
        auto cend() const -> const_iterator
            { return _iter.crend(); }

        // Reverse iterator functions
        auto rbegin() -> reverse_iterator
            { return _iter.begin(); }
        auto rbegin() const -> const_reverse_iterator
            { return _iter.cbegin(); }
        auto crbegin() const -> const_reverse_iterator
            { return _iter.cbegin(); }
        auto rend() -> reverse_iterator
            { return _iter.end(); }
        auto rend() const -> const_reverse_iterator
            { return _iter.cend(); }
        auto crend() const -> const_reverse_iterator
            { return _iter.cend(); }
};

template<typename BidirectionalIterable>
inline ReversedObject<BidirectionalIterable> reversed(BidirectionalIterable&& iter)
{
    return ReversedObject<BidirectionalIterable>(std::forward<BidirectionalIterable>(iter));
}


////////////////////////////////////////////////////////////
template<typename FlatIterable>
class FlatObject<FlatIterable, false>
{
    protected:

        FlatIterable& _iter;

    public:

        using iterator                  = decltype(_iter.fbegin());
        using const_iterator            = decltype(_iter.cfbegin());

        FlatObject(FlatIterable&& iter):
            _iter(iter)
        {}

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
};

template<typename FlatIterable>
class FlatObject<FlatIterable, true>:
    public FlatObject<FlatIterable, false>
{
    using FlatObject<FlatIterable, false>::_iter;

    public:

        using iterator                  = decltype(_iter.fbegin());
        using const_iterator            = decltype(_iter.cfbegin());
        using reverse_iterator          = decltype(_iter.rfbegin());
        using const_reverse_iterator    = decltype(_iter.crfbegin());

        FlatObject(FlatIterable&& iter):
            FlatObject<FlatIterable, false>(iter)
        {}

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
        T (*_func)(T);
        decltype(_iter.begin()) _begin;
        const decltype(_iter.end()) _end;

    public:

        MapObject(T (*function)(T), const Iterable& iter):
            _iter(iter),
            _func(function),
            _begin(_iter.begin()),
            _end(_iter.end())
        {}

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
};

template<typename T, typename Iterable>
inline MapObject<T, Iterable> map(T (*function)(T) , const Iterable& iter)
{
    return MapObject<T, Iterable>(function, iter);
}

template<typename T, typename Iterable>
class __crmap
{

    private:

        const Iterable& _iter;
        T (*_func)(const T&);
        decltype(_iter.begin()) _begin;
        const decltype(_iter.end()) _end;

    public:

        __crmap(T (*function)(const T&), const Iterable& iter):
            _iter(iter),
            _func(function),
            _begin(_iter.begin()),
            _end(_iter.end())
        {}

        const __crmap& begin() const
        {
            return *this;
        }

        const __crmap& end() const
        {
            return *this;
        }

        bool operator!=(const __crmap&) const
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
};

template<typename T, typename Iterable>
inline __crmap<T, Iterable> map(T (*function)(const T&) , const Iterable& iter)
{
    return __crmap<T, Iterable>(function, iter);
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class ChainObject:
    private ChainObject<Iterables...>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

    public:

        ChainObject(First&& first, Iterables&&... iters):
            ChainObject<Iterables...>(std::forward<Iterables>(iters)...),
            _first(first),
            _iter(first.begin())
        {}

        const ChainObject<First, Iterables...>& begin() const
        {
            return *this;
        }

        const ChainObject<First, Iterables...>& end() const
        {
            return *this;
        }

        bool operator!=(const ChainObject&) const
        {
            return ChainObject<Iterables...>::operator!=(*this);
        }

        void operator++()
        {
            if (_iter != _first.end())
            {
                ++_iter;
            }
            else
            {
                ChainObject<Iterables...>::operator++();
            }
        }

        auto operator*() -> decltype(*_iter)
        {
            if (_iter != _first.end())
            {
                return *_iter;
            }
            return ChainObject<Iterables...>::operator*();
        }
};

template<typename First>
class ChainObject<First>
{
    private:

        First& _first;
        decltype(_first.begin()) _iter;

    public:

        ChainObject(First&& first):
            _first(first),
            _iter(first.begin())
        {}

        const ChainObject<First>& begin() const
        {
            return *this;
        }

        const ChainObject<First>& end() const
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

        auto operator*() -> decltype(*_iter)
        {
            return *_iter;
        }
};

template<typename... Iterables>
inline ChainObject<Iterables...> chain(Iterables&&... iters)
{
    return ChainObject<Iterables...>(std::forward<Iterables>(iters)...);
}
