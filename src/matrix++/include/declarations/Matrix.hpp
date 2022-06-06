#pragma once

#include <memory>
#include <functional>
#include <initializer_list>
#include <vector>

// #include <iostream>
#include <cstring>
// #include <cmath>
// #include <string>

#include "ejovo/rng/Xoshiro.hpp"
#include "Grid1D.hpp"
#include "Grid2D.hpp"


namespace ejovo {

// Forward declaration of the vector class so that we can create some simple conversion
// functions
// template <class T> class Vector;

template <class T = double>
class Matrix : public Grid2D<T> {

public:

    /**============================================
     *!               Fields
     *=============================================**/
    std::size_t m;
    std::size_t n;
    // static ejovo::rng::Xoshiro& xoroshiro;
    std::unique_ptr<T[]> data;

    /**============================================
     *!    Grid1D Pure Virtual Functions
     *=============================================**/
    T& operator[](int i) override;
    const T& operator[](int i) const override;

    /**============================================
     *!     Grid2D Pure Virtual Functions
     *=============================================**/
    std::size_t ncol() const override;
    std::size_t nrow() const override;

    /**============================================
     *!               Using Overloads
     *=============================================**/
    using ejovo::Grid1D<T>::at;
    using ejovo::Grid1D<T>::operator();
    using ejovo::Grid2D<T>::at;
    using ejovo::Grid2D<T>::operator();
    using ejovo::Grid1D<T>::sum;

    /**============================================
     *!               Constructors
     *=============================================**/
    Matrix();
    Matrix(int m); // create a column vector
    Matrix(int m, int n);
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);

    Matrix(const Vector<T>& rhs); // Go ahead and copy the data
    Matrix(Vector<T>&& rhs); // Simply transfer the data

    // Matrix(std::initializer_list<T> list);
    // Matrix<const

    /**========================================================================
     *!                           From functions
     *========================================================================**/


