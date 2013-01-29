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
#include <cstddef>
#include <iterator>
#include <utility>
#include <tuple>
#include <POLDER/config.h>
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
class RangeObject;
template<typename BidirectionalIterable>
class ReversedObject;
template<typename FlatIterable, bool IsReverseIterable>
class FlatObject;
template<typename T, typename Iterable>
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
constexpr RangeObject range(int end) noexcept;

/**
 * @brief Versatile range of integers
 *
 * Generates a RangeObject, which is a generator
 * which will yield values from \a begin to \a end
 * with agiven \a step. The direction of the
 * iteration depends on \a begin and \a end.
 *
 * @param begin First value
 * @param end Last value
 * @param step Step between two values
 * @return Generator
 */
constexpr RangeObject range(int begin, int end, unsigned int step=1) noexcept;

/**
 * @brief Global rbegin function
 *
 * The equilavent of std::begin for reversed
 * iteration.
 */
template<typename T>
auto rbegin(T& iter)        -> decltype(iter.rbegin());
template<typename T>
auto rbegin(const T& iter)  -> decltype(iter.crbegin());
template<typename T, std::size_t N>
auto rbegin(T (&array)[N])  -> std::reverse_iterator<T*>;


/**
 * @brief Global rend function
 *
 * The equilavent of std::end for reversed
 * iteration.
 */
template<typename T>
auto rend(T& iter)          -> decltype(iter.rend());
template<typename T>
auto rend(const T& iter)    -> decltype(iter.crend());
template<typename T, std::size_t N>
auto rend(T (&array)[N])    -> std::reverse_iterator<T*>;

/**
 * @brief Reversed iterable
 *
 * This function acts like a wrapper that allows to
 * use the rbegin and rend functions to operate
 * reverse iteration in a foreach loop.
 *
 * @param iter Iterable
 * @return Generator
 */
template<typename BidirectionalIterable>
auto reversed(BidirectionalIterable&& iter)
    -> ReversedObject<BidirectionalIterable>;

/**
 * @brief Flat iterable
 *
 * This function acts like a wrapper that allows to
 * use the fbegin and fend functions to operate
 * flat iteration in a foreach loop.
 *
 * @param iter Iterable
 * @return Generator
 */
template<typename FlatIterable>
auto flat(FlatIterable&& iter)
    -> FlatObject<FlatIterable, is_reverse_iterable<FlatIterable>::value>;

/**
 * @brief Apply function to iterable
 *
 * Generates a MapObject. It's a generator that
 * yields the values of \a iter one by one after
 * \a function has been applied to them.
 *
 * @param function Function to apply
 * @param iter Iterable
 * @return Generator
 */
template<typename T, typename Iterable>
auto map(T (*function)(const T&) , Iterable&& iter)
    -> MapObject<T, Iterable>;

/**
 * @brief Filter elements from an iterable
 *
 * Generates a FilterObject. It's a generator that
 * yields the values of \a iter one by one if
 * \a function returns true.
 *
 * @param function Filter function to apply
 * @param iter Iterable
 * @return Generator
 */
template<typename T, typename Iterable>
auto filter(bool (*function)(const T&) , Iterable&& iter)
    -> FilterObject<T, Iterable>;

/**
 * @brief Iter through many containers
 *
 * Acts like a wrapper that would allow to iter through
 * many containers as if there was just one of them
 * containings all of their values.
 *
 * It is possible to chain different containers (list, vector
 * array, etc...) but the contained values must be of the same
 * type. Otherwise, it will crash at compile time.
 */
template<typename... Iterables>
auto chain(Iterables&&... iters)
    -> ChainObject<Iterables...>;

/**
 * @brief Aggregates elements from iterables
 *
 * Make groups of elements from different iterables.
 * For exemple, a list of int zipped with a list
 * of float would generate elements of type
 * std::tuple<int, float>.
 */
template<typename... Iterables>
auto zip(Iterables&&... iters)
    -> ZipObject<Iterables...>;


#include <POLDER/itertools.inl>

} // namespace itertools
} // namespace polder


#endif // _POLDER_ITERTOOLS_H
