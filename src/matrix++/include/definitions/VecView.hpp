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
std::size_t Matrix<T>::VecView::nrow() const {
    return 1;
}

template <class T>
std::size_t Matrix<T>::VecView::ncol() const {
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
typename Matrix<T>::VecView& Matrix<T>::VecView::operator=(const VecView& rv) {
    this->assign(rv, ejovo::id_eq<T, T>);
    return *this;
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

template <class T>
T& Matrix<T>::VecView::operator[](int i) const {
    return mat(true_ind[i]);
}

template <class T>
T& Matrix<T>::VecView::operator[](int i) {
    return mat(true_ind[i]);
}

};