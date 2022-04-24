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

    // AbsView(Matrix &m);
    // virtual int nrow() const = 0;
    // virtual int ncol() const = 0;
    virtual std::string to_string() const = 0;
    virtual Matrix& matrix() const = 0;
    // virtual T& operator()(int i) const = 0; // Don't check bounds!!
    // virtual T& operator()(int i, int j) const = 0; // Don't check bounds!!

    // virtual T& at(int i) = 0; // check bounds!!
    // virtual T& at(int i, int j) = 0; // check bounds!!
    // T& at(int i); // check bounds!!
    // T& at(int i, int j); // check bounds!!

    T* get_ptr(); // get a pointer to the underlying data of the matrix
    // int size();
    // bool valid_bounds(int i);
    // bool valid_bounds(int i, int j);
    // AbsView& print() override;

    // template <class Fn>
    // AbsView& loop(std::function<T(T)>);
    // virtual AbsView& loop(std::function<void(T)>);
    // virtual AbsView& loop_i(std::function<void(int)>);
    // virtual AbsView& loop_ij(std::function<void(int, int)>);

    // virtual AbsView& mutate(std::function<T(T)>);
    // AbsView& mutate(std::function<T(T)>);

    // These Three assignment operators WORK!!!
    // virtual AbsView& assign(Matrix&& mat, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const Matrix& mat, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const T& scalar, std::function<void(T&, const T&)> ass_op);
    virtual AbsView& assign(const AbsView& view, std::function<void(T&, const T&)> ass_op); // use const AbsView to bind with any type..

    // Once we get to the actual overload though, we are having non-stop problems....
    // virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const Matrix& mat);
    virtual AbsView& operator=(const AbsView& view);
    virtual AbsView& operator=(const T& scalar);
    // template <class U> AbsView& operator=(const U& scalar);
    // virtual AbsView& operator=(T scalar);
    // virtual AbsView& operator=(double x);
    // virtual AbsView& operator=(Matrix mat);
    // virtual AbsView& operator=(Matrix&& mat);
    // virtual AbsView& operator=(AbsView& view);

    // template <class U> AbsView& operator=(const U& scalar);

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

    // Matrix<T> &mat = Matrix<T>::null();

private:

protected:


};

};

