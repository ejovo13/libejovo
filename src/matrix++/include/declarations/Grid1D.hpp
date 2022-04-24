#pragma once

#include <iostream>
#include <functional>
#include <cmath>
#include <cstddef>

// Abstract class to implement the common behavior that is associated with a 1 dimensional vector
namespace ejovo {

    template <class T> T abs(T x) {
        return x < 0 ? -x : x;
    }

    double log_base(double base, double x) {
        return (::std::log(x) / ::std::log(base));
    }

    double kthRoot(double n, int k) {
        return ::std::pow(k, (1.0 / k) * (log_base(k, n)));
    }


};



namespace ejovo {

template <class T> class Matrix; // Forward declaration to Return Matrix type
template <class T> class Vector;

template <class T>
class Grid1D {

public:

    using predicate = std::function<bool(T)>;
    using binary_op = std::function<T(T, T)>;
    using unary_op = std::function<T(const T&)>;
    using loop_fn = std::function<void(T&)>; // Used to succinctly modify the elements that are being accessed
    using loop_fn_const = std::function<void(const T&)>;
    using loop_ind_fn = std::function<void(int)>;
    // using index_op = std::function<T(int)>;

    // virtual Grid1D clone() = 0;

    /**========================================================================
     *!                           Virtual Functions
     *========================================================================**/
    virtual T& operator[](int i) = 0; // 0-based indexing
    const virtual T& operator[](int i) const = 0;
    virtual std::size_t size() const = 0;

    /**========================================================================
     *!                      Virtual Concept Functions
     *========================================================================**/
    virtual Matrix<T> to_matrix()  const = 0;
    // virtual Matrix<T> new_matrix(int n) const = 0;


    T& at(int i);         // 1-based indexing with bounds checking
    T& operator()(int i); // 1-based indexing M(1) is the first element
    const T& at(int i) const; // at actually goes ahead and verifies whether or not the bounds are legit
    const T& operator()(int i) const;

    /**========================================================================
     *!                           First, Last
     *========================================================================**/
    T& first();
    T& last();
    const T& first() const;
    const T& last() const;


    /**========================================================================
     *!                           Inquiry Functions
     *========================================================================**/
    template <class U> bool is_same_size(const Grid1D<U>& rhs) const;
    template <class U> bool isnt_same_size(const Grid1D<U>& rhs) const;
    bool is_valid_bound(int i) const; // Check if i is a valid 1-based indexing bound.

    /**========================================================================
     *!                           Assignment Overloading
     *========================================================================**/
    Grid1D& operator=(const Grid1D& rhs);

    bool operator==(const Grid1D& rhs);

    /**========================================================================
     *!                           Mutating functions
     *========================================================================**/
    Grid1D& fill(const T& value);
    Grid1D& fill_if(const T& value, predicate pred);
    Grid1D& mutate(unary_op f);
    Grid1D& mutate_if(unary_op f, predicate pred);

    /**========================================================================
     *!                           Looping Functions
     *========================================================================**/
    Grid1D& loop(loop_fn f);
    Grid1D& loop_i(loop_ind_fn f);
    Grid1D& swap(int ai, int bi);

    const Grid1D& loop(loop_fn_const f) const;
    const Grid1D& loop_i(loop_ind_fn f) const;

    /**========================================================================
     *!                           Printing Functions
     *========================================================================**/
    Grid1D& print();
    // Grid1D& print_lin();

    const Grid1D& print() const;
    // const Grid1D& print_lin() const;

    /**========================================================================
     *!                           Statistical Routines
     *========================================================================**/
    T reduce(binary_op f, T init = 0) const;
    T sum() const;
    T sum_abs() const;
    T prod() const;
    T mean() const;
    T min() const;
    T max() const;
    T sd(bool population = true) const;
    T var(bool population = true) const;
    T pnorm(int p = 2) const;
    T norm() const;

    /**========================================================================
     *!                           Boolean Functions
     *========================================================================**/
    // template <class U> U sum() const; // Allow a Grid1D<bool> to return an integer for the sum.
    int count() const; // Count the elements of Grid1D<T> that evaluate to true in a boolean expression
    int count(predicate pred) const; // Count number of elements where pred is true
    bool any() const;
    bool any(predicate pred) const;
    bool all() const;
    bool all(predicate pred) const;
    bool none() const;
    bool none(predicate pred) const;

    /**========================================================================
     *!                Functional Programming Concrete Return Types
     *========================================================================**/
    Matrix<T> map(unary_op fn) const;
    // virtual template<class U> Matrix<U> map(std::function<U(T)> fn);
    Matrix<T> map_if(unary_op fn, predicate pred) const;
    Matrix<T> filter(predicate pred) const;
    Matrix<T> diff() const; // outputs a row vector of differences
    Matrix<T> midpoints() const; // return the midpoints of adjacent elements
    Matrix<T> abs() const;

    /**========================================================================
     *!                           Power Operations
     *========================================================================**/
    Matrix<T> sqrt() const;
    Matrix<T> cbrt() const;
    Matrix<T> nth_root() const;

    Matrix<T> pow(int k) const;
    Matrix<T> sqrd() const;
    Matrix<T> cubd() const;

    Matrix<T> normalized(int p = 2) const;
    Grid1D& normalize(int p = 2);

    /**========================================================================
     *!                           Repeat Operations
     *========================================================================**/
    Matrix<T> repcol(int n) const;
    Matrix<T> reprow(int n) const;

    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    T dot(const Grid1D& rhs) const;
    // T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    T inner_product(const Grid1D& rhs) const;
    Matrix<T> outer_product(const Grid1D& rhs) const; // must be two vectors...
    // Matrix kronecker_product(const Matrix& rhs) const;
    Matrix<T> hadamard_product(const Grid1D& rhs) const; // element wise multiplication

    // /**========================================================================
    //  *!                           Runif Functions
    //  *========================================================================**/
    // Vector<T>

    Matrix<T> zeros(bool col = true) const;
    Matrix<T> zeros(int n, bool col = true) const;



};




};
