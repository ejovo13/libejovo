#pragma once

#include "ejovo.hpp"
#include "matrix.hpp"
#include "matrix_impl.hpp"

template <class T>
class View {

    // A view can be ENTIRELY represented with row and column indices!!!!!

public:

    Matrix<int> row_ind;
    Matrix<int> col_ind;
    int m;
    int n;

    // View();
    View(Matrix<T>& mat);
    View(Matrix<T>& mat, const Matrix<int> row_ind, const Matrix<int> col_ind);

    View& loop_ij(std::function<T(int, int)>);
    View& loop_ij(std::function<void(int, int)>);

    int size();

    T& operator()(int i, int j);
    T& at(int i, int j);
    const T& at(int i, int j) const;
    // T& View<T>::operator()(int i, int j)

    View<T>& operator=(T val);
    View<T>& operator=(View<T> view);
    View<T>& operator=(const Matrix<T>& mat);

    View<T>& operator +=(T val);
    View<T>& operator -=(T val);
    View<T>& operator *=(T val);
    View<T>& operator /=(T val);

    View<T>& assign_op(View<T> view, std::function<void(T&, T&)> ass_op);

    View<T>& operator +=(View<T> view);
    View<T>& operator -=(View<T> view);
    View<T>& operator *=(View<T> view);
    View<T>& operator /=(View<T> view);

    Matrix<T> map(std::function<T(T)> f) const;
    View<T>& mutate(std::function<T(T)> f);

    Matrix<T> break_away() const;
    Matrix<T> to_matrix() const;

    // V * 5
    friend Matrix<T> operator*(const View<T>& lhs, const T& scalar) {
        return lhs.break_away() * scalar;
    }

    // 5 * V
    friend Matrix<T> operator*(const T& scalar, const View<T>& rhs) {
        return rhs.break_away() * scalar;
    }

    friend Matrix<T> operator/(const View<T>& lhs, const T& scalar) {
        return lhs.break_away() / scalar;
    }

    friend Matrix<T> operator/(const T& scalar, const View<T>& rhs) {
        return scalar / rhs.break_away();
    }

    friend Matrix<T> operator+(const View<T>& lhs, const T& scalar) {
        return lhs.break_away() + scalar;
    }

    friend Matrix<T> operator+(const T& scalar, const View<T>& rhs) {
        return rhs.break_away() + scalar;
    }

    friend Matrix<T> operator-(const View<T>& lhs, const T& scalar) {
        return lhs.break_away() - scalar;
    }

    friend Matrix<T> operator-(const T& scalar, const View<T>& rhs) {
        return rhs.break_away() - scalar;
    }

    void print();

private:

    Matrix<T>& mat;

};



template <class T>
class ConstView {

public:

    Matrix<int> row_ind;
    Matrix<int> col_ind;

    ConstView(const Matrix<T>& mat);
    ConstView(const Matrix<T>& mat, const Matrix<int> row_ind, const Matrix<int> col_ind);

private:

    const Matrix<T>& mat;

};



// template <class T>
// View<T>::View(const Matrix<T> &mat)