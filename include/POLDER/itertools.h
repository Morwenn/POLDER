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
#include <utility>
#include <POLDER/config.h>


namespace polder
{

/**
 * @namespace polder::itertools
 * @brief Iterator tools
 *
 * Collection of functions an functor inspired
 * from Python programming. Most of them are meant
 * be used with the C++11 for loop.
 */
namespace itertools
{


// Forward declarations
class RangeObject;
template<typename BidirectionalIterable>
class ReversedObject;
template<typename T, typename Iterable>
class MapObject;
template<typename First, typename... Iterables>
class ChainObject;


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
constexpr RangeObject range(int end);

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
constexpr RangeObject range(int begin, int end, unsigned int step=1);

/**
 * @brief Reversed iterable
 *
 * This function acts like a wrapper that allows to
 * use the rebing and rend functions to operate
 * reverse iteration in a foreach loop.
 *
 * @param iter Iterable
 * @return Generator
 */
template<typename BidirectionalIterable>
ReversedObject<BidirectionalIterable> reversed(BidirectionalIterable&& iter);

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
MapObject<T, Iterable> map(T (*function)(T) , const Iterable& iter);

template<typename T, typename Iterable>
MapObject<T, Iterable> map(T (*function)(const T&) , const Iterable& iter);

/**
 * @brief Iter through many containers
 *
 * Acts like a wrapper that would allow to iter through
 * many containers as if there was just one of them
 * containings all of their values.
 *
 * It is possible to chain different containers (list, vector
 * array, etc...) but the contained values must be of the same
 * type. Otherwise, it will crash at compilation.
 */
template<typename... Iterables>
ChainObject<Iterables...> chain(Iterables&&... iters);


#include <POLDER/itertools.inl>

} // namespace itertools
} // namespace polder


#endif // _POLDER_ITERTOOLS_H
