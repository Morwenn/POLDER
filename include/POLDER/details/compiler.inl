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

////////////////////////////////////////////////////////////
// Details

namespace details
{
    ////////////////////////////////////////////////////////////
    // has_ebco helpers

    struct empty {};

    struct not_empty
    {
        empty dummy;
        int integer;
    };

    struct ebco_check:
        empty
    {
        int integer;
    };

    ////////////////////////////////////////////////////////////
    // has_ebco_for helpers

    struct functor
    {
        void operator()(int*) {}
    };

    template<template<typename...> class>
    constexpr bool has_ebco_for_helper = false;

    template<>
    constexpr bool has_ebco_for_helper<std::tuple> =
        sizeof(std::tuple<int, empty>) == sizeof(std::tuple<int>);

    template<>
    constexpr bool has_ebco_for_helper<std::unique_ptr> =
        sizeof(std::unique_ptr<int, functor>) < sizeof(std::unique_ptr<int, void(*)(int*)>);
}
