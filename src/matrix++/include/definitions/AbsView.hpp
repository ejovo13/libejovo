#pragma once

#include "declarations/AbsView.hpp"

namespace ejovo {

template <class T>
std::pair<int, int> Matrix<T>::AbsView::ind_to_ij(int n) const {
    int i = ((n  - 1) / this->nrow()) + 1;
    int j = (n - 1) % this->nrow() + 1;
    return std::make_pair<int, int>(std::move(i), std::move(j));
}

// template <class T>
// std::pair<int, int> convert_vector_indices_to_ij(const typename Matrix<T>::AbsView& mat, int n) {
//     int i = ((n  - 1) / mat.nrow()) + 1;
//     int j = (n - 1) % mat.nrow() + 1;
//     return std::make_pair<int, int>(std::move(i), std::move(j));
// }


/**========================================================================
 *!                           Abstract View
 *========================================================================**/
// template <class T>
// int Matrix<T>::AbsView::size() {
//     return this->ncol() * this->nrow();
// }


/**============================================
 *!               Operator =
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const AbsView& view) {
    return this->assign(view, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator=(const T& scalar) {
    return this->assign(scalar, ejovo::id_eq<T, T>);
}


/**============================================
 *!               Operator +=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::plus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const AbsView& view) {
    return this->assign(view, ejovo::plus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator+=(const T& scalar) {
    return this->assign(scalar, ejovo::plus_eq<T, T>);
}

/**============================================
 *!               Operator -=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const Matrix& mat) {
    return this->assign(mat, ejovo::minus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const AbsView& view) {
    return this->assign(view, ejovo::minus_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator-=(const T& scalar) {
    return this->assign(scalar, ejovo::minus_eq<T, T>);
}
/**============================================
 *!               Operator *=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator*=(const T& scalar) {
    return this->assign(scalar, ejovo::times_eq<T, T>);
}

/**============================================
 *!               Operator /=
 *=============================================**/
template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::operator/=(const T& scalar) {
    return this->assign(scalar, ejovo::divide_eq<T, T>);
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const T& scalar, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), scalar);
    });
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const Matrix& mat, std::function<void(T&, const T&)> ass_op) {
    if (this->nrow() != mat.m || this->ncol() != mat.n) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::AbsView& Matrix<T>::AbsView::assign(const AbsView& view, std::function<void(T&, const T&)> ass_op) {
    if (this->nrow() != view.nrow() || this->ncol() != view.ncol()) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), view(i, j));
    });
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::AbsView::to_matrix() const {

    Matrix out{this->nrow(), this->ncol()};

    out.loop_i([&] (int i) {
        out(i) = this->operator()(i);
    });

    return out;
}

template <class T>
T* Matrix<T>::AbsView::get_ptr() {
    return matrix().data.get();
}

};