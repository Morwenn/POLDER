////////////////////////////////////////////////////////////
///
/// POLDER Matrix - POLDER library dealing with matrix
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_MATRIX_H
#define _POLDER_MATRIX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <ostream>
#include "math.h"


namespace polder
{

////////////////////////////////////////////////////////////
// Matrix definition
////////////////////////////////////////////////////////////

class Matrix
{
    public:

        ////////////////////////////////////////////////////////////
        /// Constructors and destructors
        ///
        ////////////////////////////////////////////////////////////

        // Default constructor
        Matrix();
        // Copy constructor
        Matrix(const Matrix& other);
        // Move constructor
        Matrix(Matrix&& other);
        // Initializer list constructors
        Matrix(const std::initializer_list<double>& values);
        Matrix(const std::initializer_list<const std::initializer_list<double>>& values);
        // Constructors with size
        Matrix(size_t x);
        Matrix(size_t x, size_t y);

        // Destructor
        ~Matrix();


        ////////////////////////////////////////////////////////////
        /// Matrix iterators
        ///
        ////////////////////////////////////////////////////////////

        // Iterator
        class iterator
        {
            public:

                // Iterator arithmetics
                double& operator*() const;
                void operator++();
                void operator++(int);
                void operator--();
                void operator--(int);
                bool operator==(iterator other) const;
                bool operator!=(iterator other) const;

            private:

                iterator(double* val);
                double* _value;
                friend class Matrix;
        };

        // Reverse iterator
        class reverse_iterator
        {
            public:

                // Iterator arithmetics
                double& operator*() const;
                void operator++();
                void operator++(int);
                void operator--();
                void operator--(int);
                bool operator==(reverse_iterator other) const;
                bool operator!=(reverse_iterator other) const;

            private:

                reverse_iterator(double* val);
                double* _value;
                friend class Matrix;
        };


        ////////////////////////////////////////////////////////////
        /// Operators
        ///
        ////////////////////////////////////////////////////////////

        // Accessor operators
        const double* operator[](size_t index) const;
        double* operator[](size_t index);
        double operator()(size_t x, size_t y) const;
        double& operator()(size_t x, size_t y);

        // Assignement operator
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other);

        // Matrix-Matrix operations
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        Matrix& operator/=(const Matrix& other);

        const Matrix operator+(const Matrix& other) const;
        const Matrix operator-(const Matrix& other) const;
        const Matrix operator*(const Matrix& other) const;
        const Matrix operator/(const Matrix& other) const;

        // Matrix-Matrix logic operations
        bool operator&&(const Matrix& other);
        bool operator||(const Matrix& other);

        // Matrix-Matrix comparison
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        // Matrix-double operations
        Matrix& operator+=(const double d);
        Matrix& operator-=(const double d);
        Matrix& operator*=(const double d);
        Matrix& operator/=(const double d);
        Matrix& operator%=(const int d);

        const Matrix operator+(const double& other) const;
        const Matrix operator-(const double& other) const;
        const Matrix operator*(const double& other) const;
        const Matrix operator/(const double& other) const;
        const Matrix operator%(const int& other) const;

        const Matrix operator==(const double& other) const;
        const Matrix operator!=(const double& other) const;
        const Matrix operator>(const double& other) const;
        const Matrix operator<(const double& other) const;
        const Matrix operator>=(const double& other) const;
        const Matrix operator<=(const double& other) const;

        // Stream gestion
        friend std::ostream& operator<<(std::ostream& stream, const Matrix& M);


        ////////////////////////////////////////////////////////////
        /// STL-like functions
        ///
        ////////////////////////////////////////////////////////////

        // Accessors
        double& at(size_t x, size_t y);
        const double& at(size_t x, size_t y) const;
        double& front();
        const double& front() const;
        double& back();
        const double& back() const;

        // Iterators
        iterator begin() const;
        iterator end() const;
        reverse_iterator rbegin() const;
        reverse_iterator rend() const;

        // Capacity
        size_t size() const;

        // Modifiers
        void fill(double value);
        void swap(Matrix& other);


        ////////////////////////////////////////////////////////////
        /// Miscellaneous functions
        ///
        ////////////////////////////////////////////////////////////

        size_t width() const;
        size_t height() const;
        bool is_square() const;
        bool is_symmetric() const;
        bool is_invertible() const;
        bool any() const;
        bool all() const;
        bool exists(double d) const;
        double min() const;
        double max() const;
        double sum() const;
        double mean() const;
        double trace() const;
        size_t count(double d) const;
        double determinant() const;

        void flatten();
        void reshape(size_t x, size_t y);


    private:

        // Member data
        size_t _height; // Number of rows
        size_t _width;  // Number of columns
        size_t _size;   // height * width

        double* _data;  // Matrix data
};

// Output streams gestion
std::ostream& operator<<(std::ostream& stream, const Matrix& M);



////////////////////////////////////////////////////////////
// Outside class functions
////////////////////////////////////////////////////////////

namespace matrix
{

    // Matrix creation from nothing
    Matrix zeros(size_t x);
    Matrix zeros(size_t x, size_t y);
    Matrix ones(size_t x);
    Matrix ones(size_t x, size_t y);
    Matrix identity(size_t n);
    Matrix eye(size_t x, size_t y=0, int k=0);
    Matrix range(int end);
    Matrix range(int beginning, int end, int step=0);

    // Matrix creation from other matrix
    Matrix transpose(const Matrix& M);
    Matrix zeros_like(const Matrix& M);
    Matrix ones_like(const Matrix& M);
    Matrix reshape(const Matrix& M, size_t x, size_t y);
    Matrix diag(const Matrix& M);
    Matrix upper_triangle(const Matrix& M);
    Matrix lower_triangle(const Matrix& M);
    Matrix adjugate(const Matrix& M);
    Matrix inverse(const Matrix& M);
    Matrix where(const Matrix& expr, double yes, double no);

    // Output functions
    void print_matrix(const Matrix& M);
    void fprint_matrix(FILE* f, const Matrix& M);

} // namespace matrix

} // namespace polder


#endif
