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

/**
 * @file POLDER/compiler.h
 * @brief Implementation properties.
 *
 * This header contains functions that provide some information
 * about the compiler and the standard library used.
 */

#ifndef POLDER_COMPILER_H_
#define POLDER_COMPILER_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <tuple>
#include <POLDER/details/config.h>

namespace polder
{
namespace compiler
{
    #include "details/compiler.inl"

    /**
     * @brief Empty base class optimization check.
     *
     * This variable contains \c true if the compiler performs the empty
     * base class optimization.
     */
    constexpr bool has_ebco =
        sizeof(details::ebco_check) < sizeof(details::not_empty);

    /**
     * @brief Empty base class optimization check for a given template.
     *
     * This variable template is specialized for some specific templates
     * and will always contain \c false for the other ones. It may contain
     * \c true for the following templates: std::tuple, std::unique_ptr.
     *
     * It will contain \c true for the specialized template if and only
     * if the implementation optimizes these templates so that they can
     * benefit from the empty base class optimization.
     */
    template<template<typename...> class TT>
    constexpr bool has_ebco_for =
        details::has_ebco_for_helper<TT>;
}}

#endif // POLDER_COMPILER_H_
