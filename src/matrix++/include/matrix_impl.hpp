
#pragma once

#include "ejovo.hpp"
// #include "view.hpp"
#include <initializer_list>

// This file is like the .cpp counterpart of matrix.hpp, although since we are dealing with a
// template library we are forced to keep this in a header file that will be included.

/**========================================================================
 *!                           Trigonometric functions
 *========================================================================**/

// I could always have a namespace name that corresponds to a typeclass



/**========================================================================
 *!                           Constructors
 *========================================================================**/
template <class T> Matrix<T>::Matrix() : m{0}, n{0} { this->data = nullptr; }

template <class T> void Matrix<T>::reset() {
    this->m = 0;
    this->n = 0;
    this->data = nullptr;
}

template <class T> Matrix<T>::Matrix(int n) : m{1}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [n]);
}

template <class T> Matrix<T>::Matrix(int m, int n) : m{m}, n{n} {
    this->data = std::unique_ptr<T[]>(new T [m * n]);
}

template <class T>
Matrix<T> Matrix<T>::from(std::initializer_list<T> list) {
    int n = list.size();
    Matrix<T> out{1, n};
    int i = 1;
    for (auto el : list) {
        out(i) = el;
        i++;
    }
    return out;
}

template <class T>
Matrix<T> Matrix<T>::from(std::initializer_list<T> list, int m, int n) {
    int n_el = list.size();
    Matrix<T> out;

    if (n_el == m * n) {
        out = Matrix<T>::zeros(m, n);
    } else {
        out = Matrix<T>::zeros(1, n_el);
    }

    int i = 1;
    for (auto el : list) {
        out(i) = el;
        i++;
    }
    return out;
}

/**========================================================================
 *!                           Random Matrices
 *========================================================================**/
template <class T>
ejovo::rng::Xoshiro& Matrix<T>::xoroshiro = g_XOSHIRO;

// template <class T>
// Matrix<T> Matrix<T>





template <class T> std::unique_ptr<T[]> Matrix<T>::copyData() const {
    int n = this->size();

    // this->print();
    auto ptr = new T[n]; // allocate the proper space
    memcpy(ptr, this->data.get(), n * sizeof(T)); // copy the data on over
    return std::unique_ptr<T[]>(ptr);
}

template <class T> Matrix<T>::Matrix(const Matrix& rhs) : m{rhs.m}, n{rhs.n} {
    this->data = rhs.copyData();
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs) {
    // std::cerr << "Performing copy assignment\n";
    if (this == &rhs)
        return *this;

    this->data = rhs.copyData();
    this->m = rhs.m;
    this->n = rhs.n;

    return *this;
}

// template <class T>
// Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) {

//     // check if the matrices are compatible for matrix addition.
//     if (!this->canAddB(rhs)) {
//         std::cerr << "Can't add two matrices\n";
//         return *this;
//     }

//     loop_i(rhs, [&] (int i) {
//         this->at(i) += rhs(i);
//     });

//     return *this;
// }

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) {
    // std::cerr << "Performing move assignment =\n";
    if (this == &rhs)
        return *this;

    this->data = std::move(rhs.data);
    this->m = rhs.m;
    this->n = rhs.n;

    // leave rhs in default state
    rhs.nullify();

    return *this;
}

// template <class T>
// Matrix<T>& Matrix<T>::operator=(const Matrix rhs) {
//     std::swap(data, rhs.data);
//     return *this;
// }

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

template <class T>
T& Matrix<T>::operator()(int i) {
    return (this->data)[i - 1];
}

template <class T>
T& Matrix<T>::operator()(int i, int j) {
    return this->operator()(i*this->n + j  - this->n);
}

template <class T>
const T& Matrix<T>::operator()(int i) const {
    return (this->data)[i - 1];
}

template <class T>
const T& Matrix<T>::operator()(int i, int j) const {
    return this->operator()(i*this->n + j - this->n);
}

// // todo
// template <class T>
// this should return a VIEW
// Matrix<T> Matrix<T>::operator()(const Matrix<int>& ind) const {
//     // let's count how many valid bounds there are....
//     auto valid_bounds = [&] (int i) {
//         return i >= 1 && i <= this.size();
//     };

//     int n_valid = ind.filter(valid_bounds).size();
//     ind.map([&] (int i) {
//         return this->at(i);
//     });
// }

template <class T>
Matrix<T> Matrix<T>::rep_col(int n) const {
    // create a new matrix that is this VECTOR repeated vertically n times.
    Matrix out{this->size(), n}; // create n columns.

    return out.loop_ij([&] (int i, int j) {
        return this->at(i);
    });
}

