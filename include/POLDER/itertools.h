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
#ifndef POLDER_ITERTOOLS_H_
#define POLDER_ITERTOOLS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <iterator>
#include <utility>
#include <tuple>
#include <POLDER/details/config.h>
#include <POLDER/type_traits.h>

namespace polder
{

/**
 * @namespace polder::itertools
 * @brief Iterator tools
 *
 * Collection of functions and functors inspired
 * by Python programming. Most of them are meant to
 * be used with the C++11 for[each] loop.
 */
namespace itertools
{
    // Forward declarations
    template<typename Integer>
    class RangeObject;
    template<typename BidirectionalIterable>
    class ReversedObject;
    template<typename FlatIterable, bool IsReverseIterable>
    class FlatObject;
    template<typename T, typename Iterable, bool IsReverseIterable>
    class MapObject;
    template<typename T, typename Iterable>
    class FilterObject;
    template<typename First, typename... Iterables>
    class ChainObject;
    template<typename First, typename... Iterables>
    class ZipObject;

    /**
     * @brief Range of integers
     *
     * Generates a RangeObject, which is a generator
     * which will yield values from 0 to \a end with a
     * step of 1 or -1 depending on the value of
     * \a end.
     *
     * @param end Last value
     * @return Generator
     */
    template<typename Integer>
    constexpr auto range(Integer end) noexcept
        -> RangeObject<Integer>;

    /**
     * @brief Versatile range of integers
     *
     * Generates a RangeObject, which is a generator
     * which will yield values from \a begin to \a end
     * with a given \a step. The direction of the
     * iteration depends on \a begin and \a end.
     *
     * @param begin First value
     * @param end Last value
     * @param step Step between two values
     * @return Generator
     */
    template<typename Integer>
    constexpr auto range(Integer begin, Integer end, Integer step=1) noexcept
        -> RangeObject<Integer>;

    /**
     * @brief Global rbegin function
     *
     * The equivalent of std::begin for reversed
     * iteration.
     */
    template<typename T>
    auto rbegin(T& iterable)
        -> decltype(iterable.rbegin());
    template<typename T>
    auto rbegin(const T& iterable)
        -> decltype(iterable.crbegin());
    template<typename T, std::size_t N>
    auto rbegin(T (&array)[N])
        -> std::reverse_iterator<T*>;

    /**
     * @brief Global rend function
     *
     * The equivalent of std::end for reversed
     * iteration.
     */
    template<typename T>
    auto rend(T& iterable)
        -> decltype(iterable.rend());
    template<typename T>
    auto rend(const T& iterable)
        -> decltype(iterable.crend());
    template<typename T, std::size_t N>
    auto rend(T (&array)[N])
        -> std::reverse_iterator<T*>;

    /**
     * @brief Reversed iterable
     *
     * This function acts like a wrapper that allows to
     * use the rbegin and rend functions to operate
     * reverse iteration in a foreach loop.
     *
     * @param iterable Iterable
     * @return Generator
     */
    template<typename BidirectionalIterable>
    auto reversed(BidirectionalIterable&& iterable)
        -> ReversedObject<BidirectionalIterable>;

    /**
     * @brief Flat iterable
     *
     * This function acts like a wrapper that allows to
     * use the fbegin and fend functions to operate
     * flat iteration in a foreach loop.
     *
     * @param iterable Iterable
     * @return Generator
     */
    template<typename FlatIterable>
    auto flat(FlatIterable&& iterable)
        -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;

    /**
     * @brief Apply function to iterable
     *
     * Generates a MapObject. It's a generator that
     * yields the values of \a iterable one by one
     * after \a function has been applied to them.
     *
     * @param function Function to apply
     * @param iterable Iterable
     * @return Generator
     */
    template<typename T, typename Iterable>
    auto map(T (*function)(const T&) , Iterable&& iterable)
        -> MapObject<T, Iterable, is_reverse_iterable<Iterable>::value>;

    /**
     * @brief Filter elements from an iterable
     *
     * Generates a FilterObject. It's a generator that
     * yields the values of \a iterable one by one if
     * \a function returns true.
     *
     * @param function Filter function to apply
     * @param iterable Iterable
     * @return Generator
     */
    template<typename T, typename Iterable>
    auto filter(bool (*function)(const T&) , Iterable&& iterable)
        -> FilterObject<T, Iterable>;

    /**
     * @brief Iter through many containers
     *
     * Acts like a wrapper that would allow to iterate through
     * many containers as if there was just one of them
     * containing all of their values.
     *
     * It is possible to chain different containers (list, vector
     * array, etc...) but the contained values must be of the same
     * type. Otherwise, it will crash at compile time.
     */
    template<typename... Iterables>
    auto chain(Iterables&&... iterables)
        -> ChainObject<Iterables...>;

    /**
     * @brief Aggregates elements from iterables
     *
     * Make groups of elements from different iterables.
     * For example, a list of int zipped with a list
     * of float would generate elements of type
     * std::tuple<int, float>.
     */
    template<typename... Iterables>
    auto zip(Iterables&&... iterables)
        -> ZipObject<Iterables...>;

    /**
     * @brief Iterator adapter
     *
     * Make an iterator which will get the nth
     * element of the object returned by the
     * given iterator. It allows to create iterators
     * to traverse keys of a std::map-like object
     * for example.
     * Useful to iterate through some specific std::pair
     * or std::tuple elements.
     */
    template<std::size_t N, typename Iterator>
    class get_iterator
    {
        private:

            Iterator _current;

        public:

            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using iterator_type     = Iterator;
            using value_type        = std::remove_reference_t<decltype(std::get<N>(*_current))>;
            using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
            using pointer           = value_type*;
            using reference         = value_type&;

            get_iterator();
            explicit get_iterator(Iterator it);
            template<typename U>
            get_iterator(const get_iterator<N, U>& other);

            template<typename U>
            auto operator=(const get_iterator<N, U>& other)
                -> get_iterator&;

            auto base() const
                -> Iterator;

            auto operator*() const
                -> reference;
            auto operator->() const
                -> pointer;

            auto operator++()
                -> get_iterator&;
            auto operator++(int)
                -> get_iterator&;

            auto operator--()
                -> get_iterator&;
            auto operator--(int)
                -> get_iterator&;
    };

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator==(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator!=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator<(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator<=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator>(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator>=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    #include "details/itertools.inl"
}}

#endif // POLDER_ITERTOOLS_H_
