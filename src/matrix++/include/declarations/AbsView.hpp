#pragma once

#include "Matrix.hpp"

/**========================================================================
 *!                           AbstractView definition
*========================================================================**/
namespace ejovo {

// Since we've factored out common grid behavior into Grid1D and Grid2D,
// we want to remove redundant behavior defined here. loops. mutations.
// let's factor it out.

// This interface has properties concerning PEEKING at a matrix. Everything else should
// be handles by the Grid abstraction.
//
//

template <class T>
class Matrix<T>::AbsView : public Grid2D<T> {

public:

    virtual std::string to_string() const = 0;
    virtual Matrix& matrix() const = 0;

    T* get_ptr(); // get a pointer to the underlying data of the matrix

    virtual AbsView& assign(const Matrix& mat, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const T& scalar, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const AbsView& view, std::function<void(T&, const T&)> ass_op); // use const AbsView to bind with any type..

    // Once we get to the actual overload though, we are having non-stop problems....
    // virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const Matrix& mat);
    virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const T& scalar);

    virtual AbsView& operator+=(const Matrix& mat);
    virtual AbsView& operator+=(const T& scalar);
    virtual AbsView& operator+=(const AbsView& view);

    virtual AbsView& operator-=(const Matrix& mat);
    virtual AbsView& operator-=(const T& scalar);
    virtual AbsView& operator-=(const AbsView& view);

    virtual AbsView& operator*=(const T& scalar);
    virtual AbsView& operator/=(const T& scalar);

    Matrix to_matrix() const;
    // Matrix to_rowvec();
    // Matrix to_colvec();

        // V * 5
    friend Matrix<T> operator*(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() *= scalar;
    }

    // 5 * V
    friend Matrix<T> operator*(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() *= scalar;
    }

    friend Matrix<T> operator/(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() /= scalar;
    }

    friend Matrix<T> operator/(const T& scalar, const AbsView& rhs) {
        return scalar / rhs.to_matrix();
    }


    friend Matrix<T> operator+(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() += scalar;
    }

    friend Matrix<T> operator+(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() += scalar;
    }

    friend Matrix<T> operator-(const AbsView& lhs, const T& scalar) {
        return lhs.to_matrix() -= scalar;
    }

    friend Matrix<T> operator-(const T& scalar, const AbsView& rhs) {
        return rhs.to_matrix() -= scalar;
    }

    friend Matrix<T> operator-(const AbsView& lhs, const Matrix<T>& rhs) {
        return lhs.to_matrix() -= rhs;
    }

    friend Matrix<T> operator-(const Matrix<T>& lhs, const AbsView& rhs) {
        // We can avoid a copy here and just loop over the rhs elements
        return lhs - rhs.to_matrix();
    }

    std::pair<int, int> ind_to_ij(int n) const;

};

};

