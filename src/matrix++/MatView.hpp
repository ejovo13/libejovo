#pragma once

#include "ejovo.hpp"
#include "matrix.hpp"
#include "matrix_impl.hpp"
#include "AbsView.hpp"

template <class T>
class Matrix<T>::MatView : public AbsView {

    // A view can be ENTIRELY represented with row and column indices!!!!!

public:

    Matrix<int> row_ind;
    Matrix<int> col_ind;

    // View();
    MatView(Matrix& mat);
    MatView(Matrix& mat, const Matrix<int> row_ind, const Matrix<int> col_ind);

    MatView(MatView&);
    MatView(MatView&&);

    int nrows() const override;
    int ncols() const override;
    std::string to_string() const override;
    Matrix& matrix() const override;
    T& operator()(int n) const override;
    T& operator()(int i, int j) const override;

    MatView& operator=(MatView&);
    MatView& operator=(MatView&&);
    // template <class U>
    // MatView& operator=(const Matrix<T>& x) {
    //     return this->assign(x, ejovo::id_eq<T, T>);
    // }


private:

    Matrix<T>& mat;

};

template <class T>
Matrix<T>::MatView::MatView(Matrix& mat)
    : mat{mat}
    , row_ind{ejovo::seq(mat.m)}
    , col_ind{ejovo::seq(mat.n)}
{};

template <class T>
Matrix<T>::MatView::MatView(Matrix& mat, const Matrix<int> row_ind, const Matrix<int> col_ind)
    : mat{mat}
    , row_ind{row_ind}
    , col_ind{col_ind}
{};

template <class T>
Matrix<T>::MatView::MatView(typename Matrix<T>::MatView& view)
    // : mat{view.mat}
    : row_ind{view.row_ind}
    , col_ind{view.col_ind}
{
    mat = view.mat; // point to the same place, but dont copy?
};

template <class T>
Matrix<T>::MatView::MatView(typename Matrix<T>::MatView&& view)
    : mat{view.mat}
    , row_ind{view.row_ind}
    , col_ind{view.col_ind}
{};

template <class T>
int Matrix<T>::MatView::nrows() const {
    return row_ind.size();
}

template <class T>
int Matrix<T>::MatView::ncols() const {
    return col_ind.size();
}

template <class T>
std::string Matrix<T>::MatView::to_string() const {
    return "MatView";
}

template <class T>
Matrix<T>& Matrix<T>::MatView::matrix() const {
    return mat;
}

template <class T>
T& Matrix<T>::MatView::operator()(int i, int j) const {
    return mat(row_ind(i), col_ind(j));
}

template <class T>
T& Matrix<T>::MatView::operator()(int n) const {
    std::pair<int, int> pair = this->ind_to_ij(n);
    return mat(row_ind(std::get<0>(pair), std::get<1>(pair)));
}

template <class T>
typename Matrix<T>::MatView& Matrix<T>::MatView::operator=(MatView& view) {
    this->assign(view, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::MatView& Matrix<T>::MatView::operator=(MatView&& view) {
    this->assign(view, ejovo::id_eq<T, T>);
}