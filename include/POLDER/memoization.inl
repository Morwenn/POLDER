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

template<typename Ret, typename... Args>
MemoizedFunction<Ret, Args...>::MemoizedFunction(const std::function<Ret(Args...)>& func):
    _func(func)
{}

template<typename Ret, typename... Args>
auto MemoizedFunction<Ret, Args...>::operator()(Args... args)
    -> Ret
{
    auto tuple_args = std::make_tuple(args...);
    if (not _memory.count(tuple_args))
    {
        auto res = _func(args...);
        _memory[tuple_args] = res;
        return res;
    }
    return _memory[tuple_args];
}

template<typename Ret, typename... Args>
auto memoized(Ret (*func)(Args...))
    -> MemoizedFunction<Ret, Args...>
{
    return { std::function<Ret(Args...)>(func) };
}

template<typename Ret, typename... Args>
auto memoized(const std::function<Ret(Args...)>& func)
    -> MemoizedFunction<Ret, Args...>
{
    return { func };
}
