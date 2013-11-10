/*
 * Copyright (C) 2011-2013 Morwenn
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
#include <unordered_map>
#include <POLDER/config.h>
#include <POLDER/utility.h>

namespace polder
{
    // Forward declaration
    template<typename Ret, typename... Args>
    class MemoizedFunction;

    template<typename Ret, typename... Args>
    auto memoized(Ret (*func)(Args...))
        -> MemoizedFunction<Ret, Args...>;

    template<typename Ret, typename... Args>
    auto memoized(const std::function<Ret(Args...)>& func)
        -> MemoizedFunction<Ret, Args...>;

    #include "memoization.inl"
}

#endif // _POLDER_MEMOIZATION_H
