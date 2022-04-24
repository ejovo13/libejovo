#pragma once

#include "declarations/AbsView.hpp"

namespace ejovo {

template <class T>
Matrix<T>::MatView::MatView(Matrix& mat)
    : mat{mat}
    , row_ind(ejovo::seq<int>(mat.m))
    , col_ind(ejovo::seq<int>(mat.n))
{};

template <class T>
Matrix<T>::MatView::MatView(Matrix& mat, const Matrix<int> row_ind, const Matrix<int> col_ind)
    : mat{mat}
    , row_ind{row_ind}
    , col_ind{col_ind}
{};

template <class T>
Matrix<T>::MatView::MatView(typename Matrix<T>::MatView& view)
    : mat{view.mat}
    , row_ind{view.row_ind}
    , col_ind{view.col_ind}
{
    // mat = view.mat; // point to the same place, but dont copy?
};

template <class T>
Matrix<T>::MatView::MatView(typename Matrix<T>::MatView&& view)
    : mat{view.mat}
    , row_ind{view.row_ind}
    , col_ind{view.col_ind}
{};

template <class T>
std::size_t Matrix<T>::MatView::nrow() const {
    return row_ind.size();
}

template <class T>
std::size_t Matrix<T>::MatView::ncol() const {
    return col_ind.size();
}

template <class T>
std::string Matrix<T>::MatView::to_string() const {
    return "MatView";
}

template <class T>
T& Matrix<T>::MatView::operator[](int n) const {
    const auto& [i, j] = this->to_ij(n, true);
    return this->matrix()(row_ind(i), col_ind(j));
}

template <class T>
T& Matrix<T>::MatView::operator[](int n) {
    const auto& [i, j] = this->to_ij(n, true);
    return this->matrix()(row_ind(i), col_ind(j));
}

template <class T>
Matrix<T>& Matrix<T>::MatView::matrix() const {
    return mat;
}

template <class T>
typename Matrix<T>::MatView& Matrix<T>::MatView::operator=(const MatView& rv) {
    this->assign(rv, ejovo::id_eq<T, T>);
    return *this;
}

};