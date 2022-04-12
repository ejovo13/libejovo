#pragma once

#include "ejovo.hpp"
#include "matrix.hpp"

template <class T>
class Matrix<T>::VecView : public AbsView {

public:

    // Bare minimum info needed to store a matrix
    Matrix<int> true_ind;

    VecView(Matrix& mat);
    VecView(Matrix& mat, const Matrix<bool> mask);
    VecView(Matrix& mat, const Matrix<int> true_ind); // vector indices

    int nrows() const override;
    int ncols() const override;
    std::string to_string() const override;
    Matrix& matrix() const override;
    T& operator()(int n) const override;
    T& operator()(int i, int j) const override;

    VecView& assign(const T&, std::function<void(T&, const T&)>);
    VecView& assign(const Matrix&, std::function<void(T&, const T&)>);
    VecView& assign(const VecView&, std::function<void(T&, const T&)>);

    VecView& operator=(const T&);
    VecView& operator=(const Matrix&);
    VecView& operator=(const VecView&);


private:

    Matrix<T>& mat;

};

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