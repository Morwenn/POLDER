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
#ifndef _POLDER_MATRIX_H
#define _POLDER_MATRIX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <POLDER/config.h>
#include <POLDER/exceptions.h>


namespace polder
{


/**
 * @brief Matrix implementation
 *
 * A Matrix is a two dimensions array of data.
 * It can be accessed as an array of arrays but
 * has some particulerities described below.
 */
class POLDER_API Matrix
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors and destructors
        ////////////////////////////////////////////////////////////

        // Default constructor
        constexpr Matrix();
        // Copy constructor
        Matrix(const Matrix& other);
        // Move constructor
        Matrix(Matrix&& other) noexcept;
        // Initializer list constructors
        Matrix(const std::initializer_list<double>& values);
        Matrix(const std::initializer_list<const std::initializer_list<double>>& values);
        // Constructors with size
        Matrix(size_t w);
        Matrix(size_t h, size_t w);

        // Destructor
        ~Matrix();


        /**
         * @brief Matrix line
         *
         * To facilite some operations such as iterating
         * through a Matrix or accessing the elements with
         * an array-like syntax, we must create this class.
         * The Matrix is an array of Matrix::line, which are
         * themselves arrays of data.
         */
        class line
        {
            public:

                // Return the line size
                size_t size() const;

                ////////////////////////////////////////////////////////////
                // Matrix::line operators
                ////////////////////////////////////////////////////////////

                // Accessors
                double& operator[](size_t index);
                const double& operator[](size_t index) const;

                ////////////////////////////////////////////////////////////
                // Matrix::line iterators
                ////////////////////////////////////////////////////////////

                typedef double* iterator;
                typedef const double* const_iterator;

                class reverse_iterator
                {
                    public:

                        double& operator*() const;
                        reverse_iterator operator++();
                        reverse_iterator operator++(int);
                        reverse_iterator operator--();
                        reverse_iterator operator--(int);
                        bool operator==(const reverse_iterator& other) const;
                        bool operator!=(const reverse_iterator& other) const;

                    private:

                        reverse_iterator(double* val);
                        double* _value;

                    friend class line;
                };

                class const_reverse_iterator
                {
                    public:

                        double operator*() const;
                        const_reverse_iterator operator++();
                        const_reverse_iterator operator++(int);
                        const_reverse_iterator operator--();
                        const_reverse_iterator operator--(int);
                        bool operator==(const const_reverse_iterator& other) const;
                        bool operator!=(const const_reverse_iterator& other) const;

                    private:

                        const_reverse_iterator(double* val);
                        double* _value;

                    friend class line;
                };


                // Iterators-related functions
                iterator begin();
                const_iterator begin() const;
                const_iterator cbegin() const;
                iterator end();
                const_iterator end() const;
                const_iterator cend() const;

                reverse_iterator rbegin();
                const_reverse_iterator rbegin() const;
                const_reverse_iterator crbegin() const;
                reverse_iterator rend();
                const_reverse_iterator rend() const;
                const_reverse_iterator crend() const;


            private:

                ////////////////////////////////////////////////////////////
                // Constructors
                ////////////////////////////////////////////////////////////

                // The class can not copied
                line(const line&) = delete;

                // Default constructor
                line();
                // Initialisation constructor
                line(size_t width, double* data_addr);

                ////////////////////////////////////////////////////////////
                // Operators
                ////////////////////////////////////////////////////////////

                // Assignement
                line& operator=(const line& other);
                line& operator=(line&& other);

                size_t _size;   /**< Number of doubles */
                double* _data;  /**< Beginning of the data */

            friend class Matrix;
        };


        ////////////////////////////////////////////////////////////
        // Matrix iterators
        ////////////////////////////////////////////////////////////

        typedef line* iterator;
        typedef const line* const_iterator;

        class reverse_iterator
        {
            public:

                // Iterator arithmetics
                line& operator*();
                line* operator->();
                reverse_iterator operator++();
                reverse_iterator operator++(int);
                reverse_iterator operator--();
                reverse_iterator operator--(int);
                bool operator==(const reverse_iterator& other) const;
                bool operator!=(const reverse_iterator& other) const;

            private:

                reverse_iterator(line* val);
                line* _value;

            friend class Matrix;
        };

        class const_reverse_iterator
        {
            public:

                // Iterator arithmetics
                const line& operator*();
                const line* operator->();
                const_reverse_iterator operator++();
                const_reverse_iterator operator++(int);
                const_reverse_iterator operator--();
                const_reverse_iterator operator--(int);
                bool operator==(const const_reverse_iterator& other) const;
                bool operator!=(const const_reverse_iterator& other) const;

