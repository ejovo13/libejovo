#pragma once

#include "AbsView.hpp"

namespace ejovo{

template <class T>
class Matrix<T>::VecView : public AbsView {

public:

    // Bare minimum info needed to store a matrix
    Matrix<int> true_ind;

    VecView(Matrix& mat);
    VecView(Matrix& mat, const Matrix<bool> mask);
    VecView(Matrix& mat, const Matrix<int> true_ind); // vector indices
    VecView(Matrix& mat, std::function<bool(T)> pred);

    std::size_t nrow() const override;
    std::size_t ncol() const override;
    std::string to_string() const override;
    Matrix& matrix() const override;
    // T& operator()(int n) const override;
    // T& operator()(int i, int j) const override;

    T& operator[] (int i) const override;
    T& operator[] (int i) override;

    // VecView& assign(const T&, std::function<void(T&, const T&)>);
    // VecView& assign(const Matrix&, std::function<void(T&, const T&)>);
    // VecView& assign(const VecView&, std::function<void(T&, const T&)>);

    using AbsView::operator=;
    // VecView& operator=(const T&);
    // VecView& operator=(const Matrix&);
    VecView& operator=(const VecView&);

    // return a new vec view
    VecView filter(std::function<bool(T)> f);


private:

    Matrix<T>& mat;

};

};