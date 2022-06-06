#pragma once

#include "declarations/Matrix.hpp"

// #include "ejovo/rng/Xoshiro.hpp"
#include "ejovo/rng/rng.hpp"
#include "ejovo/core.hpp"

namespace ejovo {

template <class T>
std::size_t Matrix<T>::nrow() const {
    return this->m;
}

template <class T>
std::size_t Matrix<T>::ncol() const {
    return this->n;
}

/**========================================================================
 *!                           Trigonometric functions
 *========================================================================**/

// I could always have a namespace name that corresponds to a typeclass



/**========================================================================
 *!                           Constructors
 *========================================================================**/
template <class T> Matrix<T>::Matrix()
    : m{0}
    , n{0}
    , data{nullptr}
{}

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

template <class T> Matrix<T>::Matrix(const Vector<T>& rhs) {
    if (rhs.col) {
        this->m = rhs.size();
        this->n = 1;
    } else {
        this->m = 1;
        this->n = rhs.size();
    }
    this->data = rhs.copy_data();
}

template <class T> Matrix<T>::Matrix(Vector<T>&& rhs) {
    if (rhs.col) {
        this->m = rhs.size();
        this->n = 1;
    } else {
        this->m = 1;
        this->n = rhs.size();
    }
    this->data = std::move(rhs.data);

    rhs.reset();
}

template <class T>
Matrix<T> Matrix<T>::from(std::initializer_list<T> list, bool by_row) {
    int n = list.size();
    Matrix<T> out{1, n};
    int i = 1;

    if (by_row) {

        for (auto el : list) {
            out.at_row_major(i) = el;
            i++;
        }

    } else {

        for (auto el : list) {
            out.at_col_major(i) = el;
            i++;
        }
    }

    return out;
}

template <class T>
Matrix<T> Matrix<T>::from(std::initializer_list<T> list, int m, int n, bool by_row) {
    int n_el = list.size();
    Matrix<T> out;

    if (n_el == m * n) {
        out = Matrix<T>::zeros(m, n);
    } else {
        out = Matrix<T>::zeros(1, n_el);
    }

    int i = 1;

    if (by_row) {

        for (auto el : list) {
            out.at_row_major(i) = el;
            i++;
        }

    } else {

        for (auto el : list) {
            out.at_col_major(i) = el;
            i++;
        }
    }
    return out;
}

/**========================================================================
 *!                           Random Matrices
 *========================================================================**/
// template <class T>
// ejovo::rng::Xoshiro& Matrix<T>::xoroshiro = ejovo::rng::g_XOSHIRO;

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

// extract the specified integers
template <class T>
Matrix<T> Matrix<T>::operator()(const Matrix<int>& ind) {
    // Assume all the indices are legitamete
    const int n = this->size();
    // check the bounds
    auto valid_ind = ind.filter([&] (int x) {
        return x >= 1 && x <= n;
    });

    // now extract those valid indices
    Matrix<T> out (valid_ind.size()); // create a mutable Matrix

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
const Matrix<T>& Matrix<T>::summary() const {

    if (this->size() == 0) {
        std::cerr << "Empty matrix trying to call Matrix<T>::print_lin()";
        return *this;
    }

    // Check if this is a matrix, a column vector, or a row vector..
    if (this->is_col()) {
        std::cout << "Column vector with n: " << this->size() << "\n";
        std::cout << "Euclidean norm: ";
    } else if (this->is_row()) {
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
T Matrix<T>::dot(const Matrix& rhs, int i, int j) const {
    // we are assuming that the sizes are legit
    T total = 0;
    for (int k = 1; k <= this->n; k++) {
        total += (this->at(i, k) * rhs(k, j));
    }
    return total;
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

// Matrix multiplication!!!
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix&rhs) const {

    if (this->cant_mult(rhs)) {
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
Matrix<T> Matrix<T>::operator^(int k) const {

    if (!this->is_square()) throw "Cannot take the power of non square matrix";
    if (k < 0) return Matrix<T>::null();
    if (k == 0) return Matrix<T>::id(n);
    if (k == 1) return *this;

    Matrix<T> out (*this);

    for (int i = 2; i <= k; i++) {
        out = out * *this;
    }

    return out;
}

template <class T> Matrix<T>::Matrix(Matrix&& rhs) : m{rhs.m}, n{rhs.n} {

    this->data = std::move(rhs.data);
    this->m = rhs.m;
    this->n = rhs.n;

    rhs.data = nullptr;
    rhs.m = 0;
    rhs.n = 0;
}

// template <class T> Matrix<T>::Matrix(const Vector<T>& rhs) : m{rhs.m}, n{rhs.n} {

//     this->data = std::move(rhs.data);
//     this->m = rhs.m;
//     this->n = rhs.n;

//     rhs.data = nullptr;
//     rhs.m = 0;
//     rhs.n = 0;
// }

/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/




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
    Matrix zero (mat.m, mat.n);
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
    out.loop_diag([&] (auto& d) {
        d = 1;
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

template <class T>
Matrix<T> Matrix<T>::as_vector() const {
    Matrix out{*this}; // copy this matrix
    out.reshape_vec();
    return out;
}

template <class T>
Matrix<T> Matrix<T>::as_colvec() const {
    Matrix out{*this}; // copy this matrix
    out.reshape_col();
    return out;
}

template <class T>
Matrix<T> Matrix<T>::as_rowvec() const {
    Matrix out{*this}; // copy this matrix
    out.reshape_row();
    return out;
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
Matrix<T> Matrix<T>::from(const std::vector<U>& vec, bool by_row) {
    int n = vec.size();
    Matrix out {1, n};
    int i = 1;

    if (by_row) {

        for (auto el : vec) {
            out.at_row_major(i) = el;
            i++;
        }

    } else {

        for (auto el : vec) {
            out.at_col_major(i) = el;
            i++;
        }
    }

    return out;
}

/**========================================================================
 *!                           Inquiry functions
 *========================================================================**/
template <class T>
bool Matrix<T>::is_null() const {
    return this->data == nullptr;
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
    Matrix row_i (1, this->m);

    for (int j = 1; j <= this->m; j++) {
        row_i(j) = this->operator()(i, j);
    }

    return row_i;
}

/**========================================================================
 *!                           Ejovo interface
 *========================================================================**/
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

// template <class T>
// Matrix<T> Matrix<T>::filter_lt(T val) const {
//     return this->filter([&] (T x) {
//         return x < val;
//     });
// }

// template <class T>
// Matrix<T> Matrix<T>::filter_leq(T val) const {
//     return this->filter([&] (T x) {
//         return x <= val;
//     });
// }

// template <class T>
// Matrix<T> Matrix<T>::filter_gt(T val) const {
//     return this->filter([&] (T x) {
//         return x > val;
//     });
// }

// template <class T>
// Matrix<T> Matrix<T>::filter_geq(T val) const {
//     return this->filter([&] (T x) {
//         x >= val;
//     });
// }

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


/**========================================================================
 *!                           View functions
 *========================================================================**/
template <class T>
typename Matrix<T>::MatView Matrix<T>::view_row(int i) {
    MatView v (*this, Matrix<int>::val(1, 1, i), ejovo::seq<int>(this->n));
    return v;
}

template <class T>
typename Matrix<T>::MatView Matrix<T>::view_col(int j) {
    MatView v (*this, ejovo::seq<int>(this->n), Matrix<int>::val(1, 1, j));
    return v;
}

template <class X>
typename Matrix<X>::VecView Matrix<X>::vecview(const Matrix<bool>& mask) {
    VecView v(*this, mask);
    return v;
}

template <class X>
typename Matrix<X>::VecView Matrix<X>::vecview(const Matrix<int>& ind) {
    VecView v(*this, ind);
    return v;
}

template <class X>
typename Matrix<X>::VecView Matrix<X>::vecview(std::function<bool(X)> pred) {
    VecView v(*this, this->where(pred));
    return v;
}


/**========================================================================
 *!                           Random functions
 *========================================================================**/
template <class T>
Matrix<T> Matrix<T>::rand() {
    return Matrix<T>::rand(10, 0.0, 1.0);
}

template <class T>
Matrix<T> Matrix<T>::rand(int n, double min, double max) {
    Matrix out (1, n);
    out.loop_i([&] (int i) { out(i) = ejovo::rng::g_XOSHIRO.unifd(min, max); });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::rand(int m, int n,  double min, double max) {
    Matrix out (m, n);
    out.loop_i([&] (int i) { out(i) = ejovo::rng::g_XOSHIRO.unifd(min, max); });
    return out;
}

template <class T>
Matrix<T> Matrix<T>::rand(int m, int n) {
    return Matrix<T>::rand(m * n).reshape(m, n);
}

// template <class T>
// Matrix<T> rand(int m, int n, double min, double max) {

// }


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

// template <class T>
// Matrix<bool> Matrix<T>::operator==(const T& rhs) const {
//     return this->binop_k(ejovo::eq<T>, rhs);
// }

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

/**========================================================================
 *!                           RowView stuff
 *========================================================================**/
template <class T>
typename Matrix<T>::RowView Matrix<T>::get_row_view(int i) {
    RowView rv {*this, i};
    return rv;
}

template <class T>
typename Matrix<T>::RowView Matrix<T>::get_row_view(int i, int jb) {
    RowView rv (*this, i, jb);
    return rv;
}

template <class T>
typename Matrix<T>::RowView Matrix<T>::get_row_view(int i, int jb, int je) {
    RowView rv (*this, i, jb, je);
    return rv;
}



template <class T>
typename Matrix<T>::ColView Matrix<T>::get_col_view(int j) {
    ColView cv {*this, j};
    return cv;
}

template <class T>
typename Matrix<T>::ColView Matrix<T>::get_col_view(int j, int ib) {
    ColView cv (*this, j, ib);
    return cv;
}

template <class T>
typename Matrix<T>::ColView Matrix<T>::get_col_view(int j, int ib, int ie) {
    ColView cv (*this, j, ib, ie);
    return cv;
}

};