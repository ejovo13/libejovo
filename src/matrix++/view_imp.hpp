#pragma once

#include "view.hpp"


template <class T>
View<T>::View(Matrix<T>& mat)
    : mat{mat}
    , row_ind{ejovo::seq(mat.m)}
    , col_ind{ejovo::seq(mat.n)}
    , m{mat.m}
    , n{mat.n}
{};

template <class T>
View<T>::View(Matrix<T>& mat, const Matrix<int> row_ind, const Matrix<int> col_ind)
    : mat{mat}
    , row_ind{row_ind}
    , col_ind{col_ind}
    , m{row_ind.size()}
    , n{col_ind.size()}
{};

// template <class T>
// View<T>::View()
//     : mat{0, 0}
//     , row_ind{Matrix<int>::null()}
//     , col_ind{Matrix<int>::null()}
//     , m{0}
//     , n{0}
// {

//     mat = Matrix<T>::zeros(1);

// };


template <class T>
View<T>& View<T>::loop_ij(std::function<T(int, int)> f) {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            this->at(i, j) = f(row_ind(i), col_ind(j));
        }
    }
    return *this;
}

template <class T>
T& View<T>::operator()(int i, int j) {
    return mat(row_ind(i), col_ind(j));
}

template <class T>
T& View<T>::at(int i, int j) {
    return mat(row_ind(i), col_ind(j));
}

// Loops the
template <class T>
View<T>& View<T>::loop_ij(std::function<void(int, int)> f) {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            f(row_ind(i), col_ind(j));
        }
    }
    return *this;
}

// template <class T>
// View<T>& View<T>::loop_ij_view(std::function<void(int, int)> f) {

// }

template <class T>
void View<T>::print() {

    std::cout << this->m << " x " << this->n << " View\n";

    for (int i = 1; i <= this->m; i++) {

        std::cout << "|";

        for (int j = 1; j < this->n; j++) {
            std::cout << this->at(i, j) << ", ";
        }

        std::cout << this->at(i, this->n) << "|\n";
    }
}

template <class T>
View<T>& View<T>::operator=(T val) {
    this->loop_ij([&] (int i, int j) {
        this->at(i, j) = val;
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator=(View<T> view) {
    // Check if the views are the same size!
    if (this->m != view.m || this->n != view.n) return *this; // no assignment occurs

    this->loop_ij([&] (int i, int j) {
        this->at(i, j) = view(i, j);
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator=(const Matrix<T>& mat) {
    // Check if the views are the same size!
    if (this->m != mat.m || this->n != mat.n) return *this; // no assignment occurs

    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            this->at(i, j) = mat(i, j);
        }
    }

    // i, j are the ORIGINAL MATRICES indices
    // this->loop_ij([&] (int i, int j) {
    //     this->at(i, j) = mat(i, j);
    // });
    return *this;
}

template <class T>
Matrix<T> View<T>::map(std::function<T(T)> f) {
    Matrix<T> out = Matrix<T>::zeros(this->m, this->n);
    out.loop_ij([&] (int i, int j) {
        out(i, j) = f(this->at(i, j));
    });
    return out;
}

template <class T>
View<T>& View<T>::mutate(std::function<T(T)> f) {
    this->loop_ij([&] (int i, int j) {
        this->at(i, j) = f(this->at(i, j));
    });
    return *this;
}

template <class T>
Matrix<T> View<T>::break_away() {
    return this->map(ejovo::id);
}
