/*
 * Copyright (C) 2011 Morwenn
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
#include <POLDER/matrix.h>


namespace polder
{

////////////////////////////////////////////////////////////
/// Matrix constructors and destrutor
///
////////////////////////////////////////////////////////////

// Default constructor
constexpr Matrix::Matrix():
    _height(0),
    _width(0),
    _size(0),
    _data(nullptr),
    _lines(nullptr)
{}

// Copy constructor
Matrix::Matrix(const Matrix& other):
    _height(other._height),
    _width(other._width),
    _size(other._size),
    _data((double*) malloc(_size * sizeof(double))),
    _lines((line*) malloc(_height * sizeof(line)))
{
    memcpy(_data, other._data, _size * sizeof(double));
    for (size_t i = 0 ; i < _height ; ++i)
    {
        _lines[i] = line(_width, _data+i*_width);
    }
}

// Move constructor
Matrix::Matrix(Matrix&& other) noexcept:
    _height(other._height),
    _width(other._width),
    _size(other._size),
    _data(other._data),
    _lines(other._lines)
{
    other._data = nullptr;
    other._lines = nullptr;
}

// Initializer list constructors
Matrix::Matrix(const std::initializer_list<double>& values):
    _height(1),
    _width(values.size()),
    _size(_width),
    _data((double*) malloc(_size * sizeof(double))),
    _lines((line*) malloc(sizeof(line)))
{
    std::copy(values.begin(), values.end(), _data);
    _lines[0] = line(_width, _data);
}

Matrix::Matrix(const std::initializer_list<const std::initializer_list<double>>& values):
    _height(values.size()),
    _width((*(values.begin())).size()),
    _size(_height*_width),
    _data((double*) malloc(_size * sizeof(double))),
    _lines((line*) malloc(_height * sizeof(line)))
{
    size_t _count = 0;
    for (const std::initializer_list<double>& i: values)
    {
        if (i.size() != _width)
        {
            throw std::logic_error("All the lines in a Matrix should have the same size.");
        }
        _lines[_count] = line(_width, _data+_count*_width);
        std::copy(i.begin(), i.end(), _data+_count*_width);
        ++_count;
    }
}

// Uninitilized Matrix constructor
Matrix::Matrix(size_t h, size_t w):
    _height(h),
    _width(w),
    _size(_height*_width),
    _data((double*) malloc(_size * sizeof(double))),
    _lines((line*) malloc(_height * sizeof(line)))
{
    assert(h > 0 && w > 0);
    for (size_t i = 0 ; i < _height ; ++i)
    {
        _lines[i] = line(_width, _data+i*_width);
    }
}

// Uninitialized line Matrix constructor
Matrix::Matrix(size_t w):
    _height(1),
    _width(w),
    _size(_width),
    _data((double*) malloc(_size * sizeof(double))),
    _lines((line*) malloc(sizeof(line)))
{
    assert(w > 0);
    _lines[0] = line(_width, _data);
}

// Destructor
Matrix::~Matrix()
{
    if (_data != nullptr)
    {
        free(_data);
        free(_lines);
    }
}



////////////////////////////////////////////////////////////
/// Matrix creation from other matrix
///
////////////////////////////////////////////////////////////

// Assignement operator
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        if (_data != nullptr)
        {
            free(_lines);
            free(_data);
        }
        _height = other._height;
        _width = other._width;
        _size = other._size;
        _data = (double*) malloc(_size * sizeof(double));
        memcpy(_data, other._data, _size * sizeof(double));
        _lines = (line*) malloc(_height * sizeof(line));
        for (size_t i = 0 ; i < _height ; ++i)
        {
            _lines[i] = line(_width, _data+i*_width);
        }
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this != &other)
    {
        if (_data != nullptr)
        {
            free(_lines);
            free(_data);
        }
        _height = other._height;
        _width = other._width;
        _size = other._size;
        _data = other._data;
        _lines = other._lines;
        other._data = nullptr;
        other._lines = nullptr;
    }
    return *this;
}


////////////////////////////////////////////////////////////
// Matrix elements accessors
////////////////////////////////////////////////////////////

Matrix::line& Matrix::operator[](size_t index)
{
    if (index >= _height)
    {
        throw std::out_of_range("Height out of range.");
    }
    return _lines[index];
}

const Matrix::line& Matrix::operator[](size_t index) const
{
    if (index >= _height)
    {
        throw std::out_of_range("Height out of range.");
    }
    return _lines[index];
}

double& Matrix::operator()(size_t h, size_t w)
{
    if (h >= _height)
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (w >= _width)
    {
        throw std::out_of_range("Width out of range.");
    }
    return _lines[h][w];
}

const double& Matrix::operator()(size_t h, size_t w) const
{
    if (h >= _height)
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (w >= _width)
    {
        throw std::out_of_range("Width out of range.");
    }
    return _lines[h][w];
}


////////////////////////////////////////////////////////////
// Matrix logic operations
////////////////////////////////////////////////////////////

bool Matrix::operator&&(const Matrix& other)
{
    return any() && other.any();
}

bool Matrix::operator||(const Matrix& other)
{
    return any() || other.any();
}


////////////////////////////////////////////////////////////
// Matrix comparison
////////////////////////////////////////////////////////////

bool Matrix::operator==(const Matrix& other) const
{
    if (this->_height != other._height
        || this->_width != other._width)
    {
        return false;
    }
    return std::equal(_data, _data+_height*_width, other._data);
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}


////////////////////////////////////////////////////////////
// Matrix-double operations (compound assignement)
////////////////////////////////////////////////////////////
Matrix& Matrix::operator+=(double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] += d;
    }
    return *this;
}

Matrix& Matrix::operator-=(double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] -= d;
    }
    return *this;
}

Matrix& Matrix::operator*=(double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] *= d;
    }
    return *this;
}

Matrix& Matrix::operator/=(double d)
{
    if (d == 0)
    {
        throw division_by_zero();
    }
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] /= d;
    }
    return *this;
}

Matrix& Matrix::operator%=(int d)
{
    assert(d != 0);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] = (int) _data[i] % d;
    }
    return *this;
}


////////////////////////////////////////////////////////////
// Matrix-double operations
////////////////////////////////////////////////////////////

const Matrix Matrix::operator+(double other) const
{
    return Matrix(*this) += other;
}

const Matrix Matrix::operator-(double other) const
{
    return Matrix(*this) -= other;
}

const Matrix Matrix::operator*(double other) const
{
    return Matrix(*this) *= other;
}

const Matrix Matrix::operator/(double other) const
{
    return Matrix(*this) /= other;
}

const Matrix Matrix::operator%(int other) const
{
    return Matrix(*this) %= other;
}


////////////////////////////////////////////////////////////
// Matrix-double "masks"
////////////////////////////////////////////////////////////

const Matrix Matrix::operator==(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] == other);
    }
    return res;
}

const Matrix Matrix::operator!=(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] != other);
    }
    return res;
}

const Matrix Matrix::operator>(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] > other);
    }
    return res;
}

const Matrix Matrix::operator<(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] < other);
    }
    return res;
}

const Matrix Matrix::operator>=(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] >= other);
    }
    return res;
}

const Matrix Matrix::operator<=(double other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] <= other);
    }
    return res;
}


////////////////////////////////////////////////////////////
// Matrix-Matrix operations (compound assignement)
////////////////////////////////////////////////////////////
Matrix& Matrix::operator+=(const Matrix& M)
{
    assert(_width == M._width && _height == M._height);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] += M._data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& M)
{
    assert(_width == M._width && _height == M._height);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] -= M._data[i];
    }
    return *this;
}

// Matrix multiplication
Matrix& Matrix::operator*=(const Matrix& M)
{
    assert(_width == M._height);
    Matrix N = Matrix(_height, M._width);

    for (size_t i = 0 ; i < _height ; ++i)
    {
        for (size_t j = 0 ; j < M._width ; ++j)
        {
            double res = 0;
            for (unsigned int k = 0 ; k < _width ; ++k)
            {
                res += _data[i*_width+k] * M[k][j];
            }
            N[i][j] = res;
        }
    }
    *this = N;
    return *this;
}

Matrix& Matrix::operator/=(const Matrix& other)
{
    return *this *= matrix::inverse(other);
}


////////////////////////////////////////////////////////////
// Matrix-Matrix operations (outside class)
////////////////////////////////////////////////////////////

const Matrix operator+(const Matrix& m, const Matrix& n)
{
    return Matrix(m) += n;
}
const Matrix operator+(const Matrix& m, Matrix&& n)
{
    return std::move(n += m);
}
const Matrix operator+(Matrix&& m, const Matrix& n)
{
    return std::move(m += n);
}
const Matrix operator+(Matrix&& m, Matrix&& n)
{
    return std::move(m += n);
}

const Matrix operator-(const Matrix& m, const Matrix& n)
{
    return Matrix(m) -= n;
}
const Matrix operator-(const Matrix& m, Matrix&& n)
{
    return std::move(n -= m);
}
const Matrix operator-(Matrix&& m, const Matrix& n)
{
    return std::move(m -= n);
}
const Matrix operator-(Matrix&& m, Matrix&& n)
{
    return std::move(m -= n);
}

const Matrix operator*(const Matrix& m, const Matrix& n)
{
    return Matrix(m) *= n;
}
const Matrix operator*(const Matrix& m, Matrix&& n)
{
    return std::move(n *= m);
}
const Matrix operator*(Matrix&& m, const Matrix& n)
{
    return std::move(m *= n);
}
const Matrix operator*(Matrix&& m, Matrix&& n)
{
    return std::move(m *= n);
}

const Matrix operator/(const Matrix& m, const Matrix& n)
{
    return Matrix(m) /= n;
}
const Matrix operator/(const Matrix& m, Matrix&& n)
{
    return std::move(n /= m);
}
const Matrix operator/(Matrix&& m, const Matrix& n)
{
    return std::move(m /= n);
}
const Matrix operator/(Matrix&& m, Matrix&& n)
{
    return std::move(m /= n);
}




////////////////////////////////////////////////////////////
/// STL-like functions
///
////////////////////////////////////////////////////////////

// Accessors
double& Matrix::at(size_t h, size_t w)
{
    if (h >= _size)
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (w >= _size)
    {
        throw std::out_of_range("Width out of range.");
    }
    return _lines[h][w];
}
const double& Matrix::at(size_t h, size_t w) const
{
    if (h >= _size)
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (w >= _size)
    {
        throw std::out_of_range("Width out of range.");
    }
    return _lines[h][w];
}

double& Matrix::front()
{
    return _data[0];
}
const double& Matrix::front() const
{
    return _data[0];
}

double& Matrix::back()
{
    return _data[_size];
}
const double& Matrix::back() const
{
    return _data[_size];
}

// Iterators
Matrix::iterator Matrix::begin()
{
    return _lines;
}
Matrix::const_iterator Matrix::begin() const
{
    return _lines;
}
Matrix::const_iterator Matrix::cbegin() const
{
    return _lines;
}
Matrix::iterator Matrix::end()
{
    return _lines + _height;
}
Matrix::const_iterator Matrix::end() const
{
    return _lines + _height;
}
Matrix::const_iterator Matrix::cend() const
{
    return _lines + _height;
}
Matrix::reverse_iterator Matrix::rbegin()
{
    return reverse_iterator(_lines+_height-1);
}
Matrix::const_reverse_iterator Matrix::rbegin() const
{
    return const_reverse_iterator(_lines+_height-1);
}
Matrix::const_reverse_iterator Matrix::crbegin() const
{
    return const_reverse_iterator(_lines+_height-1);
}
Matrix::reverse_iterator Matrix::rend()
{
    return reverse_iterator(_lines-1);
}
Matrix::const_reverse_iterator Matrix::rend() const
{
    return const_reverse_iterator(_lines-1);
}
Matrix::const_reverse_iterator Matrix::crend() const
{
    return const_reverse_iterator(_lines-1);
}

// Capacity
size_t Matrix::size() const
{
    return _size;
}

// Modifiers
void Matrix::fill(double value)
{
    std::fill_n(_data, _size, value);
}
void Matrix::swap(Matrix&& other)
{
    std::swap(*this, other);
}


////////////////////////////////////////////////////////////
/// Miscellaneous functions (in class)
///
////////////////////////////////////////////////////////////

// Matrix width
size_t Matrix::width() const
{
    return _width;
}

// Matrix height
size_t Matrix::height() const
{
    return _height;
}

// Returns true if the matrix is a square matrix
bool Matrix::is_square() const
{
    return _height == _width;
}

// Returns true if the matrix is symmetric
bool Matrix::is_symmetric() const
{
    for (size_t i = 1 ; i < _height ; ++i)
    {
        for (size_t j = 0 ; j < i ; ++j)
        {
            if (_lines[i][j] != _lines[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

// Returns true if the matrix is inversible
bool Matrix::is_invertible() const
{
    return (is_square() && determinant() != 0);
}

// Returns true if at least one element of the Matrix is not null
bool Matrix::any() const
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        if (_data[i] != 0)
        {
            return true;
        }
    }
    return false;
}

// Returns true if none of the elements of the matrix is null
bool Matrix::all() const
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        if (_data[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// Returns true if the given number exists in the matrix
bool Matrix::exists(double d) const
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        if (_data[i] == d)
        {
            return true;
        }
    }
    return false;
}

// Returns the smallest element of a matrix
double Matrix::min() const
{
    double mini = _data[0];
    for (size_t i = 1 ; i < _size ; ++i)
    {
        if (_data[i] < mini)
        {
            mini = _data[i];
        }
    }
    return mini;
}

// Returns the greatest element of a matrix
double Matrix::max() const
{
    double maxi = _data[0];
    for (size_t i = 1 ; i < _size ; ++i)
    {
        if (_data[i] > maxi)
        {
            maxi = _data[i];
        }
    }
    return maxi;
}

// Returns the sum of all the elements of a Matrix
double Matrix::sum() const
{
    double res = _data[0];
    for (size_t i = 1 ; i < _size ; ++i)
    {
        res += _data[i];
    }
    return res;
}

// Returns the mean of all the elements of a matrix
double Matrix::mean() const
{
    double res = _data[0];
    for (size_t i = 1 ; i < _size ; ++i)
    {
        res += _data[i];
    }
    return res / _size;
}

// Returns the trace of the matrix
double Matrix::trace() const
{
    assert(is_square());
    double res = _data[0];
    for (size_t i = 1 ; i < _height ; ++i)
    {
        res += _lines[i][i];
    }
    return res;
}

// Returns the number of occurences of the given number in the matrix
size_t Matrix::count(double d) const
{
    size_t res = 0;
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res += (_data[i] == d);
    }
    return res;
}

double Matrix::determinant() const
{
    assert(is_square());

    if (_height == 2)
    {
        // Return the number corresponding to the determinant of degree two
        return _data[0]*_data[3] - _data[1]*_data[2];
    }
    else
    {
        double res = 0;

        // For all numbers in the first line
        for (size_t i = 0 ; i < _width ; ++i)
        {
            // Create a matrix 1 degree lesser than the first one
            Matrix _sub(_height-1, _width-1);

            size_t _count = 0;
            // Fill the new matrix
            for (size_t j = 1 ; j < _height ; ++j)
            {
                for (size_t k = 0 ; k < _width ; ++k)
                {
                    if (k != i)
                    {
                        _sub._data[_count++] = _lines[j][k];
                    }
                }
            }
            res += _data[i] * _sub.determinant() * pow(-1, i);
        }
        return res;
    }
}

double Matrix::minor(size_t h, size_t w) const
{
    assert(h < _height && w < _width);

    // Create a matrix 1 degree lesser than the first one
    Matrix _sub(_height-1, _width-1);

    size_t _count = 0;
    // Fill the new matrix
    for (size_t i = 0 ; i < _height ; ++i)
    {
        for (size_t j = 0 ; j < _width ; ++j)
        {
            if (i != h && j != w)
            {
                _sub._data[_count++] = _lines[i][j];
            }
        }
    }
    return _sub.determinant();
}

double Matrix::cofactor(size_t h, size_t w) const
{
    assert(h < _height && w < _width);
    return minor(h, w) * pow(-1, h+w);
}

// Flat iterators
Matrix::flat_iterator Matrix::fbegin()
{
    return _data;
}
Matrix::const_flat_iterator Matrix::fbegin() const
{
    return _data;
}
Matrix::const_flat_iterator Matrix::cfbegin() const
{
    return _data;
}
Matrix::flat_iterator Matrix::fend()
{
    return _data+_size;
}
Matrix::const_flat_iterator Matrix::fend() const
{
    return _data+_size;
}
Matrix::const_flat_iterator Matrix::cfend() const
{
    return _data+_size;
}
Matrix::reverse_flat_iterator Matrix::rfbegin()
{
    return reverse_flat_iterator(_data+_size-1);
}
Matrix::const_reverse_flat_iterator Matrix::rfbegin() const
{
    return const_reverse_flat_iterator(_data+_size-1);
}
Matrix::const_reverse_flat_iterator Matrix::crfbegin() const
{
    return const_reverse_flat_iterator(_data+_size-1);
}
Matrix::reverse_flat_iterator Matrix::rfend()
{
    return reverse_flat_iterator(_data-1);
}
Matrix::const_reverse_flat_iterator Matrix::rfend() const
{
    return const_reverse_flat_iterator(_data-1);
}
Matrix::const_reverse_flat_iterator Matrix::crfend() const
{
    return const_reverse_flat_iterator(_data-1);
}


////////////////////////////////////////////////////////////
/// Miscellaneous procedures (in class)
///
////////////////////////////////////////////////////////////

// Reshape the matrix with the given height and width
void Matrix::reshape(size_t h, size_t w)
{
    assert(h*w == _size);
    _height = h;
    _width = w;
    _lines = (line*) malloc(h * sizeof(line));
    for (size_t i = 0 ; i < _height ; ++i)
    {
        _lines[i] = line(w, _data+i*_width);
    }
}

// Collapse the Matrix into one dimension
void Matrix::flatten()
{
    _width *= _height;
    _height = 1;
    _size = _width;
    _lines = (line*) malloc(sizeof(line));
    _lines[0] = line(_width, _data);
}


////////////////////////////////////////////////////////////
/// Output streams gestion
///
////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Matrix& M)
{
    for (size_t i = 0 ; i < M._height ; ++i)
    {
        for (size_t j = 0 ; j < M._width ; ++j)
        {
            stream << M._lines[i][j] << "\t";
        }
        stream << std::endl;
    }
    return stream;
}


////////////////////////////////////////////////////////////
/// Matrix iterators
///
////////////////////////////////////////////////////////////

// Reversed iterators
Matrix::reverse_iterator::reverse_iterator(line* val):
    _value(val)
{}
Matrix::line& Matrix::reverse_iterator::operator*()
{
    return *_value;
}
Matrix::line* Matrix::reverse_iterator::operator->()
{
    return _value;
}
Matrix::reverse_iterator Matrix::reverse_iterator::operator++()
{
    reverse_iterator i = *this;
    --_value;
    return i;
}
Matrix::reverse_iterator Matrix::reverse_iterator::operator++(int)
{
    return --_value;
}
Matrix::reverse_iterator Matrix::reverse_iterator::operator--()
{
    reverse_iterator i = *this;
    ++_value;
    return i;
}
Matrix::reverse_iterator Matrix::reverse_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::reverse_iterator::operator==(const reverse_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::reverse_iterator::operator!=(const reverse_iterator& other) const
{
    return _value != other._value;
}


// Constant reversed iterators
Matrix::const_reverse_iterator::const_reverse_iterator(const line* val):
    _value(val)
{}
const Matrix::line& Matrix::const_reverse_iterator::operator*()
{
    return *_value;
}
const Matrix::line* Matrix::const_reverse_iterator::operator->()
{
    return _value;
}
Matrix::const_reverse_iterator Matrix::const_reverse_iterator::operator++()
{
    const_reverse_iterator i = *this;
    --_value;
    return i;
}
Matrix::const_reverse_iterator Matrix::const_reverse_iterator::operator++(int)
{
    return --_value;
}
Matrix::const_reverse_iterator Matrix::const_reverse_iterator::operator--()
{
    const_reverse_iterator i = *this;
    ++_value;
    return i;
}
Matrix::const_reverse_iterator Matrix::const_reverse_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return _value != other._value;
}

// Reversed flat iterators
Matrix::reverse_flat_iterator::reverse_flat_iterator(double* val):
    _value(val)
{}
double& Matrix::reverse_flat_iterator::operator*()
{
    return *_value;
}
Matrix::reverse_flat_iterator Matrix::reverse_flat_iterator::operator++()
{
    reverse_flat_iterator i = *this;
    --_value;
    return i;
}
Matrix::reverse_flat_iterator Matrix::reverse_flat_iterator::operator++(int)
{
    return --_value;
}
Matrix::reverse_flat_iterator Matrix::reverse_flat_iterator::operator--()
{
    reverse_flat_iterator i = *this;
    ++_value;
    return i;
}
Matrix::reverse_flat_iterator Matrix::reverse_flat_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::reverse_flat_iterator::operator==(const reverse_flat_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::reverse_flat_iterator::operator!=(const reverse_flat_iterator& other) const
{
    return _value != other._value;
}


// Constant reversed flat iterators
Matrix::const_reverse_flat_iterator::const_reverse_flat_iterator(const double* val):
    _value(val)
{}
const double& Matrix::const_reverse_flat_iterator::operator*()
{
    return *_value;
}
Matrix::const_reverse_flat_iterator Matrix::const_reverse_flat_iterator::operator++()
{
    const_reverse_flat_iterator i = *this;
    --_value;
    return i;
}
Matrix::const_reverse_flat_iterator Matrix::const_reverse_flat_iterator::operator++(int)
{
    return --_value;
}
Matrix::const_reverse_flat_iterator Matrix::const_reverse_flat_iterator::operator--()
{
    const_reverse_flat_iterator i = *this;
    ++_value;
    return i;
}
Matrix::const_reverse_flat_iterator Matrix::const_reverse_flat_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::const_reverse_flat_iterator::operator==(const const_reverse_flat_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::const_reverse_flat_iterator::operator!=(const const_reverse_flat_iterator& other) const
{
    return _value != other._value;
}



////////////////////////////////////////////////////////////
/// Matrix::line class
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Matrix::line constructors
////////////////////////////////////////////////////////////

// Default constructor
Matrix::line::line():
    _size(0),
    _data(nullptr)
{}

// Initilization constructor
Matrix::line::line(size_t width, double* data_addr):
    _size(width),
    _data(data_addr)
{}


/// Matrix::line size() function
size_t Matrix::line::size() const
{
    return _size;
}

////////////////////////////////////////////////////////////
/// Matrix::line operators
////////////////////////////////////////////////////////////

// Accessors
double& Matrix::line::operator[](size_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("Width out of range.");
    }
    return *(_data + index);
}
const double& Matrix::line::operator[](size_t index) const
{
    if (index >= _size)
    {
        throw std::out_of_range("Width out of range.");
    }
    return *(_data + index);
}

// Assignement
Matrix::line& Matrix::line::operator=(const line& other)
{
    if (this != &other)
    {
        _size = other._size;
        memcpy(_data, other._data, _size * sizeof(double));
    }
    return *this;
}
Matrix::line& Matrix::line::operator=(line&& other)
{
    if (this != &other)
    {
        _size = other._size;
        _data = other._data;
        other._data = nullptr;
    }
    return *this;
}


////////////////////////////////////////////////////////////
/// Matrix::line iterators
////////////////////////////////////////////////////////////

// Reverse iterators
Matrix::line::reverse_iterator::reverse_iterator(double* val):
    _value(val)
{}
double& Matrix::line::reverse_iterator::operator*() const
{
    return *_value;
}
Matrix::line::reverse_iterator Matrix::line::reverse_iterator::operator++()
{
    reverse_iterator i = *this;
    --_value;
    return i;
}
Matrix::line::reverse_iterator Matrix::line::reverse_iterator::operator++(int)
{
    return --_value;
}
Matrix::line::reverse_iterator Matrix::line::reverse_iterator::operator--()
{
    reverse_iterator i = *this;
    ++_value;
    return i;
}
Matrix::line::reverse_iterator Matrix::line::reverse_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::line::reverse_iterator::operator==(const reverse_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::line::reverse_iterator::operator!=(const reverse_iterator& other) const
{
    return _value != other._value;
}

// Constant reverse iterators
Matrix::line::const_reverse_iterator::const_reverse_iterator(double* val):
    _value(val)
{}
double Matrix::line::const_reverse_iterator::operator*() const
{
    return *_value;
}
Matrix::line::const_reverse_iterator Matrix::line::const_reverse_iterator::operator++()
{
    const_reverse_iterator i = *this;
    --_value;
    return i;
}
Matrix::line::const_reverse_iterator Matrix::line::const_reverse_iterator::operator++(int)
{
    return --_value;
}
Matrix::line::const_reverse_iterator Matrix::line::const_reverse_iterator::operator--()
{
    const_reverse_iterator i = *this;
    ++_value;
    return i;
}
Matrix::line::const_reverse_iterator Matrix::line::const_reverse_iterator::operator--(int)
{
    return ++_value;
}
bool Matrix::line::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return _value == other._value;
}
bool Matrix::line::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return _value != other._value;
}


////////////////////////////////////////////////////////////
/// Matrix::line begin and end functions
////////////////////////////////////////////////////////////

Matrix::line::iterator Matrix::line::begin()
{
    return _data;
}
Matrix::line::const_iterator Matrix::line::begin() const
{
    return _data;
}
Matrix::line::const_iterator Matrix::line::cbegin() const
{
    return _data;
}
Matrix::line::iterator Matrix::line::end()
{
    return _data + _size;
}
Matrix::line::const_iterator Matrix::line::end() const
{
    return _data + _size;
}
Matrix::line::const_iterator Matrix::line::cend() const
{
    return _data + _size;
}

Matrix::line::reverse_iterator Matrix::line::rbegin()
{
    return reverse_iterator(_data + _size - 1);
}
Matrix::line::const_reverse_iterator Matrix::line::rbegin() const
{
    return const_reverse_iterator(_data + _size - 1);
}
Matrix::line::const_reverse_iterator Matrix::line::crbegin() const
{
    return const_reverse_iterator(_data + _size - 1);
}
Matrix::line::reverse_iterator Matrix::line::rend()
{
    return reverse_iterator(_data - 1);
}
Matrix::line::const_reverse_iterator Matrix::line::rend() const
{
    return const_reverse_iterator(_data - 1);
}
Matrix::line::const_reverse_iterator Matrix::line::crend() const
{
    return const_reverse_iterator(_data - 1);
}




////////////////////////////////////////////////////////////
/// Functions not in the Matrix class
///
////////////////////////////////////////////////////////////

namespace matrix
{

////////////////////////////////////////////////////////////
/// Matrix creation from scratch
///
////////////////////////////////////////////////////////////

// Creation of a matrix of 0
Matrix zeros(size_t height, size_t width)
{
    assert(height > 0 && width > 0);
    Matrix res = Matrix(height, width);
    res.fill(0.0);
    return res;
}

// Creation of a line matrix of 0
Matrix zeros(size_t width)
{
    assert(width > 0);
    Matrix res = Matrix(width);
    res.fill(0.0);
    return res;
}

// Creation of a matrix of 1
Matrix ones(size_t height, size_t width)
{
    assert(width > 0 && height > 0);
    Matrix res = Matrix(height, width);
    res.fill(1.0);
    return res;
}

// Creation of a line matrix of 1
Matrix ones(size_t width)
{
    assert(width > 0);
    Matrix res = Matrix(width);
    res.fill(1.0);
    return res;
}

// Creation of the identity Matrix of degree N
Matrix identity(size_t n)
{
    Matrix I = zeros(n, n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        I[i][i] = 1;
    }
    return I;
}

// Creation of a Matrix with ones on a diagonal and zeros elsewhere
Matrix eye(size_t x, size_t y, int k)
{
    assert(x > 0 && y >= 0);
    Matrix res = (y == 0) ? Matrix(x, x) : Matrix(x, y);
    for (size_t i = 0 ; i < res.height() ; ++i)
    {
        for (size_t j = 0 ; j < res.width() ; ++j)
        {
            if (j == i + k)
            {
                res[i][j] = 1.0;
            }
            else
            {
                res[i][j] = 0.0;
            }
        }
    }

    return res;
}

// Creation of a 1D Matrix
// Matrix M = Range([beginning, ]end[, step])
Matrix range(int end)
{
    assert(end != 0);
    Matrix M = Matrix(abs(end));
    if (end > 0) // If end is positive
    {
        for (int i = 0 ; i < end ; ++i)
        {
            M[0][i] = i;
        }
    }
    else
    {
        for (int i = 0 ; i > end ; --i)
        {
            M[0][-i] = i;
        }
    }
    return M;
}
Matrix range(int begin, int end, int step)
{
    assert(end != begin);
    Matrix M;
    if (begin < end)
    {
        assert(step >= 0);
        if (step == 0)
        {
            step = 1;
        }
        size_t nb_values = (end - begin - 1) / step + 1;
        M = Matrix(nb_values);
        size_t count = 0;
        for (int i = begin ; i < end ; i += step)
        {
            M[0][count++] = i;
        }
    }
    else
    {
        assert(step <= 0);
        if (step == 0)
        {
            step = -1;
        }
        size_t nb_values = (begin - end - 1) / -step + 1;
        M = Matrix(nb_values);
        size_t count = 0;
        for (int i = begin ; i > end ; i += step)
        {
            M[0][count++] = i;
        }
    }
    return M;
}

////////////////////////////////////////////////////////////
/// Matrix creation from other Matrix
///
////////////////////////////////////////////////////////////

// Transpose of a Matrix
Matrix transpose(const Matrix& M)
{
    Matrix res = Matrix(M.width(), M.height());
    for (size_t i = 0 ; i < M.height() ; ++i)
    {
        for (size_t j = 0 ; j < M.width() ; ++j)
        {
            res[j][i] = M[i][j];
        }
    }
    return res;
}

// Creation of a matrix of 0 with the same size as a given matrix
Matrix zeros_like(const Matrix& M)
{
    return zeros(M.height(), M.width());
}

// Creation of a matrix of 1 with the same size as a given matrix
Matrix ones_like(const Matrix& M)
{
    return ones(M.height(), M.width());
}

// Creation of a matrix by changing the shape of another
Matrix reshape(const Matrix& M, size_t x, size_t y)
{
    assert(x > 0 && y > 0);
    assert(M.size() == x*y);
    Matrix res = M;
    res.reshape(x, y);
    return res;
}

// Diagonal matrix of M
Matrix diag(const Matrix& M)
{
    assert(M.is_square());
    Matrix N = zeros_like(M);
    for (size_t i = 0 ; i < M.width() ; ++i)
    {
        N[i][i] = M[i][i];
    }
    return N;
}

// Upper triangular matrix of M
Matrix upper_triangle(const Matrix& M)
{
    assert(M.is_square());
    Matrix N = zeros_like(M);
    for (size_t i = 0 ; i < N.height() ; ++i)
    {
        for (size_t j = i ; j < N.width() ; ++j)
        {
            N[i][j] = M[i][j];
        }
    }
    return N;
}

// Lower triangular matrix of M
Matrix lower_triangle(const Matrix& M)
{
    assert(M.is_square());
    Matrix N = zeros_like(M);
    for (size_t i = 0 ; i < N.height() ; ++i)
    {
        for (size_t j = 0 ; j <= i ; ++j)
        {
            N[i][j] = M[i][j];
        }
    }
    return N;
}

// Adjugate matrix of M
Matrix adjugate(const Matrix& M)
{
    assert(M.is_square());
    Matrix res(M.height(), M.width());

    // Light version of the script for the 2x2 Matrix
    if (M.height() == 2)
    {
        res[0][0] = M[1][1];
        res[0][1] = -M[0][1];
        res[1][0] = -M[1][0];
        res[1][1] = M[0][0];
    }
    else // Full version for a NxN Matrix
    {
        const size_t degree = M.height();
        //Matrix _sub(degree-1, degree-1);
        //int sign = 1; // + or -

        // For each cell of the Matrix
        for (size_t i = 0 ; i < degree ; ++i)
        {
            for (size_t j = 0 ; j < degree ; ++j)
            {
                res[i][j] = M.cofactor(i, j);
            }
        }
    }

    return res;
}

// Inverse matrix of M
Matrix inverse(const Matrix& M)
{
    assert(M.is_square());

    // Light version of the script for the 2x2 Matrix
    if (M.height() == 2)
    {
        const double det = M[0][0]*M[1][1] - M[0][1]*M[1][0];
        if (det == 0)
        {
            throw division_by_zero("Division by zero: Matrix determinant is 0.");
        }
        Matrix res(2, 2);
        res[0][0] = M[1][1];
        res[0][1] = -M[0][1];
        res[1][0] = -M[1][0];
        res[1][1] = M[0][0];
        return (res /= det);
    }
    else // Full version for a NxN Matrix
    {
        const double det = M.determinant();
        if (det == 0)
        {
            throw division_by_zero("Division by zero: Matrix determinant is 0.");
        }
        return (transpose(adjugate(M)) /= det);
    }
}

Matrix where(Matrix expr, double yes, double no)
{
    for (auto it = expr.fbegin() ; it != expr.fend() ; ++it)
    {
        *it = (*it ? yes : no);
    }
    return expr;
}


////////////////////////////////////////////////////////////
/// Display functions
///
////////////////////////////////////////////////////////////

void print_matrix(const Matrix& M)
{
    for (size_t i = 0 ; i < M.height() ; ++i)
    {
        for (size_t j = 0 ; j < M.width() ; ++j)
        {
            printf("%f ", M[i][j]);
        }
        printf("\n");
    }
}

void fprint_matrix(FILE* f, const Matrix& M)
{
    for (size_t i = 0 ; i < M.height() ; ++i)
    {
        for (size_t j = 0 ; j < M.width() ; ++j)
        {
            fprintf(f, "%f ", M[i][j]);
        }
        fprintf(f, "\n");
    }
}

} // namespace matrix
} // namespace polder
