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
#ifndef _POLDER_MEMOIZATION_H
#define _POLDER_MEMOIZATION_H

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

namespace polder
{
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
     * @brief Create a memoized function
     *
     * @param func Function to memoize.
     * @return Memoized function corresponding to \a func
     */
    template<typename Ret, typename... Args>
    auto memoized(Ret (&func)(Args...))
        -> MemoizedFunction<Ret, Args...>;

    template<typename Function, std::size_t... Ind>
    auto memoized_impl(Function&& func, indices<Ind...>)
        -> MemoizedFunction<
            typename function_traits<typename std::remove_reference<Function>::type>::result_type,
            typename function_traits<typename std::remove_reference<Function>::type>::template arg<Ind>...>;

    template<typename Function, typename Indices=make_indices<function_traits<typename std::remove_reference<Function>::type>::arity>>
    auto memoized(Function&& func)
        -> decltype(memoized_impl(std::forward<Function>(func), Indices()));

    #include "details/memoization.inl"
}

#endif // _POLDER_MEMOIZATION_H
