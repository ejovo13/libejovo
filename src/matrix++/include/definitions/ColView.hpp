#pragma once

#include "declarations/ColView.hpp"

namespace ejovo {

/**========================================================================
 *!                           ColView
 *========================================================================**/
template <class T>
Matrix<T>::ColView::ColView(Matrix& mat, int j)
    : j{j}
    , ib{1}
    , ie{mat.m}
    , mat{mat}
{};

template <class T>
Matrix<T>::ColView::ColView(Matrix& mat, int j, int ib)
    : j{j}
    , ib{ib}
    , ie{mat.n}
    , mat{mat}
{};

template <class T>
Matrix<T>::ColView::ColView(Matrix& mat, int j, int ib, int ie)
    : j{j}
    , ib{ib}
    , ie{ie}
    , mat{mat}
{};

template <class T>
Matrix<T>::ColView::ColView(ColView&& cv)
    : j{cv.j}
    , ib{cv.ib}
    , ie{cv.ie}
    , mat{cv.mat}
{};

template <class T>
std::string Matrix<T>::ColView::to_string() const {
    return "ColView";
}

template <class T>
int Matrix<T>::ColView::nrows() const {
    return ie - ib + 1;
}

template <class T>
int Matrix<T>::ColView::ncols() const {
    return 1;
}

template <class T>
T& Matrix<T>::ColView::operator()(int n) const {
    return this->mat(ib + n - 1, j);
}

template <class T>
T& Matrix<T>::ColView::operator()(int i, int j) const {
    return this->mat(this->ib + i - 1, this->j);
}


// template <class T>
// T& Matrix<T>::ColView::at(int n) {
//     // throw error if we are out of bounds
//     if (!this->valid_bounds(n)) {
//         std::cerr << "Bound: " << n << " out of bounds " << this->size() << "\n";
//         throw "Out of bounds accessing";
//     }
//     return this->operator()(n);
// }

// template <class T>
// T& Matrix<T>::ColView::at(int i, int j) {
//     // throw error if we are out of bounds
//     if (!this->valid_bounds(i, j)) {
//         std::cerr << "Bounds: (" << i << ", " << j << "), out of bounds nrows: " << this->nrows() << " ncol: " << this->ncols() << "\n";
//         throw "Out of bounds accessing";
//     }

//     return this->operator()(i, j);
// }

template <class T>
Matrix<T>& Matrix<T>::ColView::matrix() const {
    return this->mat;
}

template <class T>
// template <class U>
typename Matrix<T>::ColView& Matrix<T>::ColView::assign(const T& scalar, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), scalar);
    });
    return *this;
}

template <class T>
typename Matrix<T>::ColView& Matrix<T>::ColView::operator=(const T& val) {
    return this->assign(val, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::ColView& Matrix<T>::ColView::assign(const Matrix<T>& mat, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::ColView& Matrix<T>::ColView::operator=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::ColView& Matrix<T>::ColView::assign(const ColView& rv, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), rv(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::ColView& Matrix<T>::ColView::operator=(const ColView& rv) {
    return this->assign(rv, ejovo::id_eq<T, T>);
}

};