template <class T>
Matrix<T> Matrix<T>::rep_row(int n) const {
    // create a new matrix that is this VECTOR repeated horizontally n times.
    Matrix out{n, this->size()};

    return out.loop_ij([&] (int i, int j) {
        return this->at(j);
    });
}


    // for (int j = 1; j <= out.n; j++) {
    //     for (int i = 1; i <= out.m; i++) {
    //         out(i, j) = this->at(i)
    //     }
    // }


template <class T>
T& Matrix<T>::at(int i) {
    return this->operator()(i);
}

template <class T>
T& Matrix<T>::at(int i, int j) {
    return this->operator()(i, j);
}

template <class T>
const T& Matrix<T>::at(int i) const {
    return this->operator()(i);
}

template <class T>
const T& Matrix<T>::at(int i, int j) const {
    return this->operator()(i, j);
}

// template <class T>
// T& Matrix<T>::at(int i) {
//     return this->operator()(i);
// }

// extract the specified integers
template <class T>
Matrix<T> Matrix<T>::operator()(const Matrix<int> ind) {
    // Assume all the indices are legitamete
    const int n = this->size();
    // check the bounds
    auto valid_ind = ejovo::filter(ind, [&] (int x) {
        return x >= 1 && x <= n;
    });

    // now extract those valid indices
    Matrix<T> out{valid_ind.size()};

    valid_ind.loop_i([&] (int i) {
        out(i) = this->at(ind(i));
    });

    return out;
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::operator()(const Matrix<int>& row_ind, const Matrix<int>& col_ind) {
    MatView v{*this, row_ind, col_ind};
    return v;
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::operator()(int i, const Matrix<int>& col_ind) {
    MatView v{*this, Matrix<int>::val(1, 1, i), col_ind};
    return v;
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::operator()(const Matrix<int>& row_ind, int j) {
    MatView v{*this, row_ind, Matrix<int>::val(1, 1, j)};
    return v;
}



/**========================================================================
 *!                           Mutations
 *========================================================================**/
template <class T>
void Matrix<T>::fill(T val) {
    for (int i = 0; i < this->size(); i++) {
        this->operator()(i + 1) = val;
        // std::cout << "filling i: " << i << "\n";
    }
}

template <class T>
int Matrix<T>::size() const {
    return this->m * this->n;
}

template <class T>
const Matrix<T>& Matrix<T>::print() const {

    std::cout << this->m << " x " << this->n << " matrix\n";

    for (int i = 1; i <= this->m; i++) {
        std::cout << "|";

        for (int j = 1; j < this->n; j++) {
            std::cout << this->operator()(i, j) << ", ";
        }

        std::cout << this->operator()(i, this->n) << "|\n";
    }

    return *this;
}

template <class T>
const Matrix<T>& Matrix<T>::print_lin() const {

    if (this->size() == 0) {
        std::cerr << "Empty matrix trying to call Matrix<T>::print_lin()";
        return *this;
    }

    // Check if this is a matrix, a column vector, or a row vector..
    if (this->is_colvec()) {
        std::cout << "Column vector with n: " << this->size() << "\n";
        std::cout << "Euclidean norm: ";
    } else if (this->is_rowvec()) {
        std::cout << "Row vector with n: " << this->size() << "\n";
        std::cout << "Euclidiean norm: ";
    } else {
        std::cout << "Matrix with shape: " << this->m << " x " << this->n << "\n";
        std::cout << "Frobenius norm: ";
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
Matrix<T> Matrix<T>::t() const {

    Matrix<T> A{this->n, this->m};

    A.loop_ij([&] (int i, int j) {A(i, j) = this->operator()(j, i);});
    return A;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    return this->t();
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) {

    if (this->cant_add_b(rhs)) {
        std::cerr << "Trying to add incompatible matrices\n";
        return *this;
    }
    // element-wise addition
    this->loop_i([&] (int i) {
        this->at(i) += rhs(i);
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& rhs) {

    if (this->cant_add_b(rhs)) {
        std::cerr << "Trying to add incompatible matrices\n";
        return *this;
    }
    // element-wise addition
    this->loop_i([&] (int i) {
        this->at(i) -= rhs(i);
    });
    return *this;
}

//========================= Scalar operations ====================
template <class T>
Matrix<T>& Matrix<T>::operator+=(const T scalar) {
    this->loop_i([&] (int i) {
        this->at(i) += scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const T scalar) {
    // element-wise addition
    this->loop_i([&] (int i) {
        this->at(i) -= scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T scalar) {
    this->loop_i([&] (int i) {
        this->at(i) *= scalar;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator/=(const T scalar) {
    this->loop_i([&] (int i) {
        this->at(i) /= scalar;
    });
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix dup{*this};
    dup.loop_i([&] (int i) {dup(i) = -this->operator()(i);});
    return dup;
}

// hadamard multiplication
template <class T>
Matrix<T>& Matrix<T>::operator%=(const Matrix& rhs) {

    if (this->size() != rhs.size()) {
        std::cerr << "Not the same size, cant perform hadamard multiplication\n";
        return *this;
    }
    this->loop_i([&] (int i) {
        this->at(i) *= rhs(i);
    });
    return *this;
}

template <class T>
T Matrix<T>::dot(const Matrix& rhs) const {
    auto had_res = *this % rhs;
    return ejovo::sum(had_res);
}

template <class T>
T Matrix<T>::dot(const Matrix& rhs, int i, int j) const {
    // we are assuming that the sizes are legit
    T total = 0;
    for (int k = 1; k <= this->n; k++) {
        total += (this->at(i, k) * rhs(k, j));
    }
    return total;
}

template <class T>
T Matrix<T>::inner_product(const Matrix& rhs) const {
    return this->dot(rhs);
}

template <class T>
Matrix<T> Matrix<T>::outer_product(const Matrix& rhs) const {
    // Treat these as two vectors
    Matrix out{this->size(), rhs.size()};
    out.loop_ij([&] (int i, int j) {
        out(i, j) = (this->at(i)) * (rhs(j));
    });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::kronecker_product(const Matrix& rhs) const {

    Matrix out{Matrix<T>::zeros(this->m * rhs.m, this->n * rhs.n)};

    int block_rowmaj_pos = 0;

    // I think I need a function to set a block matrix..
    auto set_block = [&] (int i, int j) {

        MatView block{out, ejovo::seq<int>(i, i + rhs.m - 1), ejovo::seq<int>(j, j + rhs.n - 1)}; // construct the block view
        block = rhs * this->operator[](block_rowmaj_pos);

    };

    // Equipped with the basics of views, I think I'm ready to tackle this function!
    for (int i = 1; i < out.m; i += rhs.m) {
        for (int j = 1; j < out.n; j += rhs.n) {
            set_block(i, j);
            block_rowmaj_pos ++;
        }
    }

    return out;
}

template <class T>
Matrix<T> Matrix<T>::hadamard_product(const Matrix& rhs) const {
    // element-wise multiplication
    return *this % rhs;
}

// Matrix multiplication!!!
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix&rhs) const {

    if (this->cant_mult_b(rhs)) {
        std::cerr << "Can't multiply matrices\n";
        return zeros(1);
    }
    // o(n3), so we will have 3 loops

    // create output matrix
    Matrix out{this->m, rhs.n};

    for (int i = 1; i <= out.m; i++) {
        for (int j = 1; j <= out.n; j++) {
            out(i, j) = this->dot(rhs, i, j);
        }
    }
    return out;
}

template <class T>
Matrix<T> Matrix<T>::diff() const {
    // create matrix that is smaller
    Matrix out{this->size() - 1};
    for (int i = 0; i < out.size(); i++) {
        out[i] = this->operator[](i + 1) - this->operator[](i);
    }
    return out;
}

template <class T>
Matrix<T> Matrix<T>::abs() const {
    return ejovo::map(*this, [&] (auto x) {
        return ejovo::abs(x);
    });
}


template <class T> Matrix<T>::Matrix(Matrix&& rhs) : m{rhs.m}, n{rhs.n} {

    this->data = std::move(rhs.data);
    this->m = rhs.m;
    this->n = rhs.n;

    rhs.data = nullptr;
    rhs.m = 0;
    rhs.n = 0;
}

/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/

template <class T>
int Matrix<T>::mindim() const {
    return this->m < this->n ? this->m : this->n;
}


/**========================================================================
 *!                           Static functions
 *========================================================================**/
template <class T>
Matrix<T> Matrix<T>::null() {
    Matrix out{};
    return out;
}

template <class T>
Matrix<T> Matrix<T>::zeros(int m) {

    Matrix zero{m, m};
    zero.fill(0);
    return zero;
}

template <class T>
Matrix<T> Matrix<T>::zeros(int m, int n) {

    Matrix zero(m, n);
    zero.fill(0);
    return zero;
}

template <class T>
Matrix<T> Matrix<T>::zeros(const Matrix& mat) {
    Matrix zero{mat.m, mat.n};
    zero.fill(0);
    return zero;
}

template <class T>
Matrix<T> Matrix<T>::row(int n) {
    return Matrix<T>::zeros(1, n);
}

template <class T>
Matrix<T> Matrix<T>::row(int n, T val) {
    return Matrix<T>::val(1, n, val);
}

template <class T>
Matrix<T> Matrix<T>::col(int n, T val) {
    return Matrix<T>::val(n, 1, val);
}

template <class T>
Matrix<T> Matrix<T>::col(int n) {
    return Matrix<T>::zeros(n, 1);
}

template <class T>
Matrix<T> Matrix<T>::val(int n, T val) {
    Matrix out{n};
    out.fill(val);
    return out;
}

template <class T>
Matrix<T> Matrix<T>::val(int m, int n, T val) {
    Matrix out{m, n};
    out.fill(val);
    return out;
}

template <class T>
Matrix<T> Matrix<T>::ones(int m) {

    Matrix one{m};
    one.fill(1);
    return one;
}

template <class T>
Matrix<T> Matrix<T>::ones(int m, int n) {

    Matrix one(m, n);
    one.fill(1);
    return one;
}

template <class T>
Matrix<T> Matrix<T>::id(int n) {
    // take 1 as the identity element...
    Matrix out = zeros(n, n);
    loop_diag(out, [&] (int d) {
        out(d, d) = 1;
    });

    return out;
}

// template <class T>
// Matrix<T> Matrix<T>::id(int m, int n) {

// }

template <class T>
Matrix<T> Matrix<T>::i(int n) {
    // take 1 as the identity element...
    Matrix out = Matrix<T>::zeros(n, n);
    out.loop_i([&] (int i) {
        out(i) = i;
    });

    return out;
}

template <class T>
Matrix<T> Matrix<T>::i(int m, int n) {
    // take 1 as the identity element...
    Matrix out = Matrix<T>::zeros(m, n);
    out.loop_i([&] (int i) {
        out(i) = i;
    });

    return out;
}

template <class T>
Matrix<T> Matrix<T>::ij(int n) {
    Matrix out(n, n);
    out.loop_ij([&] (int i, int j) {
        out(i, j) = i + j - 1;
    });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::ij(int m, int n) {
    Matrix out(m, n);
    out.loop_ij([&] (int i, int j) {
        out(i, j) = i + j - 1;
    });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::hilbert(int n) {
    Matrix out = Matrix::ij(n, n);
    out.loop_i([&] (int i) {
        out(i) = 1 / out(i);
    });
    return out;
}

/**========================================================================
 *!                           Transformations
 *========================================================================**/
template <class T>
Matrix<T>& Matrix<T>::reshape(std::tuple<int, int> ind) {

    // verify that the first times the second is legitimate
    if (std::get<0>(ind) * std::get<1>(ind) != this->size()) {
        std::cerr << "Sizes not compatible for reshaping. Aborting.\n";
        return *this;
    }

    this->m = std::get<0>(ind);
    this->n = std::get<1>(ind);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::reshape(int m, int n) {

    // verify that the first times the second is legitimate
    if (m * n != this->size()) {
        std::cerr << "Sizes not compatible for reshaping. Aborting.\n";
        return *this;
    }

    this->m = m;
    this->n = n;

    return *this;
}


template <class T>
Matrix<T>& Matrix<T>::reshape_row() {
    this->reshape(1, this->size());
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::reshape_col() {
    this->reshape(this->size(), 1);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::reshape_vec() {
    this->reshape_col();
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::nullify() {
    this->m = 0;
    this->n = 0;
    this->data = nullptr;
    return *this;
}

// template <class T>
// Matrix<T>& Matrix<T>::nullify() {
//     return this->to_null();
// }

template <class T>
Matrix<T> Matrix<T>::as_vector() {
    Matrix out{*this}; // copy this matrix
    out.to_vec();
}

template <class T>
Matrix<T> Matrix<T>::as_colvec() {
    Matrix out{*this}; // copy this matrix
    out.to_col();
}

template <class T>
Matrix<T> Matrix<T>::as_rowvec() {
    Matrix out{*this}; // copy this matrix
    out.to_row();
}

template <class T>
std::vector<T> Matrix<T>::to_vector() {
    std::vector<T> out (this->size());
    this->loop_i([&] (int i) {
        out[i - 1] = this->operator()(i);
    });
    return out;
}

template <class T>
template <class U>
Matrix<T> Matrix<T>::from(const std::vector<U>& vec) {
    int n = vec.size();
    Matrix out {1, n};
    int i = 1;
    for (auto el : vec) {
        out(i) = el;
        i++;
    }
    return out;
}






/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/
template <class T>
bool Matrix<T>::is_square() const {
    return this->m == this->n;
}

// Eventual I should just have a parent class that is a vector
template <class T>
bool Matrix<T>::is_vector() const {
    return this->m == 1 || this->n == 1;
}

template <class T>
bool Matrix<T>::is_colvec() const {
    return this->n == 1;
}

template <class T>
bool Matrix<T>::is_rowvec() const {
    return this->m == 1;
}

template <class T>
bool Matrix<T>::is_null() const {
    return this->data == nullptr;
}

template <class T>
bool Matrix<T>::can_mult_b(const Matrix &rhs) const {
    return this->n == rhs.m;
}

template <class T>
bool Matrix<T>::cant_mult_b(const Matrix &rhs) const {
    return !(this->can_mult_b(rhs));
}

template <class T>
template <class U>
bool Matrix<T>::is_same_size(const Matrix<U> &rhs) const {
    return this->size() == rhs.size();
}

template <class T>
template <class U>
bool Matrix<T>::isnt_same_size(const Matrix<U> &rhs) const {
    return !this->is_same_size(rhs);
}

template <class T>
template <class U>
bool Matrix<T>::is_same_shape(const Matrix<U> &rhs) const {
    return this->m == rhs.m && this->n == rhs.n;
}

template <class T>
template <class U>
bool Matrix<T>::isnt_same_shape(const Matrix<U> &rhs) const {
    return !this->is_same_shape(rhs);
}

template <class T>
bool Matrix<T>::can_add_b(const Matrix &rhs) const {
    return this->is_same_shape(rhs);
}

template <class T>
bool Matrix<T>::cant_add_b(const Matrix &rhs) const {
    return !(this->is_same_shape(rhs));
}

template <class T>
Matrix<T> Matrix<T>::get_row(int i) const {
    Matrix row_i {this->m};

}

// template <class T>
// bool Matrix<T>::is_diagonally_dominant() const {

//     // Iterate along the rows
//     for (int i = 1; i <= this->m; i++) {

//         if ()

//     }

//     return true;

// }

// template <class T>
// using ScalarFn = T (* ) (T);

// functions


/**========================================================================
 *!                           Functional style things
 *========================================================================**/

namespace std {
    double power(double __x, double __y) {
        return pow(__x, __y);
    }
}


/**========================================================================
 *!                           Statistics functions
 *========================================================================**/


/**========================================================================
 *!                           Looping functions
 *========================================================================**/
template <class T>
Matrix<T>& Matrix<T>::loop(std::function<T(T)> f) {
    for (int i = 1; i <= this->size(); i++) {
        this->at(i) = f(this->at(i));
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::loop_i(std::function<T(int)> f) {
    for (int i = 1; i <= this->size(); i++) {
        this->at(i) = f(i);
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::loop_ij(std::function<T(int, int)> f) {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            this->at(i, j) = f(i, j);
        }
    }
    return *this;
}

template <class T>
const Matrix<T>& Matrix<T>::loop(std::function<void(T)> f) const {
    for (int i = 1; i <= this->size(); i++) {
        f(this->at(i));
    }
    return *this;
}

template <class T>
const Matrix<T>& Matrix<T>::loop_i(std::function<void(int)> f) const {
    for (int i = 1; i <= this->size(); i++) {
        f(i);
    }
    return *this;
}

// No more mutations
template <class T>
const Matrix<T>& Matrix<T>::loop_ij(std::function<void(int, int)> f) const {
    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            f(i, j);
        }
    }
    return *this;
}


/**========================================================================
 *!                           Ejovo interface
 *========================================================================**/
template <class T>
Matrix<T> Matrix<T>::map(std::function<T(T)> f) const {
    return ejovo::map(*this, f);
}

template <class T>
template <class U>
Matrix<U> Matrix<T>::map(std::function<U(T)> f) const {
    Matrix<U> out (this->m, this->n);
    out.loop_i([&] (int i) {
        out(i) = f(this->operator()(i));
    });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::accumulate(std::function<T(const T&, const T&)> bin_op, T init) const {
    Matrix<T> out (1, this->size());
    out(1) = this->operator()(1);
    for (int i = 2; i <= out.size(); i++) {
        out(i) = bin_op(out(i - 1), this->operator()(i));
    }
    return out;
}

// ternary operator of the for ter_op(lhs, rhs, i)
template <class T>
Matrix<T> Matrix<T>::accumulate(std::function<T(const T&, const T&, int)> ter_op, T init) const {
    Matrix<T> out (1, this->size());
    out(1) = this->operator()(1);
    for (int i = 2; i <= out.size(); i++) {
        out(i) = ter_op(out(i - 1), this->operator()(i), i);
    }
    return out;
}

template <class T>
Matrix<T> Matrix<T>::cumavg() const {
    return this->accumulate([&] (T prev, T next, int i) {
        return ((prev * (i - 1)) + next) / i;
    });
}

template <class T>
Matrix<T> Matrix<T>::cumsum() const {
    return this->accumulate(ejovo::plus<T, T>);
}

template <class T>
Matrix<T> Matrix<T>::cummax() const {
    return this->accumulate(ejovo::scalar::max<T>);
}

template <class T>
Matrix<T> Matrix<T>::cummin() const {
    return this->accumulate(ejovo::scalar::min<T>);
}

template <class T>
Matrix<T> Matrix<T>::filter(std::function<bool(T)> predicate) const {
    return ejovo::filter(*this, predicate);
}

template <class T>
Matrix<T> Matrix<T>::map_if(std::function<T(T)> f, std::function<bool(T)> predicate) const {
    return this.filter(predicate).map(f);
}

template <class T>
Matrix<T>& Matrix<T>::mutate(std::function<T(T)> f) {
    return ejovo::mutate(*this, f);
}

template <class T>
Matrix<T>& Matrix<T>::mutate_if(std::function<T(T)> f, std::function<bool(T)> predicate) {
    // loop through the whole matrix, element-wise
    this->loop([&] (T x) {
        if (predicate(x)) return f(x);
        else return x;
    });
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::fill_if(T val, std::function<bool(T)> predicate) {
    this->loop([&] (T x) {
        if (predicate(x)) return val;
        else return x;
    });
    return *this;
}

template <class T>
T Matrix<T>::reduce(std::function<T(T, T)> f, T init) const {
    return ejovo::reduce(*this, f, init);
}

template <>
template <>
int Matrix<bool>::sum() const {
    int sum = 0;
    this->loop([&] (auto x) {
        if (x) sum ++;
    });
    return sum;
}

template <class T>
template <class U>
U Matrix<T>::sum() const = delete;

template <class T>
T Matrix<T>::sum() const {
    return ejovo::sum(*this);
}

template <class T>
int Matrix<T>::count() const {
    int cnt = 0;
    this->loop([&] (auto x) {
        if (x) cnt ++;
    });
    return cnt;
}

template <class T>
int Matrix<T>::count(std::function<bool(T)> pred) const {
    int cnt = 0;
    this->loop([&] (auto x) {
        if (pred(x)) cnt ++;
    });
    return cnt;
}

template <class T>
bool Matrix<T>::any() const {
    for (int i = 1; i <= this->size(); i++) {
        if (this->operator()(i)) return true;
    }
    return false;
}

template <class T>
bool Matrix<T>::any(std::function<bool(T)> pred) const {
    for (int i = 1; i <= this->size(); i++) {
        if (pred(this->operator()(i))) return true;
    }
    return false;
}

template <class T>
bool Matrix<T>::all() const {
    for (int i = 1; i <= this->size(); i++) {
        if (! (this->operator()(i))) return false;
    }
    return true;
}

template <class T>
bool Matrix<T>::all(std::function<bool(T)> pred) const {
    for (int i = 1; i <= this->size(); i++) {
        if (!pred(this->operator()(i))) return false; //
    }
    return true;
}

template <class T>
T Matrix<T>::sum_abs() const {
    T abs_sum = 0;
    this->loop([&] (T x) {
        abs_sum += ejovo::abs(x);
    });
    return abs_sum;
}

template <class T>
T Matrix<T>::mean() const {
    return ejovo::mean(*this);
}

template <class T>
T Matrix<T>::prod() const {
    return ejovo::prod(*this);
}

template <class T>
T Matrix<T>::min() const {
    return ejovo::min(*this);
}

template <class T>
T Matrix<T>::max() const {
    return ejovo::max(*this);
}

template <class T>
T Matrix<T>::sd(bool population) const {
    return ejovo::sd(*this, population);
}

template <class T>
T Matrix<T>::var(bool population) const {
    return ejovo::var(*this, population);
}

template <class T>
Matrix<T> Matrix<T>::sqrt() const {
    return this->map([&] (auto x) {
        return std::sqrt(x);
    });
}

template <class T>
Matrix<T> Matrix<T>::cbrt() const {
    return this->map([&] (auto x) {
        return ejovo::kthRoot(x, 3);
    });
}

template<class T>
Matrix<T> Matrix<T>::pow(int k) const {
    return this->map([&] (auto x) {
        return std::pow(x, k);
    });
}

template<class T>
Matrix<T> Matrix<T>::sqrd() const {
    return this->pow(2);
}

template <class T>
Matrix<T> Matrix<T>::filter_lt(T val) const {
    return this->filter([&] (T x) {
        return x < val;
    });
}

template <class T>
Matrix<T> Matrix<T>::filter_leq(T val) const {
    return this->filter([&] (T x) {
        return x <= val;
    });
}

template <class T>
Matrix<T> Matrix<T>::filter_gt(T val) const {
    return this->filter([&] (T x) {
        return x > val;
    });
}

template <class T>
Matrix<T> Matrix<T>::filter_geq(T val) const {
    return this->filter([&] (T x) {
        x >= val;
    });
}

template <class T>
T Matrix<T>::pnorm(int p) const {
    return ejovo::kthRoot(this->pow(p).sum(), p);
}

template <class T>
T Matrix<T>::norm() const {
    return this->pnorm(2);
}

template <class T>
Matrix<T> Matrix<T>::clone() const {
    Matrix out {*this}; // copy constructor
    return out;
}

template <class T>
Matrix<bool> Matrix<T>::test(std::function<bool(T)> pred) const {

    auto logical = Matrix<bool>::zeros(this->m, this->n);
    logical.loop_i([&] (int i) {
        return pred(this->at(i));
    });

    return logical;
}




// template <class T>
// Matrix<T> Matrix<T>::map(std::function<T(T)> f) const {
//     return ejovo::map(this*, f);
// }

// template <class T>
// Matrix<T> Matrix<T>::map(std::function<T(T)> f) const {
//     return ejovo::map(this*, f);
// }



/**========================================================================
 *!                           View functions
 *========================================================================**/
template <class T>
typename Matrix<T>::MatView Matrix<T>::view_row(int i) {
    MatView v{*this, Matrix<int>::val(1, 1, i), ejovo::seq(this->n)};
    return v;
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::view_col(int j) {
    MatView v{*this, ejovo::seq(this->n), Matrix<int>::val(1, 1, j)};
    return v;
}


/**========================================================================
 *!                           Logical indexing type functions
 *========================================================================**/
template<>
Matrix<bool> Matrix<bool>::operator!() const {
    return this->map([&] (bool b) {
        return !b;
    });
}

// Add a binary COMPARISON that returns a bool no matter what T is.
// Map the elements of this to the binop(this, k)
template <class T>
Matrix<bool> Matrix<T>::binop_k(std::function<bool(T, T)> binop, const T& k) const {
    // Create a bool matrix that is the same size
    Matrix<bool> logical {this->m, this->n};

    logical.loop_i([&] (int i) {
        logical(i) = binop(this->at(i), k);
    });

    return logical;
}

template <class T>
Matrix<bool> Matrix<T>::operator<(const T& rhs) const {
    return this->binop_k(ejovo::lt<T>, rhs);
}

template <class T>
Matrix<bool> Matrix<T>::operator<=(const T& rhs) const {
    return this->binop_k(ejovo::leq<T>, rhs);
}

template <class T>
Matrix<bool> Matrix<T>::operator>(const T& rhs) const {
    return this->binop_k(ejovo::gt<T>, rhs);
}

template <class T>
Matrix<bool> Matrix<T>::operator>=(const T& rhs) const {
    return this->binop_k(ejovo::geq<T>, rhs);
}

template <class T>
Matrix<bool> Matrix<T>::operator==(const T& rhs) const {
    return this->binop_k(ejovo::eq<T>, rhs);
}

template <>
Matrix<int> Matrix<bool>::which() const {

    int count = 0;
    this->loop_i([&] (int i) {
        if (this->at(i)) count++;
    });

    Matrix<int> out {1, count};

    int out_i = 1;
    this->loop_i([&] (int i) {
        if (this->at(i)) {
            out(out_i) = i;
            out_i ++;
        }
    });

    return out;
}

// where returns a mask visually showing where the elements are true
template<class T>
Matrix<bool> Matrix<T>::where(std::function<bool(T)> pred) const {
    Matrix<bool> out {this->m, this->n};
    out.loop_i([&] (int i) {
        out(i) = pred(this->operator()(i));
    });
    return out;
}

// return the VECTOR indices where the mask is TRUE
template <class T>
Matrix<int> Matrix<T>::which(const Matrix<bool>& mask) const{
    // make one pass to count how many are true.
    // Check to make sure that the mask has the same shape
    if (this->isnt_same_shape(mask)) return Matrix<int>::null();

    return mask.which();
}

// return the VECTOR indices where the mask is TRUE
template <class T>
Matrix<int> Matrix<T>::which(std::function<bool(T)> pred) const{
    return this->where(pred).which();
}



template <class T>
typename Matrix<T>::VecView Matrix<T>::operator()(const Matrix<bool>& mask) {
    // When given a mask, create a new BoolView.
    VecView out{*this, mask};
    return out;
}

template <class T>
typename Matrix<T>::VecView Matrix<T>::operator[](const Matrix<bool>& mask) {
    // When given a mask, create a new BoolView.
    VecView out{*this, mask};
    return out;
}



// template <class T>
// typename Mat


/**========================================================================
 *!                           Class Template Type Members
 *========================================================================**/
/**======================
 *!    Constructors
 *========================**/
template <class T>
Matrix<T>::BoolView::BoolView(Matrix<T>& mat)
    : m{mat.m}
    , n{mat.n}
    , true_ind{ejovo::seq<int>(mat.size())}
    , mat{mat}
{};

template <class T>
Matrix<T>::BoolView::BoolView(Matrix<T>& mat, const Matrix<bool> mask)
    : m{mat.m}
    , n{mat.n}
    , true_ind{mat.which(mask)}
    , mat{mat}
{};

template <class T>
Matrix<T>::BoolView::BoolView(Matrix<T>& mat, const Matrix<int> true_ind)
    : m{mat.m}
    , n{mat.n}
    , true_ind{true_ind}
    , mat{mat}
{};

template <class T>
typename Matrix<T>::BoolView& Matrix<T>::BoolView::loop_i(std::function<void(int)> f) {
    this->true_ind.loop_i(f);
    return *this;
}

template <class T>
T& Matrix<T>::BoolView::operator()(int i) {
    return mat(true_ind(i));
}

template <class T>
T& Matrix<T>::BoolView::at(int i) {
    return mat(true_ind(i));
}

template <class T>
typename Matrix<T>::BoolView& Matrix<T>::BoolView::operator=(T val) {
    std::cerr << "Called BoolView operator=\n";
    this->loop_i([&] (int i) {
        this->at(i) = val;
    });
    return *this;
}
// TODO validate the indices of the submatrix
template <class T>
typename Matrix<T>::MatView Matrix<T>::submat(const Matrix<int>& row_ind, const Matrix<int>& col_ind) {
    return this->operator()(row_ind, col_ind);
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::submat(int ib, int ie, int jb, int je) {
    return this->operator()(ejovo::seq<int>(ib, ie), ejovo::seq<int>(jb, je));
}

// A({1, 3}, {1, 4}) === A(1:3, 1:4)
template <class T>
typename Matrix<T>::MatView Matrix<T>::submat(std::initializer_list<int> list_1, std::initializer_list<int> list_2) {
    return this->operator()(Matrix<int>::from(list_1), Matrix<int>::from(list_2));
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::submat(std::initializer_list<int> list, const Matrix<int>& col_ind) {
    return this->operator()(Matrix<int>::from(list), col_ind);
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::submat(const Matrix<int>& row_ind, std::initializer_list<int> list) {
    return this->operator()(row_ind, Matrix<int>::from(list));
}


// A.rows(1, 4) === A(1:4,:)
template <class T>
typename Matrix<T>::MatView Matrix<T>::rows(int ib, int ie) {
    return this->submat(ib, ie, 1, this->n);
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::rows(std::initializer_list<int> list, int from) {
    return this->submat(Matrix<int>::from(list), ejovo::seq<int>(from, this->n));
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::rows(int ib) {
    return this->rows(ib, ib);
}

// A.cols (1, 3) == A(:, 1:3)

template <class T>
typename Matrix<T>::MatView Matrix<T>::cols(int jb, int je) {
    return this->submat(1, this->m, jb, je);
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::cols(int jb) {
    return this->cols(jb, jb);
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::cols(std::initializer_list<int> list) {
    return this->submat(ejovo::seq<int>(1, this->m), Matrix<int>::from(list));
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::block(int i, int j, int m, int n) {
    return this->submat(i, i + m - 1, j, j + n - 1);
}


// template <class T>
// typename Matrix<T>::BoolView

template <class T>
std::tuple<Matrix<T>, Matrix<T>> Matrix<T>::lu() const {

    // let's only accept square matrices....
    if (!this->is_square()) return std::make_tuple(Matrix<T>::null(), Matrix<T>::null());

    Matrix L = Matrix<T>::id(this->m);
    Matrix U = this->clone();

    for (int j = 1; j < L.n; j++) {
        for (int i = j + 1; i <= L.m; i++) {

            T scalar = U(i, j) / U(j, j);
            U.rows({i}, j) = U.rows({i}, j) - scalar * U.rows({j}, j);
            L(i, j) = scalar;

        }
    }

    return std::make_tuple<Matrix<T>, Matrix<T>>(std::move(L), std::move(U));

}

template <class T>
Matrix<T>& Matrix<T>::swap(int ai, int bi) {
    T temp = this->at(ai);
    this->at(ai) = this->at(bi);
    this->at(bi) = temp;
    return *this;
}

/**========================================================================
 *!                           RowView stuff
 *========================================================================**/
template <class T>
typename Matrix<T>::RowView Matrix<T>::get_row_view(int i) {
    RowView rv {*this, i};
    return rv;
}

template <class T>
typename Matrix<T>::ColView Matrix<T>::get_col_view(int j) {
    ColView cv {*this, j};
    return cv;
}