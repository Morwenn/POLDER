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
#include "matrix.h"


namespace polder
{

////////////////////////////////////////////////////////////
/// Matrix constructors and destrutor
///
////////////////////////////////////////////////////////////

// Default constructor
Matrix::Matrix():
    _height(0),
    _width(0),
    _size(0),
    _data(NULL)
{}

// Copy constructor
Matrix::Matrix(const Matrix& other):
    _height(other._height),
    _width(other._width),
    _size(other._size),
    _data((double*) malloc(_size * sizeof(double)))
{
    memcpy(_data, other._data, _size * sizeof(double));
}

// Move constructor
Matrix::Matrix(Matrix&& other):
    _height(other._height),
    _width(other._width),
    _size(other._size),
    _data(other._data)
{
    other._data = NULL;
}

Matrix::Matrix(const std::initializer_list<double>& values):
    _height(1),
    _width(values.size()),
    _size(_width),
    _data((double*) malloc(_size * sizeof(double)))
{
    std::copy(values.begin(), values.end(), _data);
}

Matrix::Matrix(const std::initializer_list<const std::initializer_list<double>>& values):
    _height(values.size()),
    _width((*(values.begin())).size()),
    _size(_height*_width),
    _data((double*) malloc(_size * sizeof(double)))
{
    size_t count = 0;
    for (auto i = values.begin() ; i != values.end() ; ++i, ++count)
    {
        assert((*i).size() == _width);
        std::copy((*i).begin(), (*i).end(), _data+count*_width);
    }
}

// Uninitilized Matrix constructor
Matrix::Matrix(size_t x, size_t y):
    _height(x),
    _width(y),
    _size(x*y),
    _data((double*) malloc(_size * sizeof(double)))
{
    assert(x > 0 && y > 0);
}

// Uninitialized line Matrix constructor
Matrix::Matrix(size_t x):
    _height(1),
    _width(x),
    _size(x),
    _data((double*) malloc(x * sizeof(double)))
{
    assert(x > 0);
}

// Destructor
Matrix::~Matrix()
{
    if (_data != NULL)
    {
        free(_data);
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
        if (_data != NULL)
        {
            free(_data);
        }
        _height = other._height;
        _width = other._width;
        _data = (double*) malloc(_height * _width * sizeof(double));
        memcpy(_data, other._data, _height*_width*sizeof(double));
    }
    return *this;
}
Matrix& Matrix::operator=(Matrix&& other)
{
    if (this != &other)
    {
        if (_data != NULL)
        {
            free(_data);
        }
        _height = other._height;
        _width = other._width;
        _data = other._data;
        other._data = NULL;
    }
    return *this;
}


////////////////////////////////////////////////////////////
// Matrix elements accessors
////////////////////////////////////////////////////////////

const double* Matrix::operator[](size_t index) const
{
    assert(index < _height);
    return _data + index * _width;
}

double* Matrix::operator[](size_t index)
{
    assert(index < _height);
    return _data + index * _width;
}

double Matrix::operator()(size_t x, size_t y) const
{
    assert(x < _height && y < _width);
    return _data[x*_width+y];
}

double& Matrix::operator()(size_t x, size_t y)
{
    assert(x < _height && y < _width);
    return _data[x*_width+y];
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
Matrix& Matrix::operator+=(const double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] += d;
    }
    return *this;
}

Matrix& Matrix::operator-=(const double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] -= d;
    }
    return *this;
}

Matrix& Matrix::operator*=(const double d)
{
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] *= d;
    }
    return *this;
}

Matrix& Matrix::operator/=(const double d)
{
    assert(d != 0);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        _data[i] /= d;
    }
    return *this;
}

Matrix& Matrix::operator%=(const int d)
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

const Matrix Matrix::operator+(const double& other) const
{
    return Matrix(*this) += other;
}

const Matrix Matrix::operator-(const double& other) const
{
    return Matrix(*this) -= other;
}