            private:

                const_reverse_iterator(const line* val);
                const line* _value;

            friend class Matrix;
        };


        ////////////////////////////////////////////////////////////
        // Matrix flat iterators
        ////////////////////////////////////////////////////////////

        /**
         * @brief Flat iterators
         *
         * A flat iterator is an iterator that allows to iterate
         * through the Matrix not as an array of arrays but as
         * a one-line only array of data. It can be useful in some
         * cases such as when we want to check whether an element
         * exists in the Matrix or not.
         */
        typedef double* flat_iterator;

        /**
         * @brief Constant flat iterators
         * @see flat_iterator
         */
        typedef const double* const_flat_iterator;

        /**
         * @brief Reversed flat iterators
         * @see flat_iterator
         */
        class reverse_flat_iterator
        {
            public:

                // Iterator arithmetics
                double& operator*();
                reverse_flat_iterator operator++();
                reverse_flat_iterator operator++(int);
                reverse_flat_iterator operator--();
                reverse_flat_iterator operator--(int);
                bool operator==(const reverse_flat_iterator& other) const;
                bool operator!=(const reverse_flat_iterator& other) const;

            private:

                reverse_flat_iterator(double* val);
                double* _value;

            friend class Matrix;
        };

        /**
         * @brief Constant reversed flat iterators
         * @see flat_iterator
         */
        class const_reverse_flat_iterator
        {
            public:

                // Iterator arithmetics
                const double& operator*();
                const_reverse_flat_iterator operator++();
                const_reverse_flat_iterator operator++(int);
                const_reverse_flat_iterator operator--();
                const_reverse_flat_iterator operator--(int);
                bool operator==(const const_reverse_flat_iterator& other) const;
                bool operator!=(const const_reverse_flat_iterator& other) const;

            private:

                const_reverse_flat_iterator(const double* val);
                const double* _value;

            friend class Matrix;
        };


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessor operators
        line& operator[](size_t index);
        const line& operator[](size_t index) const;
        double& operator()(size_t h, size_t w);
        const double& operator()(size_t h, size_t w) const;

        // Assignement operator
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;

        // Matrix-Matrix operations
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        Matrix& operator/=(const Matrix& other);

        // Matrix-Matrix logic operations
        bool operator&&(const Matrix& other);
        bool operator||(const Matrix& other);

        // Matrix-Matrix comparison
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        // Matrix-double operations
        Matrix& operator+=(double d);
        Matrix& operator-=(double d);
        Matrix& operator*=(double d);
        Matrix& operator/=(double d);
        Matrix& operator%=(int d);

        const Matrix operator+(double other) const;
        const Matrix operator-(double other) const;
        const Matrix operator*(double other) const;
        const Matrix operator/(double other) const;
        const Matrix operator%(int other) const;

        const Matrix operator==(double other) const;
        const Matrix operator!=(double other) const;
        const Matrix operator>(double other) const;
        const Matrix operator<(double other) const;
        const Matrix operator>=(double other) const;
        const Matrix operator<=(double other) const;

        // Stream gestion
        friend std::ostream& operator<<(std::ostream& stream, const Matrix& M);


        ////////////////////////////////////////////////////////////
        // STL-like functions
        ////////////////////////////////////////////////////////////

        // Accessors
        double& at(size_t h, size_t w);
        const double& at(size_t h, size_t w) const;
        double& front();
        const double& front() const;
        double& back();
        const double& back() const;

        // Iterators
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        const_reverse_iterator crend() const;

        // Capacity
        size_t size() const;

        // Modifiers

        /**
         * @brief Fills the Matrix with the given value
         * @param value Value to fill the Matrix with
         */
        void fill(double value);

        /**
         * @brief Swap the Matrix contents with another Matrix's
         * @param other Matrix to swap contents with
         */
        void swap(Matrix&& other);


        ////////////////////////////////////////////////////////////
        // NumPy-like functions
        ////////////////////////////////////////////////////////////

        // Functions
        bool any() const;
        bool all() const;
        double min() const;
        double max() const;
        double sum() const;
        double mean() const;
        double trace() const;
        Matrix diagonal() const;

        // Procedures
        void reshape(size_t h, size_t w);
        void flatten();

        // To be consistant towards NumPy
        inline double det() const
        {
            return determinant();
        }


        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        size_t width() const;
        size_t height() const;

