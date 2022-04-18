#pragma once

#include <memory>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <functional>
#include <initializer_list>
#include <string>

#include "Xoshiro.hpp"
#include "Grid1D.hpp"
#include "Grid2D.hpp"

// template <class T>
// class View;

// template <class T>
// class ConstView;

ejovo::rng::Xoshiro g_XOSHIRO {};


template <class T = double>
class Matrix : public ejovo::Grid2D<T> {

public:

    /**============================================
     *!               Fields
     *=============================================**/
    std::size_t m;
    std::size_t n;
    static ejovo::rng::Xoshiro& xoroshiro;
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
    // Matrix(std::initializer_list<T> list);

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
    const Matrix& print_lin() const;
    // void fill(T val);
    void reset(); // set data to nullptr, m and n to 0.

    /**========================================================================
     *!                           Transformations
     *========================================================================**/
    // create a new matrix whose data is a copy
    Matrix as_vector(); // return a copy of this data in column form
    Matrix as_colvec(); // just a call to as_vector
    Matrix as_rowvec();

    // template <class U> bool is_same_size(const Matrix<U> &rhs) const;
    // template <class U> bool isnt_same_size(const Matrix<U> &rhs) const;
    // template <class U> bool is_same_shape(const Matrix<U> &rhs) const;
    // template <class U> bool isnt_same_shape(const Matrix<U> &rhs) const;
    // bool can_mult_b(const Matrix &rhs) const;
    // bool cant_mult_b(const Matrix &rhs) const;
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
    static Matrix from(const std::vector<U>& vec);

    // Matrix& to_null();

    // ConstView<T> view_row(int i) const;
    // ConstView<T> view_col(int j) const;

    Matrix& nullify();

    // Matrix diff() const; // return the back elements minus the front elements
    // Matrix abs() const;




    // interpret the indices as INTEGERS and
    Matrix operator()(const Matrix<int>& ind);



    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    // Take the dot product as if we were VECTORS
    // T dot(const Matrix& rhs) const;
    using ejovo::Grid1D<T>::dot;
    T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    // T inner_product(const Matrix& rhs) const;
    // Matrix outer_product(const Matrix& rhs) const; // must be two vectors...
    Matrix kronecker_product(const Matrix& rhs) const;
    // Matrix hadamard_product(const Matrix& rhs) const; // element wise multiplication


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

    // friend Matrix operator+(const T scalar )

    // Matrix& operator-=(const Matrix& rhs);

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


    // fried Matrix operator-(Mat)



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
    // bool is_square() const;
    // bool is_vector() const; // return true if one of the dimensions are 1
    // bool is_colvec() const;
    // bool is_rowvec() const;
    bool is_null() const;
    bool is_diagonally_dominant() const;

    // int mindim() const;

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
    static Matrix<T> from(std::initializer_list<T>);
    static Matrix<T> from(std::initializer_list<T>, int m, int n);


    /**========================================================================
     *!                     Matrices with random elements
     *========================================================================**/
    static Matrix<T> rand();
    static Matrix<T> rand(int n, double min = 0, double max = 20);
    static Matrix<T> rand(int m, int n);
    static Matrix<T> rand(int m, int n, double min, double max);
    // static Matrix<T> randi();

    // static Matrix<T> runif(int n, double a = 0, double b = 1);




    // static Matrix<T> householder
    // static Matrix<T> vec(int n);

    /**========================================================================
     *!                           Matrix interface to ejovo functions
     *========================================================================**/
    // Loop mutators based on the element, (i), or (i, j);
    // Matrix& loop(std::function<T(T)> f); // f: T -> T thus this function is assumed to be SETTING ELEMENTS!!!! Call f and set this->to the results
    // Matrix& loop_i(std::function<T(int)> f);
    // Matrix& loop_ij(std::function<T(int, int)> f);

    // const Matrix& loop(std::function<void(T)> f) const;
    // const Matrix& loop_i(std::function<void(int)> f) const; // f: T -> void thus this function can really do whatever the f we want. Call f without overwriting this, looping over the elements as if this were a vector
    // const Matrix& loop_ij(std::function<void(int, int)> f) const; // Do something with (i, j)

    // Swap the vector elements M(ai) and M(bi)
    Matrix& swap(int ai, int bi);



    // void loop_if(std::function<bool(T)> predicate); // f: T -> Bool thus this function is a predicate!!

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

    Matrix filter_lt(T val) const;
    Matrix filter_leq(T val) const;
    Matrix filter_gt(T val) const;
    Matrix filter_geq(T val) const;


    // Matrix& mutate(std::function<T(T)> f); // Mutating in place, not const
    // Matrix& mutate_if(std::function<T(T)> f, std::function<bool(T)> predicate);

