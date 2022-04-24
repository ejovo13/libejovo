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

    T& operator[](int i) override;
    T& operator[](int i) const;

    std::size_t nrow() const override;
    std::size_t ncol() const override;

    Matrix& matrix() const;

    using AbsView::operator=;
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