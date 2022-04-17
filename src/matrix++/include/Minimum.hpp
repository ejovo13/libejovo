#pragma once

#include <cstdlib>
#include <utility>
#include <memory>
#include <iostream>

template <class T>
class Grid1D {

public:

    /**========================================================================
     *!                           Virtual Functions
     *========================================================================**/
    virtual T& operator[](int i) = 0; // 0-based indexing
    const virtual T& operator[](int i) const = 0;
    virtual std::size_t size() const = 0;


    T& at(int i);         // 1-based indexing with bounds checking
    T& operator()(int i); // 1-based indexing M(1) is the first element
    const T& at(int i) const; // at actually goes ahead and verifies whether or not the bounds are legit
    const T& operator()(int i) const;

    T& first();
    T& last();
    const T& first() const;
    const T& last() const;

};

template <class T>
T& Grid1D<T>::operator()(int i) {
    return this->operator[](i - 1);
}

template <class T>
const T& Grid1D<T>::operator()(int i) const {
    return this->operator[](i - 1);
}

template <class T>
T& Grid1D<T>::at(int i) {
    if (!(this->is_valid_bound(i))) throw "Error out of bounds";
    return this->operator[](i - 1);
}

template <class T>
const T& Grid1D<T>::at(int i) const {
    if (!(this->is_valid_bound(i))) throw "Error out of bounds";
    return this->operator[](i - 1);
}

template <class T>
T& Grid1D<T>::first() {
    return this->operator()(1);
}

template <class T>
const T& Grid1D<T>::first() const {
    return this->operator()(1);
}

template <class T>
T& Grid1D<T>::last() {
    return this->operator()(this->size());
}

template <class T>
const T& Grid1D<T>::last() const {
    return this->operator()(this->size());
}

template <class T>
class Grid2D : public Grid1D<T> {

public:

    /**========================================================================
     *!                           Virtual functions
     *========================================================================**/
    virtual std::size_t ncol() const = 0;
    virtual std::size_t nrow() const = 0;

    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;

    T& at(int i, int j);
    const T& at(int i, int j) const;

    virtual std::size_t size() const override;

    std::pair<int, int> to_ij(int n, bool col_major = true) const; // Take a vector index
    int to_i(int i, int j, bool col_major = true) const; // Take a vector index

private:

    bool col_major = true;

};

template <class T>
T& Grid2D<T>::at(int i, int j) {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
const T& Grid2D<T>::at(int i, int j) const {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
std::size_t Grid2D<T>::size() const {
    return this->ncol() * this->nrow();
}

template <class T>
const T& Grid2D<T>::operator()(int i, int j) const {
    return this->operator[](this->to_i(i, j) - 1);
}

template <class T>
T& Grid2D<T>::operator()(int i, int j) {
    return this->operator[](this->to_i(i, j) - 1);
}

template <class T>
std::pair<int, int> Grid2D<T>::to_ij(int n, bool col_major) const {

    if (col_major) {

        int i = (n - 1) % this->nrow() + 1;
        int j = ((n  - 1) / this->nrow()) + 1;
        return std::make_pair<int, int>(std::move(i), std::move(j));


    } else {

        int i = ((n  - 1) / this->ncol()) + 1;
        int j = (n - 1) % this->ncol() + 1;
        return std::make_pair<int, int>(std::move(i), std::move(j));

    }
}

// take i,j coordinates and translate to vector coordinates
template <class T>
int Grid2D<T>::to_i(int i, int j, bool col_major) const {
    if (col_major) return 1 + (i - 1) + (j - 1) * this->nrow();
    else return 1 + (j - 1) + (i - 1) * this->ncol();
}

template <class T = double>
class Matrix : public Grid2D<T> {

public:

    std::size_t m;
    std::size_t n;

    /**============================================
     *!    Grid1D Pure Virtual Functions
     *=============================================**/
    T& operator[](int i) override;
    const T& operator[](int i) const override;

    /**============================================
     *!     Grid2D Pure Virtual Functions
     *=============================================**/
    std::size_t ncol() const override;
    std::size_t nrow() const override;

    std::unique_ptr<T[]> data;

    //======= constructors
    Matrix();
    Matrix(int m); // create a column vector
    Matrix(int m, int n);
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);

};

/**========================================================================
 *!                           Constructors
 *========================================================================**/
template <class T> Matrix<T>::Matrix() : m{0}, n{0} { this->data = nullptr; }

template <class T> Matrix<T>::Matrix(int n) : m{1}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [n]);
}

template <class T> Matrix<T>::Matrix(int m, int n) : m{m}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [m * n]);
}

/**========================================================================
 *!                           Indexing operators
 *========================================================================**/
template <class T>
T& Matrix<T>::operator[](int i) {
    return (this->data)[i];
}

template <class T>
const T& Matrix<T>::operator[](int i) const {
    return (this->data)[i];
}

/**========================================================================
 *!                           Pure Virtual Overloads
 *========================================================================**/
template <class T>
std::size_t Matrix<T>::nrow() const {
    return this->m;
}

template <class T>
std::size_t Matrix<T>::ncol() const {
    return this->n;
}