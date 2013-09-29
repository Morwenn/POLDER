/*
 * Copyright (C) 2011-2013 Morwenn
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
#ifndef _POLDER_MATRIX_H
#define _POLDER_MATRIX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <numeric>
#include <ostream>
#include <vector>
#include <POLDER/algorithm.h>
#include <POLDER/config.h>
#include <POLDER/functional.h>
#include <POLDER/matrix/base.h>

namespace polder
{
    template<typename T>
    class Matrix;

    /**
     * @brief Trait holding the Matrix types
     */
    template<typename T>
    struct types_t<Matrix<T>>
    {
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
    };

    /**
     * @brief Matrix implementation
     *
     * A Matrix is a two dimensions array of data.
     * It can be accessed as an array of arrays but
     * has some particularities described below.
     */
    template<typename T>
    class Matrix:
        public MutableMatrix<Matrix<T>>
    {
        public:

            // Forward declaration
            struct row;

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            using super = MutableMatrix<Matrix<T>>;

            // Sizes
            using size_type = typename super::size_type;
            using difference_type = typename super::difference_type;
            // Value
            using value_type = T;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type*;
            // Iterators
            using iterator = typename std::vector<row>::iterator;
            using const_iterator = typename std::vector<row>::const_iterator;
            using reverse_iterator = typename std::vector<row>::reverse_iterator;
            using const_reverse_iterator = typename std::vector<row>::const_reverse_iterator;
            // Flat iterators
            using flat_iterator = typename std::vector<T>::iterator;
            using const_flat_iterator = typename std::vector<T>::const_iterator;
            using reverse_flat_iterator = typename std::vector<T>::reverse_iterator;
            using const_reverse_flat_iterator = typename std::vector<T>::const_reverse_iterator;

            ////////////////////////////////////////////////////////////
            // Constructors and destructor
            ////////////////////////////////////////////////////////////

            // Default constructor
            Matrix();
            // Copy constructor
            Matrix(const Matrix& other);
            // Move constructor
            Matrix(Matrix&& other) noexcept;
            // Initializer list constructors
            Matrix(std::initializer_list<T> values);
            Matrix(std::initializer_list<std::initializer_list<T>> values);
            // Constructors with size
            Matrix(size_type height, size_type width);
            explicit Matrix(size_type width);

            // Destructor
            ~Matrix();

            ////////////////////////////////////////////////////////////
            // Construction functions
            ////////////////////////////////////////////////////////////

            static auto zeros(size_type height, size_type width)
                -> Matrix;
            static auto zeros(size_type width)
                -> Matrix;
            static auto ones(size_type height, size_type width)
                -> Matrix;
            static auto ones(size_type width)
                -> Matrix;
            static auto identity(size_type size)
                -> Matrix;
            static auto eye(size_type x, size_type y=0, int k=0)
                -> Matrix;

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Accessors
            auto operator[](size_type index)
                -> row&;
            auto operator[](size_type index) const
                -> const row&;
            auto operator()(size_type y, size_type x)
                -> reference;
            auto operator()(size_type y, size_type x) const
                -> value_type;

            // Assignment operator
            auto operator=(const Matrix<T>& other)
                -> Matrix&;
            auto operator=(Matrix<T>&& other) noexcept
                -> Matrix&;

            // Matrix-Matrix arithmetic operations
            auto operator+=(const Matrix<T>& other)
                -> Matrix&;
            auto operator-=(const Matrix<T>& other)
                -> Matrix&;
            auto operator*=(const Matrix<T>& other)
                -> Matrix&;
            auto operator/=(const Matrix<T>& other)
                -> Matrix&;

            // Matrix-value_type arithmetic operations
            auto operator*=(value_type other)
                -> Matrix&;
            auto operator/=(value_type other)
                -> Matrix&;

            ////////////////////////////////////////////////////////////
            // STL-like functions
            ////////////////////////////////////////////////////////////

            // Capacity
            using super::size; // Solve ADL problem

            // Accessors
            auto front()
                -> reference;
            auto front() const
                -> const_reference;
            auto back()
                -> reference;
            auto back() const
                -> const_reference;
            auto data()
                -> T*;
            auto data() const
                -> const T*;

            // Iterators
            auto begin()
                -> iterator;
            auto begin() const
                -> const_iterator;
            auto cbegin() const
                -> const_iterator;
            auto end()
                -> iterator;
            auto end() const
                -> const_iterator;
            auto cend() const
                -> const_iterator;

            auto rbegin()
                -> reverse_iterator;
            auto rbegin() const
                -> const_reverse_iterator;
            auto crbegin() const
                -> const_reverse_iterator;
            auto rend()
                -> reverse_iterator;
            auto rend() const
                -> const_reverse_iterator;
            auto crend() const
                -> const_reverse_iterator;

            // Modifiers

            /**
             * @brief Fills the Matrix with the given value
             * @param value Value to fill the Matrix with
             */
            auto fill(value_type value)
                -> void;

            /**
             * @brief Swap the Matrix contents with another Matrix's
             * @param other Matrix to swap contents with
             */
            auto swap(Matrix<T>&& other)
                -> void;


            ////////////////////////////////////////////////////////////
            // NumPy-like functions
            ////////////////////////////////////////////////////////////

            /**
             * @brief Checks whether all the element are true
             * @return true if all the elements evaluate to true
             */
            auto all() const
                -> bool;

            /**
             * @brief Checks whether there are non-zero elements
             * @return true if there is at least one non-zero element
             */
            auto any() const
                -> bool;

            /**
             * @brief Least element of the Matrix
             * @return Least element of the Matrix
             */
            auto min() const
                -> value_type;

            /**
             * @brief Greatest element of the Matrix
             * @return Greatest element of the Matrix
             */
            auto max() const
                -> value_type;

            /**
             * @brief Sum of all the elements
             * @return Sum of all the elements of the Matrix
             */
            auto sum() const
                -> value_type;

            /**
             * @brief Reshape the Matrix
             *
             * The number of elements in the Matrix must be the same
             * before and after the call of this function. Otherwise,
             * the program shall crash.
             *
             * @param height New height
             * @param width New width
             */
            auto reshape(size_type height, size_type width)
                -> void;

            /**
             * @brief Collapses the Matrix in one dimension
             *
             * All the elements are put in the same line. The
             * transformation is done in a row-major order.
             */
            auto flatten()
                -> void;

            ////////////////////////////////////////////////////////////
            // Miscellaneous functions
            ////////////////////////////////////////////////////////////

            // Capacity
            auto height() const
                -> size_type;
            auto width() const
                -> size_type;

            // Properties
            using super::is_square; // Solve ADL problem
            auto is_symmetric() const
                -> bool;
            auto is_invertible() const
                -> bool;

            // Other functions
            // Some of them could have been implemented
            // as free function (ex: determinant) but are
            // easier to implement as in-class functions
            auto determinant() const
                -> value_type;
            auto minor(size_type y, size_type x) const
                -> value_type;

            // Flat iterators
            auto fbegin()
                -> flat_iterator;
            auto fbegin() const
                -> const_flat_iterator;
            auto cfbegin() const
                -> const_flat_iterator;
            auto fend()
                -> flat_iterator;
            auto fend() const
                -> const_flat_iterator;
            auto cfend() const
                -> const_flat_iterator;

            auto rfbegin()
                -> reverse_flat_iterator;
            auto rfbegin() const
                -> const_reverse_flat_iterator;
            auto crfbegin() const
                -> const_reverse_flat_iterator;
            auto rfend()
                -> reverse_flat_iterator;
            auto rfend() const
                -> const_reverse_flat_iterator;
            auto crfend() const
                -> const_reverse_flat_iterator;

        private:

            // Member data
            size_type _height = 0;      /**< Number of rows */
            size_type _width  = 0;      /**< Number of columns */

            std::vector<T>      _data;  /**< Matrix data */
            std::vector<row>    _rows;  /**< Matrix rows */

        public:

            /**
             * @brief Matrix row
             *
             * To facilitate some operations such as iterating
             * through a Matrix or accessing the elements with
             * an array-like syntax, we must create this class.
             * The Matrix is an array of Matrix::row, which are
             * themselves arrays of data.
             */
            struct row
            {
                ////////////////////////////////////////////////////////////
                // Types
                ////////////////////////////////////////////////////////////
                using value_type = T;
                using size_type = std::size_t;
                using difference_type = std::ptrdiff_t;
                using reference = value_type&;
                using const_reference = const value_type&;
                using pointer = value_type*;
                using const_pointer = const value_type*;
                using iterator = value_type*;
                using const_iterator = const value_type*;
                using reverse_iterator = std::reverse_iterator<iterator>;
                using const_reverse_iterator = std::reverse_iterator<const_iterator>;

                ////////////////////////////////////////////////////////////
                // Constructors and destructor
                ////////////////////////////////////////////////////////////

                // Defaulted functions
                row()           = default;
                row(const row&) = default;
                row(row&&)      = default;
                ~row()          = default;

                // Initialization constructor
                row(size_type size, T* data_addr);

                ////////////////////////////////////////////////////////////
                // Operators
                ////////////////////////////////////////////////////////////

                auto operator[](size_type index)
                    -> reference;
                auto operator[](size_type index) const
                    -> const_reference;

                ////////////////////////////////////////////////////////////
                // Functions
                ////////////////////////////////////////////////////////////

                // Iterators
                auto begin()
                    -> iterator;
                auto begin() const
                    -> const_iterator;
                auto cbegin() const
                    -> const_iterator;
                auto end()
                    -> iterator;
                auto end() const
                    -> const_iterator;
                auto cend() const
                    -> const_iterator;

                auto rbegin()
                    -> reverse_iterator;
                auto rbegin() const
                    -> const_reverse_iterator;
                auto crbegin() const
                    -> const_reverse_iterator;
                auto rend()
                    -> reverse_iterator;
                auto rend() const
                    -> const_reverse_iterator;
                auto crend() const
                    -> const_reverse_iterator;

                // Capacity
                auto size() const
                    -> size_type;

                private:

                    size_type _size;    /**< Number of values */
                    T* _data;           /**< Beginning of the data */
            };
    };

    ////////////////////////////////////////////////////////////
    // Outside class operators
    ////////////////////////////////////////////////////////////

    // Matrix-Matrix comparison
    template<typename T>
    auto operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
        -> bool;
    template<typename T>
    auto operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
        -> bool;

    // Matrix-Matrix arithmetic operations
    template<typename T>
    auto operator+(Matrix<T> lhs, const Matrix<T>& rhs)
        -> Matrix<T>;
    template<typename T>
    auto operator-(Matrix<T> lhs, const Matrix<T>& rhs)
        -> Matrix<T>;
    template<typename T>
    auto operator*(Matrix<T> lhs, const Matrix<T>& rhs)
        -> Matrix<T>;
    template<typename T>
    auto operator/(Matrix<T> lhs, const Matrix<T>& rhs)
        -> Matrix<T>;

    // Matrix-value_type arithmetic operations
    template<typename T>
    auto operator*(Matrix<T> lhs, T rhs)
        -> Matrix<T>;
    template<typename T>
    auto operator*(T lhs, Matrix<T> rhs)
        -> Matrix<T>;
    template<typename T>
    auto operator/(Matrix<T> lhs, T rhs)
        -> Matrix<T>;

    // Streams handling
    template<typename T>
    auto operator<<(std::ostream& stream, const Matrix<T>& mat)
        -> std::ostream&;

    ////////////////////////////////////////////////////////////
    // Miscellaneous functions
    ////////////////////////////////////////////////////////////

    template<typename T>
    auto adjugate(const Matrix<T>& mat)
        -> Matrix<T>;
    template<typename T>
    auto cofactor(const Matrix<T> mat, std::pair<size_t, size_t> index)
        -> typename Matrix<T>::value_type;
    template<typename T>
    auto determinant(const Matrix<T>& mat)
        -> typename Matrix<T>::value_type;
    template<typename T>
    auto inverse(const Matrix<T>& mat)
        -> Matrix<T>;
    template<typename T>
    auto minor(const Matrix<T>& mat, std::pair<size_t, size_t> index)
        -> typename Matrix<T>::value_type;
    template<typename T>
    auto trace(const Matrix<T>& mat)
        -> typename Matrix<T>::value_type;
    template<typename T>
    auto transpose(const Matrix<T>& mat)
        -> Matrix<T>;

    #include "matrix.inl"
}

#endif // _POLDER_MATRIX_H
