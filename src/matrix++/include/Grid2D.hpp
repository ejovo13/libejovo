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
    using loop_fn = std::function<T(T)>;

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
     *!                           Indexing
     *========================================================================**/
    T& operator()(int i, int j); // 1-based indexing, don't check bounds
    T& at(int i, int j); // Check bounds
    const T& operator()(int i, int j) const;
    const T& at(int i, int j) const;

    std::pair<int, int> to_ij(int n, bool col_major = true) const; // Take a vector index
    int to_i(int i, int j, bool col_major = true) const; // Take a vector index

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

    /**========================================================================
     *!                           Looping functions
     *========================================================================**/
    Grid2D& loop_ij(loop_ij_fn fn);
    const Grid2D& loop_ij(loop_ij_fn fn) const;

    /**========================================================================
     *!                           Mutate Functions
     *========================================================================**/
    Grid2D& mut_row(loop_fn fn, int i = 1);
    Grid2D& mut_col(loop_fn fn, int j = 1);
    Grid2D& mut_diag(loop_fn fn, int d = 0);


private:

    bool col_major = true;







};

template <class T>
std::size_t Grid2D<T>::size() const {
    return this->ncol() * this->nrow();
}

// Translate vector index to 2-dimensional index
template <class T>
std::pair<int, int> Grid2D<T>::to_ij(int n, bool col_major) const {

    if (col_major) {

        int i = (n - 1) % this->nrow() + 1;
        int j = ((n  - 1) / this->nrow()) + 1;
        return std::make_pair<int, int>(std::move(i), std::move(j));


    } else {

        int i = ((n  - 1) / this->ncol()) + 1;
        int j = (n - 1) % this->ncol() + 1;
        return std::make_pair<int, int>(std::move(i), std::move(j));

    }
}

// take i,j coordinates and translate to vector coordinates
template <class T>
int Grid2D<T>::to_i(int i, int j, bool col_major) const {
    if (col_major) return 1 + (i - 1) + (j - 1) * this->nrow();
    else return 1 + (j - 1) + (i - 1) * this->ncol();
}

template <class T>
T& Grid2D<T>::at(int i, int j) {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
const T& Grid2D<T>::at(int i, int j) const {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
const T& Grid2D<T>::operator()(int i, int j) const {
    return this->operator[](this->to_i(i, j) - 1);
}

template <class T>
T& Grid2D<T>::operator()(int i, int j) {
    return this->operator[](this->to_i(i, j) - 1);
}

template <class T>
bool Grid2D<T>::are_valid_bounds(int i, int j) const {
    bool a = i >= 1 && i <= this->nrow();
    bool b = j >= 1 && i <= this->ncol();
    return a && b;
}

template <class T>
template <class U>
bool Grid2D<T>::is_same_shape(const Grid2D<U>& rhs) const {
    bool a = this->ncol() == rhs.ncol();
    bool b = this->nrow() == rhs.nrow();
    return a && b;
}

template <class T>
template <class U>
bool Grid2D<T>::isnt_same_shape(const Grid2D<U>& rhs) const {
    return !(this->is_same_shape(rhs));
}

template <class T>
template <class U>
bool Grid2D<T>::can_mult(const Grid2D<U> &rhs) const {
    return this->ncol() == this->nrow();
}

template <class T>
template <class U>
bool Grid2D<T>::cant_mult(const Grid2D<U> &rhs) const {
    return !(this->can_mult_b(rhs));
}

template <class T>
bool Grid2D<T>::is_square() const {
    return this->ncol() == this->nrow();
}

template <class T>
bool Grid2D<T>::is_col() const {
    return this->ncol() == 1;
}

template <class T>
bool Grid2D<T>::is_row() const {
    return this->nrow() == 1;
}

template <class T>
Grid2D<T>& Grid2D<T>::loop_ij(loop_ij_fn fn) {

    const auto m = this->nrow();
    const auto n = this->ncol();

    for (std::size_t i = 1; i <= m; i++) {
        for (std::size_t j = 1; j <= n; j++) {
            fn(i, j);
        }
    }

    return *this;
}

template <class T>
const Grid2D<T>& Grid2D<T>::loop_ij(loop_ij_fn fn) const {

    const auto m = this->nrow();
    const auto n = this->ncol();

    for (std::size_t i = 1; i <= m; i++) {
        for (std::size_t j = 1; j <= n; j++) {
            fn(i, j);
        }
    }

    return *this;
}

template <class T>
Grid2D<T>& Grid2D<T>::mut_col(loop_fn f, int j) {

    const auto m = this->nrow();

    for (std::size_t i = 1; i <= m; i++) {
        this->operator()(i, j) = f(this->operator()(i, j));
    }
}

template <class T>
Grid2D<T>& Grid2D<T>::mut_row(loop_fn f, int i) {

    const auto n = this->ncol();

    for (std::size_t j = 1; j <= n; j++) {
        this->operator()(i, j) = f(this->operator()(i, j));
    }
}





};