const Matrix Matrix::operator*(const double& other) const
{
    return Matrix(*this) *= other;
}

const Matrix Matrix::operator/(const double& other) const
{
    return Matrix(*this) /= other;
}

const Matrix Matrix::operator%(const int& other) const
{
    return Matrix(*this) %= other;
}


////////////////////////////////////////////////////////////
// Matrix-double "masks"
////////////////////////////////////////////////////////////

const Matrix Matrix::operator==(const double& other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] == other);
    }
    return res;
}

const Matrix Matrix::operator!=(const double& other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] != other);
    }
    return res;
}

const Matrix Matrix::operator>(const double& other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] > other);
    }
    return res;
}

const Matrix Matrix::operator<(const double& other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] < other);
    }
    return res;
}

const Matrix Matrix::operator>=(const double& other) const
{
    Matrix res = Matrix(_height, _width);
    for (size_t i = 0 ; i < _size ; ++i)
    {
        res._data[i] = (_data[i] >= other);
    }
    return res;
}

const Matrix Matrix::operator<=(const double& other) const
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
    return (*this *= matrix::inverse(other));
}


////////////////////////////////////////////////////////////
// Matrix-Matrix operations
////////////////////////////////////////////////////////////

const Matrix Matrix::operator+(const Matrix& other) const
{
    return (Matrix(*this) += other);
}

const Matrix Matrix::operator-(const Matrix& other) const
{
    return (Matrix(*this) -= other);
}

const Matrix Matrix::operator*(const Matrix& other) const
{
    return (Matrix(*this) *= other);
}

const Matrix Matrix::operator/(const Matrix& other) const
{
    return (Matrix(*this) /= other);
}


////////////////////////////////////////////////////////////
/// STL-like functions
///
////////////////////////////////////////////////////////////

