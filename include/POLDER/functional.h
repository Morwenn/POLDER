/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef POLDER_FUNCTIONAL_H_
#define POLDER_FUNCTIONAL_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <functional>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/type_traits.h>
#include <POLDER/utility.h>
#include <POLDER/io.h>

namespace polder
{
    ////////////////////////////////////////////////////////////
    // Function objects for compound assignment

    struct plus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs += rhs;
        }
    };

    struct minus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs -= rhs;
        }
    };

    struct multiplies_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs *= rhs;
        }
    };

    struct divides_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs /= rhs;
        }
    };

    struct modulus_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs %= rhs;
        }
    };

    struct bit_and_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs &= rhs;
        }
    };

    struct bit_or_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs |= rhs;
        }
    };

    struct bit_xor_assign
    {
        template<typename T, typename U>
        auto operator()(T& lhs, U&& rhs) const
            -> T
        {
            return lhs ^= rhs;
        }
    };

    ////////////////////////////////////////////////////////////
    // memoized

    /**
     * @brief Wrapper memoizing a function's results
     *
     * This class is used to wrap a function and store
     * its results. Whenever the function is called, it
     * checks whether the arguments tuple is known and,
     * if so, simply returns the associated result. If it
     * is the first time that the argument tuple has been
     * seen, this class calls the underlying function to
     * compute the result, stores it and returns it.
     *
     * @warning Only works for pure functions
     */
    template<typename Ret, typename... Args>
    class MemoizedFunction
    {
        public:

            MemoizedFunction(const std::function<Ret(Args...)>& func);

            /**
             * @brief Gets the result
             *
             * Returns the result if it is already known.
             * If not, it computes and stores it beforehand.
             *
             * @param args Arguments for the underlying function
             * @return Result from the underlying function
             */
            auto operator()(Args&&... args)
                -> Ret;

            /**
             * @brief Clears the cache
             *
             * This function clears all the data in the
             * cache. It does not clear the function
             * pointer.
             */
            auto clear() noexcept
                -> void;

        private:

            // Stored function
            std::function<Ret(Args...)> _func;
            // Map containing the pairs args/return
            std::unordered_map<std::tuple<Args...>, Ret> _cache;
    };

    /**
     * @brief Creates a memoized function
     *
     * @param func Function to memoize
     * @return Memoized function corresponding to \a func
     */
    template<typename Function>
    auto memoized(Function&& func);

    ////////////////////////////////////////////////////////////
    // curried

    /**
     * @brief Ties the first argument of a function to a value
     *
     * @param func Function to curry
     * @param first Value to tie to \a func
     * @return \a func curried with \a first
     */
    template<typename Function, typename First>
    auto curried(Function&& func, First first);

    #include "details/functional.inl"
}

#endif // POLDER_FUNCTIONAL_H_
