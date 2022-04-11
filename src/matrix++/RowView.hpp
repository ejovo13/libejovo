#pragma once

#include "ejovo.hpp"
#include "matrix.hpp"

template <class T>
class Matrix<T>::RowView : public AbsView {

public:

    int i;
    int jb;
    int je;

    Matrix& matrix() const override;
    std::string to_string() const override;

    int nrows() const override;
    int ncols() const override;

    T& operator()(int i) const override;
    T& operator()(int i, int j) const override;
    // T& at(int i) override;
    // T& at(int i, int j) override;

    RowView(Matrix& mat, int i);
    RowView(Matrix& mat, int i, int jb);
    RowView(Matrix& mat, int i, int jb, int je);

private:

    Matrix& mat;

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


// template <class T>
// T& Matrix<T>::RowView::at(int n) {
//     // throw error if we are out of bounds
//     if (!this->valid_bounds(n)) {
//         std::cerr << "Bound: " << n << " out of bounds " << this->size() << "\n";
//         throw "Out of bounds accessing";
//     }
//     return this->operator()(n);
// }

// template <class T>
// T& Matrix<T>::RowView::at(int i, int j) {
//     // throw error if we are out of bounds
//     if (!this->valid_bounds(i, j)) {
//         std::cerr << "Bounds: (" << i << ", " << j << "), out of bounds nrows: " << this->nrows() << " ncol: " << this->ncols() << "\n";
//         throw "Out of bounds accessing";
//     }

//     return this->operator()(i, j);
// }

template <class T>
Matrix<T>& Matrix<T>::RowView::matrix() const {
    return this->mat;
}

