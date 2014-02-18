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
#include <utility>
#include <POLDER/io.h>

using std::forward;
using std::string;


namespace polder
{
namespace io
{


bool fgetl(char*& line, FILE* f)
{
    int c;
    int size = 1;
    delete[] line; // Ensure that line has been set to nullptr

    // Count the number of characters in the string
    while ((c = fgetc(f)) != EOF) if (++size && c == '\n') break;
    // If the only character is EOF, finish
    if (size == 1) return false;
    line = new char[size+1];
    // Replace the file iterator a the beginning of the line
    fseek(f, -size, SEEK_CUR);
    char* cs = line; // Iterator
    // Copy the line in the output string
    while ((*cs++ = fgetc(f)) != '\n');
    *cs = '\0';
    return true;
}

File::File(std::string&& fname, std::string&& mode):
    _file(fopen(fname.c_str(), mode.c_str())),
    _closed(false)
{}

File::~File()
{
    if (_closed == false)
    {
        fclose(_file);
    }
}

void File::close()
{
    fclose(_file);
    _closed = true;
}

int File::flush()
{
    return fflush(_file);
}

char File::getc()
{
    return fgetc(_file);
}

void File::putc(char c)
{
    fputc(int(c), _file);
}

void File::puts(const std::string& str)
{
    fputs(str.c_str(), _file);
}

void File::seek(long offset, seek_t origin)
{
    fseek(_file, offset, int(origin));
}

long File::tell()
{
    return ftell(_file);
}

const File& File::begin() const
{
    return *this;
}

const File& File::end() const
{
    return *this;
}

bool File::operator!=(const File&) const
{
    char c = fgetc(_file);
    fseek(_file, -1, SEEK_CUR);
    return (c != EOF);
}

void File::operator++() {}

string File::operator*() const
{
    char* line = nullptr;
    if (fgetl(line, _file))
    {
        return string(line);
    }
    return string("");
}

auto open(std::string&& fname, std::string&& mode)
    -> File
{
    return { std::forward<string>(fname), std::forward<string>(mode) };
}


} // namespace io
} // namespace polder
