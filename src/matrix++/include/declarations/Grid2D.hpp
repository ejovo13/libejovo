#pragma once

#include "Grid1D.hpp"
#include <utility>

namespace ejovo {

template <class T>
class Grid2D : public ejovo::Grid1D<T> {

public:

    using ejovo::Grid1D<T>::predicate;
    using ejovo::Grid1D<T>::binary_op;
    using ejovo::Grid1D<T>::unary_op;
    // using ejovo::Grid1D<T>::loop_fn;
    using ejovo::Grid1D<T>::loop_fn_const;
    using ejovo::Grid1D<T>::loop_ind_fn;
    using loop_ij_fn = std::function<void(int, int)>;
    using loop_fn = std::function<void(T&)>;
    using mutate_fn = std::function<void(T)>;

    using ejovo::Grid1D<T>::at;
    using ejovo::Grid1D<T>::operator();

    /**========================================================================
     *!                           Virtual functions
     *========================================================================**/
    virtual std::size_t ncol() const = 0;
    virtual std::size_t nrow() const = 0;

    /**========================================================================
     *!                           Grid1D Overrides
     *========================================================================**/
    virtual std::size_t size() const override;

    /**========================================================================
     *!                           Grid1D Extensions
     *========================================================================**/
    // using ejovo::Grid1D<T>::new_matrix;
    // Matrix<T> new_matrix(int m, int n);


    /**========================================================================
     *!                           Indexing
     *========================================================================**/
    T& operator()(int i, int j); // 1-based indexing, don't check bounds
    T& at(int i, int j); // Check bounds
    const T& operator()(int i, int j) const;
    const T& at(int i, int j) const;

    T& at_row_major(int i);
    T& at_col_major(int i);


    virtual std::pair<int, int> to_ij(int n, bool col_major = true) const; // Take a vector index
    virtual int to_i(int i, int j, bool col_major = true) const; // Take a vector index

    /**========================================================================
     *!                           Inquiry Functions
     *========================================================================**/
    bool are_valid_bounds(int i, int j) const;
    template <class U> bool is_same_shape(const Grid2D<U>& rhs) const;
    template <class U> bool isnt_same_shape(const Grid2D<U>& rhs) const;
    template <class U> bool can_mult(const Grid2D<U> &rhs) const;
    template <class U> bool cant_mult(const Grid2D<U> &rhs) const;

    bool is_square() const;
    bool is_col() const; // Check if ncol == 1
    bool is_row() const; // check if nrow == 1
    bool is_vec() const; // Return true if ncol == 1 or nrow == 1
    std::size_t mindim() const;

    /**========================================================================
     *!                           Looping functions
     *========================================================================**/
    Grid2D& loop_ij(loop_ij_fn fn);

    const Grid2D& loop_ij(loop_ij_fn fn) const;

    Grid2D& loop_diag(loop_fn fn);
    const Grid2D& loop_diag(loop_fn fn) const;

    /**========================================================================
     *!                           Mutate Functions
     *========================================================================**/
    Grid2D& mut_row(mutate_fn fn, int i = 1);
    Grid2D& mut_col(mutate_fn fn, int j = 1);
    Grid2D& mut_diag(mutate_fn fn, int d = 0);

    Matrix<T> zeros() const;
    Matrix<T> zeros(int m, int n) const;


private:

    bool col_major = true;

};

};