    /**----------------------
     *!    operators
     *------------------------**/
    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs);

    // call memcpy to copy the data
    std::unique_ptr<T[]> copyData() const;

    const Matrix& print() const;
    const Matrix& summary() const;
    // void fill(T val);
    void reset(); // set data to nullptr, m and n to 0.

    /**========================================================================
     *!                           Transformations
     *========================================================================**/
    // create a new matrix whose data is a copy
    Matrix as_vector() const; // return a copy of this data in column form
    Matrix as_colvec() const; // just a call to as_vector
    Matrix as_rowvec() const;

    bool can_add_b(const Matrix &rhs) const;
    bool cant_add_b(const Matrix &rhs) const;

    Matrix& reshape(std::tuple<int, int> ind);
    Matrix& reshape(Matrix& ind);
    Matrix& reshape(int i, int j);

    // void to_vector(); // Computing the size of the matrix, change the elements so that the matrix is a col vector;
    // void to_rowvec();
    Matrix& reshape_row();
    Matrix& reshape_col();
    Matrix& reshape_vec();

    std::vector<T> to_vector();
    template <class U>
    static Matrix from(const std::vector<U>& vec, bool by_row = false);

    Matrix& nullify();

    // interpret the indices as INTEGERS and
    Matrix operator()(const Matrix<int>& ind);



    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    // Take the dot product as if we were VECTORS
    // T dot(const Matrix& rhs) const;
    using ejovo::Grid1D<T>::dot;
    T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    Matrix kronecker_product(const Matrix& rhs) const;

    //* Matrix Moperators
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator%=(const Matrix& rhs); // hadamard multiplication

    //* Matrix + scalar
    Matrix& operator+=(const T scalar);
    Matrix& operator-=(const T scalar);
    Matrix& operator/=(const T scalar);
    Matrix& operator*=(const T scalar);


    Matrix operator-() const;
    Matrix operator*(const Matrix& rhs) const;
    // using Grid
    // Matrix dot(const Matrix& rhs) const;
    Matrix operator^(int k) const;

    friend Matrix operator+(Matrix lhs, const Matrix rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Matrix operator+(Matrix lhs, const T scalar) {
        lhs += scalar;
        return lhs;
    }

    friend Matrix operator+(const T scalar, Matrix rhs) {
        rhs += scalar;
        return rhs;
    }

    // these values are passed in by  copy
    friend Matrix operator-(Matrix lhs, const Matrix rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Matrix operator-(Matrix lhs, const T scalar) {
        lhs -= scalar;
        return lhs;
    }

    friend Matrix operator-(const T scalar, Matrix rhs) {
        rhs -= scalar;
        return rhs;
    }

    friend Matrix operator*(const T scalar, Matrix rhs) {
        rhs *= scalar;
        return rhs;
    }

    friend Matrix operator*(Matrix lhs, const T scalar) {
        lhs *= scalar;
        return lhs;
    }

    friend Matrix operator%(Matrix lhs, const Matrix rhs) {
        lhs %= rhs;
        return lhs;
    }

    friend Matrix operator/(const T scalar, Matrix rhs) {
        rhs.loop_i([&] (int i) {
            return rhs(i) = scalar * (1 / rhs(i));
        });
        return rhs;
    }

    friend Matrix operator/(Matrix lhs, const T scalar) {
        lhs /= scalar;
        return lhs;
    }

    // matrix transpose
    Matrix t() const;
    Matrix transpose() const;

    // Matrix multiplication

    /**========================================================================
     *!                   Functions to extract columns and rows
     *========================================================================**/
    Matrix get_row(int i) const;
    Matrix get_col(int j) const;

    /**========================================================================
     *!                           Decompositions!!
     *========================================================================**/
    std::tuple<Matrix, Matrix> lu() const;


    /**========================================================================
     *!                           Inquiry functions
     *========================================================================**/
    bool is_null() const;
    bool is_diagonally_dominant() const;

    /**========================================================================
     *!                           Static functions
     *========================================================================**/
    static Matrix<T> zeros(int m);
    static Matrix<T> zeros(int m, int n);
    static Matrix<T> zeros(const Matrix& mat);
    static Matrix<T> ones(int m);
    static Matrix<T> ones(int m, int n);
    static Matrix<T> ij(int n);
    static Matrix<T> ij(int m, int n);
    static Matrix<T> i(int n); // like ij but elements are i
    static Matrix<T> i(int m, int n);
    static Matrix<T> id(int n);
    static Matrix<T> id(int m, int n);
    static Matrix<T> val(int n, T val);
    static Matrix<T> val(int m, int n, T val);

    static Matrix<T> hilbert(int n);
    static Matrix<T> hilbert(int m, int n);

    static Matrix<T> diagonal(Matrix& vals);

    static Matrix<T> null();
    static Matrix<T> row(int n); // Create a new zeros row vector
    static Matrix<T> row(int n, T val);
    static Matrix<T> col(int n); // Create a new zeros col vector
    static Matrix<T> col(int n, T val);
    static Matrix<T> from(std::initializer_list<T>, bool by_row = false);
    static Matrix<T> from(std::initializer_list<T>, int m, int n, bool by_row = false);


    /**========================================================================
     *!                     Matrices with random elements
     *========================================================================**/
    static Matrix<T> rand();
    static Matrix<T> rand(int n, double min = 0, double max = 20);
    static Matrix<T> rand(int m, int n);
    static Matrix<T> rand(int m, int n, double min, double max);
    // static Matrix<T> randi();


    // static Matrix<T> householder
    // static Matrix<T> vec(int n);

    /**========================================================================
     *!                           Matrix interface to ejovo functions
     *========================================================================**/

    Matrix accumulate(std::function<T(const T&, const T&)> bin_op, T init = 0) const;
    Matrix accumulate(std::function<T(const T&, const T&, int)> ter_op, T init = 0) const;
    Matrix cumsum() const;
    Matrix cumavg() const;
    Matrix cummin() const;
    Matrix cummax() const;


    // Matrix map(std::function<T(T)> f) const; // returns a Matrix that's the same size as this
    using ejovo::Grid1D<T>::map;
    template <class U> Matrix<U> map(std::function<U(T)> f) const;

    // Apply a function if the predicate of an ELEMENT is true
    // Matrix map_if(std::function<T(T)> f, std::function<bool(T)> predicate) const;


    // Matrix filter(std::function<bool(T)> predicate) const; // returns a VECTOR!!!!!!!

    // Matrix filter_lt(T val) const;
    // Matrix filter_leq(T val) const;
    // Matrix filter_gt(T val) const;
    // Matrix filter_geq(T val) const;


    Matrix clone() const;

    Matrix to_matrix() const override {
        return this->clone();
    }

    Matrix new_matrix(int __m, int __n) const {
        return this->zeros(__m, __n);
    }

    Matrix new_matrix(int __n) const {
        return this->zeros(1, __n);
    }



    /**========================================================================
     *!                           Logical indexing type functions
     *========================================================================**/
    // Let's start off with indexing with a SINGLE vector.
    // Matrix operator()(const Matrix<int>& ind) const;
    Matrix<bool> binop_k(std::function<bool(T, T)> binop, const T& k) const;

    Matrix<bool> operator<(const T& rhs) const;
    Matrix<bool> operator<=(const T& rhs) const;
    Matrix<bool> operator>(const T& rhs) const;
    Matrix<bool> operator>=(const T& rhs) const;
    // Matrix<bool> operator==(const T& rhs) const;




    // test a condition, returning a logical matrix
    Matrix<bool> test(std::function<bool(T)> pred) const;

    Matrix<int> which(const Matrix<bool>& mask) const;

    /**========================================================================
     *!                           Matrix<bool> functions
     *========================================================================**/
    Matrix<bool> operator!() const;
    Matrix<bool> where(std::function<bool(T)> pred) const; // return a mask where the condition is true
    Matrix<int> which() const; // return a vector of vector indices
    Matrix<int> which(std::function<bool(T)> pred) const;

    template <class U> U sum() const; // Allow a bool Matrix to call Matrix<bool>::sum<int>() -> int


    // class BoolView;
    // class ConstBoolView;

    class AbsView;
    class RowView;
    class ColView;
    class VecView; // 1 Dimensional view indexed by a single array of vector indices
    class MatView;

    VecView operator()(const Matrix<bool>& mask);
    VecView operator[](const Matrix<bool>& mask);
    // ConstBoolView operator()(const Matrix<bool>& mask) const;

    MatView view_row(int i);
    MatView view_col(int j);

    VecView vecview(const Matrix<bool>& mask);
    VecView vecview(const Matrix<int>& ind);
    VecView vecview(std::function<bool(T)> pred);
    RowView get_row_view(int i);
    RowView get_row_view(int i, int jb);
    RowView get_row_view(int i, int jb, int je);
    ColView get_col_view(int j);
    ColView get_col_view(int j, int ib);
    ColView get_col_view(int j, int ib, int ie);

    // View<T> operator()(const Matrix<int>& row_ind) const;
    MatView operator()(const Matrix<int>& row_ind, const Matrix<int>& col_ind);
    MatView operator()(const Matrix<int>& row_ind, int j);
    MatView operator()(int i, const Matrix<int>& col_ind);

    MatView submat(int ib, int ie, int jb, int je);
    MatView submat(std::initializer_list<int>, std::initializer_list<int>);
    MatView submat(const Matrix<int>& row_ind, const Matrix<int>& col_ind);
    MatView submat(std::initializer_list<int>, const Matrix<int>& col_ind);
    MatView submat(const Matrix<int>& col_ind, std::initializer_list<int>);
    // MatView submat(int i, std::initializer_list<int>);
    // MatView submat(std::initializer_list<int>, int j);

    // submat chooses A(ib:ie, jb:je) whereas block chooses A(i:i+m, j:j+n)
    MatView block(int i, int j, int m, int n);

    // MatView rows_from(const Matrix<int>& col_ind, int j)

    MatView rows(int ib, int ie);
    MatView rows(int i);
    MatView rows(std::initializer_list<int> list, int from = 1);
    MatView cols(int jb, int je);
    MatView cols(int j);
    MatView cols(std::initializer_list<int> list);

    /**========================================================================
     *!                           Crazy Concepts Stuff
     *========================================================================**/

};


};