// Accessors
double& Matrix::at(size_t x, size_t y)
{
    assert(x < _height && y < _width);
    return _data[x*_width+y];
}
const double& Matrix::at(size_t x, size_t y) const
{
    assert(x < _height && y < _width);
    return _data[x*_width+y];
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
Matrix::iterator Matrix::begin() const
{
    return iterator(_data);
}
Matrix::iterator Matrix::end() const
{
    return iterator(_data+_size);
}
Matrix::reverse_iterator Matrix::rbegin() const
{
    return reverse_iterator(_data+_size);
}
Matrix::reverse_iterator Matrix::rend() const
{
    return reverse_iterator(_data);
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
void Matrix::swap(Matrix& other)
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
    return (_height == _width);
}

// Returns true if the matrix is symmetric
bool Matrix::is_symmetric() const
{
    for (size_t i = 1 ; i < _height ; ++i)
    {
        for (size_t j = 0 ; j < i ; ++j)
        {
            if (_data[i*_width+j] != _data[j*_width+i])
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
        res += _data[i*_width+i];
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
    return math::determinant(_height, _data);
}


////////////////////////////////////////////////////////////
/// Miscellaneous procedures (in class)
///
////////////////////////////////////////////////////////////

// Reshape the matrix with the given height and width
void Matrix::reshape(size_t x, size_t y)
{
    assert(x*y == _size);
    _height = x;
    _width = y;
}

// Collapse the Matrix into one dimension
void Matrix::flatten()
{
    _width *= _height;
    _height = 1;
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
            stream << M[i][j] << " ";
        }
        stream << std::endl;
    }
    return stream;
}


////////////////////////////////////////////////////////////
/// Matrix iterators
///
////////////////////////////////////////////////////////////

// Constructor
Matrix::iterator::iterator(double* val):
    _value(val)
{}

double& Matrix::iterator::operator*() const
{
    return *_value;
}

void Matrix::iterator::operator++()
{
    ++_value;
}

void Matrix::iterator::operator++(int)
{
    ++_value;
}

void Matrix::iterator::operator--()
{
    --_value;
}

void Matrix::iterator::operator--(int)
{
    --_value;
}

bool Matrix::iterator::operator==(iterator other) const
{
    return _value == other._value;
}

bool Matrix::iterator::operator!=(iterator other) const
{
    return _value != other._value;
}

////////////////////////////////////////////////////////////
/// Matrix reverse iterators
///
////////////////////////////////////////////////////////////

// Constructor
Matrix::reverse_iterator::reverse_iterator(double* val):
    _value(val)
{}

double& Matrix::reverse_iterator::operator*() const
{
    return *_value;
}

void Matrix::reverse_iterator::operator++()
{
    --_value;
}

void Matrix::reverse_iterator::operator++(int)
{
    --_value;
}

void Matrix::reverse_iterator::operator--()
{
    ++_value;
}

void Matrix::reverse_iterator::operator--(int)
{
    ++_value;
}

bool Matrix::reverse_iterator::operator==(reverse_iterator other) const
{
    return _value == other._value;
}

bool Matrix::reverse_iterator::operator!=(reverse_iterator other) const
{
    return _value != other._value;
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
Matrix zeros(size_t x, size_t y)
{
    assert(x > 0 && y > 0);
    Matrix res = Matrix(x, y);
    for (size_t i = 0 ; i < x ; ++i)
    {
        for (size_t j = 0 ; j < y ; ++j)
        {
            res[i][j] = 0.0;
        }
    }
    return res;
}

// Creation of a matrix of 0
Matrix zeros(size_t x)
{
    Matrix res = Matrix(x);
    for (size_t i = 0 ; i < x ; ++i)
    {
        res[0][i] = 0.0;
    }
    return res;
}

// Creation of a matrix of 1
Matrix ones(size_t x, size_t y)
{
    assert(x > 0 && y > 0);
    Matrix res = Matrix(x, y);
    for (size_t i = 0 ; i < x ; ++i)
    {
        for (size_t j = 0 ; j < y ; ++j)
        {
            res[i][j] = 1.0;
        }
    }
    return res;
}

// Creation of a matrix of 1
Matrix ones(size_t x)
{
    Matrix res = Matrix(x);
    for (size_t i = 0 ; i < x ; ++i)
    {
        res[0][i] = 1.0;
    }
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
Matrix range(int beginning, int end, int step)
{
    assert(end != beginning);
    Matrix M;
    if (beginning < end)
    {
        assert(step >= 0);
        if (step == 0)
        {
            step = 1;
        }
        size_t nb_values = (end - beginning - 1) / step + 1;
        M = Matrix(nb_values);
        size_t count = 0;
        for (int i = beginning ; i < end ; i += step)
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
        size_t nb_values = (beginning - end - 1) / -step + 1;
        M = Matrix(nb_values);
        size_t count = 0;
        for (int i = beginning ; i > end ; i += step)
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
        double* tmp_tab = (double*) malloc((degree-1)*(degree-1) * sizeof(double));
        int sign = 1; // + or -

        // For each cell of the Matrix
        for (size_t i = 0 ; i < degree ; ++i)
        {
            for (size_t j = 0 ; j < degree ; ++j)
            {
                // Fill the temporary tab
                size_t count = 0;
                sign = (((i+j) % 2 == 0) ? 1 : -1);
                for (size_t k = 0 ; k < degree ; ++k)
                {
                    for (size_t l = 0 ; l < degree ; ++l)
                    {
                        if (k != i && l != j)
                        {
                            tmp_tab[count++] = M[k][l];
                        }
                    }
                }
                res[i][j] = sign * math::determinant(degree-1, tmp_tab);
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
        assert(det != 0);
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
        assert(det != 0); // M must be invertible
        return (transpose(adjugate(M)) /= det);
    }
}

Matrix where(const Matrix& expr, double yes, double no)
{
    Matrix res = Matrix(expr);
    for (size_t i = 0 ; i < res.height() ; ++i)
    {
        for (size_t j = 0 ; j < res.width() ; ++j)
        {
            res[i][j] = ((res[i][j]) ? yes : no);
        }
    }
    return res;
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
