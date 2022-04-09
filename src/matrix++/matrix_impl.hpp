
#pragma once

#include "ejovo.hpp"
#include "view.hpp"

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
    std::cerr << "Performing copy assignment\n";
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
View<T> Matrix<T>::operator()(const Matrix<int>& row_ind, const Matrix<int>& col_ind) {
    View<T> v{*this, row_ind, col_ind};
    return v;
}

template <class T>
View<T> Matrix<T>::operator()(int i, const Matrix<int>& col_ind) {
    View<T> v{*this, Matrix<int>::val(1, 1, i), col_ind};
    return v;
}

template <class T>
View<T> Matrix<T>::operator()(const Matrix<int>& row_ind, int j) {
    View<T> v{*this, row_ind, Matrix<int>::val(1, 1, j)};
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
void Matrix<T>::print() const {

    std::cout << this->m << " x " << this->n << " matrix\n";

    for (int i = 1; i <= this->m; i++) {
        std::cout << "|";

        for (int j = 1; j < this->n; j++) {
            std::cout << this->operator()(i, j) << ", ";
        }

        std::cout << this->operator()(i, this->n) << "|\n";
    }
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

    if (this->cantAddB(rhs)) {
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

    if (this->cantAddB(rhs)) {
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

        View<T> block{out, ejovo::seq<int>(i, i + rhs.m - 1), ejovo::seq<int>(j, j + rhs.n - 1)}; // construct the block view
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

    if (this->cantMultB(rhs)) {
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
Matrix<T>& Matrix<T>::to_row() {
    this->reshape(1, this->size());
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::to_col() {
    this->reshape(this->size(), 1);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::to_vec() {
    this->to_col();
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::to_null() {
    this->m = 0;
    this->n = 0;
    this->data = nullptr;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::nullify() {
    return this->to_null();
}

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
bool Matrix<T>::canMultB(const Matrix &rhs) const {
    return this->n == rhs.m;
}

template <class T>
bool Matrix<T>::cantMultB(const Matrix &rhs) const {
    return !(this->canMultB(rhs));
}

template <class T>
bool Matrix<T>::isSameSize(const Matrix &rhs) const {
    return this->m == rhs.m && this->n == rhs.n;
}

template <class T>
bool Matrix<T>::canAddB(const Matrix &rhs) const {
    return this->isSameSize(rhs);
}

template <class T>
bool Matrix<T>::cantAddB(const Matrix &rhs) const {
    return !(this->isSameSize(rhs));
}

template <class T>
Matrix<T> Matrix<T>::get_row(int i) const {
    Matrix row_i {this->m};

}

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

template <class T>
T Matrix<T>::sum() const {
    return ejovo::sum(*this);
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
View<T> Matrix<T>::view_row(int i) {
    View<T> v{*this, Matrix<int>::val(1, 1, i), ejovo::seq(this->n)};
    return v;
}

template <class T>
View<T> Matrix<T>::view_col(int j) {
    View<T> v{*this, ejovo::seq(this->n), Matrix<int>::val(1, 1, j)};
    return v;
}
