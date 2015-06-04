/*
 * Copyright (C) 2015 Morwenn
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

template<typename Number>
template<typename Func>
callback<Number>::callback(Func&& function):
    callback(
        std::forward<Func>(function),
        std::make_index_sequence<
            polder::arity<Func>
        >{}
    )
{}

template<typename Number>
auto callback<Number>::operator()(Number* args) const
    -> Number
{
    return _func(args);
}

template<typename Number>
template<typename Func, std::size_t... Ind>
callback<Number>::callback(Func&& function, std::index_sequence<Ind...>):
    arity(sizeof...(Ind)),
    _func([function](Number* args)
    {
        return function(args[Ind]...);
    })
{}
