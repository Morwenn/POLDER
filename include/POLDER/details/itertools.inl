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
template<typename Integer>
class range_object
{
    private:

        constexpr range_object(Integer end) noexcept:
            _i(0),
            _end(end),
            _sup(end >= 0),
            _step(1)
        {}

        constexpr range_object(Integer begin, Integer end, Integer step) noexcept:
            _i(begin),
            _end(end),
            _sup(end >= begin),
            _step(_sup ? step : -step)
        {}

    public:

        constexpr auto begin() const noexcept
            -> const range_object&
        {
            return *this;
        }

        constexpr auto end() const noexcept
            -> const range_object&
        {
            return *this;
        }

        constexpr auto operator!=(const range_object&) const noexcept
            -> bool
        {
            return _sup ? (_i < _end) : (_i > _end);
        }

        auto operator++() noexcept
            -> void
        {
            _i += _step;
        }

        constexpr auto operator*() const noexcept
            -> Integer
        {
            return _i;
        }

    private:

        Integer _i;
        const Integer _end;
        const bool _sup;
        const Integer _step;

    friend auto range<>(Integer) noexcept
        -> range_object;
    friend auto range<>(Integer, Integer, Integer) noexcept
        -> range_object;
};

template<typename Integer>
constexpr auto range(Integer end) noexcept
    -> range_object<Integer>
{
    return { end };
}

template<typename Integer>
constexpr auto range(Integer begin, Integer end, Integer step) noexcept
    -> range_object<Integer>
{
    return { begin, end, step };
}


////////////////////////////////////////////////////////////
template<typename BidirectionalIterable>
class reversed_object
{
    private:

        BidirectionalIterable& _iterable;

        reversed_object(BidirectionalIterable&& iterable):
            _iterable(iterable)
        {}

    public:

        using value_type                = std::decay_t<decltype(*std::begin(_iterable))>;
        using reference                 = value_type&;
        using pointer                   = value_type*;
        using iterator                  = std::remove_reference_t<decltype(std::rbegin(_iterable))>;
        using const_iterator            = std::remove_reference_t<decltype(std::rbegin(_iterable))>;
        using reverse_iterator          = decltype(std::begin(_iterable));
        using const_reverse_iterator    = decltype(std::begin(_iterable));
        using iterator_category         = typename std::iterator_traits<iterator>::iterator_category;

        // Iterator functions
        auto begin() -> iterator
            { return std::rbegin(_iterable); }
        auto begin() const -> const_iterator
            { return std::rbegin(_iterable); }
        auto cbegin() const -> const_iterator
            { return std::rbegin(_iterable); }
        auto end() -> iterator
            { return std::rend(_iterable); }
        auto end() const -> const_iterator
            { return std::rend(_iterable); }
        auto cend() const -> const_iterator
            { return std::rend(_iterable); }

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
        -> reversed_object;
};

