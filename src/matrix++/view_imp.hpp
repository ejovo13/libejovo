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

template <class T>
View<T>& View<T>::loop_ij(std::function<T(int, int)> f) {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            this->at(i, j) = f(i, j);
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

template <class T>
const T& View<T>::at(int i, int j) const {
    return mat(row_ind(i), col_ind(j));
}

// Loops the
template <class T>
View<T>& View<T>::loop_ij(std::function<void(int, int)> f) {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            f(i, j);
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
    // std::cout << "Setting a view to a const\n";
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
Matrix<T> View<T>::map(std::function<T(const T)> f) const {
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
Matrix<T> View<T>::break_away() const {
    return this->map(ejovo::id<T>);
}

template <class T>
Matrix<T> View<T>::to_matrix() const {
    return this->map(ejovo::id<T>);
}

/**========================================================================
 *!                           Operators Implementation
 *========================================================================**/
template <class T>
View<T>& View<T>::operator+=(T val) {
    this->mutate([&] (auto x) {
        return x + val;
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator-=(T val) {
    this->mutate([&] (auto x) {
        return x - val;
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator*=(T val) {
    this->mutate([&] (auto x) {
        return x * val;
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator/=(T val) {
    this->mutate([&] (auto x) {
        return x / val;
    });
    return *this;
}

template <class T>
View<T>& View<T>::assign_op(const Matrix<T>& mat, std::function<void(T&, T&)> ass_op) {
    // check if they are able to add
    if (this->m != mat.m || this->n != mat.n) {
        std::cerr << "Matrix operands are not compatible\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), mat(i, j));
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator+=(const Matrix<T>& mat) {
    return this->assign_op(mat, ejovo::plus_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator-=(const Matrix<T>& mat) {
    return this->assign_op(mat, ejovo::minus_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator*=(const Matrix<T>& mat) {
    return this->assign_op(mat, ejovo::times_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator/=(const Matrix<T>& mat) {
    return this->assign_op(mat, ejovo::divide_eq<T, T>);
}

template <class T>
int View<T>::size() {
    return this->m * this->n;
}

template <class T>
View<T>& View<T>::assign_op(View<T> view, std::function<void(T&, T&)> ass_op) {
    if (this->m != view.m || this->n != view.n) {
        std::cerr << "Unable to perform assignment with non conforming Views\n";
        return *this;
    }

    this->loop_ij([&] (int i, int j) {
        ass_op(this->at(i, j), view(i, j));
    });
    return *this;
}

template <class T>
View<T>& View<T>::operator +=(View<T> view) {
    // std::cout << "Calling assign_op\n";
    return this->assign_op(view, ejovo::plus_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator -=(View<T> view) {
    return this->assign_op(view, ejovo::minus_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator *=(View<T> view) {
    return this->assign_op(view, ejovo::times_eq<T, T>);
}

template <class T>
View<T>& View<T>::operator /=(View<T> view) {
    return this->assign_op(view, ejovo::divide_eq<T, T>);
}