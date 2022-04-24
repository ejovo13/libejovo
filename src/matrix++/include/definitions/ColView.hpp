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
std::size_t Matrix<T>::ColView::nrow() const {
    return ie - ib + 1;
}

template <class T>
std::size_t Matrix<T>::ColView::ncol() const {
    return 1;
}

template <class T>
T& Matrix<T>::ColView::operator[](int i) {
    // ColView[0]'s location is A(ib, j)
    // ColView[1] = A(ib + 1, j)
    return mat(ib + i, j);
}

template <class T>
T& Matrix<T>::ColView::operator[](int i) const {
    return mat(ib + i, j);
}

template <class T>
Matrix<T>& Matrix<T>::ColView::matrix() const {
    return mat;
}

template <class T>
typename Matrix<T>::ColView& Matrix<T>::ColView::operator=(const ColView& rv) {
    this->assign(rv, ejovo::id_eq<T, T>);
    return *this;
}

};