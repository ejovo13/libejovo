#pragma once

#include "AbsView.hpp"

namespace ejovo {

template <class T>
class Matrix<T>::RowView : public AbsView {

public:

    int i = 0;
    int jb = 0;
    int je = 0;

    Matrix& matrix() const override;
    std::string to_string() const override;

    std::size_t nrow() const override;
    std::size_t ncol() const override;

    T& operator[](int i) const override;
    T& operator[](int i) override;

    // T& operator()(int i) const override;
    // T& operator()(int i, int j) const override;
    // T& at(int i) override;
    // T& at(int i, int j) override;

    // RowView& assign(const T&, std::function<void(T&, const T&)>);
    // RowView& assign(const Matrix&, std::function<void(T&, const T&)>);
    // RowView& assign(const RowView&, std::function<void(T&, const T&)>);
    // using AbsView::assign;

    using AbsView::operator=;
    RowView& operator=(const RowView&);

    // RowView& operator=(const T&);
    // RowView& operator=(const Matrix&);

    RowView(Matrix& mat, int i);
    RowView(Matrix& mat, int i, int jb);
    RowView(Matrix& mat, int i, int jb, int je);
    RowView(RowView&& rv);

    Matrix<T>& mat;

};

};