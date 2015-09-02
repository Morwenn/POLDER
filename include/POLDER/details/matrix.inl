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

////////////////////////////////////////////////////////////
// Defaulted functions
////////////////////////////////////////////////////////////

template<typename T>
Matrix<T>::Matrix() = default;

template<typename T>
Matrix<T>::~Matrix() = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<typename T>
Matrix<T>::Matrix(const Matrix& other):
    _height(other._height),
    _width(other._width),
    _data(other._data),
    _rows()
{
    for (size_type i = 0 ; i < height() ; ++i)
    {
        T* target = _data.data() + i * _width;
        _rows.emplace_back(_width, target);
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept:
    _height(other._height),
    _width(other._width),
    _data(std::move(other._data)),
    _rows(std::move(other._rows))
{}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<T> values):
    _height(1),
    _width(values.size()),
    _data(std::begin(values), std::end(values)),
    _rows()
{
    _rows.emplace_back(_width, data());
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> values):
    _height(values.size()),
    _width(std::begin(values)->size()),
    _data(_height*_width), // reserve memory
    _rows()
{
    size_type _count = 0;
    for (const auto& row: values)
    {
        if (row.size() != _width)
        {
            throw std::logic_error("All the rows in a Matrix should have the same size.");
        }
        T* target = _data.data() + _count * _width;
        _rows.emplace_back(_width, target);
        std::copy(std::begin(row), std::end(row), target);
        ++_count;
    }
}

template<typename T>
Matrix<T>::Matrix(size_type h, size_type w):
    _height(h),
    _width(w),
    _data(_height*_width), // reserve memory
    _rows()
{
    for (size_type i = 0 ; i < height() ; ++i)
    {
        T* target = _data.data() + i * _width;
        _rows.emplace_back(_width, target);
    }
}

template<typename T>
Matrix<T>::Matrix(size_type w):
    Matrix<T>(1, w)
{}

////////////////////////////////////////////////////////////
// Construction functions
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::zeros(size_type height, size_type width)
    -> Matrix
{
    auto res = Matrix<T>(height, width);
    res.fill(T{});
    return res;
}

template<typename T>
auto Matrix<T>::zeros(size_type width)
    -> Matrix
{
    auto res = Matrix<T>(width);
    res.fill(T{});
    return res;
}

template<typename T>
auto Matrix<T>::ones(size_type height, size_type width)
    -> Matrix
{
    auto res = Matrix<T>(height, width);
    res.fill(T{1});
    return res;
}

template<typename T>
auto Matrix<T>::ones(size_type width)
    -> Matrix
{
    auto res = Matrix<T>(width);
    res.fill(T{1});
    return res;
}

template<typename T>
auto Matrix<T>::identity(size_type size)
    -> Matrix
{
    auto res = zeros(size, size);
    for (size_type i = 0 ; i < size ; ++i)
    {
        res(i, i) = T{1};
    }
    return res;
}

template<typename T>
auto Matrix<T>::eye(size_type x, size_type y, int k)
    -> Matrix
{
    POLDER_ASSERT(x > 0);

    Matrix<T> res = (y == 0) ? Matrix<T>(x, x) : Matrix<T>(x, y);
    for (size_type i = 0 ; i < res.height() ; ++i)
    {
        for (size_type j = 0 ; j < res.width() ; ++j)
        {
            if (j == i + k)
            {
                res(i, j) = T{1};
            }
            else
            {
                res(i, j) = T{};
            }
        }
    }
    return res;
}

////////////////////////////////////////////////////////////
// Assignment operator
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::operator=(const Matrix<T>& other) &
    -> Matrix&
{
    if (this != &other)
    {
        _height = other._height;
        _width = other._width;
        _data = other._data;
        _rows = std::vector<row>();
        for (size_type i = 0 ; i < height() ; ++i)
        {
            T* target = _data.data() + i * _width;
            _rows.emplace_back(_width, target);
        }
    }
    return *this;
}

template<typename T>
auto Matrix<T>::operator=(Matrix<T>&& other) & noexcept
    -> Matrix&
{
    if (this != &other)
    {
        _height = other._height;
        _width = other._width;
        _data = std::move(other._data);
        _rows = std::move(other._rows);
    }
    return *this;
}

////////////////////////////////////////////////////////////
// Operators (accessors)
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::operator[](size_type index)
    -> row&
{
    return _rows[index];
}

template<typename T>
auto Matrix<T>::operator[](size_type index) const
    -> const row&
{
    return _rows[index];
}

template<typename T>
auto Matrix<T>::operator()(size_type y, size_type x)
    -> reference
{
    return _data[y*width()+x];
}

template<typename T>
auto Matrix<T>::operator()(size_type y, size_type x) const
    -> value_type
{
    return _data[y*width()+x];
}

////////////////////////////////////////////////////////////
// Matrix-Matrix arithmetic operations
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::operator+=(const Matrix<T>& other)
    -> Matrix&
{
    POLDER_ASSERT(width() == other.width());
    POLDER_ASSERT(height() == other.height());
    for_each(fbegin(), fend(), other.fbegin(), plus_assign());
    return *this;
}

template<typename T>
auto Matrix<T>::operator-=(const Matrix<T>& other)
    -> Matrix&
{
    POLDER_ASSERT(width() == other.width());
    POLDER_ASSERT(height() == other.height());
    for_each(fbegin(), fend(), other.fbegin(), minus_assign());
    return *this;
}

template<typename T>
auto Matrix<T>::operator*=(const Matrix<T>& other)
    -> Matrix&
{
    *this = (*this * other);
    return *this;
}

template<typename T>
auto Matrix<T>::operator/=(const Matrix<T>& other)
    -> Matrix<T>&
{
    POLDER_ASSERT(is_square());
    POLDER_ASSERT(other.is_invertible());
    return (*this) *= inverse(other);
}

////////////////////////////////////////////////////////////
// Matrix-value_type arithmetic operations
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::operator*=(value_type other)
    -> Matrix&
{
    for (auto& val: _data)
    {
        val *= other;
    }
    return *this;
}

template<typename T>
auto Matrix<T>::operator/=(value_type other)
    -> Matrix&
{
    for (auto& val: _data)
    {
        val /= other;
    }
    return *this;
}

////////////////////////////////////////////////////////////
// STL-like functions
////////////////////////////////////////////////////////////

// Accessors
template<typename T>
auto Matrix<T>::front()
    -> reference
{
    return _data.front();
}
template<typename T>
auto Matrix<T>::front() const
    -> const_reference
{
    return _data.front();
}

template<typename T>
auto Matrix<T>::back()
    -> reference
{
    return _data.back();
}
template<typename T>
auto Matrix<T>::back() const
    -> const_reference
{
    return _data.back();
}

template<typename T>
auto Matrix<T>::data()
    -> T*
{
    return _data.data();
}
template<typename T>
auto Matrix<T>::data() const
    -> const T*
{
    return _data.data();
}

// Iterators
template<typename T>
auto Matrix<T>::begin()
    -> iterator
{
    return std::begin(_rows);
}
template<typename T>
auto Matrix<T>::begin() const
    -> const_iterator
{
    return std::begin(_rows);
}
template<typename T>
auto Matrix<T>::cbegin() const
    -> const_iterator
{
    return std::begin(_rows);
}

template<typename T>
auto Matrix<T>::end()
    -> iterator
{
    return std::end(_rows);
}
template<typename T>
auto Matrix<T>::end() const
    -> const_iterator
{
    return std::end(_rows);
}
template<typename T>
auto Matrix<T>::cend() const
    -> const_iterator
{
    return std::end(_rows);
}

template<typename T>
auto Matrix<T>::rbegin()
    -> reverse_iterator
{
    return _rows.rbegin();
}
template<typename T>
auto Matrix<T>::rbegin() const
    -> const_reverse_iterator
{
    return _rows.rbegin();
}
template<typename T>
auto Matrix<T>::crbegin() const
    -> const_reverse_iterator
{
    return _rows.crbegin();
}

template<typename T>
auto Matrix<T>::rend()
    -> reverse_iterator
{
    return _rows.rend();
}
template<typename T>
auto Matrix<T>::rend() const
    -> const_reverse_iterator
{
    return _rows.rend();
}
template<typename T>
auto Matrix<T>::crend() const
    -> const_reverse_iterator
{
    return _rows.crend();
}

// Modifiers
template<typename T>
auto Matrix<T>::fill(value_type value)
    -> void
{
    std::fill(std::begin(_data), std::end(_data), value);
}

template<typename T>
auto Matrix<T>::swap(Matrix<T>&& other)
    -> void
{
    std::swap(*this, other);
}

////////////////////////////////////////////////////////////
// NumPy-like functions
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::all() const
    -> bool
{
    for (const auto& val: _data)
    {
        if (not val)
        {
            return false;
        }
    }
    return true;
}

template<typename T>
auto Matrix<T>::any() const
    -> bool
{
    for (const auto& val: _data)
    {
        if (val)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
auto Matrix<T>::min() const
    -> value_type
{
    return *std::min_element(fbegin(), fend());
}

template<typename T>
auto Matrix<T>::max() const
    -> value_type
{
    return *std::max_element(fbegin(), fend());
}

template<typename T>
auto Matrix<T>::sum() const
    -> value_type
{
    return std::accumulate(fbegin(), fend(), T{0});
}

template<typename T>
auto Matrix<T>::reshape(size_type height, size_type width)
    -> void
{
    POLDER_ASSERT(height*width == size());

    _height = height;
    _width = width;
    _rows = std::vector<row>();
    for (size_type i = 0 ; i < _height ; ++i)
    {
        T* target = _data.data() + i * _width;
        _rows.emplace_back(_width, target);
    }
}

template<typename T>
auto Matrix<T>::flatten()
    -> void
{
    _height = 1;
    _width = _data.size();
    _rows = std::vector<row>();
    _rows.emplace_back(_width, data());
}

////////////////////////////////////////////////////////////
// Miscellaneous functions (in class)
////////////////////////////////////////////////////////////

// Capacity
template<typename T>
auto Matrix<T>::height() const
    -> size_type
{
    return _height;
}

template<typename T>
auto Matrix<T>::width() const
    -> size_type
{
    return _width;
}

// Properties
template<typename T>
auto Matrix<T>::is_symmetric() const
    -> bool
{
    for (size_type i = 1 ; i < _height ; ++i)
    {
        for (size_type j = 0 ; j < i ; ++j)
        {
            if (_rows[i][j] != _rows[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
auto Matrix<T>::is_invertible() const
    -> bool
{
    return is_square() && (determinant() != 0);
}

// other functions
template<typename T>
auto Matrix<T>::determinant() const
    -> value_type
{
    POLDER_ASSERT(is_square());

    if (height() == 2)
    {
        // Return the number corresponding to the determinant of degree two
        return _data[0] * _data[3] -
               _data[1] * _data[2];
    }
    else
    {
        value_type res{};
        // For all numbers in the first line
        for (size_type i = 0 ; i < width() ; ++i)
        {
            // Create a matrix 1 degree lesser than the first one
            Matrix<T> sub(height()-1, width()-1);

            size_type count = 0;
            // Fill the new matrix
            for (size_type j = 1 ; j < height() ; ++j)
            {
                for (size_type k = 0 ; k < width() ; ++k)
                {
                    if (k != i)
                    {
                        sub._data[count++] = _rows[j][k];
                    }
                }
            }
            res += _data[i] * sub.determinant() * int(std::pow(-1, i));
        }
        return res;
    }
}

template<typename T>
auto Matrix<T>::minor(size_type y, size_type x) const
    -> value_type
{
    POLDER_ASSERT(y < height() && x < width());

    // Create a matrix 1 degree lesser than the first one
    Matrix<T> sub(height()-1, width()-1);

    size_type count = 0;
    // Fill the new matrix
    for (size_type i = 0 ; i < height() ; ++i)
    {
        for (size_type j = 0 ; j < width() ; ++j)
        {
            if (i != y && j != x)
            {
                sub._data[count++] = _rows[i][j];
            }
        }
    }
    return sub.determinant();
}

////////////////////////////////////////////////////////////
// Flat iterator functions
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::fbegin()
    -> flat_iterator
{
    return std::begin(_data);
}
template<typename T>
auto Matrix<T>::fbegin() const
    -> const_flat_iterator
{
    return std::begin(_data);
}
template<typename T>
auto Matrix<T>::cfbegin() const
    -> const_flat_iterator
{
    return std::begin(_data);
}

template<typename T>
auto Matrix<T>::fend()
    -> flat_iterator
{
    return std::end(_data);
}
template<typename T>
auto Matrix<T>::fend() const
    -> const_flat_iterator
{
    return std::end(_data);
}
template<typename T>
auto Matrix<T>::cfend() const
    -> const_flat_iterator
{
    return std::end(_data);
}

template<typename T>
auto Matrix<T>::rfbegin()
    -> reverse_flat_iterator
{
    return _data.rbegin();
}
template<typename T>
auto Matrix<T>::rfbegin() const
    -> const_reverse_flat_iterator
{
    return _data.rbegin();
}
template<typename T>
auto Matrix<T>::crfbegin() const
    -> const_reverse_flat_iterator
{
    return _data.crbegin();
}

template<typename T>
auto Matrix<T>::rfend()
    -> reverse_flat_iterator
{
    return _data.rend();
}
template<typename T>
auto Matrix<T>::rfend() const
    -> const_reverse_flat_iterator
{
    return _data.rend();
}
template<typename T>
auto Matrix<T>::crfend() const
    -> const_reverse_flat_iterator
{
    return _data.crend();
}

////////////////////////////////////////////////////////////
// Matrix::row constructors
////////////////////////////////////////////////////////////

template<typename T>
Matrix<T>::row::row(size_type size, T* data_addr):
    _size(size),
    _data(data_addr)
{}

////////////////////////////////////////////////////////////
// Matrix::row operators
////////////////////////////////////////////////////////////

template<typename T>
auto Matrix<T>::row::operator[](size_type index)
    -> reference
{
    return _data[index];
}

template<typename T>
auto Matrix<T>::row::operator[](size_type index) const
    -> const_reference
{
    return _data[index];
}

////////////////////////////////////////////////////////////
// Matrix::row functions
////////////////////////////////////////////////////////////

// Iterators
template<typename T>
auto Matrix<T>::row::begin()
    -> iterator
{
    return _data;
}
template<typename T>
auto Matrix<T>::row::begin() const
    -> const_iterator
{
    return _data;
}
template<typename T>
auto Matrix<T>::row::cbegin() const
    -> const_iterator
{
    return _data;
}

template<typename T>
auto Matrix<T>::row::end()
    -> iterator
{
    return _data + _size;
}
template<typename T>
auto Matrix<T>::row::end() const
    -> const_iterator
{
    return _data + _size;
}
template<typename T>
auto Matrix<T>::row::cend() const
    -> const_iterator
{
    return _data + _size;
}

template<typename T>
auto Matrix<T>::row::rbegin()
    -> reverse_iterator
{
    return reverse_iterator(end());
}
template<typename T>
auto Matrix<T>::row::rbegin() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(end());
}
template<typename T>
auto Matrix<T>::row::crbegin() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(cend());
}

template<typename T>
auto Matrix<T>::row::rend()
    -> reverse_iterator
{
    return reverse_iterator(begin());
}
template<typename T>
auto Matrix<T>::row::rend() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(begin());
}
template<typename T>
auto Matrix<T>::row::crend() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(cbegin());
}

// Capacity
template<typename T>
auto Matrix<T>::row::size() const
    -> size_type
{
    return _size;
}

////////////////////////////////////////////////////////////
// Matrix-Matrix comparison (outside class)
////////////////////////////////////////////////////////////

template<typename T>
auto operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
    -> bool
{
    if (lhs.height() != rhs.height()
        || lhs.width() != rhs.width())
    {
        return false;
    }
    return std::equal(lhs.fbegin(), lhs.fend(),
                      rhs.fbegin(), rhs.fend());
}

template<typename T>
auto operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Matrix-Matrix arithmetic operations (outside class)
////////////////////////////////////////////////////////////

template<typename T>
auto operator+(Matrix<T> lhs, const Matrix<T>& rhs)
    -> Matrix<T>
{
    return lhs += rhs;
}

template<typename T>
auto operator-(Matrix<T> lhs, const Matrix<T>& rhs)
    -> Matrix<T>
{
    return lhs -= rhs;
}

template<typename T>
auto operator*(Matrix<T> lhs, const Matrix<T>& rhs)
    -> Matrix<T>
{
    POLDER_ASSERT(lhs.width() == rhs.height());
    using size_type = typename Matrix<T>::size_type;

    Matrix<T> res = Matrix<T>(lhs.height(), rhs.width());
    for (size_type i = 0 ; i < lhs.height() ; ++i)
    {
        for (size_type j = 0 ; j < rhs.width() ; ++j)
        {
            T val{};
            for (size_type k = 0 ; k < lhs.width() ; ++k)
            {
                val += lhs(i, k) * rhs(k, j);
            }
            res(i, j) = val;
        }
    }
    return res;
}

template<typename T>
auto operator/(Matrix<T> lhs, const Matrix<T>& rhs)
    -> Matrix<T>
{
    return lhs /= rhs;
}

////////////////////////////////////////////////////////////
// Matrix-value_type arithmetic operations (outside class)
////////////////////////////////////////////////////////////

template<typename T>
auto operator*(Matrix<T> lhs, T rhs)
    -> Matrix<T>
{
    return lhs *= rhs;
}

template<typename T>
auto operator*(T lhs, Matrix<T> rhs)
    -> Matrix<T>
{
    return rhs *= lhs;
}

template<typename T>
auto operator/(Matrix<T> lhs, T rhs)
    -> Matrix<T>
{
    return lhs /= rhs;
}

////////////////////////////////////////////////////////////
// Stream handling
////////////////////////////////////////////////////////////

template<typename T>
auto operator<<(std::ostream& stream, const Matrix<T>& mat)
    -> std::ostream&
{
    for (const auto& row: mat)
    {
        for (const auto& value: row)
        {
            stream << value << '\t';
        }
        stream << '\n';
    }
    return stream;
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

template<typename T>
auto adjugate(const Matrix<T>& mat)
    -> Matrix<T>
{
    POLDER_ASSERT(mat.is_square());
    using size_type = typename Matrix<T>::size_type;

    Matrix<T> res(mat.height(), mat.width());

    if (mat.height() == 2)
    {
        // Optimized formula for 2x2 Matrix
        res(0, 0) = mat(1, 1);
        res(0, 1) = -mat(0, 1);
        res(1, 0) = -mat(1, 0);
        res(1, 1) = mat(0, 0);
    }
    else // Generic formula
    {
        size_type degree = mat.height();
        for (size_type i = 0 ; i < degree ; ++i)
        {
            for (size_type j = 0 ; j < degree ; ++j)
            {
                res(i, j) = cofactor(mat, {i, j});
            }
        }
    }
    return res;
}

template<typename T>
auto cofactor(const Matrix<T> mat, std::pair<std::size_t, std::size_t> index)
    -> typename Matrix<T>::value_type
{
    auto y = index.first;
    auto x = index.second;
    POLDER_ASSERT(y < mat.height() && x < mat.width());
    return minor(mat, {y, x}) * int(std::pow(-1, y+x));
}

template<typename T>
inline auto determinant(const Matrix<T>& mat)
    -> typename Matrix<T>::value_type
{
    return mat.determinant();
}

template<typename T>
auto inverse(const Matrix<T>& mat)
    -> Matrix<T>
{
    // Faster than mat.is_invertible
    POLDER_ASSERT(mat.is_square());
    const T det = determinant(mat);
    POLDER_ASSERT(det != 0);

    if (mat.height() == 2)
    {
        // Optimized formula for 2x2 Matrix
        Matrix<T> res(2, 2);
        res(0, 0) = mat(1, 1);
        res(0, 1) = -mat(0, 1);
        res(1, 0) = -mat(1, 0);
        res(1, 1) = mat(0, 0);
        return (res /= det);
    }
    else
    {
        // Generic formula
        return transpose(adjugate(mat)) /= det;
    }
}

template<typename T>
inline auto minor(const Matrix<T>& mat, std::pair<std::size_t, std::size_t> index)
    -> typename Matrix<T>::value_type
{
    return mat.minor(index.first, index.second);
}

template<typename T>
auto trace(const Matrix<T>& mat)
    -> typename Matrix<T>::value_type
{
    POLDER_ASSERT(mat.is_square());

    auto res = mat(0, 0);
    for (decltype(mat.size()) i = 1 ; i < mat.height() ; ++i)
    {
        res += mat(i, i);
    }
    return res;
}

template<typename T>
auto transpose(const Matrix<T>& mat)
    -> Matrix<T>
{
    using size_type = typename Matrix<T>::size_type;
    Matrix<T> res = Matrix<T>(mat.width(), mat.height());
    for (size_type i = 0 ; i < mat.height() ; ++i)
    {
        for (size_type j = 0 ; j < mat.width() ; ++j)
        {
            res[j][i] = mat[i][j];
        }
    }
    return res;
}
