#pragma once

#include <memory>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <functional>
#include <initializer_list>

template <class T>
class View;

template <class T>
class ConstView;

template <class T = double>
class Matrix {

    public:

    int m;
    int n;

    std::unique_ptr<T[]> data;

    //======= constructors
    Matrix();
    Matrix(int m); // create a column vector
    Matrix(int m, int n);
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);
    // Matrix(std::initializer_list<T> list);

    /**========================================================================
     *!                           From functions
     *========================================================================**/
    // Matrix from


    /**----------------------
     *!    operators
     *------------------------**/
    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs);

    // call memcpy to copy the data
    std::unique_ptr<T[]> copyData() const;

    int size() const;
    void print() const;
    void fill(T val);
    void reset(); // set data to nullptr, m and n to 0.

    /**========================================================================
     *!                           Transformations
     *========================================================================**/
    // create a new matrix whose data is a copy
    Matrix as_vector(); // return a copy of this data in column form
    Matrix as_colvec(); // just a call to as_vector
    Matrix as_rowvec();

    bool isSameSize(const Matrix &rhs) const;
    bool canMultB(const Matrix &rhs) const;
    bool cantMultB(const Matrix &rhs) const;
    bool canAddB(const Matrix &rhs) const;
    bool cantAddB(const Matrix &rhs) const;

    Matrix& reshape(std::tuple<int, int> ind);
    Matrix& reshape(Matrix& ind);
    Matrix& reshape(int i, int j);

    // void to_vector(); // Computing the size of the matrix, change the elements so that the matrix is a col vector;
    // void to_rowvec();
    Matrix& to_col();
    Matrix& to_vec();
    Matrix& to_row();
    Matrix& to_null();




    View<T> view_row(int i);
    View<T> view_col(int j);

    ConstView<T> view_row(int i) const;
    ConstView<T> view_col(int j) const;

    Matrix& nullify();

    Matrix diff() const; // return the back elements minus the front elements
    Matrix abs() const;


    T& operator()(int i);
    const T& operator()(int i) const;
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;

    T& at(int i);
    T& at(int i, int j);
    const T& at(int i) const;
    const T& at(int i, int j) const;

    // interpret the indices as INTEGERS and
    Matrix operator()(const Matrix<int> ind);

    T& operator[](int i);
    const T& operator[](int i) const;

    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    // Take the dot product as if we were VECTORS
    T dot(const Matrix& rhs) const;
    T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    T inner_product(const Matrix& rhs) const;
    Matrix outer_product(const Matrix& rhs) const; // must be two vectors...
    Matrix kronecker_product(const Matrix& rhs) const;
    Matrix hadamard_product(const Matrix& rhs) const; // element wise multiplication


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
     *!                           Inquiry functions
     *========================================================================**/
    bool is_square() const;
    bool is_vector() const; // return true if one of the dimensions are 1
    bool is_colvec() const;
    bool is_rowvec() const;
    bool is_null() const;

    int mindim() const;

    /**========================================================================
     *!                           Static functions
     *========================================================================**/
    static Matrix<T> zeros(int m);
    static Matrix<T> zeros(int m, int n);
    static Matrix<T> ones(int m);
    static Matrix<T> ones(int m, int n);
    static Matrix<T> ij(int n);
    static Matrix<T> ij(int m, int n);
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
    // static Matrix<T> vec(int n);

    /**========================================================================
     *!                           Matrix interface to ejovo functions
     *========================================================================**/
    // Loop mutators based on the element, (i), or (i, j);
    Matrix& loop(std::function<T(T)> f); // f: T -> T thus this function is assumed to be SETTING ELEMENTS!!!! Call f and set this->to the results
    Matrix& loop_i(std::function<T(int)> f);
    Matrix& loop_ij(std::function<T(int, int)> f);

    const Matrix& loop(std::function<void(T)> f) const;
    const Matrix& loop_i(std::function<void(int)> f) const; // f: T -> void thus this function can really do whatever the f we want. Call f without overwriting this, looping over the elements as if this were a vector
    const Matrix& loop_ij(std::function<void(int, int)> f) const; // Do something with (i, j)





    // void loop_if(std::function<bool(T)> predicate); // f: T -> Bool thus this function is a predicate!!



    Matrix map(std::function<T(T)> f) const; // returns a Matrix that's the same size as this

    // Apply a function if the predicate of an ELEMENT is true
    Matrix map_if(std::function<T(T)> f, std::function<bool(T)> predicate) const;


    Matrix filter(std::function<bool(T)> predicate) const; // returns a VECTOR!!!!!!!

    Matrix filter_lt(T val) const;
    Matrix filter_leq(T val) const;
    Matrix filter_gt(T val) const;
    Matrix filter_geq(T val) const;


    Matrix& mutate(std::function<T(T)> f); // Mutating in place, not const
    Matrix& mutate_if(std::function<T(T)> f, std::function<bool(T)> predicate);

    Matrix& fill_if(T val, std::function<bool(T)> predicate);

    T reduce(std::function<T(T, T)> f, T init = 0) const;
    T sum() const;
    T mean() const;
    T prod() const;
    T min() const;
    T max() const;
    T sd(bool population = true) const; // default to the population sd
    T var(bool population = true) const;

    Matrix sqrt() const;
    Matrix cbrt() const;
    Matrix kth_root() const;

    Matrix pow(int k) const;
    Matrix sqrd() const;

    T pnorm(int p) const;
    T norm() const;

    Matrix clone() const;

    // repeat columns. Sends a vector v to [v ... v_n]
    Matrix rep_col(int n) const;
    Matrix rep_row(int n) const;


    /**========================================================================
     *!                           Logical indexing type functions
     *========================================================================**/
    // Let's start off with indexing with a SINGLE vector.
    Matrix operator()(const Matrix<int>& ind) const;


    // View<T> operator()(const Matrix<int>& row_ind) const;
    View<T> operator()(const Matrix<int>& row_ind, const Matrix<int>& col_ind);
    View<T> operator()(const Matrix<int>& row_ind, int j);
    View<T> operator()(int i, const Matrix<int>& col_ind);

    // test a condition, returning a logical matrix
    Matrix<bool> test(std::function<bool(T)> pred) const;





};


/**========================================================================
 *!                           Looping functions
 *========================================================================**/
// loop elements i, j and set i, j according to what f(i, j) returns
template <class T, class BinaryFn>
void loop_ij(Matrix<T>& A, BinaryFn f) {
    for (int i = 1; i <= A.m; i++) {
        for (int j = 1; j <= A.n; j++) {
            f(i, j);
        }
    }
}

template <class T, class UnaryFn>
void loop_i(Matrix<T>& A, UnaryFn f) {
    for (int i = 1; i <= A.size(); i++) {
        f(i);
    }
}

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
template <class T, class UnaryFn>
void mut_col(Matrix<T>& A, UnaryFn f, int j = 1) {
    for (int i = 1; i <= A.m; i++) {
        A(i, j) = f(A(i, j));
    }
}

template <class T, class UnaryFn>
void mut_row(Matrix<T>& A, UnaryFn f, int i = 1) {
    for (int j = 1; j <= A.n; j++) {
        A(i, j) = f(A(i, j));
    }
}

template <class T, class UnaryFn>
void mut_diag(Matrix<T>& A, UnaryFn f, int diag = 0) {
    for (int d = 1 + diag; d <= A.mindim(); d++) {
        A(d, d) = f(A(d, d));
    }
}

