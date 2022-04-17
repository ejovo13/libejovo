#pragma once

#include "Grid1D.hpp"
#include <utility>

namespace ejovo {

template <class T>
class Grid2D : public ejovo::Grid1D<T> {

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
    // const T& at(int i) const;
    // const T& operator()(int i) const;

    virtual std::size_t size() const override;

    bool are_valid_bounds(int i, int j) const;
    bool is_same_shape(const Grid2D& rhs) const;

    std::pair<int, int> to_ij(int n, bool col_major = true) const; // Take a vector index
    int to_i(int i, int j, bool col_major = true) const; // Take a vector index


private:

    bool col_major = true;







};

template <class T>
std::size_t Grid2D<T>::size() const {
    return this->ncol() * this->nrow();
}

// Translate vector index to 2-dimensional index
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

template <class T>
T& Grid2D<T>::at(int i, int j) {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
const T& Grid2D<T>::at(int i, int j) const {
    return this->at(this->to_i(i, j, this->col_major));
}

template <class T>
const T& Grid2D<T>::operator()(int i, int j) const {
    return this->operator[](this->to_i(i, j) - 1);
}

template <class T>
T& Grid2D<T>::operator()(int i, int j) {
    return this->operator[](this->to_i(i, j) - 1);
}



};
