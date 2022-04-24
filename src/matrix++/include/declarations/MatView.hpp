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

    using AbsView::operator=;
    MatView& operator=(const MatView&);

    Matrix<T> &mat;



private:


};



};