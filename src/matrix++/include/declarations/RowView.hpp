#pragma once

#include "AbsView.hpp"

namespace ejovo {

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

};