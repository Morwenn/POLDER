/*
 * Copyright (C) 2014 Morwenn
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

/**
 * @file POLDER/ini.h
 * @brief This header includes the whole ini module.
 */

#ifndef POLDER_INI_H_
#define POLDER_INI_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/ini/dialect.h>
#include <POLDER/ini/element.h>
#include <POLDER/ini/error.h>
#include <POLDER/ini/parser.h>

////////////////////////////////////////////////////////////
// Documentation
////////////////////////////////////////////////////////////

/**
 * @namespace polder::ini
 * @brief Functions and classes to read and write INI files
 *
 * While going under the name "ini", this module provides
 * tools to read and write INI-like configuration files.
 * The class \a ini::Dialect can be passed to the parser
 * to read and write configuration files with different
 * syntaxes.
 */

#endif // POLDER_INI_H_
