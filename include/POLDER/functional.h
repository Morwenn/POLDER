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

namespace polder
{
    namespace detail
    {
        using is_transparent_t = std::plus<>::is_transparent;
    }

    ////////////////////////////////////////////////////////////
    // Function objects from the standard library

    // Arithmetic operations
    using plus = std::plus<>;
    using minus = std::minus<>;
    using multiplies = std::multiplies<>;
    using divides = std::divides<>;
    using modulus = std::modulus<>;
    using negate = std::negate<>;

    // Comparisons
    using equal_to = std::equal_to<>;
    using not_equal_to = std::not_equal_to<>;
    using greater = std::greater<>;
    using less = std::less<>;
    using greater_equal= std::greater_equal<>;
    using less_equal = std::less_equal<>;

    // Logical operations
    using logical_and = std::logical_and<>;
    using logical_or = std::logical_or<>;
    using logical_not = std::logical_not<>;

    // Bitwise operations
    using bit_and = std::bit_and<>;
    using bit_or = std::bit_or<>;
    using bit_xor = std::bit_xor<>;
    using bit_not = std::bit_not<>;

    ////////////////////////////////////////////////////////////
    // Missing function objects for shift operators

    struct left_shift
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) << std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) << std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) << std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct right_shift
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) >> std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) >> std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) >> std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    ////////////////////////////////////////////////////////////
    // Missing function objects for assignment operators

    struct assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) = std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) = std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) = std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct plus_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) += std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) += std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) += std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct minus_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) -= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) -= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) -= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct multiplies_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) *= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) *= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) *= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct divides_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) /= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) /= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) /= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct modulus_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) %= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) %= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) %= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct bit_and_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) &= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) &= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) &= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct bit_or_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) |= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) |= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) |= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct bit_xor_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) ^= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) ^= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) ^= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct left_shift_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) <<= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) <<= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) <<= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
    };

    struct right_shift_assign
    {
        template<typename T, typename U>
        constexpr auto operator()(T&& lhs, U&& rhs) const
            noexcept(noexcept(std::forward<T>(lhs) >>= std::forward<U>(rhs)))
            -> decltype(std::forward<T>(lhs) >>= std::forward<U>(rhs))
        {
            return std::forward<T>(lhs) >>= std::forward<U>(rhs);
        }

        using is_transparent = detail::is_transparent_t;
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
     * @warning It only works with pure functions.
     */
    template<typename Callable>
    class memoized_function;

    template<typename Ret, typename... Args>
    class memoized_function<Ret(Args...)>
    {
        public:

            memoized_function(const std::function<Ret(Args...)>& func);

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
    auto memoized(Function&& func)
        -> decltype(auto);

    #include "details/functional.inl"
}

#endif // POLDER_FUNCTIONAL_H_
