#pragma once

#include "declarations/Grid1D.hpp"

#include "ejovo/operations.hpp"

namespace ejovo {

/**========================================================================
 *!                           Implementation of Grid1D
 *========================================================================**/
// 1-based indexing without checking bounds
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
template <class U>
bool Grid1D<T>::is_same_size(const Grid1D<U>& rhs) const {
    return this->size() == rhs.size();
}

template <class T>
template <class U>
bool Grid1D<T>::isnt_same_size(const Grid1D<U>& rhs) const {
    return this->size() != rhs.size();
}

template <class T>
bool Grid1D<T>::is_valid_bound(int i) const {
    return (i >= 1 && i <= this->size());
}

template <class T>
Grid1D<T>& Grid1D<T>::operator=(const Grid1D& rhs) {
    // Check if they are the same size
    if (this->isnt_same_size(rhs)) return *this;
    return rhs.loop_i([&] (int i) { this->operator()(i) = rhs(i); } );
}

template <class T>
bool Grid1D<T>::operator==(const Grid1D& rhs) {
    if (this->isnt_same_size(rhs)) return false;
    const std::size_t n = rhs.size();

    for (std::size_t i = 1; i <= n; i++) {
        if (this->operator()(i) != rhs(i)) return false;
    }

    return true;
}

template <class T>
Grid1D<T>& Grid1D<T>::fill(const T& value) {
    return this->loop_i([&] (int i) { this->operator()(i) = value; } );
}

template <class T>
Grid1D<T>& Grid1D<T>::fill_if(const T& value, predicate pred) {
    return this->loop([&] (T& t) { if (pred(t)) t = value; } );
}

template <class T>
Grid1D<T>& Grid1D<T>::mutate(unary_op f) {
    return this->loop([&] (T& t) { t = f(t); });
}

template <class T>
Grid1D<T>& Grid1D<T>::mutate_if(unary_op f, predicate pred) {
    return this->loop([&] (T& t) { if (pred(t)) t = f(t); } );
}

template <class T>
Grid1D<T>& Grid1D<T>::loop(loop_fn f) {
    const std::size_t n = this->size();
    for (std::size_t i = 1; i <= n; i++) {
        f(this->operator()(i));
    }
    return *this;
}

template <class T>
const Grid1D<T>& Grid1D<T>::loop(loop_fn_const f) const {
    const std::size_t n = this->size();
    for (std::size_t i = 1; i <= n; i++) {
        f(this->operator()(i));
    }
    return *this;
}

template <class T>
Grid1D<T>& Grid1D<T>::loop_i(loop_ind_fn f) {
    const std::size_t n = this->size();
    for (std::size_t i = 1; i <= n; i++) {
        f(i);
    }
    return *this;
}

template <class T>
const Grid1D<T>& Grid1D<T>::loop_i(loop_ind_fn f) const {
    const std::size_t n = this->size();
    for (std::size_t i = 1; i <= n; i++) {
        f(i);
    }
    return *this;
}

template <class T>
Grid1D<T>& Grid1D<T>::swap(int ai, int bi) {
    if (this->is_valid_bound(ai) && this->is_valid_bound(bi)) {
        const T& temp = this->operator()(ai);
        this->operator()(ai) = this->operator()(bi);
        this->operator()(bi) = temp;
    }
    return *this;
}

template <class T>
const Grid1D<T>& Grid1D<T>::print() const {

    const std::size_t n = this->size();
    std::cout << "Vector with length: " << n << "\n";

    std::cout << "{";
    for (int i = 1; i < n; i++) {
        std::cout << this->operator()(i) << ", ";
    }
    std::cout << this->last() << "}\n";

    return *this;
}

template <class T>
Grid1D<T>& Grid1D<T>::print() {

    const std::size_t n = this->size();
    std::cout << "Vector with length: " << n << "\n";

    std::cout << "{";
    for (int i = 1; i < n; i++) {
        std::cout << this->operator()(i) << ", ";
    }
    std::cout << this->last() << "}\n";

    return *this;

}

// TODO print_lin
// TODO abstract Grid1D([1, 2, 3]) functionality to return another Grid1D...

template <class T>
T Grid1D<T>::reduce(binary_op f, T init) const {
    this->loop([&] (auto x) { init = f(init, x); } );
    return init;
}

template <class T>
T Grid1D<T>::sum() const {
    return this->reduce(ejovo::binop::plus<T, T>, 0);
}

template <class T>
T Grid1D<T>::sum_abs() const {
    return this->reduce(ejovo::binop::plus_abs<T, T>, 0);
}

template <class T>
T Grid1D<T>::mean() const {
    T sumx = this->sum();
    return sumx / this->size();
}

template <class T>
T Grid1D<T>::prod() const {
    return this->reduce(ejovo::binop::times<T, T>, 1);
}

template <class T>
T Grid1D<T>::min() const {
    return this->reduce(ejovo::binop::min<T>, this->first());
}

template <class T>
T Grid1D<T>::max() const {
    return this->reduce(ejovo::binop::max<T>, this->last());
}

template <class T>
T Grid1D<T>::sd(bool population) const {
    return std::sqrt(this->var(population));
}

template <class T>
T Grid1D<T>::var(bool population) const {

    T mu = this->mean();

    T out = 0;
    this->loop([&] (auto x) {
        const T a = (x - mu);
        out += a * a;
    });

    if (population) return out / (this->size());
    else return out / (this->size() - 1);
}

template <class T>
T Grid1D<T>::pnorm(int p) const {

    T p_sum = this->reduce([&] (T acc, T x) {
        return acc + std::pow(x, p);
    });

    return kthRoot(p_sum, p);
}

template <class T>
T Grid1D<T>::norm() const {
    return this->pnorm(2);
}

template <class T>
int Grid1D<T>::count() const {
    int c = 0;
    this->loop([&] (auto x) { if (x) c++; });
    return c;
}

template <class T>
int Grid1D<T>::count(predicate pred) const {
    int c = 0;
    this->loop([&] (auto x) { if (pred(x)) c++; });
    return c;
}

template <class T>
bool Grid1D<T>::any() const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if (this->operator()(i)) return true;
    }

    return false;
}