template<typename BidirectionalIterable>
inline auto reversed(BidirectionalIterable&& iterable)
    -> reversed_object<BidirectionalIterable>
{
    return { std::forward<BidirectionalIterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename FlatIterable>
class flat_object<FlatIterable, false>
{
    protected:

        FlatIterable& _iterable;

        flat_object(FlatIterable&& iterable):
            _iterable(iterable)
        {}

    public:

        using value_type        = std::decay_t<decltype(*_iterable.fbegin())>;
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
        -> flat_object<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
class flat_object<FlatIterable, true>:
    public flat_object<FlatIterable, false>
{
    private:

        using super = flat_object<FlatIterable, false>;
        using super::_iterable;

        flat_object(FlatIterable&& iterable):
            flat_object<FlatIterable, false>(iterable)
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
        -> flat_object<FlatIterable, is_reverse_iterable<FlatIterable>::value>;
};

template<typename FlatIterable>
inline auto flat(FlatIterable&& iterable)
    -> flat_object<FlatIterable, is_reverse_iterable<FlatIterable>::value>
{
    return { std::forward<FlatIterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class map_object<T, Iterable, false>
{
    protected:

        const Iterable& _iterable;
        T (*_func)(const T&);
        decltype(std::begin(_iterable)) _begin;
        const decltype(std::end(_iterable)) _end;

        map_object(T (*function)(const T&), Iterable&& iterable):
            _iterable(iterable),
            _func(function),
            _begin(std::begin(_iterable)),
            _end(std::end(_iterable))
        {}

    public:

        using value_type        = std::decay_t<decltype(*std::begin(_iterable))>;
        using difference_type   = std::ptrdiff_t;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = map_object&;
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

        auto operator!=(const map_object&) const
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
        -> map_object<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
class map_object<T, Iterable, true>:
    public map_object<T, Iterable, false>
{
    private:

        using super = map_object<T, Iterable, false>;
        using super::_iterable;
        using super::_func;
        using super::_begin;
        using super::_end;

        mutable bool _forward = true;
        decltype(std::rbegin(_iterable)) _rbegin;
        const decltype(std::rend(_iterable)) _rend;

        map_object(T (*function)(const T&), Iterable&& iterable):
            super(function, iterable),
            _rbegin(std::rbegin(_iterable)),
            _rend(std::rend(_iterable))
        {}

    public:

        using typename super::value_type;
        using typename super::difference_type;
        using typename super::reference;
        using typename super::pointer;
        using iterator                  = map_object&;
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

        auto operator!=(const map_object&) const
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
        -> map_object<T, Iterable, is_reverse_iterable<Iterable>::value>;
};

template<typename T, typename Iterable>
inline auto map(T (*function)(const T&) , Iterable&& iterable)
    -> map_object<T, Iterable, is_reverse_iterable<Iterable>::value>
{
    return { function, std::forward<Iterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename T, typename Iterable>
class filter_object
{
    private:

        const Iterable& _iterable;
        bool (*_func)(const T&);
        decltype(std::begin(_iterable)) _begin;
        const decltype(std::end(_iterable)) _end;

        filter_object(bool (*function)(const T&), Iterable&& iterable):
            _iterable(iterable),
            _func(function),
            _begin(std::begin(_iterable)),
            _end(std::end(_iterable))
        {}

    public:

        using value_type        = std::decay_t<decltype(*std::begin(_iterable))>;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = filter_object&;
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

        auto operator!=(const filter_object&) const
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
        -> filter_object;
};

template<typename T, typename Iterable>
inline auto filter(bool (*function)(const T&) , Iterable&& iterable)
    -> filter_object<T, Iterable>
{
    return { function, std::forward<Iterable>(iterable) };
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class chain_object:
    private chain_object<Iterables...>
{
    private:

        First& _first;
        decltype(std::begin(_first)) _iter;

        using super = chain_object<Iterables...>;

    public:

        using typename super::value_type;
        using typename super::reference;
        using typename super::pointer;
        using iterator          = chain_object&;
        using const_iterator    = const iterator;
        using typename super::iterator_category;

        chain_object(First&& first, Iterables&&... iterables):
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

        auto operator!=(const chain_object&) const
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
class chain_object<First>
{
    private:

        First& _first;
        decltype(std::begin(_first)) _iter;

    public:

        using value_type        = std::decay_t<decltype(*_iter)>;
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = chain_object&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        chain_object(First&& first):
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

        auto operator!=(const chain_object&) const
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
    -> chain_object<Iterables...>
{
    static_assert(is_same<typename std::decay_t<Iterables>::value_type...>{},
                  "different value_type for arguments passed to chain");

    return { std::forward<Iterables>(iterables)... };
}


////////////////////////////////////////////////////////////
template<typename First, typename... Iterables>
class zip_object:
    public zip_object<std::decay_t<Iterables>...>
{
    private:

        const First& _first;
        decltype(std::begin(_first)) _iter;

        using super = zip_object<std::decay_t<Iterables>...>;

    public:

        using value_type = decltype(
            std::tuple_cat(
                std::make_tuple(*_iter),
                super().operator*()
            )
        );
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = zip_object&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        zip_object():
            super(std::forward<std::decay_t<Iterables>>(Iterables())...),
            _first(First())
        {}

        zip_object(First&& first, Iterables&&... iterables):
            super(std::forward<std::decay_t<Iterables>>(iterables)...),
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

        auto operator!=(const zip_object&) const
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
class zip_object<First>
{
    private:

        const First& _first;
        decltype(std::begin(_first)) _iter;

    public:

        using value_type        = decltype(std::make_tuple(*_iter));
        using reference         = value_type&;
        using pointer           = value_type*;
        using iterator          = zip_object&;
        using const_iterator    = const iterator;
        using iterator_category = std::forward_iterator_tag;

        zip_object():
            _first(First())
        {}

        zip_object(First&& first):
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

        auto operator!=(const zip_object&) const
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
    -> zip_object<Iterables...>
{
    return { std::forward<Iterables>(iterables)... };
}
