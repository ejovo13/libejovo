#pragma once

#include "ejovo.hpp"
#include "matrix.hpp"

template <class T>
class Matrix<T>::RowView : public AbsView {

public:

    int i = 0;
    int jb = 0;
    int je = 0;

    Matrix& matrix() const override;
    std::string to_string() const override;

    int nrows() const override;
    int ncols() const override;

    T& operator()(int i) const override;
    T& operator()(int i, int j) const override;
    // T& at(int i) override;
    // T& at(int i, int j) override;

    RowView& assign(const T&, std::function<void(T&, const T&)>);
    RowView& assign(const Matrix&, std::function<void(T&, const T&)>);
    RowView& assign(const RowView&, std::function<void(T&, const T&)>);

    RowView& operator=(const T&);
    RowView& operator=(const Matrix&);
    RowView& operator=(const RowView&);

    RowView(Matrix& mat, int i);
    RowView(Matrix& mat, int i, int jb);
    RowView(Matrix& mat, int i, int jb, int je);
    RowView(RowView&& rv);

private:

    Matrix& mat = Matrix::null();

};

/**========================================================================
 *!                           RowView
 *========================================================================**/
template <class T>
Matrix<T>::RowView::RowView(Matrix& mat, int i)
    : i{i}
    , jb{1}
    , je{mat.n}
    , mat{mat}
{};

template <class T>
Matrix<T>::RowView::RowView(Matrix& mat, int i, int jb)
    : i{i}
    , jb{jb}
    , je{mat.n}
    , mat{mat}
{};

template <class T>
Matrix<T>::RowView::RowView(Matrix& mat, int i, int jb, int je)
    : i{i}
    , jb{jb}
    , je{je}
    , mat{mat}
{};

// This might not be sharing the same reference to the matrix...
template <class T>
Matrix<T>::RowView::RowView(RowView&& rv)
    : i{rv.i}
    , jb{rv.jb}
    , je{rv.je}
    , mat{mat}
{};
// deconstruct rv??

template <class T>
// template <class U>
typename Matrix<T>::RowView& Matrix<T>::RowView::assign(const T& scalar, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), scalar);
    });
    return *this;
}

template <class T>
typename Matrix<T>::RowView& Matrix<T>::RowView::operator=(const T& val) {
    return this->assign(val, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::RowView& Matrix<T>::RowView::assign(const Matrix<T>& mat, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::RowView& Matrix<T>::RowView::operator=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::RowView& Matrix<T>::RowView::assign(const RowView& rv, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), rv(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::RowView& Matrix<T>::RowView::operator=(const RowView& rv) {
    return this->assign(rv, ejovo::id_eq<T, T>);
}








template <class T>
std::string Matrix<T>::RowView::to_string() const {
    return "RowView";
}

template <class T>
int Matrix<T>::RowView::nrows() const {
    return 1;
}

template <class T>
int Matrix<T>::RowView::ncols() const {
    return je - jb + 1;
}

template <class T>
T& Matrix<T>::RowView::operator()(int n) const {
    return this->mat(this->i, this->jb + n - 1);
}

template <class T>
T& Matrix<T>::RowView::operator()(int i, int j) const {
    return this->mat(this->i, this->jb + j - 1);
}

template <class T>
Matrix<T>& Matrix<T>::RowView::matrix() const {
    return this->mat;
}