template <class T>
bool Grid1D<T>::any(predicate pred) const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if ( pred( this->operator()(i) ) ) return true;
    }

    return false;
}

template <class T>
bool Grid1D<T>::all() const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if (!this->operator()(i)) return false;
    }

    return true;
}

template <class T>
bool Grid1D<T>::all(predicate pred) const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if ( !pred( this->operator()(i) ) ) return false;
    }

    return true;
}

template <class T>
bool Grid1D<T>::none() const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if (this->operator()(i)) return false;
    }

    return true;
}

template <class T>
bool Grid1D<T>::none(predicate pred) const {

    const std::size_t n = this->size();

    for (std::size_t i = 1; i <= n; i++) {
        if ( pred( this->operator()(i) ) ) return false;
    }

    return true;
}

template <class T>
Matrix<T> Grid1D<T>::map(unary_op fn) const {
    auto out = this->to_matrix();
    out.mutate(fn);
    return out;
}

template <class T>
Matrix<T> Grid1D<T>::map_if(unary_op fn, predicate pred) const {
    int c = this->count(pred);

    auto out = this->new_matrix(c);
    out.mutate(fn);

    return out;
}

template <class T>
Matrix<T> Grid1D<T>::filter(predicate pred) const {
    int c = this->count(pred);

    auto out = this->zeros(c, false);
    int out_i = 1;
    this->loop([&] (auto x) {
        if (pred(x)) {
            out(out_i) = x;
            out_i++;
        }
    });
}

