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

    T& operator()(int i, int j);
    T& at(int i, int j);
    // T& View<T>::operator()(int i, int j)

    View<T>& operator=(T val);
    View<T>& operator=(View<T> view);
    View<T>& operator=(const Matrix<T>& mat);

    Matrix<T> map(std::function<T(T)> f);
    View<T>& mutate(std::function<T(T)> f);

    Matrix<T> break_away();


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