        bool is_square() const;
        bool is_symmetric() const;
        bool is_invertible() const;

        bool exists(double d) const;
        size_t count(double d) const;
        double minor(size_t h, size_t w) const;
        double cofactor(size_t h, size_t w) const;
        double determinant() const;

        // Flat iterators
        // Used to iterate over the Matrix as a 1D array of doubles
        flat_iterator fbegin();
        const_flat_iterator fbegin() const;
        const_flat_iterator cfbegin() const;
        flat_iterator fend();
        const_flat_iterator fend() const;
        const_flat_iterator cfend() const;

        reverse_flat_iterator rfbegin();
        const_reverse_flat_iterator rfbegin() const;
        const_reverse_flat_iterator crfbegin() const;
        reverse_flat_iterator rfend();
        const_reverse_flat_iterator rfend() const;
        const_reverse_flat_iterator crfend() const;


    private:

        // Member data
        size_t _height; /**< Number of rows */
        size_t _width;  /**< Number of columns */
        size_t _size;   /**< height * width */

        double* _data;  /**< Matrix data */
        line* _lines;   /**< Matrix lines */
};

// Output streams gestion
std::ostream& operator<<(std::ostream& stream, const Matrix& M);

// Matrix-Matrix operations
const Matrix operator+(const Matrix& m, const Matrix& n);
const Matrix operator+(const Matrix& m, Matrix&& n);
const Matrix operator+(Matrix&& m, const Matrix& n);
const Matrix operator+(Matrix&& m, Matrix&& n);
const Matrix operator-(const Matrix& m, const Matrix& n);
const Matrix operator-(const Matrix& m, Matrix&& n);
const Matrix operator-(Matrix&& m, const Matrix& n);
const Matrix operator-(Matrix&& m, Matrix&& n);
const Matrix operator*(const Matrix& m, const Matrix& n);
const Matrix operator*(const Matrix& m, Matrix&& n);
const Matrix operator*(Matrix&& m, const Matrix& n);
const Matrix operator*(Matrix&& m, Matrix&& n);
const Matrix operator/(const Matrix& m, const Matrix& n);
const Matrix operator/(const Matrix& m, Matrix&& n);
const Matrix operator/(Matrix&& m, const Matrix& n);
const Matrix operator/(Matrix&& m, Matrix&& n);


////////////////////////////////////////////////////////////
// Outside class functions
////////////////////////////////////////////////////////////

/**
 * @namespace polder::matrix
 * @brief Matrix-related functions
 *
 * This namespace contains all the functions in
 * POLDER library that are related to Matrix but
 * which are not in the Matrix class themselves,
 * such as special Matrix constructors.
 */
namespace matrix
{

    ////////////////////////////////////////////////////////////
    // NumPy-like functions
    ////////////////////////////////////////////////////////////

    // Matrix creation from nothing

    /**
     * @brief Constructs a line Matrix filled with zeros
     * @param width Number of cells in the line
     * @return New zeros-filled line Matrix
     */
    POLDER_API Matrix zeros(size_t width);

    POLDER_API Matrix zeros(size_t height, size_t width);
    POLDER_API Matrix ones(size_t width);
    POLDER_API Matrix ones(size_t height, size_t width);
    POLDER_API Matrix identity(size_t n);
    POLDER_API Matrix eye(size_t x, size_t y=0, int k=0);
    POLDER_API Matrix range(int end);
    POLDER_API Matrix range(int begin, int end, int step=0);

    // Matrix creation from other matrix
    POLDER_API Matrix transpose(const Matrix& M);
    POLDER_API Matrix zeros_like(const Matrix& M);
    POLDER_API Matrix ones_like(const Matrix& M);
    POLDER_API Matrix reshape(const Matrix& M, size_t x, size_t y);
    POLDER_API Matrix diag(const Matrix& M);
    POLDER_API Matrix upper_triangle(const Matrix& M);
    POLDER_API Matrix lower_triangle(const Matrix& M);
    POLDER_API Matrix adjugate(const Matrix& M);
    POLDER_API Matrix inverse(const Matrix& M);
    POLDER_API Matrix where(Matrix expr, double yes, double no);


    ////////////////////////////////////////////////////////////
    // Miscellaneous functions
    ////////////////////////////////////////////////////////////

    // Output functions (deprecated)
    POLDER_API void print_matrix(const Matrix& M);
    POLDER_API void fprint_matrix(FILE* f, const Matrix& M);


} // namespace matrix

} // namespace polder


#endif
