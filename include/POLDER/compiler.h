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

namespace polder
{
namespace compiler
{
    /**
     * @brief Empty base class optimization check.
     * @return Whether the compiler does the empty base class optimization.
     */
    constexpr auto has_ebco()
        -> bool;

    /**
     * @brief Empty base class optimization check for a given template.
     *
     * This function is specialized for some specific templates and
     * will always return \c false for the other ones. It may return
     * \c true for the following templates: std::tuple, std::unique_ptr.
     *
     * @return Whether the given template performs EBCO.
     */
    template<template<typename...> class TT>
    constexpr auto has_ebco_for()
        -> bool;

    #include "details/compiler.inl"
}}

#endif // POLDER_COMPILER_H_
