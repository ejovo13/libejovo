#pragma once

#include "declarations/Grid2D.hpp"

namespace ejovo {

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

// template <class T>
// Matrix<T> Grid2D<T>::new_matrix(int m, int n) {
    // return Matrix<T>::zero
// }

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
T& Grid2D<T>::at_row_major(int i) {
    auto pair = to_ij(i, false);
    return this->operator()(std::get<0>(pair), std::get<1>(pair));
}

template <class T>
T& Grid2D<T>::at_col_major(int i) {
    auto pair = to_ij(i, true);
    return this->operator()(std::get<0>(pair), std::get<1>(pair));
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
    return this->ncol() == rhs.nrow();
}

template <class T>
template <class U>
bool Grid2D<T>::cant_mult(const Grid2D<U> &rhs) const {
    return !(this->can_mult(rhs));
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
Grid2D<T>& Grid2D<T>::loop_diag(loop_fn f) {

    auto lim_dim = this->mindim();

    for (std::size_t d = 1; d <= lim_dim; d++) {
        f(this->operator()(d, d));
    };

    return *this;
}

template <class T>
const Grid2D<T>& Grid2D<T>::loop_diag(loop_fn f) const {

    auto lim_dim = this->mindim();

    for (std::size_t d = 1; d <= lim_dim; d++) {
        f(this->operator()(d, d));
    };

    return *this;
}

template <class T>
Grid2D<T>& Grid2D<T>::mut_col(mutate_fn f, int j) {

    const auto m = this->nrow();

    for (std::size_t i = 1; i <= m; i++) {
        this->operator()(i, j) = f(this->operator()(i, j));
    }
}

template <class T>
Grid2D<T>& Grid2D<T>::mut_row(mutate_fn f, int i) {

    const auto n = this->ncol();

    for (std::size_t j = 1; j <= n; j++) {
        this->operator()(i, j) = f(this->operator()(i, j));
    }
}

template <class T>
std::size_t Grid2D<T>::mindim() const {
    return this->nrow() < this->ncol() ? this->nrow() : this->ncol();
}

template <class T>
Matrix<T> Grid2D<T>::zeros() const {
    return Matrix<T>::zeros(this->nrow(), this->ncol());
}

};