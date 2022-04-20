#pragma once

#include "declarations/VecView.hpp"

namespace ejovo {

/**========================================================================
 *!                           Class Template Type Members
 *========================================================================**/
/**======================
 *!    Constructors
 *========================**/
template <class T>
Matrix<T>::VecView::VecView(Matrix<T>& mat)
    : true_ind{ejovo::seq<int>(mat.size())}
    , mat{mat}
{};

template <class T>
Matrix<T>::VecView::VecView(Matrix<T>& mat, const Matrix<bool> mask)
    : true_ind{mat.which(mask)}
    , mat{mat}
{};

template <class T>
Matrix<T>::VecView::VecView(Matrix<T>& mat, const Matrix<int> true_ind)
    : true_ind{true_ind}
    , mat{mat}
{};

template <class T>
Matrix<T>::VecView::VecView(Matrix<T>& mat, std::function<bool(T)> pred)
    : true_ind{mat.where(pred).which()}
    , mat{mat}
{};

template <class T>
int Matrix<T>::VecView::nrows() const {
    return 1;
}

template <class T>
int Matrix<T>::VecView::ncols() const {
    return true_ind.size();
}

template <class T>
std::string Matrix<T>::VecView::to_string() const {
    return "VecView";
}

template <class T>
Matrix<T>& Matrix<T>::VecView::matrix() const {
    return this->mat;
}

template <class T>
T& Matrix<T>::VecView::operator()(int n) const {
    return mat(true_ind(n));
}

template <class T>
T& Matrix<T>::VecView::operator()(int i, int j) const {
    return mat(true_ind(i, j));
}

template <class T>
// template <class U>
typename Matrix<T>::VecView& Matrix<T>::VecView::assign(const T& scalar, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), scalar);
    });
    return *this;
}

template <class T>
typename Matrix<T>::VecView& Matrix<T>::VecView::operator=(const T& val) {
    return this->assign(val, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::VecView& Matrix<T>::VecView::assign(const Matrix<T>& mat, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::VecView& Matrix<T>::VecView::operator=(const Matrix<T>& mat) {
    return this->assign(mat, ejovo::id_eq<T, T>);
}

template <class T>
// template <class U>
typename Matrix<T>::VecView& Matrix<T>::VecView::assign(const VecView& rv, std::function<void(T&, const T&)> ass_op) {
    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), rv(i, j));
    });
    return *this;
}

template <class T>
typename Matrix<T>::VecView& Matrix<T>::VecView::operator=(const VecView& rv) {
    return this->assign(rv, ejovo::id_eq<T, T>);
}

template <class T>
typename Matrix<T>::VecView Matrix<T>::VecView::filter(std::function<bool(T)> f) {
    // all I have to do is filter the ind element...
    Matrix<int> ind = this->true_ind.filter([&] (int i) {
        return f(this->mat(i));
    });

    VecView out (this->mat, ind);
    return out;
}

};