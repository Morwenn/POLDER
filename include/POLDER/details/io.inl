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

namespace details
{
    inline auto print_impl(std::ostream&)
        -> void
    {}

    template<typename T>
    auto print_impl(std::ostream& stream, const T& arg)
        -> void
    {
        stream << arg << std::endl;
    }

    template<typename First, typename... Args>
    auto print_impl(std::ostream& stream, const First& first, const Args&... others)
        -> void
    {
        stream << first << " ";
        print_impl(stream, others...);
    }
}

template<typename... Args>
auto print(Args&&... args)
    -> void
{
    details::print_impl(std::cout, std::forward<Args>(args)...);
}

template<typename... Args>
auto print(std::ostream& stream, Args&&... args)
    -> void
{
    details::print_impl(stream, std::forward<Args>(args)...);
}
