/*
 * Copyright (C) 2011-2012 Morwenn
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
#include <POLDER/io.h>


bool fgetl(char*& line, FILE* f)
{
    int c;
    int size = 1;

    // Count the number of characters in the string
    while ((c = fgetc(f)) != EOF) if (++size && c == '\n') break;
    // If the only character is EOF, finish
    if (size == 1) return false;
    line = (char*) realloc(line, size * sizeof(line) + 1);
    char* cs = line; // Iterator
    // Replace the file iterator a the beginning of the line
    fseek(f, -size, SEEK_CUR);
    // Copy the line in the output string
    while ((*cs++ = fgetc(f)) != '\n');
    *cs = '\0';
    return true;
}
