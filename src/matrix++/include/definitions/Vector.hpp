#pragma once

#include "declarations/Vector.hpp"
// #include "declarations/Xoshiro.hpp"

namespace ejovo {

/**========================================================================
 *!                           Constructors
 *========================================================================**/
template <class T>
Vector<T>::Vector()
    : n{0}
    , col{true}
    , data{nullptr}
{}

template <class T>
Vector<T>::Vector(int n, bool col)
    : n{n}
    , col{col}
    , data{std::unique_ptr<T[]>(new T [n])}
{}

template <class T>
Vector<T>::Vector(const Vector& x)
    : n{x.n}
    , col{x.col}
    , data{x.copy_data()}
{}

template <class T>
Vector<T>::Vector(Vector&& x)
    : n{x.n}
    , col{x.col}
    , data{std::move(x.data)}
{
    x.reset();
}

template <class T>
Vector<T>& Vector<T>::reset() {
    this->n = 0;
    this->col = true;
    this->data = nullptr;
}

/**========================================================================
 *!                           Indexing Functions
 *========================================================================**/
template <class T>
T& Vector<T>::operator[](int i) {
    return (this->data)[i];
}

template <class T>
const T& Vector<T>::operator[](int i) const {
    return (this->data)[i];
}

/**========================================================================
 *!                           Pure Virtual Overrides
 *========================================================================**/
template <class T>
Matrix<T> Vector<T>::to_matrix() const {
    Matrix<T> out (*this); // This requires the existence of a Matrix(Vector) constructor
    return out;
}

// template <class T>
// Matrix<T> Vector<T>::new_matrix(int n) const {
//     if (col) {
//         Matrix<T> out(n, 1);
//         return out;
//     } else {
//         Matrix<T> out(1, n);
//         return out;
//     }
// }

template <class T>
std::size_t Vector<T>::size() const {
    return n;
}


/**========================================================================
 *!                           Printing Functions
 *========================================================================**/
template <class T>
Vector<T>& Vector<T>::print() {
    if (col) this->print_col();
    else this->print_row();

    return *this;
}

template <class T>
const Vector<T>& Vector<T>::print() const {
    if (col) return this->print_col();
    else return this->print_row();
}

template <class T>
const Vector<T>& Vector<T>::print_col() const {

    std::cout << "Col vector with n: " << this->n << "\n";

    for (int i = 1; i <= this->n; i++) {
        std::cout << "| ";

        std::cout << this->operator()(i);

        std::cout << " |\n";
    }

    return *this;
}

template <class T>
const Vector<T>& Vector<T>::print_row() const {

    std::cout << "Row vector with n: " << this->n << "\n";

    std::cout << "| ";

    for (int j = 1; j < this->n; j++) {
        std::cout << this->operator()(j) << ", ";
    }

    std::cout << this->operator()(this->n) << " |\n";

    return *this;

}

template <class T>
const Vector<T>& Vector<T>::summary() const {

    if (this->size() == 0) {
        std::cerr << "Empty vector\n";
        return *this;
    }

    // Check if this is a matrix, a column vector, or a row vector..
    if (col) {
        std::cout << "Column vector with n: " << this->size() << "\n";
        std::cout << "Euclidean norm: ";
    } else {
        std::cout << "Row vector with n: " << this->size() << "\n";
        std::cout << "Euclidiean norm: ";
    }

    std::cout << this->norm() << std::endl;

    std::cout << "sum:     " << this->sum() << std::endl;
    std::cout << "mean:    " << this->mean() << std::endl;
    std::cout << "min:     " << this->min()  << std::endl;
    std::cout << "max:     " << this->max()  << std::endl;
    std::cout << "sd:      " << this->sd()  << std::endl;
    std::cout << "var:     " << this->var()  << std::endl;

    return *this;

}

template <class T>
Vector<T>& Vector<T>::summary() {

    if (this->size() == 0) {
        std::cerr << "Empty vector\n";
        return *this;
    }

    // Check if this is a matrix, a column vector, or a row vector..
    if (col) {
        std::cout << "Column vector with n: " << this->size() << "\n";
        std::cout << "Euclidean norm: ";
    } else {
        std::cout << "Row vector with n: " << this->size() << "\n";
        std::cout << "Euclidiean norm: ";
    }

    std::cout << this->norm() << std::endl;

    std::cout << "sum:     " << this->sum() << std::endl;
    std::cout << "mean:    " << this->mean() << std::endl;
    std::cout << "min:     " << this->min()  << std::endl;
    std::cout << "max:     " << this->max()  << std::endl;
    std::cout << "sd:      " << this->sd()  << std::endl;
    std::cout << "var:     " << this->var()  << std::endl;

    return *this;

}

/**========================================================================
 *!                           Transpose functions
 *========================================================================**/
template <class T>
Vector<T> Vector<T>::t() const {
    Vector<T> out (*this);
    out.col = !(this->col);
    return out;
}

template <class T>
Vector<T> Vector<T>::transpose() const {
    return this->t();
}

template <class T>
Vector<T> Vector<T>::from(std::initializer_list<T> list, bool col) {
    int n = list.size();
    Vector out(n, col);
    int i = 1;
    for (auto el : list) {
        out(i) = el;
        i++;
    }
    return out;
}

template <class T>
ejovo::rng::Xoshiro& Vector<T>::xoroshiro = ejovo::rng::g_XOSHIRO;

template <class T> std::unique_ptr<T[]> Vector<T>::copy_data() const {
    // this->print();
    if(!data) return nullptr; // If data is nullptr, return nullptr

    auto ptr = new T[n]; // allocate the proper space
    memcpy(ptr, this->data.get(), n * sizeof(T)); // copy the data on over
    return std::unique_ptr<T[]>(ptr);
}

};

