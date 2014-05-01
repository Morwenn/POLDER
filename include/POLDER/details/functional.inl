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
// memoized
////////////////////////////////////////////////////////////

template<typename Ret, typename... Args>
MemoizedFunction<Ret, Args...>::MemoizedFunction(const std::function<Ret(Args...)>& func):
    _func(func)
{}

template<typename Ret, typename... Args>
auto MemoizedFunction<Ret, Args...>::operator()(Args&&... args)
    -> Ret
{
    const auto t_args = std::make_tuple(std::forward<Args>(args)...);
    auto it = _cache.find(t_args);
    if (it == _cache.cend())
    {
        it = _cache.emplace(std::piecewise_construct,
                            std::forward_as_tuple(t_args),
                            std::forward_as_tuple(_func(std::forward<Args>(args)...))
                        ).first;
    }
    return it->second;
}

template<typename Ret, typename... Args>
auto MemoizedFunction<Ret, Args...>::clear() noexcept
    -> void
{
    _cache.clear();
}

template<typename Function, std::size_t... Ind>
auto memoized_impl(Function&& func, std::index_sequence<Ind...>)
    -> MemoizedFunction<
        result_type<Function>,
        argument_type<Function, Ind>...>
{
    using Ret = result_type<Function>;
    return { std::function<Ret(argument_type<Function, Ind>...)>(func) };
}

template<typename Function>
auto memoized(Function&& func)
{
    using Indices = std::make_index_sequence<function_traits<Function>::arity>;
    return memoized_impl(std::forward<Function>(func), Indices{});
}

////////////////////////////////////////////////////////////
// curried
////////////////////////////////////////////////////////////

template<typename Function, typename First, std::size_t... Ind>
auto curried_impl(Function func, const First& first, std::index_sequence<Ind...>)
{
    return [=](argument_type<Function, Ind>... args)
    {
        return func(first, args...);
    };
}

template<typename Function, typename First>
auto curried(Function&& func, First&& first)
{
    using FirstArg = argument_type<Function, 0u>;
    static_assert(std::is_convertible<First, FirstArg>::value,
                  "the value to be tied should be convertible to the type of the function's first parameter");

    using Indices = index_range<1, function_traits<Function>::arity>;
    return curried_impl(std::forward<Function>(func), std::forward<First>(first), Indices{});
}

////////////////////////////////////////////////////////////
// compose
////////////////////////////////////////////////////////////

template<typename First, typename Second, std::size_t... Ind>
auto compose_impl(First first, Second second, std::index_sequence<Ind...>)
{
    return [=](argument_type<Second, Ind>... args)
    {
        return first(second(args...));
    };
}

template<typename First, typename Second>
auto compose(First&& first, Second&& second)
{
    static_assert(function_traits<First>::arity == 1u,
                  "all the functions passed to compose, except the last one, must take exactly one parameter");

    using Ret       = result_type<Second>;
    using FirstArg  = argument_type<First, 0u>;
    static_assert(std::is_convertible<Ret, FirstArg>::value,
                  "incompatible return types in compose");

    using Indices = std::make_index_sequence<function_traits<Second>::arity>;
    return compose_impl(std::forward<First>(first), std::forward<Second>(second), Indices{});
}
