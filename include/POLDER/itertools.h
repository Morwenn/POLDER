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
#ifndef _POLDER_ITERTOOLS_H
#define _POLDER_ITERTOOLS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/config.h>


namespace polder
{

/**
 * @namespace polder::itertools
 * @brief Iterator tools
 *
 * Collection of functions an functor inspired
 * from Python programming. Many of them are meant
 * be used with the C++11 for loop.
 */
namespace itertools
{


/**
 * @brief Range of integers
 */
class POLDER_API range
{
    public:

        constexpr range(int end):
            _i(0),
            _end(end),
            _step(1),
            _sup(end >= 0)
        {}

        constexpr range(int begin, int end, unsigned int step=1):
            _i(begin),
            _end(end),
            _step(step),
            _sup(end >= begin)
        {}

        constexpr const range& begin()
        {
            return *this;
        }

        constexpr const range& end() const
        {
            return *this;
        }

        constexpr bool operator!=(const range&) const
        {
            return _sup ? (_i < _end) : (_i > _end);
        }

        inline void operator++()
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

        constexpr const int& operator*() const
        {
            return _i;
        }

    private:

        int _i;
        const int _end;
        const unsigned int _step;
        const bool _sup;
};


/**
 * @brief Reversed iterable
 */
template<typename ReverseIterable>
class POLDER_API __reversed
{
    // FUTURE: Could be improved with concepts

    private:

        ReverseIterable& _iter;

    public:

        __reversed(ReverseIterable& iter):
            _iter(iter)
        {}

        auto begin() -> decltype(_iter.rbegin())
        {
            return _iter.rbegin();
        }

        auto end() -> decltype(_iter.rend())
        {
            return _iter.rend();
        }
};

template<typename ReverseIterable>
POLDER_API inline __reversed<ReverseIterable> reversed(ReverseIterable& iter)
{
    return __reversed<ReverseIterable>(iter);
}

/**
 * @brief Constant reversed iterable
 */
template<typename ReverseIterable>
class POLDER_API __creversed
{
    // FUTURE: Could be improved with concepts

    private:

        const ReverseIterable& _iter;

    public:

        __creversed(const ReverseIterable& iter):
            _iter(iter)
        {}

        auto begin() -> decltype(_iter.crbegin())
        {
            return _iter.crbegin();
        }

        auto end() -> decltype(_iter.crend())
        {
            return _iter.crend();
        }
};

template<typename ReverseIterable>
POLDER_API inline const __creversed<ReverseIterable> reversed(const ReverseIterable& iter)
{
    return __creversed<ReverseIterable>(iter);
}

/**
 * @brief Function mapping to iterable
 */
template<typename T, typename Iterable>
class POLDER_API __map
{
    // FUTURE: Could be improved with concepts

    private:

        const Iterable& _iter;
        T (*_func)(T);
        decltype(_iter.begin()) _begin;
        const decltype(_iter.end()) _end;

    public:

        __map(T (*function)(T), const Iterable& iter):
            _iter(iter),
            _func(function),
            _begin(_iter.begin()),
            _end(_iter.end())
        {}

        const __map& begin() const
        {
            return *this;
        }

        const __map& end() const
        {
            return *this;
        }

        bool operator!=(const __map&)
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
POLDER_API inline __map<T, Iterable> map(T (*function)(T) , const Iterable& iter)
{
    return __map<T, Iterable>(function, iter);
}


} // namespace itertools
} // namespace polder


#endif // _POLDER_ITERTOOLS_H

