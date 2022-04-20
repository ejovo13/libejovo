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

    template <class T> T abs(T x) {
        return x < 0 ? -x : x;
    }

    // namespace unop {

    //     template <class X>
    //     bool pos(const X& x) {
    //         return pos > 0;
    //     }


    // };

    double log_base(double base, double x) {
        return (::std::log(x) / ::std::log(base));
    }

    double kthRoot(double n, int k) {
        return ::std::pow(k, (1.0 / k) * (log_base(k, n)));
    }

    namespace factory {

        // template <class X, int N>
        // std::function<X(X)> mono(const X& x) {
        //     return [&] (auto _x) { return std::pow(_x, N); };
        // }

        template <class T, int K>
        std::function<T(T)> pow(T x) {
            return [&] (T x) {
                return std::pow(x, K);
            };
        }

        template <class T, int N>
        std::function<T(T)> nroot(T x) {
            return [&] (T x) {
                return ejovo::kthRoot(x, N);
            };
        }

        template <class T>
        std::function<bool(T)> NOT(std::function<bool(T)> fn) {
            return [&] (T x) {
                return !fn(x);
            };
        }

        template <class T>
        std::function<bool(T)> AND(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) && b(x);
            };
        }

        template <class T>
        std::function<bool(T)> OR(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) || b(x);
            };
        }

        template <class T>
        std::function<bool(T)> XOR(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) != b(x);
            };
        }

        template <class T>
        std::function<bool(T)> lt(const T& rhs) {
            return [&] (T x) {
                return x < rhs;
            };
        }

        template <class T>
        std::function<bool(T)> gt(const T& rhs) {
            return [&] (T x) {
                return x > rhs;
            };
        }

        template <class T>
        std::function<bool(T)> leq(const T& rhs) {
            return [&] (T x) {
                return x <= rhs;
            };
        }

        template <class T>
        std::function<bool(T)> geq(const T& rhs) {
            return [&] (T x) {
                return x >= rhs;
            };
        }

        template <class X>
        std::function<bool(X)> filter(std::function<bool(X)> f) {

            // This function seems wack but it has a purpose.
            // consider the call to
            //     m | filter(lt(10));
            // then we need to construct a std::function<bool(X)>
            // that is really just the passed in function...

            // However, this is simply to express intent. We could also simply call
            //     m | lt(10);
            return f;
        }

        template <class X>
        bool even(X x) {
            return x % 2 == 0;
        }

        template <class X>
        std::function<X(X)> times(const X& rhs) {
            return [&] (X x) {
                return x * rhs;
            };
        }

        template <class X>
        std::function<X(X)> divides(const X& rhs) {
            return [&] (X x) {
                return x / rhs;
            };
        }

        // template <class X>
        // std::function<X(X)>
    };

};

template <class T> class Matrix;


namespace ejovo {

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
    const virtual T& operator[](int i) const = 0;
    virtual std::size_t size() const = 0;

    /**========================================================================
     *!                      Virtual Concept Functions
     *========================================================================**/
    virtual Matrix<T> to_matrix()  const = 0;
    virtual Matrix<T> new_matrix(int n) const = 0;


    T& at(int i);         // 1-based indexing with bounds checking
    T& operator()(int i); // 1-based indexing M(1) is the first element
    const T& at(int i) const; // at actually goes ahead and verifies whether or not the bounds are legit
    const T& operator()(int i) const;

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
    template <class U> bool is_same_size(const Grid1D<U>& rhs) const;
    template <class U> bool isnt_same_size(const Grid1D<U>& rhs) const;
    bool is_valid_bound(int i) const; // Check if i is a valid 1-based indexing bound.

    /**========================================================================
     *!                           Assignment Overloading
     *========================================================================**/
    Grid1D& operator=(const Grid1D& rhs);

    bool operator==(const Grid1D& rhs);

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
    Grid1D& loop_i(loop_ind_fn f);
    Grid1D& swap(int ai, int bi);

    const Grid1D& loop(loop_fn_const f) const;
    const Grid1D& loop_i(loop_ind_fn f) const;

    /**========================================================================
     *!                           Printing Functions
     *========================================================================**/
    Grid1D& print();
    // Grid1D& print_lin();

    const Grid1D& print() const;
    // const Grid1D& print_lin() const;

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

    /**========================================================================
     *!                Functional Programming Concrete Return Types
     *========================================================================**/
    Matrix<T> map(unary_op fn) const;
    // virtual template<class U> Matrix<U> map(std::function<U(T)> fn);
    Matrix<T> map_if(unary_op fn, predicate pred) const;
    Matrix<T> filter(predicate pred) const;
    Matrix<T> diff() const; // outputs a row vector of differences
    Matrix<T> midpoints() const; // return the midpoints of adjacent elements
    Matrix<T> abs() const;

    /**========================================================================
     *!                           Power Operations
     *========================================================================**/
    Matrix<T> sqrt() const;
    Matrix<T> cbrt() const;
    Matrix<T> nth_root() const;

    Matrix<T> pow(int k) const;
    Matrix<T> sqrd() const;
    Matrix<T> cubd() const;

    Matrix<T> normalized(int p = 2) const;
    Grid1D& normalize(int p = 2);

    /**========================================================================
     *!                           Repeat Operations
     *========================================================================**/
    Matrix<T> repcol(int n) const;
    Matrix<T> reprow(int n) const;

    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    T dot(const Grid1D& rhs) const;
    // T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    T inner_product(const Grid1D& rhs) const;
    Matrix<T> outer_product(const Grid1D& rhs) const; // must be two vectors...
    // Matrix kronecker_product(const Matrix& rhs) const;
    Matrix<T> hadamard_product(const Grid1D& rhs) const; // element wise multiplication



};


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

    this->print();
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

    auto out = this->new_matrix(c);
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

};
