#pragma once

#include "AbsView.hpp"

namespace ejovo {
/**========================================================================
 *!                           Column View
*========================================================================**/
template <class T>
class Matrix<T>::ColView : public AbsView {

public:

    int j;
    int ib;
    int ie;

    Matrix& matrix() const override;

    int nrows() const override;
    int ncols() const override;

    T& operator()(int n) const override;
    T& operator()(int i, int j) const override;

    // T& at(int n) override;
    // T& at(int i, int j) override;

    ColView& assign(const T&, std::function<void(T&, const T&)>);
    ColView& assign(const Matrix&, std::function<void(T&, const T&)>);
    ColView& assign(const ColView&, std::function<void(T&, const T&)>);

    ColView& operator=(const T&);
    ColView& operator=(const Matrix&);
    ColView& operator=(const ColView&);

    std::string to_string() const;

    ColView(Matrix& mat, int i);
    ColView(Matrix& mat, int i, int jb);
    ColView(Matrix& mat, int i, int jb, int je);
    ColView(ColView&& cv);

private:

    Matrix& mat;

};

};