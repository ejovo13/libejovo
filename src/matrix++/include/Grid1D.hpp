#pragma once

#include <iostream>
#include <functional>
#include <cmath>

// Abstract class to implement the common behavior that is associated with a 1 dimensional vector
namespace ejovo {

    // Simple namespace to capture NAMED binary functions
    namespace binop {

        template <class X, class Y>
        X plus(const X& x, const Y& y) {
            return x + y;
        }

        template <class X, class Y>
        X plus_abs(const X& x, const Y& y) {
            return x + abs(y);
        }

        template <class X, class Y>
        X minus(const X& x, const Y& y) {
            return x - y;
        }

        template <class X, class Y>
        X times(const X& x, const Y& y) {
            return x * y;
        }

        template <class X, class Y>
        X divided_by(const X& x, const Y& y) {
            return x / y;
        }

        template <class X>
        X min(const X& a, const X& b) {
            return a < b ? a : b;
        }

        template <class X>
        X max(const X& a, const X& b) {
            return a > b ? a : b;
        }

    };

    double log_base(double base, double x) {
        return (std::log(x) / std::log(base));
    }

    double kthRoot(double n, int k) {
        return std::pow(k, (1.0 / k) * (log_base(k, n)));
    }


template <class T>
class Grid1D {

public:

    using predicate = std::function<bool(T)>;
    using binary_op = std::function<T(T, T)>;
    using unary_op = std::function<T(const T&)>;
    using loop_fn = std::function<void(T&)>; // Used to succinctly modify the elements that are being accessed
    using loop_fn_const = std::function<void(const T&)>;
    using loop_ind_fn = std::function<void(int)>;
    // using index_op = std::function<T(int)>;

    // virtual Grid1D clone() = 0;

    /**========================================================================
     *!                           Virtual Functions
     *========================================================================**/
    virtual T& operator[](int i) = 0; // 0-based indexing
    virtual T& operator()(int i) = 0; // 1-based indexing M(1) is the first element
    virtual T& at(int i) = 0;         // 1-based indexing with bounds checking

    const virtual T& operator[](int i) const = 0;
    const virtual T& operator()(int i) const = 0;
    const virtual T& at(int i) const = 0; // at actually goes ahead and verifies whether or not the bounds are legit
    virtual std::size_t size() const = 0;

    /**========================================================================
     *!                           First, Last
     *========================================================================**/
    T& first();
    T& last();

    const T& first() const;
    const T& last() const;


    /**========================================================================
     *!                           Inquiry Functions
     *========================================================================**/
    bool is_same_size(const Grid1D& rhs) const;
    bool isnt_same_size(const Grid1D& rhs) const;
    bool is_valid_bound(int i) const; // Check if i is a valid 1-based indexing bound.

    /**========================================================================
     *!                           Assignment Overloading
     *========================================================================**/
    Grid1D& operator=(const Grid1D& rhs);

    /**========================================================================
     *!                           Mutating functions
     *========================================================================**/
    Grid1D& fill(const T& value);
    Grid1D& fill_if(const T& value, predicate pred);
    Grid1D& mutate(unary_op f);
    Grid1D& mutate_if(unary_op f, predicate pred);

    /**========================================================================
     *!                           Looping Functions
     *========================================================================**/
    Grid1D& loop(loop_fn f);
    const Grid1D& loop(loop_fn_const f) const;
    Grid1D& loop_i(loop_ind_fn f);
    Grid1D& swap(int ai, int bi);

    /**========================================================================
     *!                           Printing Functions
     *========================================================================**/
    Grid1D& print();
    Grid1D& print_lin();
    const Grid1D& print() const;
    const Grid1D& print_lin() const;

    /**========================================================================
     *!                           Statistical Routines
     *========================================================================**/
    T reduce(binary_op f, T init = 0) const;
    T sum() const;
    T sum_abs() const;
    T prod() const;
    T mean() const;
    T min() const;
    T max() const;
    T sd(bool population = true) const;
    T var(bool population = true) const;
    T pnorm(int p = 2) const;
    T norm() const;

    /**========================================================================
     *!                           Boolean Functions
     *========================================================================**/
    // template <class U> U sum() const; // Allow a Grid1D<bool> to return an integer for the sum.
    int count() const; // Count the elements of Grid1D<T> that evaluate to true in a boolean expression
    int count(predicate pred) const; // Count number of elements where pred is true
    bool any() const;
    bool any(predicate pred) const;
    bool all() const;
    bool all(predicate pred) const;
    bool none() const;
    bool none(predicate pred) const;

};


/**========================================================================
 *!                           Implementation of Grid1D
 *========================================================================**/
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
bool Grid1D<T>::is_same_size(const Grid1D& rhs) const {
    return this->size() == rhs.size();
}

template <class T>
bool Grid1D<T>::isnt_same_size(const Grid1D& rhs) const {
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
Grid1D<T>& Grid1D<T>::fill(const T& value) {
    this->loop_i([&] (int i) { this->operator()(i) = value; } );
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

    this->print();
    return *this;
}

// TODO print_lin
// TODO abstract Grid1D([1, 2, 3]) functionality to return another Grid1D...

template <class T>
T Grid1D<T>::reduce(binary_op f, T init) const {
    this->loop([&] (auto x) { init = f(init, x); } );
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
    return this->reduce(ejovo::binop::min<T, T>, this->first());
}

template <class T>
T Grid1D<T>::max() const {
    return this->reduce(ejovo::binop::max<T, T>, this->last());
}

template <class T>
T Grid1D<T>::sd(bool population) const {
    return sqrt(this->var(population));
}

template <class T>
T Grid1D<T>::var(bool population) const {

    T mu = this->mean();

    T out = 0;
    this->loop([&] (auto x) {
        const T a = (x - mu);
        out += a * a;
    });

    if (population) return out / (this->size() + 1);
    else return out / this->size();
}

template <class T>
T Grid1D<T>::pnorm(int p) const {

    T p_sum = this->reduce([&] (auto acc, auto x) {
        std::pow(x, p);
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





};