    // Matrix& fill_if(T val, std::function<bool(T)> predicate);

    // T reduce(std::function<T(T, T)> f, T init = 0) const;
    // T sum() const;
    // T sum_abs() const;
    // T mean() const;
    // T prod() const;
    // T min() const;
    // T max() const;
    // T sd(bool population = true) const; // default to the population sd
    // T var(bool population = true) const;

    // Matrix sqrt() const;
    // Matrix cbrt() const;
    // Matrix kth_root() const;

    // Matrix pow(int k) const;
    // Matrix sqrd() const;

    // // T pnorm(int p) const;
    // // T norm() const;

    // Matrix normalized() const;
    // Matrix& normalize();


    Matrix clone() const;

    Matrix to_matrix() const override {
        return this->clone();
    }

    Matrix new_matrix(int __m, int __n) const {
        return this->zeros(__m, __n);
    }

    Matrix new_matrix(int __n) const override {
        return this->zeros(1, __n);
    }


    // repeat columns. Sends a vector v to [v ... v_n]
    // Matrix rep_col(int n) const;
    // Matrix rep_row(int n) const;


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
    // int count() const; // Count the elements of Matrix<T> that evaluate to true in a boolean expression
    // int count(std::function<bool(T)> pred) const;

    // bool any() const;
    // bool any(std::function<bool(T)> pred) const;

    // bool all() const;
    // bool all(std::function<bool(T)> pred) const;



    class BoolView;
    class ConstBoolView;





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
    ColView get_col_view(int j);

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

// Definition of the BoolView class

template <class T>
class Matrix<T>::BoolView {

public:

    Matrix<int> true_ind;

    int m;
    int n;

    BoolView(Matrix<T>& mat);
    BoolView(Matrix<T>& mat, const Matrix<bool> mask);
    BoolView(Matrix<T>& mat, const Matrix<int> true_ind); // vector indices

    BoolView& loop_i(std::function<void(int)> f);

    T& operator()(int i);
    T& at(int i);

    BoolView& operator=(T val);
    // BoolView& operator=(const Matrix<T>& mat);


private:

    Matrix<T>& mat;




};


/**========================================================================
 *!                           Looping functions
 *========================================================================**/
// loop elements i, j and set i, j according to what f(i, j) returns
// template <class T, class BinaryFn>
// void loop_ij(Matrix<T>& A, BinaryFn f) {
//     for (int i = 1; i <= A.m; i++) {
//         for (int j = 1; j <= A.n; j++) {
//             f(i, j);
//         }
//     }
// }

// template <class T, class UnaryFn>
// void loop_i(Matrix<T>& A, UnaryFn f) {
//     for (int i = 1; i <= A.size(); i++) {
//         f(i);
//     }
// }

//! THIS IS NOT THE PROPER BEHAVIOR of the diagonal!!!
template <class T, class UnaryFn>
void loop_diag(Matrix<T>& A, UnaryFn f, int diag = 0) {
    for (int d = 1 + diag; d <= A.mindim(); d++) {
        f(d);
    }
}

template <class T, class BinaryFn>
void loop_row(Matrix<T>& A, BinaryFn f, int i = 1) {
    for (int j = 1; j <= A.n; j++) {
        f(i, j);
    }
}

// loop through i, j of a given row. Use mutate_col if you want to
// set the contents of a row given a UnaryFn that operates on those elements
template <class T, class BinaryFn>
void loop_col(Matrix<T>& A, BinaryFn f, int j = 1) {
    for (int i = 1; i <= A.m; i++) {
        f(i, j);
    }
}

//! WARNING These anonymous functions MUST RETURN T
// template <class T, class UnaryFn>
// void mut_col(Matrix<T>& A, UnaryFn f, int j = 1) {
//     for (int i = 1; i <= A.m; i++) {
//         A(i, j) = f(A(i, j));
//     }
// }

// template <class T, class UnaryFn>
// void mut_row(Matrix<T>& A, UnaryFn f, int i = 1) {
//     for (int j = 1; j <= A.n; j++) {
//         A(i, j) = f(A(i, j));
//     }
// }

template <class T, class UnaryFn>
void mut_diag(Matrix<T>& A, UnaryFn f, int diag = 0) {
    for (int d = 1 + diag; d <= A.mindim(); d++) {
        A(d, d) = f(A(d, d));
    }
}

// template <class T>
// std::pair<int, int> convert_vector_indices_to_ij(const Matrix<T>& mat, int n) {
//     int i = ((n  - 1) / mat.n) + 1;
//     int j = (n - 1) % mat.n + 1;
//     return std::make_pair<int, int>(std::move(i), std::move(j));
// }
