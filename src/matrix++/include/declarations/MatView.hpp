#pragma once

#include "AbsView.hpp"

namespace ejovo {

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

    std::size_t nrow() const override;
    std::size_t ncol() const override;
    std::string to_string() const override;
    Matrix<T>& matrix() const override;

    T& operator[] (int i) const override;
    T& operator[] (int i) override;

    // Matrix& matrix() const override;
    // T& operator()(int n) const override;
    // T& operator()(int i, int j) const override;

    // MatView& assign(const T&, std::function<void(T&, const T&)>);
    // MatView& assign(const Matrix&, std::function<void(T&, const T&)>);
    // MatView& assign(const MatView&, std::function<void(T&, const T&)>);

    using AbsView::operator=;
    // MatView& operator=(const T&);
    // MatView& operator=(const Matrix&);
    MatView& operator=(const MatView&);
    // template <class U>
    // MatView& operator=(const Matrix<T>& x) {
    //     return this->assign(x, ejovo::id_eq<T, T>);
    // }

    // VecView get_row_view(int i = 1);
    // VecView get_col_view(int j = 1);

    Matrix<T> &mat;



private:


};



};