template <class T>
Matrix<T> Grid1D<T>::diff() const {

    Matrix<T> out{1, this->size() - 1};
    for (int i = 0; i < out.size(); i++) {
        out[i] = this->operator[](i + 1) - this->operator[](i);
    }
    return out;
}

template <class T>
Matrix<T> Grid1D<T>::midpoints() const {

    Matrix<T> out (1, this->size() - 1);
    out.loop_i([&] (int i) {
        out(i) = (this->operator()(i) + this->operator()(i + 1)) / 2.0;
    });
    return out;
}

template <class T>
Matrix<T> Grid1D<T>::abs() const {
    return this->map(ejovo::abs<T>);
}

template <class T>
Matrix<T> Grid1D<T>::sqrt() const {
    return this->map([&] (auto x) { return std::sqrt(x); } );
}

template <class T>
Matrix<T> Grid1D<T>::cbrt() const {
    // return this->map(ejovo::factory::nroot<T, 3>);
    return this->map([&] (auto x) { return ejovo::kthRoot(x, 3); } );
}

template <class T>
Matrix<T> Grid1D<T>::pow(int k) const {
    return this->map([&] (auto x) { return std::pow(x, k); } );
}

template <class T>
Matrix<T> Grid1D<T>::sqrd() const {
    return this->map([&] (auto x) { return x * x; } );
}

template <class T>
Matrix<T> Grid1D<T>::cubd() const {
    return this->map([&] (auto x) { return x * x * x; } );
}

template <class T>
Matrix<T> Grid1D<T>::normalized(int p) const {
    T nrm = this->pnorm(p);
    return this->map([&] (auto x) { return x / nrm; } );
}

// normalize the elements of the one dimensional array.
template <class T>
Grid1D<T>& Grid1D<T>::normalize(int p) {
    T nrm = this->pnorm(p);
    return this->mutate([&] (auto x) { return x / nrm; } );
}

// this might be able to be taken care of with mem copy?
// or is iterating fine?
template <class T>
Matrix<T> Grid1D<T>::repcol(int n) const {

    Matrix<T> out (this->size(), n);

    out.loop_ij([&] (int i, int j) {
        out(i, j) = this->operator()(i);
    } );

    return out;

}

template <class T>
Matrix<T> Grid1D<T>::reprow(int n) const {

    Matrix<T> out (n, this->size());

    out.loop_ij([&] (int i, int j) {
        out(i, j) = this->operator()(j);
    } );

    return out;

}

template <class T>
T Grid1D<T>::dot(const Grid1D& rhs) const {
    if (this->isnt_same_size(rhs)) throw "Grids are not the same size, unable to dot";
    T total = 0;
    for (int i = 1; i <= this->size(); i++) {
        total += this->operator()(i) * rhs(i);
    }
    return total;
}

template <class T>
T Grid1D<T>::inner_product(const Grid1D& rhs) const {
    return this->dot(rhs);
}

template <class T>
Matrix<T> Grid1D<T>::outer_product(const Grid1D& rhs) const {
    // Treat these as two vectors
    Matrix out{this->size(), rhs.size()};
    out.loop_ij([&] (int i, int j) {
        out(i, j) = (this->at(i)) * (rhs(j));
    });
    return out;
}

template <class T>
Matrix<T> Grid1D<T>::hadamard_product(const Grid1D& rhs) const {
    if (this->isnt_same_size(rhs)) throw "Grids are not the same size, unable to compute the Hadamard product";
    auto out = this->to_matrix();
    out.loop_i([&] (int i) { out(i) *= rhs(i); } );
    return out;
}

template <class T>
Matrix<T> Grid1D<T>::zeros(bool col) const {
    if (col) return Matrix<T>::zeros(this->size(), 1);
    else return Matrix<T>::zeros(1, this->size());
}

template <class T>
Matrix<T> Grid1D<T>::zeros(int n, bool col) const {
    if (col) return Matrix<T>::zeros(n, 1);
    else return Matrix<T>::zeros(1, n);
}




};